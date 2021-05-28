#include "../RogEng.h"

b8 re_key_pressed(re_keycode key)
{
	re_engine_t* engine = re_get_engine();
	if (engine->input.key_map[key] == RE_TRUE)
	{
		return RE_TRUE;
	}
	return RE_FALSE;
}
