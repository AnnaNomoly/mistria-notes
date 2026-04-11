import json

output = {}
with open("crop_timers.json", "r") as in_file:
    data = json.load(in_file)

    for key in data:
        if "timer_0" in key:
            name = key[0:key.rfind("_timer")]
            output[key + "_red"] = {
                "Location": "images/" + name + "/" + name + "_0_timer_0_red.png",
                "OriginX": data[key]["OriginX"],
                "OriginY": data[key]["OriginY"],
                "MarginLeft": data[key]["MarginLeft"],
                "MarginRight": data[key]["MarginRight"],
                "MarginBottom": data[key]["MarginBottom"],
                "MarginTop": data[key]["MarginTop"],
            }

        output[key] = data[key]

with open("output.json", "w") as out_file:
    json.dump(output, out_file)
