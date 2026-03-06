import json

preferred_gifts_lines = set()
with open("preferred_gifts.json", "r") as preferred_gifts_file:
    preferred_gifts_dict = json.loads(preferred_gifts_file.read())
    for key in preferred_gifts_dict:
        for line in preferred_gifts_dict[key]:
            preferred_gifts_lines.add(line)

temp_lines = set()
with open("temp.txt", "r") as in_file:
    data = in_file.readlines()

    for line in data:
        if "Conversations" in line or "conversations" in line or "Cutscenes" in line:
            temp_lines.add(line)

missing_lines = set()
for preferred_gift_line in preferred_gifts_lines:
    found = False

    for temp_line in temp_lines:
        if preferred_gift_line in temp_line:
            found = True
            break

    if not found:
        missing_lines.add(preferred_gift_line)


for line in missing_lines:
    print(line)