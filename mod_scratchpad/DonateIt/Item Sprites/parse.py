import os
import glob
import json
from PIL import Image


# Placeholder for the folder containing images
IMAGE_FOLDER = "C:\\Code\\mistria-notes\\mod_scratchpad\\DonateIt\\Item_UI_Sprites"

# Load items from the text file
with open("all_donatable_items.txt", "r") as f:
    items = [line.strip() for line in f if line.strip()]

# Load all image paths
image_paths = glob.glob(os.path.join(IMAGE_FOLDER, "spr_ui_item*_0.png"))

# Create a mapping of item names to their image paths
item_to_image = {}

for item in items:
    item_words = item.split('_')
    best_match = None
    best_score = 0

    for img_path in image_paths:
        img_name = os.path.basename(img_path)
        # Remove prefix and suffix
        core_name = img_name[len("spr_ui_item_"):-len("_0.png")]
        img_words = core_name.split('_')

        # Count how many words from the item match in order inside the image name
        score = 0
        for i in range(len(img_words) - len(item_words) + 1):
            if img_words[i:i+len(item_words)] == item_words and "bagseed" not in core_name and "crop_sign" not in core_name and "faux" not in core_name and "decor" not in core_name and "furniture" not in core_name and "cosmetic" not in core_name:
                score = len(item_words)
                break
        
        if score > best_score:
            best_score = score
            best_match = img_path

    item_to_image[item] = best_match


# Manually fix incorrect mappings
item_to_image["bell_berry"] = IMAGE_FOLDER + "\\" + "spr_ui_item_bush_bell_berry_0.png"
item_to_image["crab"] = IMAGE_FOLDER + "\\" + "spr_ui_item_fish_small_crab_0.png"
item_to_image["earthshroom"] = IMAGE_FOLDER + "\\" + "spr_ui_item_earthshroom_0.png"
item_to_image["firefly"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_firefly_0.png"
item_to_image["fog_orchid"] = IMAGE_FOLDER + "\\" + "spr_ui_item_fogorchid_0.png"
item_to_image["dandelion"] = IMAGE_FOLDER + "\\" + "spr_ui_item_dandelionflower_0.png"
item_to_image["moon_fruit"] = IMAGE_FOLDER + "\\" + "spr_ui_item_moon_fruit_0.png"
item_to_image["morel_mushroom"] = IMAGE_FOLDER + "\\" + "spr_ui_item_morelmushroom_0.png"
item_to_image["potato"] = IMAGE_FOLDER + "\\" + "spr_ui_item_potato_0.png"
item_to_image["snow_peas"] = IMAGE_FOLDER + "\\" + "spr_ui_item_snow_peas_0.png"
item_to_image["sweet_potato"] = IMAGE_FOLDER + "\\" + "spr_ui_item_sweet_potato_0.png"
item_to_image["sweetroot"] = IMAGE_FOLDER + "\\" + "spr_ui_item_sweetroot_0.png"
item_to_image["thyme"] = IMAGE_FOLDER + "\\" + "spr_ui_item_thyme_0.png"
item_to_image["turnip"] = IMAGE_FOLDER + "\\" + "spr_ui_item_turnip_0.png"
item_to_image["watermelon"] = IMAGE_FOLDER + "\\" + "spr_ui_item_watermelon_0.png"
item_to_image["wild_leek"] = IMAGE_FOLDER + "\\" + "spr_ui_item_springonion_0.png"

# Manually fix duplicate mappings
item_to_image["clay"] = IMAGE_FOLDER + "\\" + "spr_ui_item_clay_0.png"
item_to_image["koi"] = IMAGE_FOLDER + "\\" + "spr_ui_item_fish_medium_koi_0.png"
item_to_image["minnow"] = IMAGE_FOLDER + "\\" + "spr_ui_item_fish_small_minnow_0.png"
item_to_image["shrimp"] = IMAGE_FOLDER + "\\" + "spr_ui_item_fish_small_shrimp_0.png"
item_to_image["loach"] = IMAGE_FOLDER + "\\" + "spr_ui_item_fish_small_loach_0.png"
item_to_image["tilapia"] = IMAGE_FOLDER + "\\" + "spr_ui_item_fish_small_tilapia_0.png"
item_to_image["trout"] = IMAGE_FOLDER + "\\" + "spr_ui_item_fish_medium_trout_0.png"
item_to_image["worm"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_worm_0.png"

# Manually fix unmapped values
item_to_image["bluegill"] = IMAGE_FOLDER + "\\" + "spr_ui_item_fish_small_blue_gill_0.png"
item_to_image["breath_of_fire"] = IMAGE_FOLDER + "\\" + "spr_ui_item_breath_of_flame_0.png"
item_to_image["cicada_nymph"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_cicadanymph_0.png"
item_to_image["crystal_caterpillar"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_crystalcaterpillar_0.png"
item_to_image["fairy_bee"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_fairybee_0.png"
item_to_image["flower_crown_beetle"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_flowercrownbeetle_0.png"
item_to_image["fuzzy_moth"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_fuzzymoth_0.png"
item_to_image["hermit_crab"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_hermitcrab_0.png"
item_to_image["hummingbird_hawk_moth"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_hummingbirdhawkmoth_0.png"
item_to_image["jewel_beetle"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_jewelbeetle_0.png"
item_to_image["lava_chestnuts"] = IMAGE_FOLDER + "\\" + "spr_ui_item_lava_chestnut_0.png"
item_to_image["lightning_dragonfly"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_lightningdragonfly_0.png"
item_to_image["luna_moth"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_lunamoth_0.png"
item_to_image["magma_beetle"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_magmabeetle_0.png"
item_to_image["monarch_butterfly"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_monarchbutterfly_0.png"
item_to_image["orchid_mantis"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_orchidmantis_0.png"
item_to_image["praying_mantis"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_prayingmantis_0.png"
item_to_image["red_toadstool"] = IMAGE_FOLDER + "\\" + "spr_ui_item_redtoadstool_0.png"
item_to_image["relic_crab"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_reliccrab_0.png"
item_to_image["roly_poly"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_pillbug_0.png"
item_to_image["rose_hip"] = IMAGE_FOLDER + "\\" + "spr_ui_item_bush_rosehip_0.png"
item_to_image["seriously_square_stone"] = IMAGE_FOLDER + "\\" + "spr_ui_item_seriously_square_rock_0.png"
item_to_image["snowball_beetle"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_snowballbeetle_0.png"
item_to_image["speedy_snail"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_speedysnail_0.png"
item_to_image["strobe_firefly"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_strobefirefly_0.png"
item_to_image["tiger_swallowtail_butterfly"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_tigerswallowtailbutterfly_0.png"
item_to_image["vintage_cow_bell"] = IMAGE_FOLDER + "\\" + "spr_ui_item_vintage_bell_0.png"
item_to_image["walking_leaf"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_walkingleaf_0.png"
item_to_image["walking_stick"] = IMAGE_FOLDER + "\\" + "spr_ui_item_insect_walkingstick_0.png"


# Print the mapping
for item, img in item_to_image.items():
    print(f"{item} -> {img}")


# ==================================================================================================================================================


# Configurable light purple color (R, G, B)
LIGHT_PURPLE = (128, 53, 232) #(200, 160, 255)

# Output directory
output_dir = "C:\\Code\\mistria-notes\\mod_scratchpad\\DonateIt\\output_images"
os.makedirs(output_dir, exist_ok=True)

for sprite_name, base_path in item_to_image.items():
    # Construct outline image path by inserting "_outline" before "_0.png"
    if not base_path.endswith("_0.png"):
        raise ValueError(f"Base image path does not end with '_0.png': {base_path}")
    outline_path = base_path.replace("_0.png", "_outline_0.png")

    # Load images
    base_img = Image.open(base_path).convert("RGBA")
    outline_img = Image.open(outline_path).convert("RGBA")

    # Modify outline: replace white pixels with light purple
    outline_pixels = outline_img.load()
    for y in range(outline_img.height):
        for x in range(outline_img.width):
            r, g, b, a = outline_pixels[x, y]
            # Check if pixel is non-transparent white
            if a > 0 and r == 255 and g == 255 and b == 255:
                outline_pixels[x, y] = (*LIGHT_PURPLE, a)

    # Composite images: outline at bottom, base on top
    combined_img = Image.alpha_composite(outline_img, base_img)

    # Save output: replace "_outline" with "_donatable" in filename
    base_filename = os.path.basename(outline_path)
    output_filename = base_filename.replace("_outline", "_donatable")
    output_path = os.path.join(output_dir, output_filename)
    combined_img.save(output_path)

    print(f"Saved combined image: {output_path}")


# ==================================================================================================================================================


output_dir = "C:\\Code\\mistria-notes\\mod_scratchpad\\DonateIt\\output_images"
image_prefix = "images"  # The prefix to use in the Location/OutlineLocation fields
sprite_data = {}

for filename in os.listdir(output_dir):
    if not filename.lower().endswith(".png"):
        continue  # skip non-PNG files

    # Remove _0.png suffix for the dictionary key
    if filename.endswith("_0.png"):
        key_name = filename[:-6]  # remove last 6 chars "_0.png"
    else:
        key_name = os.path.splitext(filename)[0]

    # Relative path for Location and OutlineLocation
    relative_path = os.path.join(image_prefix, filename).replace("\\", "/")

    # Add entry to dictionary
    sprite_data[key_name] = {
        "Location": relative_path,
        "OutlineLocation": relative_path,
        "OriginX": 9,
        "OriginY": 9,
        "MarginLeft": 0,
        "MarginRight": 18,
        "MarginBottom": 18,
        "MarginTop": 0,
        "IsAnimated": False,
        "IsUiItem": True
    }

# Optional: save to JSON file
json_output_path = os.path.join(output_dir, "sprite_metadata.json")
with open(json_output_path, "w") as f:
    json.dump(sprite_data, f, indent=2)
