import json

outfits = []
with open("cosmetics.txt", "w", encoding="utf-8") as out_file:
    with open("fiddle.json", "r", encoding="utf-8") as in_file:
        fiddle = json.loads(in_file.read())

        # Festivals
        """
        festivals = fiddle["festivals"]
        for f in festivals:
            festival = festivals[f]
            if "tiers" in festival:
                tiers = festival["tiers"]
                for i in range(len(tiers)):
                    tier = tiers[i]
                    if "rewards" in tier:
                        rewards = tier["rewards"]
                        for j in range(len(rewards)):
                            reward = rewards[j]
                            if "cosmetic" in reward:
                                outfits.append(reward["cosmetic"])
        """


        # Museum Wings
        """
        museum_wings = fiddle["museum_wings"]
        for m in museum_wings:
            museum_wing = museum_wings[m]
            if "rewards" in museum_wing:
                rewards = museum_wing["rewards"]
                for i in range(len(rewards)):
                    reward = rewards[i]
                    if "entries" in reward:
                        entries = reward["entries"]
                        for j in range(len(entries)):
                            entry = entries[j]
                            if "cosmetic" in entry:
                                outfits.append(entry["cosmetic"])
        """


        # Renown
        """
        renown = fiddle["renown"]
        if "rewards" in renown:
            rewards = renown["rewards"]
            for i in range(len(rewards)):
                if "cosmetic" in rewards[i]:
                     outfits.append(rewards[i]["cosmetic"])
        """


        # Stores
        """
        stores = fiddle["stores"]
        for s in stores:
            store = stores[s]
            if "categories" in store:
                categories = store["categories"]
                for i in range(len(categories)):
                    category = categories[i]
                    if "random_stock" in category:
                        random_stock = category["random_stock"]
                        for j in range(len(random_stock)):
                            stock = random_stock[j]
                            if not isinstance(stock, str):
                                if "cosmetic" in stock:
                                    outfits.append(stock["cosmetic"])
        """


        # Wishing Well
        """
        wishing_well = fiddle["wishing_well"]
        if "common" in wishing_well:
            common = wishing_well["common"]
            if "small_roll" in common:
                small_roll = common["small_roll"]
                for i in range(len(small_roll)):
                    roll = small_roll[i]
                    if "cosmetic" in roll:
                        outfits.append(roll["cosmetic"])
        """

        player_assets = fiddle["player_assets"]
        for asset in player_assets:
            outfits.append(asset)


    outfits.sort()
    for o in outfits:
        out_file.write("| " + o + " |\n")

