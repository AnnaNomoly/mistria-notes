import json

json_root = {}

characters = [
    "adeline",
    "celine",
    "dell",
    "dozy",
    "eiland",
    "hayden",
    "hemlock",
    "henrietta",
    "holt",
    "josephine",
    "juniper",
    "landen",
    "luc",
    "maple",
    "march",
    "olric",
    "nora",
    "terithia",
]

expressions = {
    "adeline": [
        "angry_blush",
        "blush",
        "cartoon_embarassed",
        "concerned",
        "embarassed",
        "happy",
        "mad",
        "neutral",
        "sad",
        "sigh",
        "sly",
        "think",
        "ugh",
        "wink"
    ],
    "celine": [
        "angry_blush",
        "annoyed",
        "blush_closed_eyes",
        "blush_special",
        "concerned",
        "embarassed",
        "garden_angry_blush",
        "garden_annoyed",
        "garden_blush_closed_eyes",
        "garden_blush_special",
        "garden_blush",
        "garden_concerned",
        "garden_gloomy",
        "garden_happy",
        "garden_laugh",
        "garden_mad",
        "garden_neutral",
        "garden_sad",
        "garden_sweat",
        "garden_think",
        "garden_ugh",
        "garden_very_happy",
        "garden_wink",
        "gloomy",
        "happy",
        "laugh",
        "mad",
        "neutral",
        "sad",
        "sweat",
        "think",
        "ugh",
        "very_happy",
        "wink"
    ],
    "dell": [
        "embarassed",
        "happy",
        "mad",
        "neutral",
        "sad",
        "think",
        "ugh",
        "wink"
    ],
    "dozy": [
        "happy",
        "mad",
        "neutral_closed",
        "neutral",
        "sad",
        "ugh"
    ],
    "eiland": [
        "embarassed",
        "happy",
        "mad",
        "neutral",
        "sad",
        "think",
        "ugh",
        "wink"
    ],
    "hayden": [
        "annoyed",
        "blush",
        "embarassed",
        "gloomy",
        "happy_arm_down",
        "happy_fist",
        "happy",
        "laugh",
        "mad",
        "neutral_arm_down",
        "neutral_fist",
        "neutral",
        "sad",
        "sweat",
        "think",
        "ugh",
        "wink_arm_down",
        "wink_fist",
        "wink"
    ],
    "hemlock": [
        "embarassed",
        "happy",
        "mad",
        "neutral",
        "sad",
        "think",
        "ugh",
        "wink"
    ],
    "henrietta": [
        "happy",
        "mad",
        "neutral_closed",
        "neutral",
        "sad",
        "ugh"
    ],
    "holt": [
        "embarassed",
        "happy",
        "mad",
        "neutral",
        "sad",
        "think",
        "ugh",
        "wink"
    ],
    "josephine": [
        "embarassed",
        "happy",
        "mad",
        "neutral",
        "sad",
        "think",
        "ugh",
        "wink"
    ],
    "juniper": [
        "angry_blush",
        "angry_brows",
        "annoyed",
        "blush",
        "embarassed",
        "happy",
        "laugh",
        "mad",
        "neutral",
        "sad",
        "sly",
        "think",
        "ugh",
        "unimpressed",
        "wild_laugh",
        "wink"
    ],
    "landen": [
        "embarassed",
        "happy",
        "mad",
        "neutral",
        "sad",
        "think",
        "ugh",
        "wink"
    ],
    "luc": [
        "embarassed",
        "happy",
        "mad",
        "neutral",
        "sad",
        "think",
        "ugh",
        "wink"
    ],
    "maple": [
        "embarassed",
        "happy",
        "mad",
        "neutral",
        "sad",
        "think",
        "ugh",
        "wink"
    ],
    "march": [
        "drunk",
        "embarassed",
        "happy",
        "mad",
        "neutral",
        "sad",
        "sigh",
        "sly",
        "think",
        "tsundere",
        "ugh",
        "unimpressed",
        "wink"
    ],
    "nora": [
        "embarassed",
        "happy",
        "mad",
        "neutral",
        "sad",
        "think",
        "ugh",
        "wink"
    ],
    "olric": [
        "bunny_ears_neutral",
        "embarassed",
        "happy",
        "mad",
        "neutral",
        "sad",
        "think",
        "ugh",
        "wink"
    ],
    "terithia": [
        "embarassed",
        "happy",
        "mad",
        "neutral",
        "sad",
        "think",
        "ugh",
        "wink"
    ]
}

seasons = [
    "autumn"
]

def create_character_json(season, character, expression):
    key = "spr_portrait_" + character + "_" + season + "_" + expression
    value = {
        "Location": "images/spr_portrait_" + character + "_costume.png",
        "OriginX": 0,
        "OriginY": 0,
        "MarginLeft": 0,
        "MarginRight": 296,
        "MarginBottom": 180,
        "MarginTop": 0
    }
    json_root[key] = value

if __name__ == '__main__':
    for s in seasons:
        for c in characters:
            for e in expressions[c]:
                create_character_json(s, c, e)
    
    with open("halloween_outfits.json", "w") as out_file:
        out_file.write(json.dumps(json_root, indent=2))