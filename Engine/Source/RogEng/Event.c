#include "../RogEng.h"

re_dyn_array_t event_queue;

void re_event_setup()
{
    event_queue = re_dyn_array_new(re_event_t);
}

b8 re_event_queue_empty()
{
    return re_dyn_array_empty(event_queue);
}

b8 re_event_queue_idle()
{
   if (event_queue.state == IDLE)
   {
      return RE_TRUE;
   }
   return RE_FALSE;
}

// Add event to event queue
void re_raise_event(re_event_t* event)
{
    re_dyn_push_back_ref(event_queue, event);
}

void re_poll_event(re_event_t* event)
{
    *event = re_dyn_access(event_queue, 0, re_event_t);
    re_dyn_pop_front(event_queue);
}

void re_event_create_key(re_event_keyboard_t* key)
{
   re_event_t event = { 0 };
   event.key = *key;
   re_dyn_push_back_ref(event_queue, event);
}
