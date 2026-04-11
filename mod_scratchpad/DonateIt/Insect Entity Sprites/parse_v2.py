import os
import json
from PIL import Image

INPUT_FOLDER = "input_sprites"
OUTPUT_FOLDER = "output_sprites"
JSON_FILE = "insect_entities.json"
OUTLINE_COLOR = (128, 53, 232, 255)  # Purple

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

def process_folder(input_folder, output_folder):
    for root, dirs, files in os.walk(input_folder):
        # Compute corresponding output folder
        relative_path = os.path.relpath(root, input_folder)
        current_output_folder = os.path.join(output_folder, relative_path)
        os.makedirs(current_output_folder, exist_ok=True)

        for filename in files:
            if filename.lower().endswith(".png"):  # strongly recommend PNG only
                input_path = os.path.join(root, filename)
                output_path = os.path.join(current_output_folder, filename)

                with Image.open(input_path) as img:
                    result = add_outline(img)
                    result.save(output_path)

                print(f"Processed: {os.path.join(relative_path, filename)}")

def create_json_from_folders(output_folder):
    data = {}

    for root, dirs, files in os.walk(output_folder):
        # Skip the root folder itself, only use subfolders
        for dir_name in dirs:
            key = dir_name  # folder name as key
            data[key] = {
                "Location": "images/entities/insects/" + dir_name,
                "OriginX": 12,
                "OriginY": 14,
                "IsAnimated": True
            }

    # Write to JSON file
    with open(JSON_FILE, "w") as f:
        json.dump(data, f, indent=2)

    print(f"JSON file created: {JSON_FILE}")

if __name__ == "__main__":
    os.makedirs(OUTPUT_FOLDER, exist_ok=True)
    #process_folder(INPUT_FOLDER, OUTPUT_FOLDER)
    create_json_from_folders(OUTPUT_FOLDER)