"""
combine_timers.py

For every image in `input_images/` (recursively), produces 10 output images
(one per timer image in `timer_images/0.png – 9.png`).

Alignment rules
---------------
Timer image anchor : the two pixels at (4,9) and (5,9) on the *bottom* row of
                     the timer bubble define its centre-bottom.
Crop image anchor  : the highest row that contains at least one fully-black
                     pixel (R=0, G=0, B=0, A=255) is the sprite's top.

The timer is placed so that its bottom row sits in the row *above* the crop
sprite's top row.  Horizontally the timer is centred over the crop sprite;
when the crop sprite width is odd the bubble is shifted 1 px to the left.

Output
------
output_images/<same relative path>/<stem>_timer_<N>.png
"""

import os
import sys
from pathlib import Path

from PIL import Image
import numpy as np

# ---------------------------------------------------------------------------
# Directories
# ---------------------------------------------------------------------------
TIMER_DIR  = Path("timer_images")
INPUT_DIR  = Path("input_images")
OUTPUT_DIR = Path("output_images")

# The two anchor pixels on the timer image that define its bottom-centre.
# (column indices, 0-based)
TIMER_ANCHOR_COLS = (4, 5)   # x = 4 and x = 5
TIMER_ANCHOR_ROW  = 9        # y = 9  (0-based from top)

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def load_rgba(path: Path) -> Image.Image:
    """Load any image and convert to RGBA."""
    return Image.open(path).convert("RGBA")


def find_outline_color(img: Image.Image) -> tuple:
    """
    Return the outline colour of a sprite.

    Most sprites use pure black (0,0,0,255).  Seed sprites use a dark
    colour unique to each seed type.  We detect the outline as the fully-
    opaque pixel with the lowest sum of R+G+B.
    """
    arr = np.array(img)
    opaque = arr[arr[:, :, 3] == 255]
    if len(opaque) == 0:
        raise ValueError("Image has no fully-opaque pixels.")
    rgb_sums = opaque[:, 0].astype(int) + opaque[:, 1].astype(int) + opaque[:, 2].astype(int)
    darkest = opaque[rgb_sums.argmin()]
    return tuple(int(v) for v in darkest)


def find_crop_top(img: Image.Image, outline: tuple) -> int:
    """Return the topmost row index that contains at least one outline-colour pixel."""
    pixels = img.load()
    for y in range(img.height):
        for x in range(img.width):
            if pixels[x, y] == outline:
                return y
    raise ValueError(f"No outline pixel {outline} found in crop image (size {img.size}).")


def find_crop_sprite_bounds(img: Image.Image):
    """
    Return (left, right) column indices of the bounding box of ALL opaque
    pixels.  Using the full opaque extent (maximum sprite width) gives a
    visually correct horizontal centre regardless of where the outline sits.
    """
    pixels = img.load()
    min_x, max_x = img.width, -1
    for y in range(img.height):
        for x in range(img.width):
            if pixels[x, y][3] == 255:   # any fully-opaque pixel
                if x < min_x:
                    min_x = x
                if x > max_x:
                    max_x = x
    if max_x == -1:
        raise ValueError("No opaque pixels found when computing sprite bounds.")
    return min_x, max_x


def compose(crop_img: Image.Image, timer_img: Image.Image) -> Image.Image:
    """
    Place `timer_img` above `crop_img` and return the combined image.

    The combined canvas is the same size as the crop image.  The timer is
    composited in place (alpha-blended) at the computed position.
    """
    outline           = find_outline_color(crop_img)
    crop_top          = find_crop_top(crop_img, outline)
    crop_left, crop_right = find_crop_sprite_bounds(crop_img)

    # Horizontal centre of the crop sprite: midpoint of left and right extents.
    # Floor division gives left-bias (justify left 1px) when width is even-spanned odd.
    crop_centre_x = (crop_left + crop_right) // 2

    # Timer anchor: the midpoint of columns 4 and 5 is between them.
    # For a 1-px left bias when width is odd we use the left anchor pixel (4).
    # The spec says "align centred when possible, justify left 1px if
    # necessary", which maps to: timer_anchor_x = 4 if odd, 4 or 5 if even.
    # Simplest consistent rule: timer_anchor_x = (4 + 5) // 2 = 4 always,
    # giving left-bias automatically.
    timer_anchor_x = (TIMER_ANCHOR_COLS[0] + TIMER_ANCHOR_COLS[1]) // 2  # = 4

    # Where does column `timer_anchor_x` land on the canvas?
    # We want it at `crop_centre_x`.
    timer_paste_x = crop_centre_x - timer_anchor_x

    # Vertical: timer bottom row (TIMER_ANCHOR_ROW) sits one row above crop top.
    target_bottom_y = crop_top - 1          # row in the canvas for timer's row 9
    timer_paste_y   = target_bottom_y - TIMER_ANCHOR_ROW

    # If the timer would be clipped at the top of the canvas, shift it down
    # until it fits, allowing it to overlap the crop sprite.
    if timer_paste_y < 0:
        timer_paste_y = 0

    # Create output canvas (same size as crop, transparent background)
    canvas = Image.new("RGBA", crop_img.size, (0, 0, 0, 0))

    # Paste crop first, then timer on top
    canvas.paste(crop_img, (0, 0), crop_img)
    canvas.paste(timer_img, (timer_paste_x, timer_paste_y), timer_img)

    return canvas


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    # -- Load timer images ---------------------------------------------------
    timer_images = {}
    for n in range(10):
        p = TIMER_DIR / f"{n}.png"
        if not p.exists():
            sys.exit(f"ERROR: Timer image not found: {p}")
        timer_images[n] = load_rgba(p)
    print(f"Loaded {len(timer_images)} timer images from '{TIMER_DIR}'.")

    # -- Walk input directory ------------------------------------------------
    input_paths = sorted(INPUT_DIR.rglob("*.png"))
    if not input_paths:
        sys.exit(f"ERROR: No .png files found under '{INPUT_DIR}'.")
    print(f"Found {len(input_paths)} input image(s).")

    processed = 0
    for crop_path in input_paths:
        rel_path = crop_path.relative_to(INPUT_DIR)   # e.g. subdir/wheat.png
        stem     = crop_path.stem                      # e.g. wheat

        try:
            crop_img = load_rgba(crop_path)
        except Exception as e:
            print(f"  SKIP {crop_path}: {e}")
            continue

        for n, timer_img in timer_images.items():
            out_filename = f"{stem}_timer_{n}.png"
            out_path     = OUTPUT_DIR / rel_path.parent / out_filename
            out_path.parent.mkdir(parents=True, exist_ok=True)

            try:
                result = compose(crop_img, timer_img)
                result.save(out_path)
            except Exception as e:
                print(f"  ERROR composing {crop_path} + timer {n}: {e}")
                continue

        processed += 1
        print(f"  [{processed}/{len(input_paths)}] {rel_path}  →  10 outputs")

    print(f"\nDone. {processed} crop image(s) × 10 timers = {processed * 10} output files.")
    print(f"Outputs are in '{OUTPUT_DIR}'.")


if __name__ == "__main__":
    main()