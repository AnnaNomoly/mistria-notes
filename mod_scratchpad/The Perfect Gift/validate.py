import json

CURRENT_GAME_VERSION = "v0.14.4"

ADELINE = "adeline"
BALOR = "balor"
CALDARUS = "caldarus"
CELINE = "celine"
DARCY = "darcy"
DELL = "dell"
DOZY = "dozy"
EILAND = "eiland"
ELSIE = "elsie"
ERROL = "errol"
HAYDEN = "hayden"
HEMLOCK = "hemlock"
HENRIETTA = "henrietta"
HOLT = "holt"
JOSEPHINE = "josephine"
JUNIPER = "juniper"
LANDEN = "landen"
LOUIS = "louis"
LUC = "luc"
MAPLE = "maple"
MARCH = "march"
MERRI = "merri"
NORA = "nora"
OLRIC = "olric"
#PRIESTESS = "priestess"
REINA = "reina"
RYIS = "ryis"
#STILLWELL = "stillwell"
TALIFERRO = "taliferro"
TERITHIA = "terithia"
VALEN = "valen"
VERA = "vera"
WHEEDLE = "wheedle"
#ZOREL = "zorel"

GIFT_DIALOG_DICT = { # As of 0.14.4
	# Adeline
	"Cutscenes/Heart Events/Adeline/adeline_eight_hearts/adeline_eight_hearts/3":[ ADELINE, "lemon_pie" ],
	"Conversations/Bank/Adeline/Relationship Lines/Relationship/post_8h_lines_romantic/adeline_post_8h_romantic_7/init":[ ADELINE, "middlemist" ],
	"Conversations/Bank/Adeline/Relationship Lines/Relationship/post_8h_lines_best_friend/adeline_post_8h_best_friend_10/init":[ ADELINE, "coffee" ],
	"Conversations/Bank/Adeline/Banked Lines/inn_work/inn_work/init":[ ADELINE, "wildberry_scone" ],
	"Conversations/Bank/Adeline/Banked Lines/loves_paperwork/loves_paperwork/init":[ ADELINE, "paper" ],
	"Conversations/Bank/Adeline/Banked Lines/wine_cellar/wine_cellar/1":[ ADELINE, "red_wine" ],
	"Conversations/Bank/Adeline/Banked Lines/wine_cellar/wine_cellar/init":[ ADELINE, "coffee", "white_wine" ],
	"Conversations/Bank/Adeline/Gift Lines/gift_lines/lemon_pie/init":[ ADELINE, "lemon_pie" ], # Gift Line
	"Conversations/Bank/Adeline/Gift Lines/gift_lines/middlemist/init":[ ADELINE, "middlemist" ], # Gift Line
	"Conversations/Bank/Adeline/Gift Lines/gift_lines/paper/init":[ ADELINE, "paper" ], # Gift Line
	"Conversations/Bank/Adeline/Gift Lines/gift_lines/perfect_pink_diamond/init":[ ADELINE, "perfect_pink_diamond" ], # Gift Line
	"Conversations/Bank/Adeline/Market Lines/market_darcy_1/market_darcy_1/init":[ ADELINE, "coffee" ],
	"Conversations/Bank/Adeline/Market Lines/market_darcy_2/market_darcy_2/init":[ ADELINE, "coffee" ],
	"Conversations/Bank/Adeline/Market Lines/market_darcy_4/market_darcy_4/init":[ ADELINE, "spicy_cheddar_biscuit" ],
	"Cutscenes/Story Events/adeline_quest_board/adeline_quest_board/15":[ ADELINE, "tulip" ],
	"Cutscenes/Story Events/adeline_quest_board/adeline_quest_board/17":[ ADELINE, "tulip" ],
    "Conversations/Bank/Josephine/Banked Lines/week_one_pt_2/week_two/4":[ ADELINE, "coffee" ],
    "Conversations/Group Conversations/Adeline_Balor/market/market/2":[ ADELINE, "coffee" ],
	# Balor
	"Conversations/Bank/Balor/Relationship Lines/Relationship/post_8h_lines_romantic/balor_post_8h_romantic_3/init":[ BALOR, "ore_diamond", "ore_ruby"],
	"Conversations/Bank/Balor/Banked Lines/bath_smelled_nice/bath_smelled_nice/1":[ BALOR, "jasmine" ],
	"Conversations/Bank/Balor/Gift Lines/gift_lines/perfect_diamond/init":[ BALOR, "perfect_diamond" ], # Gift Line
	"Conversations/Bank/Balor/Museum Lines/alda_gem_bracelet/alda_gem_bracelet/init":[ BALOR, "alda_gem_bracelet" ],
	"Conversations/Bank/Balor/Museum Lines/family_crest_pendant/family_crest_pendant/init":[ BALOR, "family_crest_pendant" ],
	"Conversations/Bank/Balor/Museum Lines/perfect_emerald/perfect_emerald/init":[ BALOR, "perfect_emerald" ],
	"Conversations/Bank/Balor/Museum Lines/perfect_ruby/perfect_ruby/init":[ BALOR, "perfect_ruby" ],
	"Conversations/Bank/Balor/Museum Lines/perfect_sapphire/perfect_sapphire/init":[ BALOR, "perfect_sapphire" ],
	"Conversations/Bank/Balor/Museum Lines/rusted_treasure_chest/rusted_treasure_chest/init":[ BALOR, "rusted_treasure_chest" ],
	"Conversations/Bank/Balor/Museum Lines/sapphire_betta/sapphire_betta/init":[ BALOR, "sapphire_betta" ],
	"Conversations/Tutorial Dialogue/misc_quest_lines/gossip_for_elsie_juniper/7":[ BALOR, "ore_ruby" ],
	# Caldarus
	"Conversations/Bank/Caldarus/Relationship Lines/post_8h_lines_romantic/caldarus_post_8h_romantic_4/init":[ CALDARUS, "mont_blanc" ],
	"Conversations/Bank/Caldarus/Relationship Lines/post_8h_lines_best_friend/caldarus_post_8h_best_friend_6/1":[ CALDARUS, "spirit_mushroom_tea" ],
	"Conversations/Bank/Caldarus/Relationship Lines/post_8h_lines_romantic/caldarus_post_8h_romantic_8/1":[ CALDARUS, "breath_of_fire" ],
	"Conversations/Bank/Caldarus/Statue Lines/general_lines/general_lines_29/1":[ CALDARUS, "beet_soup" ],
	"Conversations/Bank/Caldarus/Statue Lines/general_lines/general_lines_30/1":[ CALDARUS, "mont_blanc" ],
	"Conversations/Bank/Caldarus/Banked Lines/items/spirit_mushroom_0/1":[ CALDARUS, "spirit_mushroom_tea" ],
	"Conversations/Bank/Caldarus/Gift Lines/gift_lines/fried_rice/init":[ CALDARUS, "fried_rice" ], # Gift Line
	"Conversations/Bank/Caldarus/Gift Lines/gift_lines/mont_blanc/init":[ CALDARUS, "mont_blanc" ], # Gift Line
	"Conversations/Bank/Caldarus/Gift Lines/gift_lines/sushi_platter/init":[ CALDARUS, "sushi_platter" ], # Gift Line
	# Celine
	"Conversations/Bank/Celine/Relationship Lines/Relationship/post_8h_lines_best_friend/celine_post_8h_best_friend_7/init":[ CELINE, "marigold" ],
	"Conversations/Bank/Celine/Relationship Lines/Relationship/post_8h_lines_best_friend/celine_post_8h_best_friend_6/init":[ CELINE, "lilac" ],
	"Conversations/Bank/Celine/Relationship Lines/Relationship/post_8h_lines_best_friend/celine_post_8h_best_friend_9/init":[ CELINE, "poinsettia" ],
	"Conversations/Bank/Celine/Date Lines/deep_woods_picnic/deep_woods_picnic_accept_2/3":[ CELINE, "temple_flower", "marigold" ],
	"Conversations/Bank/Celine/Relationship Lines/Relationship/post_8h_lines_best_friend/celine_post_8h_best_friend_8/init":[ CELINE, "heather" ],
	"Conversations/Bank/Celine/Banked Lines/daisies/daisies/init":[ CELINE, "daisy" ],
	"Conversations/Bank/Celine/Gift Lines/gift_lines/chrysanthemum/init":[ CELINE, "chrysanthemum" ], # Gift Line
	"Conversations/Bank/Celine/Gift Lines/gift_lines/plum_blossom/init":[ CELINE, "plum_blossom" ], # Gift Line
	"Conversations/Bank/Celine/Gift Lines/gift_lines/rose/init":[ CELINE, "rose" ], # Gift Line
	"Conversations/Bank/Celine/Gift Lines/gift_lines/temple_flower_0/1":[ CELINE, "temple_flower" ], # Gift Line
	"Conversations/Bank/Celine/Gift Lines/gift_lines/temple_flower_1/init":[ CELINE, "temple_flower" ], # Gift Line
	"Conversations/Bank/Celine/Market Lines/market_darcy_3/market_darcy_3/init":[ CELINE, "rose_tea" ],
	"Conversations/Group Conversations/Celine_Reina/foraging/foraging/1":[ CELINE, "frost_lily" ],	
	# Darcy
	"Conversations/General Dialogue/birthday_anticipation/darcy_birthday_anticipation_dell/1":[ DARCY, "apple" ],
    "Conversations/General Dialogue/birthday_anticipation/darcy_birthday_anticipation_luc/1":[ DARCY, "apple" ],
    "Conversations/General Dialogue/birthday_anticipation/darcy_birthday_anticipation_maple/1":[ DARCY, "apple" ],
	# Dell
	"Conversations/Bank/Dell/Museum Lines/alda_bronze_sword/alda_bronze_sword/init":[ DELL, "alda_bronze_sword" ],
	"Conversations/Bank/Dell/Museum Lines/aldarian_sword/aldarian_sword/init":[ DELL, "aldarian_sword" ],
	"Conversations/Bank/Dell/Museum Lines/caldosian_sword/caldosian_sword/init":[ DELL, "caldosian_sword" ],
	"Conversations/Bank/Dell/Museum Lines/lightning_dragonfly/lightning_dragonfly/init":[ DELL, "lightning_dragonfly" ],
	"Conversations/General Dialogue/birthday_anticipation/dell_birthday_anticipation_holt/init":[ DELL, "chocolate" ],
    "Conversations/General Dialogue/birthday_anticipation/dell_birthday_anticipation_nora/init":[ DELL, "chocolate" ],
    "Conversations/General Dialogue/birthday_anticipation/dell_birthday_anticipation_celine/init":[ DELL, "chocolate" ],
	"Conversations/Tutorial Dialogue/misc_quest_lines/gossip_for_elsie_dell/12":[ DELL, "chocolate" ],
	"Conversations/Tutorial Dialogue/misc_quest_lines/gossip_for_elsie_turn_in/2":[ DELL, "chocolate" ],
	# Dozy
	# Eiland
	"Conversations/Bank/Eiland/Relationship Lines/Relationship/post_8h_lines_romantic/eiland_post_8h_romantic_4/2":[ EILAND, "golden_cheesecake" ],
	"Conversations/Bank/Eiland/Banked Lines/pumpkin_pie/pumpkin_pie/init":[ EILAND, "pumpkin_pie" ],
	"Conversations/Bank/Eiland/Market Lines/market_darcy_1/market_darcy_1/init":[ EILAND, "roasted_rice_tea" ],
    "Conversations/Bank/Eiland/Banked Lines/breakfast/breakfast_2/2":[ EILAND, "strawberry_shortcake" ],
	# Elsie
	"Conversations/Bank/Elsie/Market Lines/market_darcy_1/market_darcy_1/init":[ ELSIE, "jasmine_tea" ],
	"Conversations/Bank/Elsie/Market Lines/market_darcy_2/market_darcy_2/init":[ ELSIE, "jasmine_tea" ],
	"Conversations/Bank/Elsie/Market Lines/market_darcy_3/market_darcy_3/init":[ ELSIE, "jasmine_tea" ],
	"Conversations/Bank/Elsie/Museum Lines/crystal_rose/crystal_rose/init":[ ELSIE, "crystal_rose" ],
	"Conversations/Bank/Elsie/Museum Lines/feather_pendant/feather_pendant/init":[ ELSIE, "alda_feather_pendant" ],
	# Errol
	"Conversations/Bank/Errol/Market Lines/market_darcy_1/market_darcy_1/init":[ ERROL, "latte" ],
	"Conversations/Bank/Errol/Market Lines/market_darcy_3/market_darcy_3/init":[ ERROL, "latte" ],
	"Conversations/Bank/Errol/Market Lines/market_darcy_4/market_darcy_4/init":[ ERROL, "mocha" ],
	# Hayden
	"Cutscenes/Heart Events/Hayden/hayden_eight_hearts/hayden_eight_hearts/1":[ HAYDEN, "vegetable_quiche" ],
	"Conversations/Bank/Hayden/Banked Lines/hot_toddy/hot_toddy/init":[ HAYDEN, "cup_of_tea" ],
	"Conversations/Bank/Hayden/Market Lines/market_darcy_1/market_darcy_1/init":[ HAYDEN, "coffee", "cup_of_tea"],
	"Conversations/Bank/Hayden/Market Lines/market_darcy_2/market_darcy_2/init":[ HAYDEN, "coffee" ],
	"Conversations/Bank/Hayden/Museum Lines/store_horse/stone_horse/init":[ HAYDEN, "stone_horse" ],
	"Conversations/Festival Lines/Hayden/shooting_star/shooting_star_romantic_follow_up_A/1":[ HAYDEN, "apple_pie" ],
	# Hemlock
	"Conversations/Bank/Hemlock/Market Lines/market_wheedle_1/market_wheedle_1/1":[ HEMLOCK, "white_wine" ],
	"Conversations/Bank/Hemlock/Gift Lines/gift_lines/crayfish_etouffee/init":[ HEMLOCK, "crayfish_etouffee" ], # Gift Line
	"Conversations/Bank/Josephine/Gift Lines/gift_lines/crayfish_etouffee/init":[ HEMLOCK, "crayfish_etouffee" ], # Gift Line
	"Conversations/Bank/Hemlock/Market Lines/market_darcy_1/market_darcy_1/init":[ HEMLOCK, "coffee", "beer"],
	"Conversations/Bank/Hemlock/Market Lines/market_darcy_2/market_darcy_2/init":[ HEMLOCK, "coffee" ],
	"Conversations/Bank/Hemlock/Market Lines/market_darcy_4/market_darcy_4/init":[ HEMLOCK, "coffee" ],
	"Conversations/Bank/Josephine/Museum Lines/caldosian_drinking_horn/caldosian_drinking_horn/init":[ HEMLOCK, "caldosian_drinking_horn" ],
	# Henrietta
	"Conversations/General Dialogue/season_transition/early_summer_henrietta/init":[ HENRIETTA, "corn" ],
	"Conversations/Threads/Hayden/henrietta_tales/hayden_henrietta_tales_3/2":[ HENRIETTA, "corn" ],
	"Conversations/fetch_quests_follow_ups/request_for_ultimate_small_animal_feed_follow_up_henrietta/init":[ HENRIETTA, "ultimate_small_animal_feed" ],
	# Holt
	"Conversations/Bank/Holt/Museum Lines/narrows_moss/narrows_moss/init":[ HOLT, "narrows_moss" ],
    "Conversations/General Dialogue/birthday_anticipation/holt_birthday_anticipation_dell/1":[ HOLT, "hard_wood" ],
    "Conversations/General Dialogue/birthday_anticipation/holt_birthday_anticipation_celine/1":[ HOLT, "hard_wood" ],
	# Josephine
	"Conversations/Bank/Hemlock/Gift Lines/gift_lines/crayfish_etouffee/init":[ JOSEPHINE, "crayfish_etouffee" ], # Gift Line
	"Conversations/Bank/Josephine/Gift Lines/gift_lines/crayfish_etouffee/init":[ JOSEPHINE, "crayfish_etouffee" ], # Gift Line
	"Conversations/Bank/Josephine/Banked Lines/quiche/quiche/init":[ JOSEPHINE, "quiche" ],
	"Conversations/Bank/Josephine/Market Lines/market_darcy_1/market_darcy_1/init":[ JOSEPHINE, "cup_of_tea", "green_tea", "jasmine_tea", "lavender_tea", "roasted_rice_tea", "rose_tea", "tea"],
	"Conversations/Bank/Josephine/Market Lines/market_darcy_2/market_darcy_2/init":[ JOSEPHINE, "cup_of_tea", "green_tea", "jasmine_tea", "lavender_tea", "roasted_rice_tea", "rose_tea", "tea" ],
	"Conversations/Bank/Josephine/Market Lines/market_darcy_4/market_darcy_4/init":[ JOSEPHINE, "cup_of_tea", "green_tea", "jasmine_tea", "lavender_tea", "roasted_rice_tea", "rose_tea", "tea" ],
	"Conversations/Bank/Hemlock/Market Lines/market_darcy_2/market_darcy_2/init":[ JOSEPHINE, "cup_of_tea", "green_tea", "jasmine_tea", "lavender_tea", "roasted_rice_tea", "rose_tea", "tea" ], # Indicates Josephine likes tea, but without the highlighting hint.
	# Juniper
	"Conversations/Bank/Juniper/Banked Lines/breakfast/breakfast/1":[ JUNIPER, "latte" ],
	"Conversations/Bank/Juniper/Banked Lines/foraging/foraging_3/1":[ JUNIPER, "nettle" ],
	"Conversations/Bank/Juniper/Banked Lines/foraging/foraging_3/init":[ JUNIPER, "nettle" ],
	"Conversations/Bank/Juniper/Banked Lines/middlemist_red/middlemist_red/init":[ JUNIPER, "middlemist" ],
	"Conversations/Bank/Juniper/Banked Lines/new_potion/new_potion/init":[ JUNIPER, "newt" ],
	"Conversations/Bank/Juniper/Banked Lines/orb_viewing/orb_viewing_2/1":[ JUNIPER, "water_chestnut_fritters" ],
	"Conversations/Bank/Juniper/Gift Lines/gift_lines/ancient_royal_scepter/init":[ JUNIPER, "ancient_royal_scepter" ], # Gift Line
	"Conversations/Bank/Juniper/Gift Lines/gift_lines/crystal_rose/init":[ JUNIPER, "crystal_rose" ], # Gift Line
	"Conversations/Bank/Juniper/Market Lines/market_darcy_1/market_darcy_1/init":[ JUNIPER, "latte" ],
	"Conversations/Bank/Juniper/Museum Lines/ancient_royal_scepter/ancient_royal_scepter/init":[ JUNIPER, "ancient_royal_scepter" ],
	"Conversations/Bank/Valen/Market Lines/market_darcy_4/market_darcy_4/init":[ JUNIPER, "latte" ],
	"Conversations/Tutorial Dialogue/misc_quest_lines/gossip_for_elsie_balor/2":[ JUNIPER, "newt" ],
	"Conversations/Tutorial Dialogue/misc_quest_lines/gossip_for_elsie_balor/4":[ JUNIPER, "newt" ],
	"Conversations/Tutorial Dialogue/misc_quest_lines/gossip_for_elsie_turn_in/7":[ JUNIPER, "newt" ],
    "Conversations/General Dialogue/ari_birthday/ari_birthday_juniper_low_hearts/2":[ JUNIPER, "newt" ],
	# Landen
	"Conversations/Bank/Landen/Banked Lines/inn_special/inn_special/init":[ LANDEN, "vegetable_pot_pie" ],
	"Cutscenes/Heart Events/Ryis/ryis_six_hearts/ryis_six_hearts/17":[ LANDEN, "coconut_cream_pie" ],
    "Cutscenes/Story Events/Town Repair/upgrade_the_carpenters_shop/upgrade_the_carpenters_shop_pt_2_follow_up_landen/1":[ LANDEN, "vegetable_pot_pie" ],
	# Luc
	"Conversations/fetch_quests_follow_ups/request_for_cheese_follow_up_hemlock/init":[ LUC, "cheese" ],
	"Conversations/Bank/Luc/Gift Lines/gift_lines/grilled_cheese/init":[ LUC, "grilled_cheese" ], # Gift Line
	"Conversations/Bank/Luc/Market Lines/market_darcy_1/market_darcy_1/init":[ LUC, "hot_cocoa" ],
	"Conversations/Bank/Luc/Museum Lines/amber_trapped_insect/amber_trapped_insect/init":[ LUC, "amber_trapped_insect" ],
	"Conversations/Bank/Luc/Museum Lines/cave_shrimp/cave_shrimp/init":[ LUC, "cave_shrimp" ],
	"Conversations/Bank/Luc/Museum Lines/copper_nugget_beetle/copper_nugget_beetle/init":[ LUC, "copper_beetle" ],
	"Conversations/Bank/Luc/Museum Lines/fairy_bee/fairy_bee/init":[ LUC, "fairy_bee" ],
	"Conversations/Bank/Luc/Museum Lines/puddle_spider/puddle_spider/init":[ LUC, "puddle_spider" ],
	"Conversations/Bank/Luc/Museum Lines/sea_scarab/sea_scarab/init":[ LUC, "sea_scarab" ],
	"Conversations/Bank/Luc/Museum Lines/snowball_beetle/snowball_beetle/init":[ LUC, "snowball_beetle" ],
	"Conversations/Bank/Luc/Museum Lines/strobe_firefly/strobe_firefly/init":[ LUC, "strobe_firefly" ],
	"Conversations/Bank/Reina/Banked Lines/luc_and_maple_cheese/luc_and_maple_cheese/init":[ LUC, "cheese" ],
	# Louis
	"Conversations/Bank/Louis/Gift Lines/gift_lines/crystal/init":[ LOUIS, "crystal" ], # Gift Line
	"Conversations/Bank/Louis/Gift Lines/gift_lines/lilac/init":[ LOUIS, "lilac" ], # Gift Line
	"Conversations/Bank/Louis/Gift Lines/gift_lines/red_wine/init":[ LOUIS, "red_wine" ], # Gift Line
	"Conversations/Bank/Louis/Gift Lines/gift_lines/white_wine/init":[ LOUIS, "white_wine" ], # Gift Line
	# Maple
	"Conversations/Bank/Maple/Gift Lines/gift_lines/berries_and_cream/init":[ MAPLE, "berries_and_cream" ], # Gift Line
	"Conversations/Bank/Maple/Market Lines/market_darcy_2/market_darcy_2/init":[ MAPLE, "hot_cocoa" ],
	"Conversations/Bank/Maple/Market Lines/market_darcy_4/market_darcy_4/init":[ MAPLE, "hot_cocoa" ],
	"Conversations/Bank/Maple/Museum Lines/stone_shell/stone_shell/init":[ MAPLE, "stone_shell" ],
	"Conversations/Bank/Reina/Banked Lines/luc_and_maple_cheese/luc_and_maple_cheese/init":[ MAPLE, "cheese" ],
	"Conversations/General Dialogue/birthday_anticipation/maple_self_birthday_anticipation/init":[ MAPLE, "lost_crown_of_aldaria" ],
	# March
	"Conversations/Bank/March/Banked Lines/beer/beer/init":[ MARCH, "beer" ],
	"Conversations/Bank/March/Banked Lines/chocolate/chocolate/init":[ MARCH, "chocolate" ],
	"Conversations/Bank/March/Banked Lines/cold_beer_long_day/cold_beer_long_day/init":[ MARCH, "beer" ],
	"Conversations/Bank/March/Gift Lines/gift_lines/gold_ingot/init":[ MARCH, "gold_ingot" ], # Gift Line
	"Conversations/Bank/March/Gift Lines/gift_lines/mocha/init":[ MARCH, "mocha" ], # Gift Line
	"Conversations/Bank/March/Gift Lines/gift_lines/red_snapper_sushi/init":[ MARCH, "red_snapper_sushi" ], # Gift Line
	"Conversations/Bank/March/Market Lines/market_darcy_1/market_darcy_1/init":[ MARCH, "hot_cocoa" ],
	"Conversations/Bank/March/Market Lines/market_darcy_3/market_darcy_3/init":[ MARCH, "hot_cocoa" ],
	"Conversations/Bank/March/Museum Lines/meteorite/meteorite/init":[ MARCH, "meteorite" ],
	"Conversations/Bank/March/Museum Lines/perfect_copper_ore/perfect_copper_ore/init":[ MARCH, "perfect_copper_ore" ],
	"Conversations/Bank/March/Museum Lines/perfect_iron_ore/perfect_iron_ore/init":[ MARCH, "perfect_iron_ore" ],
	"Conversations/Bank/March/Museum Lines/perfect_silver_ore/perfect_silver_ore/init":[ MARCH, "perfect_silver_ore" ],
	"Conversations/Festival Lines/March/animal_festival/animal_festival_0/init":[ MARCH, "hot_cocoa" ],
	"Conversations/Group Conversations/Elsie_March_Olric_Ryis/breakfast/breakfast_3/1":[ MARCH, "coffee" ],
	# Merri
	"Conversations/Bank/Merri/Gift Lines/gift_lines/glass/init":[ MERRI, "glass" ], # Gift Line
	"Conversations/Bank/Merri/Gift Lines/gift_lines/hard_wood/init":[ MERRI, "hard_wood" ], # Gift Line
	"Conversations/Bank/Merri/Gift Lines/gift_lines/latte/init":[ MERRI, "latte" ], # Gift Line
	# Nora
	"Conversations/Bank/Nora/Gift Lines/gift_lines/ancient_gold_coin/init":[ NORA, "ancient_gold_coin" ], # Gift Line
	"Conversations/Bank/Nora/Gift Lines/gift_lines/coffee/init":[ NORA, "coffee" ], # Gift Line
	"Conversations/Bank/Nora/Market Lines/market_darcy_4/market_darcy_4/init":[ NORA, "latte" ],
	"Conversations/Bank/Nora/Museum Lines/ancient_gold_coin/ancient_gold_coin/init":[ NORA, "ancient_gold_coin" ],
	"Conversations/General Dialogue/birthday_anticipation/nora_birthday_anticipation_dell/1":[ NORA, "baked_potato" ],
    "Conversations/General Dialogue/birthday_anticipation/nora_birthday_anticipation_celine/1":[ NORA, "baked_potato" ],
	# Olric
	"Conversations/Bank/March/Banked Lines/hardboiled_egg/hardboiled_egg/init":[ OLRIC, "hard_boiled_egg" ],
	"Conversations/Bank/Olric/Gift Lines/gift_lines/hard_boiled_egg/init":[ OLRIC, "hard_boiled_egg" ], # Gift Line
	"Conversations/Group Conversations/Elsie_March_Olric_Ryis/breakfast/breakfast_3/3":[ OLRIC, "hard_boiled_egg" ],
	"Conversations/Bank/March/Banked Lines/olric_stone/olric_stone/init":[ OLRIC, "ore_stone" ],
	"Conversations/Bank/Olric/Market Lines/market_wheedle_1/market_wheedle_1/init":[ OLRIC, "ore_stone" ],
	# Priestess
	# Reina
	"Conversations/Bank/Reina/Relationship Lines/Relationship/post_8h_lines_romantic/reina_post_8h_romantic_2/1":[ REINA, "cauliflower_curry" ],
	"Conversations/Bank/Reina/Relationship Lines/Relationship/post_8h_lines_romantic/reina_post_8h_romantic_8/1":[ REINA, "turnip_and_potato_gratin" ],
	"Conversations/Bank/Reina/Banked Lines/garlic/garlic/init":[ REINA, "garlic" ],
	"Conversations/Bank/Reina/Banked Lines/garlic/garlic_2/init":[ REINA, "garlic" ],
    "Conversations/Bank/Reina/Banked Lines/general_store_shopping/general_store_shopping_3/init":[ REINA, "garlic" ],
	"Conversations/Bank/Reina/Gift Lines/gift_lines/daffodil/init":[ REINA, "daffodil" ], # Gift Line
	"Conversations/Bank/Reina/Market Lines/market_darcy_1/market_darcy_1/init":[ REINA, "coffee", "iced_coffee"],
	"Conversations/Bank/Reina/Market Lines/market_darcy_4/market_darcy_4/init":[ REINA, "coffee" ],
	"Cutscenes/Heart Events/Reina/reina_six_hearts/reina_six_hearts/37":[ REINA, "grilled_cheese" ],
	"Cutscenes/Heart Events/Reina/reina_two_hearts/reina_two_hearts/1":[ REINA, "wildberry_pie" ],
    "Conversations/General Dialogue/ari_birthday/ari_birthday_reina_romantic/1":[ REINA, "wildberry_pie" ],
	# Ryis
	"Conversations/Bank/Ryis/Relationship Lines/post_8h_lines_romantic/ryis_post_8h_romantic_10/init":[ RYIS, "iced_coffee" ],
	"Conversations/Bank/Ryis/Relationship Lines/Relationship/post_8h_lines_best_friend/ryis_post_8h_best_friend_12/4":[ RYIS, "golden_horse_hair" ],
	"Conversations/Bank/Ryis/Relationship Lines/Relationship/post_8h_lines_best_friend/ryis_post_8h_best_friend_2/1":[ RYIS, "iced_coffee" ],
    "Conversations/Bank/Ryis/Relationship Lines/Relationship/post_8h_lines_romantic/ryis_post_8h_romantic_10/init":[ RYIS, "iced_coffee" ],
	"Conversations/Bank/Ryis/Banked Lines/bath_smells_like_lavender/bath_smells_like_lavender/init":[ RYIS, "lilac" ],
	"Conversations/Bank/Ryis/Gift Lines/gift_lines/hard_wood/1":[ RYIS, "hard_wood" ], # Gift Line
	"Conversations/Bank/Ryis/Market Lines/market_darcy_1/market_darcy_1/init":[ RYIS, "iced_coffee" ],
	"Conversations/Bank/Ryis/Market Lines/market_darcy_2/market_darcy_2/init":[ RYIS, "iced_coffee" ],
	"Conversations/Bank/Ryis/Market Lines/market_darcy_3/market_darcy_3/init":[ RYIS, "iced_coffee" ],
	"Conversations/Bank/Landen/Banked Lines/veggie_sub/veggie_sub/init":[ RYIS, "veggie_sub_sandwich" ],
	"Conversations/Bank/Ryis/Banked Lines/shopping_for_landen/shopping_for_landen_2/init":[ RYIS, "bread" ],
	"Conversations/Group Conversations/Elsie_March_Olric_Ryis/breakfast/breakfast_3/2":[ RYIS, "bread" ],
	# Stillwell
	# Taliferro
	"Conversations/Bank/Taliferro/Banked Lines/challenge_completed_lines/incredibly_hot_pot_terithia/init":[ TALIFERRO, "incredibly_hot_pot" ],
	"Conversations/Bank/Taliferro/Banked Lines/challenge_completed_lines/veggie_sub_sandwich_holt/init":[ TALIFERRO, "veggie_sub_sandwich" ],
	# Terithia
	"Conversations/Bank/Terithia/Gift Lines/gift_lines/fish_stew/init":[ TERITHIA, "fish_stew" ], # Gift Line
	"Conversations/Bank/Valen/Banked Lines/terithia_fish_jerky/terithia_fish_jerky/init":[ TERITHIA, "canned_sardines" ],
	"Conversations/General Dialogue/birthday_anticipation/terithia_birthday_anticipation_errol/1":[ TERITHIA, "dried_squid" ],
    "Conversations/General Dialogue/birthday_anticipation/terithia_birthday_anticipation_landen/1":[ TERITHIA, "dried_squid" ],
	# Valen
	"Conversations/Bank/Valen/Banked Lines/rainy_stock_up/rainy_stock_up/init":[ VALEN, "honey" ],
	"Conversations/Bank/Valen/Banked Lines/winter_honey/winter_honey/init":[ VALEN, "honey" ],
	"Conversations/Bank/Valen/Market Lines/market_darcy_1/market_darcy_1/init":[ VALEN, "coffee" ],
	"Conversations/Bank/Valen/Market Lines/market_darcy_2/market_darcy_2/init":[ VALEN, "coffee" ],
	"Conversations/Bank/Valen/Market Lines/market_darcy_3/market_darcy_3/init":[ VALEN, "coffee" ],
    "Conversations/Bank/Valen/Banked Lines/breakfast/breakfast_4/init":[ VALEN, "coffee" ],
	"Conversations/General Dialogue/ari_birthday/ari_birthday_valen_low_hearts/1":[ VALEN, "coffee" ],
	"Conversations/Festival Lines/Valen/shooting_star/shooting_star_romantic_follow_up_A/1":[ VALEN, "beet_soup" ],
	"Conversations/General Dialogue/birthday_anticipation/valen_birthday_anticipation_hayden/1":[ VALEN, "vegetable_soup" ],
	"Conversations/Group Conversations/Adeline_Valen/salmon_benefits/salmon_benefits/init":[ VALEN, "pan_fried_salmon" ],
	"Conversations/Group Conversations/Celine_Valen/deep_woods_nettle/deep_woods_nettle/1":[ VALEN, "nettle" ],
    "Conversations/Bank/Reina/Banked Lines/general_store_shopping/general_store_shopping_3/init":[ VALEN, "garlic" ],
    "Conversations/General Dialogue/ari_birthday/ari_birthday_valen_high_hearts/1":[ VALEN, "green_tea" ],
	# Vera
	"Conversations/Bank/Vera/Gift Lines/gift_lines/coconut_milk/init":[ VERA, "coconut_milk" ], # Gift Line
	"Conversations/Bank/Vera/Gift Lines/gift_lines/cranberry_juice/init":[ VERA, "cranberry_juice" ], # Gift Line
	"Conversations/Bank/Vera/Gift Lines/gift_lines/gazpacho/init":[ VERA, "gazpacho" ], # Gift Line
	"Conversations/Bank/Vera/Gift Lines/gift_lines/orange_juice/init":[ VERA, "orange_juice" ], # Gift Line
	"Conversations/Bank/Vera/Gift Lines/gift_lines/pomegranate/init":[ VERA, "pomegranate" ], # Gift Line
	"Conversations/Bank/Vera/Gift Lines/gift_lines/summer_salad/init":[ VERA, "summer_salad" ], # Gift Line
	# Wheedle
	# Zorel
	# MOD, Talkative Celine
	"conversations/talkative_celine/frost lily/init":[ CELINE, "frost_lily" ],
	"conversations/talkative_celine/plum blossom/init":[ ADELINE, "plum_blossom" ],
	"conversations/talkative_celine/plum blossom/init":[ CELINE, "plum_blossom" ],
	"conversations/talkative_celine/jasmine/init":[ CELINE, "jasmine" ],
	"conversations/talkative_celine/jasmine/init":[ JOSEPHINE, "jasmine" ],
	"conversations/talkative_celine/poinsettia/init":[ CELINE, "poinsettia" ],
	"conversations/talkative_celine/poinsettia/init":[ JUNIPER, "poinsettia" ],
	"conversations/talkative_celine/crocus/init":[ CELINE, "crocus" ],
	"conversations/talkative_celine/snapdragon/init":[ CELINE, "snapdragon" ],
	"conversations/talkative_celine/middlemist/init":[ CELINE, "middlemist" ],
	"conversations/talkative_celine/snowdrop anemone/1":[ CELINE, "snowdrop_anemone" ],
	"conversations/talkative_celine/lilac/init":[ CELINE, "lilac" ],
	"conversations/talkative_celine/daffodil/init":[ CELINE, "daffodil" ],
	"conversations/talkative_celine/daffodil/1":[ REINA, "daffodil" ],
	"conversations/talkative_celine/dandelion/init":[ CELINE, "dandelion" ],
	"conversations/talkative_celine/dandelion/init":[ VALEN, "dandelion" ],
	"conversations/talkative_celine/tulip/init":[ CELINE, "tulip" ],
	"conversations/talkative_celine/spring galette/init":[ ADELINE, "spring_galette" ],
	"conversations/talkative_celine/rose tea/init":[ CELINE, "rose_tea" ],
	"conversations/talkative_celine/spring salad/init":[ CELINE, "spring_salad" ],
	"conversations/talkative_celine/hydrangea/init":[ CELINE, "hydrangea" ],
	"conversations/talkative_celine/rose/init":[ CELINE, "rose" ],
	"conversations/talkative_celine/catmint/init":[ CELINE, "catmint" ],
	"conversations/talkative_celine/cosmos/init":[ CELINE, "cosmos" ],
	"conversations/talkative_celine/cosmos/1":[ ELSIE, "cosmos" ],
	"conversations/talkative_celine/marigold/init":[ CELINE, "marigold" ],
	"conversations/talkative_celine/daisy/init":[ CELINE, "daisy" ],
	"conversations/talkative_celine/daisy/init":[ MAPLE, "daisy" ],
	"conversations/talkative_celine/sunflower/init":[ CELINE, "sunflower" ],
	"conversations/talkative_celine/sunflower/init":[ NORA, "toasted_sunflower_seeds" ],
	"conversations/talkative_celine/iris/init":[ CELINE, "iris" ],
	"conversations/talkative_celine/iris/init":[ ELSIE, "iris" ],
	"conversations/talkative_celine/celosia/init":[ CELINE, "celosia" ],
	"conversations/talkative_celine/celosia/init":[ LOUIS, "celosia" ],
	"conversations/talkative_celine/chrysanthemum/init":[ CELINE, "chrysanthemum" ],
	"conversations/talkative_celine/heather/init":[ CELINE, "heather" ],
	"conversations/talkative_celine/viola/init":[ CELINE, "viola" ],
	"conversations/talkative_celine/crystal rose/init":[ CELINE, "crystal_rose" ],
}

npc_gift_preferences = {}
with open(CURRENT_GAME_VERSION + "/__fiddle__.json", "r", encoding="UTF-8") as fiddle_file:
    fiddle_data = json.loads(fiddle_file.read())
    npcs = fiddle_data["npcs"]

    for npc in npcs:
        if npc not in npc_gift_preferences:
            npc_gift_preferences[npc] = []
        if "loved_gifts" in npcs[npc]:
            for gift in npcs[npc]["loved_gifts"]:
                npc_gift_preferences[npc].append(gift)
        if "liked_gifts" in npcs[npc]:
            for gift in npcs[npc]["liked_gifts"]:
                npc_gift_preferences[npc].append(gift)

for dialogue_key in GIFT_DIALOG_DICT:
    parsed_gift_preferences = GIFT_DIALOG_DICT[dialogue_key]
    npc = parsed_gift_preferences[0]
    parsed_gift_preferences = parsed_gift_preferences[1:]
    for gift in parsed_gift_preferences:
        if gift not in npc_gift_preferences[npc]:
            print("The parsed gift preference (" + gift + ") is not in the game gift preference list for npc (" + npc + ").")
