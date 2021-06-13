// === Program entry point ===

#include "../RogEng.h"

void re_entry_point(int argc, char** argv, re_app_t app)
{
	re_engine_t engine;
	re_create_engine(&engine, &app);
	re_set_engine(&engine);
	re_graphics_init();
	re_event_setup();

	engine.app.init();
	while (!re_should_close())
	{
		re_new_frame();
	}
	engine.app.shutdown();

	// re_shutdown();
}
