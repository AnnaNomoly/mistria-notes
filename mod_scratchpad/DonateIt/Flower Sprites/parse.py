import os
from PIL import Image

INPUT_FOLDER = "input_sprites"
OUTPUT_FOLDER = "output_sprites"

OUTLINE_COLOR = (128, 53, 232, 255)  # Purple

def is_background(pixel, bg_color):
    return pixel == bg_color

def add_outline(image):
    image = image.convert("RGBA")
    pixels = image.load()

    width, height = image.size
    bg_color = pixels[0, 0]  # sample top-left

    new_image = image.copy()
    new_pixels = new_image.load()

    directions = [
        (-1, -1), (-1, 0), (-1, 1),
        (0, -1),          (0, 1),
        (1, -1),  (1, 0), (1, 1)
    ]

    for y in range(height):
        for x in range(width):
            if is_background(pixels[x, y], bg_color):
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy

                    if 0 <= nx < width and 0 <= ny < height:
                        if not is_background(pixels[nx, ny], bg_color):
                            new_pixels[x, y] = OUTLINE_COLOR
                            break

    return new_image

def process_folder():
    for root, dirs, files in os.walk(INPUT_FOLDER):
        for filename in files:
            if filename.lower().endswith(".png"):
                input_path = os.path.join(root, filename)

                # Compute relative path
                relative_path = os.path.relpath(input_path, INPUT_FOLDER)
                output_path = os.path.join(OUTPUT_FOLDER, relative_path)

                # Ensure output subdirectory exists
                os.makedirs(os.path.dirname(output_path), exist_ok=True)

                with Image.open(input_path) as img:
                    result = add_outline(img)
                    result.save(output_path)

                # Write to JSON

                print(f"Processed: {relative_path}")

if __name__ == "__main__":
    process_folder()