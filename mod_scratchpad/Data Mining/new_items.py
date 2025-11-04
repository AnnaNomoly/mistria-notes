old_version = "0.13.4"
new_version = "0.14.0"

file_prefixes_and_item_name_indices = [("items", 2), ("cosmetics", 1), ("furniture", 1), ("cooking_recipes", 1)]

def diff_files(file_prefix_and_item_name_index):
    old_items = []
    with open("./" + old_version + "/" + file_prefix_and_item_name_index[0] + ".md", "r") as in_file:
        lines = in_file.readlines()
        for line in lines:
            line_parts = line.split("|")
            old_items.append(line_parts[file_prefix_and_item_name_index[1]].strip())

    new_items = []
    with open("./" + new_version + "/" + file_prefix_and_item_name_index[0] + ".md", "r") as in_file:
        lines = in_file.readlines()
        for line in lines:
            line_parts = line.split("|")
            new_items.append(line_parts[file_prefix_and_item_name_index[1]].strip())

    with open("new_" + file_prefix_and_item_name_index[0] + ".txt", "w") as out_file:
        for item in new_items:
            if item not in old_items:
                out_file.write(item + "\n")

for file_prefix_and_item_name_index in file_prefixes_and_item_name_indices:
    diff_files(file_prefix_and_item_name_index)