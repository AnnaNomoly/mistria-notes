import math
import json


ignored_item_categories = ["furniture"]
items_to_reduce_buy_price = ["sugar", "flour", "rice", "rock_salt", "oil", "soy_sauce", "curry_powder", "honey"]

def calculate_modified_item_prices(items, out_file_name, profit_margin):
    modified_item_prices = {}

    with open(out_file_name, "w") as out_file:
        for key in items:
            if key not in ignored_item_categories:
                if key not in modified_item_prices:
                    modified_item_prices[key] = {}

                # print(key)
                for sub_key in items[key]:
                    if sub_key not in ignored_item_categories:
                        if sub_key not in modified_item_prices[key]:
                            modified_item_prices[key][sub_key] = {}
                            # print("\t" + sub_key)
                            
                            for item_name in items[key][sub_key]:
                                original_bin_value = None
                                original_store_value = None
                                if "value" in items[key][sub_key][item_name]:
                                    if "bin" in items[key][sub_key][item_name]["value"]:
                                        original_bin_value = items[key][sub_key][item_name]["value"]["bin"]
                                    if "store" in items[key][sub_key][item_name]["value"]:
                                        original_store_value = items[key][sub_key][item_name]["value"]["store"]

                                # Haved values
                                modified_values = {"value": {}}

                                modified_bin_value = None
                                if original_bin_value != None and original_bin_value > 1:
                                    modified_bin_value = math.floor(float(original_bin_value) * profit_margin)
                                    if modified_bin_value == 0:
                                        modified_bin_value = 1

                                modified_store_value = None
                                if original_store_value != None and original_store_value > 1:
                                    modified_store_value = math.floor(float(original_store_value) * profit_margin)
                                    if modified_store_value == 0:
                                        modified_store_value = 1

                                if modified_bin_value != None:
                                    modified_values["value"]["bin"] = modified_bin_value
                                if ("seed_" in item_name or item_name in items_to_reduce_buy_price) and modified_store_value != None:
                                    modified_values["value"]["store"] = modified_store_value
                                if "bin" in modified_values["value"] or "store" in modified_values["value"]:
                                    modified_item_prices[key][sub_key][item_name] = modified_values    
        data = {"items": modified_item_prices}
        out_file.write(json.dumps(data, indent=2))


with open("items.json", "r", encoding="utf-8") as in_file:
    items = json.loads(in_file.read())["items"]
    calculate_modified_item_prices(items, "profit_margin_seventy_five_percent.json", 0.75)
    calculate_modified_item_prices(items, "profit_margin_fifty_percent.json", 0.5)
    calculate_modified_item_prices(items, "profit_margin_twenty_five_percent.json", 0.25)




# deviled_eggs: 160 (80)
    # egg: 20 (10)
    # mayonnaise: 90 (45)
    # horseradish: 30 (15)


# spicy_cheddar_biscuit: 510 (255)
    # chili_pepper: 75 (37)
    # cheese: 90 (45)
    # butter: 90 (45)
    # flour: 175 (87)

# 510-430=80 (1.186046511627907)
# 255-214=41 (1.191588785046729)

# seed_sugar_cane: 40 (20)


# Grown pepper: 40 (20)
# Milled Cheese: 80 (40)
# Milled Butter: 80 (40)
# Bought flour: 200 (100)
#               400 (200)
