#include "../RogEng.h"

static re_engine_t* global_engine = NULL;

re_engine_t* re_get_engine()
{
	assert(global_engine != NULL);
	return global_engine;
}

void re_set_engine(re_engine_t* engine)
{
	assert(global_engine == NULL);
	global_engine = (re_engine_t*)malloc(sizeof(re_engine_t));
	if (global_engine != NULL)
	{
		memcpy(global_engine, engine, sizeof(re_engine_t));
	}
}