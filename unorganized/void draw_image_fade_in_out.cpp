void draw_image_fade_in_out(double seconds_per_cycle, int repeat_count) {
	RValue window_get_width = g_ModuleInterface->CallBuiltin(
		"window_get_width",
		{}
	);

	RValue window_get_height = g_ModuleInterface->CallBuiltin(
		"window_get_height",
		{}
	);

	// Window corners
	std::vector<double> window_top_left = { 0.0, 0.0 };
	std::vector<double> window_top_right = { window_get_width.m_Real, 0.0 };
	std::vector<double> window_bottom_left = { 0.0, window_get_height.m_Real };
	std::vector<double> window_bottom_right = { window_get_width.m_Real, window_get_height.m_Real };

	// Window center
	auto center = GetCenter(window_top_left, window_bottom_right);
	auto centered_offset = calculate_centered_offset(center[0], center[1], 400, 120);


	if (!fade_initialized) {
		fade_start_time = get_current_time_ms();
		fade_initialized = true;
	}

	double cycle_ms = seconds_per_cycle * 1000.0;
	uint64_t elapsed = get_current_time_ms() - fade_start_time;

	int current_cycle = elapsed / cycle_ms;

	if (current_cycle >= repeat_count) {
		display_image(centered_offset.first, centered_offset.second, 0); // Fully transparent after done
		return;
	}

	double cycle_position = static_cast<double>(elapsed % static_cast<int>(cycle_ms));
	double half_cycle = cycle_ms / 2.0;
	int transparency = 0;

	if (cycle_position <= half_cycle) {
		// Fade in: 0 -> 100
		transparency = static_cast<int>((cycle_position / half_cycle) * 100);
	}
	else {
		// Fade out: 100 -> 0
		double fade_out_pos = cycle_position - half_cycle;
		transparency = static_cast<int>(((half_cycle - fade_out_pos) / half_cycle) * 100);
	}

	transparency = std::clamp(transparency, 0, 100);

	display_image(centered_offset.first, centered_offset.second, transparency);
}