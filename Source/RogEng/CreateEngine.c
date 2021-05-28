#include "../RogEng.h"

void re_create_engine(re_engine_t* engine, re_app_t* app)
{
	engine->app = *app;

	// Fill out engine->app and replace default descriptors 
	if (engine->app.window_height == 0)  { engine->app.window_height = 100;      }
	if (engine->app.window_width == 0)   { engine->app.window_width = 100;       }
	if (engine->app.window_title == 0)   { engine->app.window_title = "RogEng!"; }
	if (engine->app.window_fps_max == 0) { engine->app.window_fps_max = 60;      }
	if (engine->app.init == 0)     { engine->app.init     = re_app_default_init; }
	if (engine->app.update == 0)   { engine->app.update   = re_app_default_init; }
	if (engine->app.shutdown == 0) { engine->app.shutdown = re_app_default_init; }

	MEMZERO(engine->input.key_map);
	MEMZERO(engine->input.last_key_map);
}