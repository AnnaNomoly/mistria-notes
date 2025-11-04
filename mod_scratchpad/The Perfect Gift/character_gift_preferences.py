import re
import json

CURRENT_GAME_VERSION = "v0.14.4"

characters = [
    "adeline",
    "balor",
    "caldarus",
    "celine",
    "darcy",
    "dell",
    "dozy",
    "eiland",
    "elsie",
    "errol",
    "hayden",
    "hemlock",
    "henrietta",
    "holt",
    "josephine",
    "juniper",
    "landen",
    "louis",
    "luc",
    "maple",
    "march",
    "merri",
    "nora",
    "olric",
    #"priestess",
    "reina",
    "ryis",
    #"stillwell",
    "taliferro",
    "terithia",
    "valen",
    "vera",
    "wheedle",
    #"zorel"
]

character_gift_preferences = {}
with open("preferred_gifts.json", "w") as preferred_gifts_file:
    with open(CURRENT_GAME_VERSION + "/localization.json", "r", encoding="utf-8") as localization_file:
        eng = json.loads(localization_file.read())["eng"]
        for key in eng:
            if "gift_lines" not in key: # Ignore all dialogue that only shows up after being gifted the item
                results = re.findall(r"=(\w+(?: \w+)*)=", eng[key])
                if results:
                    for c in characters:
                        if c in key.lower():
                            if c not in character_gift_preferences:
                                character_gift_preferences[c] = {}
                            if key not in character_gift_preferences[c]:
                                character_gift_preferences[c][key] = []
                            for r in results:
                                character_gift_preferences[c][key].append(r)

    preferred_gifts_file.write(json.dumps(character_gift_preferences))