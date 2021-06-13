#include "../RogEng.h"

void re_event_loop()
{
   re_event_t event;
   while (!re_event_queue_empty())
   {
      re_poll_event(&event);
      if (event.key.type == KEYDOWN)
      {
         printf("Key pressed! Keycode: %d\n", event.key.key);
      }
   }
}
