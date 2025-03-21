with open("mistria_recipe_list.md", "w") as out_file:
    with open("mistria_recipe_list.txt", "r") as in_file:
        lines = in_file.readlines()
        for line in lines:
            line = line.strip()
            line_split = line.split(",")
            out_file.write("| " + line_split[0] + " |\n")