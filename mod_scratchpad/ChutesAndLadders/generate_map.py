with open("ladder_spawns.txt", "r") as in_file:
    data = in_file.readlines()
    for line in data:
        line_data = line.split(":")
        position_data = line_data[1].split(",")
        room_name = line_data[0].strip().lstrip()
        x_coord = position_data[0].strip().lstrip()
        y_coord = position_data[1].strip().lstrip()
        
        print("{ \"" + room_name + "\" , { " + x_coord + ", " + y_coord + " }},")

