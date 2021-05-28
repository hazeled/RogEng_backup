#include "../../../RogEng.h"

#ifdef RE_IMPL_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void re_impl_pop_up_message(unsigned short* title, unsigned short* msg)
{
   MessageBox(NULL,
              msg,
              title,
              MB_OK);
}

#endif // RE_IMPL_WINDOWS
