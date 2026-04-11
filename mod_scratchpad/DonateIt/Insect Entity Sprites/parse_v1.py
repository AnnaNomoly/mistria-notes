import os
from PIL import Image

INPUT_FOLDER = "input_sprites"
OUTPUT_FOLDER = "output_sprites"

OUTLINE_COLOR = (128, 53, 232, 255)  # Purple

os.makedirs(OUTPUT_FOLDER, exist_ok=True)

def is_black(pixel):
    return pixel[0] == 0 and pixel[1] == 0 and pixel[2] == 0 and pixel[3] != 0

def is_background(pixel):
    """Detect pixels that are NOT part of the sprite."""
    # Transparent
    if pixel[3] == 0:
        return True
    
    # Pure white background (common case)
    if pixel[0] == 255 and pixel[1] == 255 and pixel[2] == 255:
        return True

    return False

def add_outline(image):
    image = image.convert("RGBA")
    pixels = image.load()

    width, height = image.size

    new_image = image.copy()
    new_pixels = new_image.load()

    directions = [
        (-1, -1), (-1, 0), (-1, 1),
        (0, -1),          (0, 1),
        (1, -1),  (1, 0), (1, 1)
    ]

    for y in range(height):
        for x in range(width):
            if is_black(pixels[x, y]):
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy

                    if 0 <= nx < width and 0 <= ny < height:
                        neighbor = pixels[nx, ny]

                        # ONLY paint true background pixels
                        if is_background(neighbor):
                            new_pixels[nx, ny] = OUTLINE_COLOR

    return new_image

def process_folder():
    for filename in os.listdir(INPUT_FOLDER):
        if filename.lower().endswith(".png"):  # strongly recommend PNG only
            input_path = os.path.join(INPUT_FOLDER, filename)
            output_path = os.path.join(OUTPUT_FOLDER, filename)

            with Image.open(input_path) as img:
                result = add_outline(img)
                result.save(output_path)

            print(f"Processed: {filename}")

if __name__ == "__main__":
    process_folder()