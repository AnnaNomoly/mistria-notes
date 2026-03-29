import json
import getpass
from pathlib import Path

base_path = Path("C:\\Code\\mistria-notes\\mod_scratchpad\\Deep Dungeon\\Generate Backplates")
output_path = base_path / "output"
output_dict = {}

def name(p):
    return p.name[0:-4]

for p in output_path.iterdir():
    output_dict["backplate_" + name(p)] = {
        "Location": "images/ui/backplates/" + name(p) + ".png"
    }

with open(base_path / "deep_dungeon_backplates.json", "w") as out:
    out.write(json.dumps(output_dict))