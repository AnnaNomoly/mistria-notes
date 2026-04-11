#!/usr/bin/env python3
"""
highlight_forage.py

Recursively processes all PNG images in an input directory, adding a 1px
purple outline (silhouette highlight) around each sprite, and saves the
results to an output directory preserving the original directory structure.

Usage:
    python highlight_forage.py <input_dir> <output_dir>

Requirements:
    pip install Pillow scipy numpy
"""

import argparse
import sys
from pathlib import Path

import numpy as np
from PIL import Image
from scipy import ndimage

# --- Configuration -----------------------------------------------------------

# Highlight color (purple, matched to fish outline palette)
HIGHLIGHT_COLOR = (128, 53, 232, 255)

# Highlight thickness in pixels
HIGHLIGHT_THICKNESS = 1

# Image extensions to process
SUPPORTED_EXTENSIONS = {".png", ".PNG"}

# -----------------------------------------------------------------------------


def add_highlight(image: Image.Image, color: tuple[int, int, int, int], thickness: int) -> Image.Image:
    """
    Add a solid-color outline around all opaque pixels in an RGBA image.

    The highlight is drawn *outside* the existing sprite pixels (it does not
    overwrite any pixel that is already opaque in the source image).

    Args:
        image:     Source image (will be converted to RGBA internally).
        color:     Highlight color as an (R, G, B, A) tuple.
        thickness: Highlight width in pixels.

    Returns:
        A new RGBA Image with the highlight applied.
    """
    rgba = image.convert("RGBA")
    arr = np.array(rgba, dtype=np.uint8)

    # Boolean mask of every pixel that has any opacity
    opaque_mask = arr[:, :, 3] > 0

    # Dilate the mask outward by `thickness` pixels
    dilated_mask = ndimage.binary_dilation(opaque_mask, iterations=thickness)

    # The highlight region: dilated area minus the original opaque pixels
    highlight_mask = dilated_mask & ~opaque_mask

    result = arr.copy()
    result[highlight_mask] = color

    return Image.fromarray(result, mode="RGBA")


def process_directory(input_dir: Path, output_dir: Path) -> None:
    """
    Walk *input_dir* recursively, highlight every supported image, and write
    each result to the corresponding path under *output_dir*.

    Args:
        input_dir:  Root directory of source sprites.
        output_dir: Root directory for highlighted output sprites.
    """
    image_paths = [
        p for p in input_dir.rglob("*")
        if p.is_file() and p.suffix in SUPPORTED_EXTENSIONS
    ]

    if not image_paths:
        print(f"No supported images found in '{input_dir}'.")
        return

    print(f"Found {len(image_paths)} image(s) to process.\n")

    success_count = 0
    error_count = 0

    for src_path in image_paths:
        # Mirror the relative path under the output directory
        relative = src_path.relative_to(input_dir)
        dst_path = output_dir / relative

        try:
            with Image.open(src_path) as img:
                highlighted = add_highlight(img, HIGHLIGHT_COLOR, HIGHLIGHT_THICKNESS)

            # Create parent directories as needed
            dst_path.parent.mkdir(parents=True, exist_ok=True)

            # Save as PNG to preserve transparency
            highlighted.save(dst_path, format="PNG")

            print(f"  [OK]  {relative}")
            success_count += 1

        except Exception as exc:  # noqa: BLE001
            print(f"  [ERR] {relative}: {exc}", file=sys.stderr)
            error_count += 1

    print(f"\nDone. {success_count} succeeded, {error_count} failed.")
    print(f"Output written to: {output_dir.resolve()}")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Add a 1px purple highlight outline to every forage sprite in a directory tree."
    )
    parser.add_argument(
        "input_dir",
        type=Path,
        help="Root directory containing the original sprite images.",
    )
    parser.add_argument(
        "output_dir",
        type=Path,
        help="Root directory where highlighted sprites will be saved.",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()

    input_dir: Path = args.input_dir
    output_dir: Path = args.output_dir

    if not input_dir.exists():
        sys.exit(f"Error: input directory '{input_dir}' does not exist.")
    if not input_dir.is_dir():
        sys.exit(f"Error: '{input_dir}' is not a directory.")

    print(f"Input directory  : {input_dir.resolve()}")
    print(f"Output directory : {output_dir.resolve()}")
    print(f"Highlight color  : purple #8035E8")
    print(f"Highlight thickness: {HIGHLIGHT_THICKNESS}px\n")

    process_directory(input_dir, output_dir)


if __name__ == "__main__":
    main()
