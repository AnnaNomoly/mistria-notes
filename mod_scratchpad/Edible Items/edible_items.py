import re
import json

ITEM_NAME_PATTERN = r"(?:\/)([^\/]+)(?=\/name$)"

with open("edible_items.json", "w") as out_file:
    edible_items = []
    with open("items.json", "r") as in_file:
        items_other = json.loads(in_file.read())["items"]["other"]
        for category in items_other:
            for item in items_other[category]:
                add_item = False
                if category == "cooked_dishes":
                    add_item = True
                if category == "crops_and_forage":
                    if "seed_" not in item and "sapling_" not in item and "restore" in items_other[category][item]:
                        add_item = True
                if add_item:
                    if "name" in items_other[category][item]:
                        edible_items.append(items_other[category][item]["name"])
                    else:
                        print("NAME missing for item: " + item)

    edible_item_localized_names = {}
    with open("localization.json", "r", encoding="utf-8") as in_file:
        eng = json.loads(in_file.read())["eng"]
        for item_key in edible_items:
            if item_key in eng:
                match = re.search(ITEM_NAME_PATTERN, item_key)
                if match:
                    edible_item_localized_names[eng[item_key]] = match.group(1)
                else:
                    print("No match for item: " + item_key)
                #edible_item_localized_names[eng[item_key]] = item_key
    
    out_file.write(json.dumps(edible_item_localized_names, indent=2))