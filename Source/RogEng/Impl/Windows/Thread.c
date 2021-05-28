#include "../../../RogEng.h"

#ifdef RE_IMPL_WINDOWS
#include <stdarg.h>
#include <Windows.h>

// Internal thread struct
struct thread_info_t
{
   re_func_thread func;
   va_list args;
};
typedef struct thread_info_t thread_info_t;

// Internal thread wrapper
unsigned long __stdcall create_thread(void* thread_info_void)
{
   thread_info_t* thread_info = thread_info_void;
   thread_info->func(thread_info->args);
   va_end(thread_info->args);
   free(thread_info);
}

void re_impl_create_thread_void(re_func_thread func, ...)
{
   va_list args;
   va_start(args, func);

   thread_info_t* thread_info = malloc(sizeof(thread_info_t));
   thread_info->func = func;
   thread_info->args = args;

   CreateThread(NULL, 0, create_thread, thread_info, NULL, NULL);
}
#endif
