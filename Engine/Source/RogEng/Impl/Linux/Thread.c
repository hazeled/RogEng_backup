#include "../../../RogEng.h"

#ifdef RE_IMPL_LINUX

#include <stdarg.h>
#include <pthread.h>

void re_impl_create_thread_void(re_func_thread func, void* args)
{
    pthread_t thread_id;
    pthread_create(&thread_id , NULL, func, NULL);
    pthread_detach(thread_id);
}

#endif
