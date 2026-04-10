import json

output = {}
with open("sprite_metadata.json", "r") as in_file:
    data = json.load(in_file)

    for key in data:
        for i in range(10):
            name = key + "_timer_" + str(i)
            obj = {
                "Location": "/images/" + key + "/" + key + "_0_timer_" + str(i) + ".png",
                "OriginX": data[key]["OriginX"],
                "OriginY": data[key]["OriginY"],
                "MarginLeft": data[key]["MarginLeft"],
                "MarginRight": data[key]["MarginRight"],
                "MarginBottom": data[key]["MarginBottom"],
                "MarginTop": data[key]["MarginTop"],
            }
            output[name] = obj

with open("output.json", "w") as out_file:
    json.dump(output, out_file)
