	// DEBUG -------------------------------------------------------------------------------------------
	RValue escape_key_pressed = g_ModuleInterface->CallBuiltin("keyboard_check_pressed", { VK_ESCAPE });
	if (RValueAsBool(escape_key_pressed))
	{
		RValue user_input = g_ModuleInterface->CallBuiltin(
			"get_string",
			{
				"Enter the activation key you wish to use.",
				activation_button
			}
		);

		auto allowed_button = std::find(std::begin(ALLOWED_ACTIVATION_BUTTONS), std::end(ALLOWED_ACTIVATION_BUTTONS), user_input.AsString().data());
		if (allowed_button != std::end(ALLOWED_ACTIVATION_BUTTONS))
		{
			activation_button = user_input.AsString().data();
			ConfigureActivationButton();
		}
		else
		{
			std::string temp = user_input.AsString().data();
			g_ModuleInterface->Print(CM_RED, std::string("Ignoring bad activation key: ") + temp.c_str());
		}
	}
	// -------------------------------------------------------------------------------------------------