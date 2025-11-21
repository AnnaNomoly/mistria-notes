import json

count = 1
in_filename = "Deep Woods Bounding Boxes.txt"
out_filename = in_filename[0:-3] + "cpp"
with open(in_filename, "r") as in_file:
    with open(out_filename, "w") as out_file:
        lines = in_file.readlines()
        for line in lines:
            if "Bounding Box" in line:
                out_file.write("{\n")
                out_file.write("\t" + "// BBox " + str(count) + "\n")
                count += 1
            elif "," in line:
                line = line.strip()
                points = line.split(",")
                out_file.write("\t{")
                out_file.write(points[0].strip() + " / 8, ")
                out_file.write(points[1].strip() + " / 8},\n")
            else:
                out_file.write("},\n")

