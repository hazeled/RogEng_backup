#include "../RogEng.h"

void re_new_frame()
{
	re_engine_t* engine = re_get_engine();
	re_graphics_frame_start();

	//engine->app.update();

	re_event_loop();
	re_graphics_frame_end();
}