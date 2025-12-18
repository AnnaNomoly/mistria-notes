import getpass
from PIL import Image
from pathlib import Path
from itertools import combinations, product

base_path = Path("C:\\Users\\" + getpass.getuser() + "\\Pictures\\Deep Dungeon\\Custom Dungeon Backplate")
group_one_path = base_path / "floor enchantments" / "group 1"
group_two_path = base_path / "floor enchantments" / "group 2"
group_three_path = base_path / "floor enchantments" / "group 3"
offering_path = base_path / "offerings"
output_path = base_path / "output"
template_path = base_path / "template.png"

p1 = (5, 28)
p2 = (20, 28)
p3 = (35, 28)
p4 = (51, 28)

group1 = list(group_one_path.iterdir())
group2 = list(group_two_path.iterdir())
group3 = list(group_three_path.iterdir())
group4 = list(offering_path.iterdir())
groups = [
    (group1, p1),
    (group2, p2),
    (group3, p3),
    (group4, p4),
]

template = Image.open(template_path).convert("RGBA")

def get_filename(paths):
    filename = ""
    for i in range(len(paths)):
        if i < len(paths) - 1:
            filename += paths[i].name[0:-4] + "_"
        else:
            filename += paths[i].name[0:-4]
    return filename + ".png"

# Iterate over all non-empty subsets of groups
for r in range(1, len(groups) + 1):
    for subset in combinations(groups, r):
        # For each group in subset, pick exactly one image
        group_images_lists = [grp for grp, _ in subset]
        for picks in product(*group_images_lists):
            out_img = template.copy()
            names = []

            for pick_path, (_, pos) in zip(picks, subset):
                with Image.open(pick_path).convert("RGBA") as img:
                    out_img.paste(img, pos, img)
                    names.append(pick_path)

            out_img.save(output_path / get_filename(names))




# template_image = Image.open(template_path).convert("RGBA")

# for g1 in group_one_path.iterdir():
#     with Image.open(g1).convert("RGBA") as i1:
#         o1 = template_image.copy()
#         o1.paste(i1, p1, i1)
#         o1.save(output_path / get_filename([g1]))

#         for g2 in group_two_path.iterdir():
#             with Image.open(g2).convert("RGBA") as i2:
#                 o2 = o1.copy()
#                 o2.paste(i2, p2, i2)
#                 o2.save(output_path / get_filename([g1, g2]))

#                 for g3 in group_three_path.iterdir():
#                     with Image.open(g3).convert("RGBA") as i3:
#                         o3 = o2.copy()
#                         o3.paste(i3, p3, i3)
#                         o3.save(output_path / get_filename([g1, g2, g3]))

#                         for g4 in offering_path.iterdir():
#                             with Image.open(g4).convert("RGBA") as i4:
#                                 o4 = o3.copy()
#                                 o4.paste(i4, p4, i4)
#                                 o4.save(output_path / get_filename([g1, g2, g3, g4]))
