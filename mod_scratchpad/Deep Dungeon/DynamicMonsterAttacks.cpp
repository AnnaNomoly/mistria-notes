void ObjectCallback(
	IN FWCodeEvent& CodeEvent
)
{
	auto& [self, other, code, argc, argv] = CodeEvent.Arguments();

	if (!self)
		return;

	if (!self->m_Object)
		return;

	std::string name = self->m_Object->m_Name;
	if (name == "obj_monster_clod")
	{
		RValue monster = self->ToRValue();
		RValue monster_id = monster.GetMember("monster_id");
		if (monster_id.ToInt64() == 17)
		{
			RValue wait_to_change_attack_pattern_exists = g_ModuleInterface->CallBuiltin("struct_exists", { monster, "__deep_dungeon__wait_to_change_attack_pattern" });
			if (!wait_to_change_attack_pattern_exists.ToBoolean())
				StructVariableSet(monster, "__deep_dungeon__wait_to_change_attack_pattern", false);
			RValue wait_to_change_attack_pattern = monster.GetMember("__deep_dungeon__wait_to_change_attack_pattern");

			RValue custom_attack_pattern_exists = g_ModuleInterface->CallBuiltin("struct_exists", { monster, "__deep_dungeon__custom_attack_pattern" });
			if (!custom_attack_pattern_exists.ToBoolean())
			{
				StructVariableSet(monster, "__deep_dungeon__custom_attack_pattern", 0);
				if (StructVariableExists(monster, "config"))
				{
					RValue config = *monster.GetRefMember("config");
					*config.GetRefMember("attack_sequence") = 20.0;
					*config.GetRefMember("attack_legion") = 10.0;
					*config.GetRefMember("projectile_speed") = 3.5;
				}
			}

			if (StructVariableExists(monster, "fsm"))
			{
				RValue state_id = monster.GetMember("fsm").GetMember("state").GetMember("state_id"); // TODO: Don't hard-code these. Get them from the monster's __rockclod_state__ global.
				if (state_id.ToInt64() == 4) // Attack
					*monster.GetRefMember("__deep_dungeon__wait_to_change_attack_pattern") = false;

				if (state_id.ToInt64() == 5 && !wait_to_change_attack_pattern.ToBoolean()) // Tired
				{
					*monster.GetRefMember("__deep_dungeon__wait_to_change_attack_pattern") = true;

					int custom_attack_pattern = monster.GetMember("__deep_dungeon__custom_attack_pattern").ToInt64() + 1;
					if (custom_attack_pattern > 2)
						custom_attack_pattern = 0;

					if (custom_attack_pattern == 0)
					{
						if (StructVariableExists(monster, "config"))
						{
							// Shoots a wall of 10 pellets repeatedly 5 times
							RValue config = *monster.GetRefMember("config");
							*config.GetRefMember("attack_sequence") = 5.0;
							*config.GetRefMember("attack_legion") = 10.0;
							*config.GetRefMember("attack_sequence_turn") = -1.0;
							*config.GetRefMember("attack_sequence_image_speed") = -1.0;
							*config.GetRefMember("projectile_speed") = 3.0;
							*config.GetRefMember("split_distance") = -1.0;
							*config.GetRefMember("split_depth") = -1.0;
							*config.GetRefMember("split_angle") = -1.0;
						}
					}
					if (custom_attack_pattern == 1)
					{
						if (StructVariableExists(monster, "config"))
						{
							// Rotates 18-degrees at a time while shooting 5 pellets in a small cone
							RValue config = *monster.GetRefMember("config");
							*config.GetRefMember("attack_sequence") = 20.0;
							*config.GetRefMember("attack_legion") = 5.0;
							*config.GetRefMember("attack_sequence_turn") = 18.0;
							*config.GetRefMember("attack_sequence_image_speed") = 2.0;
							*config.GetRefMember("projectile_speed") = 3.0;
							*config.GetRefMember("split_distance") = -1.0;
							*config.GetRefMember("split_depth") = -1.0;
							*config.GetRefMember("split_angle") = -1.0;
						}
					}
					if (custom_attack_pattern == 2)
					{
						if (StructVariableExists(monster, "config"))
						{
							// Shoots a single pellet that then splits into many that repeatedly split
							RValue config = *monster.GetRefMember("config");
							*config.GetRefMember("attack_sequence") = 5.0;
							*config.GetRefMember("attack_legion") = 1.0;
							*config.GetRefMember("attack_sequence_turn") = -1.0;
							*config.GetRefMember("attack_sequence_image_speed") = -1.0;
							*config.GetRefMember("projectile_speed") = 3.0;
							*config.GetRefMember("split_distance") = 20.0;
							*config.GetRefMember("split_depth") = 5.0;
							*config.GetRefMember("split_angle") = 20.0;
						}
					}

					*monster.GetRefMember("__deep_dungeon__custom_attack_pattern") = custom_attack_pattern;
				}
			}
		}
	}
}