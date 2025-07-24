import re
import json

NOTICE_LOCAL = "[Ari], \\n\\nA week from now is our town's Winter Holiday celebration. Your secret gift recipient this year is ... \\n\\n\\n<name>! \\n\\nI've included some things to help get you in the holiday spirit, along with a small stipend from the town's annual holiday fund. Be sure to surprise them with something nice!"
NOTICE_SUBJECT = "Secret Gift Recipient"

REMINDER_LOCAL = "[Ari], \\n\\nJust a reminder that our tomorrow is the Winter Holiday celebration. \\n\\nDon't forget to get a gift for your secret recipient: <name>!"
REMINDER_SUBJECT = "Reminder: Secret Gift Recipient"

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

output = {}
for c in CHARACTERS:
    name = c[0].upper() + c[1:]

    # print("\"letters/secret_santa_notice_" + c + "/local\": \"" + NOTICE_LOCAL.replace("<name>", name) + "\",\n")
    # print("\"letters/secret_santa_notice_" + c + "/subject_line\": \"" + NOTICE_SUBJECT.replace("<name>", name) + "\",\n")

    # print("\"letters/secret_santa_reminder_" + c + "/local\": \"" + REMINDER_LOCAL.replace("<name>", name) + "\",\n")
    # print("\"letters/secret_santa_reminder_" + c + "/subject_line\": \"" + REMINDER_SUBJECT.replace("<name>", name) + "\",\n")

    # "Conversations/Bank/Adeline/Secret Santa/": "So you're my secret gift giver this year! Thank you, [Ari]... this means a lot.",
    print("\"Conversations/Bank/" + name + "/Secret Santa\": \"So you're my secret gift giver this year! Thank you, [Ari]... this means a lot.\"")