RValue GetDynamicItemSprite(std::string sprite_name)
{
	if (sprite_name == "spr_ui_item_tool_scrap_metal_sword") // Mistpool Sword
	{
		if (active_traps.contains(Traps::INHIBITING) || !AriCurrentGmRoomIsDungeonFloor())
		{
			if (floor_number < 20)
				return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_tool_rusty_sword_disabled" });
			else if (floor_number < 40)
				return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_tool_verdigris_sword_disabled" });
			else if (floor_number < 60)
				return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_tool_crystal_sword_disabled" });
			else
				return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_tool_tarnished_gold_sword_disabled" });
		}
		else
		{
			if (floor_number < 20)
				return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_tool_rusty_sword" });
			else if (floor_number < 40)
				return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_tool_verdigris_sword" });
			else if (floor_number < 60)
				return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_tool_crystal_sword" });
			else
				return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_tool_tarnished_gold_sword" });
		}
	}
	if (sprite_name == "spr_ui_item_equipment_mistpool_helmet_tier_1") // Mistpool Helmet
	{
		if (floor_number < 20)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_helmet_tier_1" });
		else if (floor_number < 40)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_helmet_tier_2" });
		else if (floor_number < 60)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_helmet_tier_3" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_helmet_tier_4" });
	}
	if (sprite_name == "spr_ui_item_equipment_mistpool_chestpiece_tier_1") // Mistpool Chestpiece
	{
		if (floor_number < 20)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_chestpiece_tier_1" });
		else if (floor_number < 40)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_chestpiece_tier_2" });
		else if (floor_number < 60)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_chestpiece_tier_3" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_chestpiece_tier_4" });
	}
	if (sprite_name == "spr_ui_item_equipment_mistpool_pants_tier_1") // Mistpool Pants
	{
		if (floor_number < 20)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_pants_tier_1" });
		else if (floor_number < 40)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_pants_tier_2" });
		else if (floor_number < 60)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_pants_tier_3" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_pants_tier_4" });
	}
	if (sprite_name == "spr_ui_item_equipment_mistpool_boots_tier_1") // Mistpool Boots
	{
		if (floor_number < 20)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_boots_tier_1" });
		else if (floor_number < 40)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_boots_tier_2" });
		else if (floor_number < 60)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_boots_tier_3" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_boots_tier_4" });
	}
	if (sprite_name == "spr_ui_item_equipment_mistpool_gloves_tier_1") // Mistpool Gloves
	{
		if (floor_number < 20)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_gloves_tier_1" });
		else if (floor_number < 40)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_gloves_tier_2" });
		else if (floor_number < 60)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_gloves_tier_3" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_equipment_mistpool_gloves_tier_4" });
	}
	if (sprite_name == "spr_ui_item_sigil_of_alteration")
	{
		if (active_sigils.contains(Sigils::ALTERATION) || active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_alteration_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_alteration" });
	}
	if (sprite_name == "spr_ui_item_sigil_of_concealment")
	{
		if (active_sigils.contains(Sigils::CONCEALMENT) || active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_concealment_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_concealment" });
	}
	if (sprite_name == "spr_ui_item_sigil_of_fortification")
	{
		if (active_sigils.contains(Sigils::FORTIFICATION) || active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_fortification_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_fortification" });
	}
	if (sprite_name == "spr_ui_item_sigil_of_fortune")
	{
		if (active_sigils.contains(Sigils::FORTUNE) || active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_fortune_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_fortune" });
	}
	if (sprite_name == "spr_ui_item_sigil_of_protection")
	{
		if (active_sigils.contains(Sigils::PROTECTION) || active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_protection_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_protection" });
	}
	if (sprite_name == "spr_ui_item_sigil_of_rage")
	{
		if (active_sigils.contains(Sigils::RAGE) || active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_rage_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_rage" });
	}
	if (sprite_name == "spr_ui_item_sigil_of_redemption")
	{
		if (active_sigils.contains(Sigils::REDEMPTION) || active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_redemption_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_redemption" });
	}
	if (sprite_name == "spr_ui_item_sigil_of_safety")
	{
		if (active_sigils.contains(Sigils::SAFETY) || active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_safety_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_safety" });
	}
	if (sprite_name == "spr_ui_item_sigil_of_serenity")
	{
		if (active_sigils.contains(Sigils::SERENITY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_serenity_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_serenity" });
	}
	if (sprite_name == "spr_ui_item_sigil_of_silence")
	{
		if (active_sigils.contains(Sigils::SILENCE) || active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_silence_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_silence" });
	}
	if (sprite_name == "spr_ui_item_sigil_of_strength")
	{
		if (active_sigils.contains(Sigils::STRENGTH) || active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_strength_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_strength" });
	}
	if (sprite_name == "spr_ui_item_sigil_of_temptation")
	{
		if (active_sigils.contains(Sigils::TEMPTATION) || active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_temptation_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_sigil_of_temptation" });
	}
	if (sprite_name == "spr_ui_item_potion_sustain")
	{
		if (active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_potion_sustain_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_potion_sustain" });
	}
	if (sprite_name == "spr_ui_item_salve_health")
	{
		if (salves_used.contains(item_name_to_id_map["health_salve"]) || active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_salve_health_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_salve_health" });
	}
	if (sprite_name == "spr_ui_item_salve_stamina")
	{
		if (salves_used.contains(item_name_to_id_map["stamina_salve"]) || active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_salve_stamina_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_salve_stamina" });
	}
	if (sprite_name == "spr_ui_item_salve_mana")
	{
		if (salves_used.contains(item_name_to_id_map["mana_salve"]) || active_floor_enchantments.contains(FloorEnchantments::ITEM_PENALTY) || !AriCurrentGmRoomIsDungeonFloor())
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_salve_mana_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_item_salve_mana" });
	}
	if (sprite_name == "spr_ui_journal_magic_restore_spell_icon_main")
	{
		if (active_floor_enchantments.contains(FloorEnchantments::AMNESIA) || boss_battle != BossBattle::NONE)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_journal_magic_restore_spell_icon_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_journal_magic_restore_spell_icon_main" });
	}
	if (sprite_name == "spr_ui_journal_magic_rain_spell_icon_main")
	{
		if (active_floor_enchantments.contains(FloorEnchantments::AMNESIA) || boss_battle != BossBattle::NONE)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_journal_magic_rain_spell_icon_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_journal_magic_rain_spell_icon_main" });
	}
	if (sprite_name == "spr_ui_journal_magic_growth_spell_icon_main")
	{
		if (active_floor_enchantments.contains(FloorEnchantments::AMNESIA) || boss_battle != BossBattle::NONE)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_journal_magic_growth_spell_icon_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_journal_magic_growth_spell_icon_main" });
	}
	if (sprite_name == "spr_ui_journal_magic_fire_spell_icon_main")
	{
		if (active_floor_enchantments.contains(FloorEnchantments::AMNESIA) || boss_battle != BossBattle::NONE)
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_journal_magic_fire_spell_icon_disabled" });
		else
			return g_ModuleInterface->CallBuiltin("asset_get_index", { "spr_ui_journal_magic_fire_spell_icon_main" });
	}

	return RValue();
}
