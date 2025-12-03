// Converts a X,Y point from game-space to screen-space. Returns false if not on the screen.
private static bool WorldToScreen(double X, double Y, out Point Result)
{
    var current_camera = Game.Engine.CallFunction("view_get_camera", 0);

    // This is where the camera looks in the world.
    var camera_x = Game.Engine.CallFunction("camera_get_view_x", current_camera).ToInt32();
    var camera_y = Game.Engine.CallFunction("camera_get_view_y", current_camera).ToInt32();

    // This is how much of the world the camera sees (room-space).
    var camera_x_size = Game.Engine.CallFunction("camera_get_view_width", current_camera).ToInt32();
    var camera_y_size = Game.Engine.CallFunction("camera_get_view_height", current_camera).ToInt32();

    var surface_x_size = Game.Engine.CallFunction("surface_get_width", m_LightSurface).ToInt32();
    var surface_y_size = Game.Engine.CallFunction("surface_get_height", m_LightSurface).ToInt32();

    // Out of bounds: Point is not visible by the camera
    if (X < camera_x || Y < camera_y)
    {
        Result = Point.Empty;
        return false;
    }

    // Out of bounds: Point is not visible by the camera
    if (X > (camera_x + camera_x_size) || Y > (camera_y + camera_y_size)) 
    {
        Result = Point.Empty;
        return false;
    }

    // This is the offset in room-coordinates from the top-left of the screen (the room point there)
    // to our light source's origin.
    // We now need to convert to the screen-space, since 1 room pixel may not be one surface pixel.
    int room_offset_x = (int)(X - camera_x);
    int room_offset_y = (int)(Y - camera_y);

    // Compute the scales on the X and Y axis.
    float x_scale = (surface_x_size / (float)camera_x_size);
    float y_scale = (surface_y_size / (float)camera_y_size);

    // Return the scaled offset
    Result = new((int)(room_offset_x * x_scale), (int)(room_offset_y * y_scale));
    return true;
}