import json

with open("all_items.json", "r") as f:
    items = json.load(f)

item_name_to_sprite_name_dict = {}
with open("mappings.txt", "r") as mappings:
    for line in mappings:
        line_data = line.split("->")

        item_name = line_data[0].strip()
        sprite_name = line_data[1].strip()
        sprite_name = sprite_name[sprite_name.rfind("\\")+1:-6]

        item_name_to_sprite_name_dict[item_name] = sprite_name

def check_items(obj, lookup_dict):
    if isinstance(obj, dict):
        for key, value in obj.items():
            # key is the item name you're interested in
            if key in lookup_dict and isinstance(value, dict):
                icon = value.get("icon_sprite")
                expected_icon = lookup_dict[key]
                
                if icon != expected_icon:
                    print(f"Mismatch for '{key}': JSON='{icon}' vs expected='{expected_icon}'")
                else:
                    print(f"OK: {key}")
            
            # Recurse into the value
            check_items(value, lookup_dict)

    elif isinstance(obj, list):
        for item in obj:
            check_items(item, lookup_dict)

check_items(items, item_name_to_sprite_name_dict)