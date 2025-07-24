import re
import json

CHARACTERS = {
    "adeline": True,
    "balor": True,
    "celine": True,
    "darcy": False,
    "dell": True,
    "dozy": True,
    "eiland": True,
    "elsie": False,
    "errol": False,
    "hayden": True,
    "hemlock": False,
    "henrietta": True,
    "holt": False,
    "josephine": False,
    "juniper": True,
    "landen": False,
    "luc": True,
    "louis": False,
    "maple": True,
    "march": True,
    "merri": False,
    "olric": False,
    "nora": False,
    "reina": True,
    "ryis": True,
    "terithia": False,
    "valen": True,
    "vera": False,
}

GIFTS = [
    "berry_bowl",
    "beet_soup",
    "fried_rice",
    "vegetable_pot_pie",
    "floral_tea",
    "tulip_cake",
    "sushi_platter",
    "lobster_roll",
    "summer_salad",
    "vegetable_quiche"
]

character_gift_preferences = {}
with open("letters.json", "w") as letters_file:
    with open("secret_santa_letters.json", "r", encoding="utf-8") as secret_santa_letters_file:
        secret_santa_letters = json.loads(secret_santa_letters_file.read())
    
    letters = {}
    for c in CHARACTERS:
        # DEC 21 Letter
        letters["secret_santa_notice_" + c] = {
            "default": False,
            "npc": "adeline",
            "subject_line": "letters/secret_santa_notice_" + c + "/subject_line",
            "local": "letters/secret_santa_notice_" + c + "/local",
            "items": [{
                "big_cookie": 1,
                "hot_cocoa": 1,
                "purse": 500
            }]
        }

        # DEC 27 Letter
        letters["secret_santa_reminder_" + c] = {
            "default": False,
            "npc": "adeline",
            "subject_line": "letters/secret_santa_reminder_" + c + "/subject_line",
            "local": "letters/secret_santa_reminder_" + c + "/local"
        }

        # Gift Letters
        for g in GIFTS:
            letter_name = "secret_santa_" + c + "_" + g

            if(CHARACTERS[c]):
                subject_line = "letters/secret_santa_" + c + "_gift/subject_line"
                local = "letters/secret_santa_" + c + "_gift/local"
            else:
                subject_line = "letters/secret_santa_generic_gift/subject_line"
                local = "letters/secret_santa_generic_gift/local"

            letter = {
                "default": False,
                "npc": c,
                "subject_line": subject_line,
                "local": local,
                "items": [{
                    "item_name": g,
                    "count": 3
                }]
            }

            letters[letter_name] = letter
    
    letters_file.write(json.dumps(letters, indent=2))
