import json

with open("Talkative Celine.eng.json", "r", encoding="utf-8") as in_file:
    json_data = json.loads(in_file.read())

for x in json_data:
    x = x.lower().strip()

    if("conversations/mods" in x and "gift_hint_" in x):
        print("EVALUATING: " + x)

        tokens = x.split("/")
        if(len(tokens) < 7):
            print("\tERROR: Not enough tokens in the dialogue key!")
            continue
        if(tokens[0] != "conversations"):
            print("\tERROR: First token wasn't \"conversations\"!")
            continue
        if(tokens[1] != "mods"):
            print("\tERROR: Second token wasn't \"mods\"!")
            continue            
            
        gift_hint_token_count = len(tokens) - 4
        if(gift_hint_token_count % 3 != 0):
            print("\tERROR: Invalid number of tokens in the dialogue line!")
            continue

        i = 3
        while(i < len(tokens) - 1):
            if("gift_hint_" not in tokens[i]):
                print(f"\tERROR: Expected \"gift_hint_\" at token {i}!")
                break

            npc_name = tokens[i + 1]
            item_name = tokens[i + 2]
            print(f"\t SUCCESS: Detected gift preference {item_name} for {npc_name}.")

            i += 3
