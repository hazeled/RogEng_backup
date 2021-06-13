#include "../../../RogEng.h"

#ifdef RE_IMPL_GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>

// Multithreaded key callback function
static void multithreaded_key_callback(va_list args)
{
   // GLFWwindow* window;
   // int key, scancode, action, mods;
   GLFWwindow* window = va_arg(args, GLFWwindow*);
   int key      = va_arg(args, int);
   int scancode = va_arg(args, int);
   int action   = va_arg(args, int);
   int mods     = va_arg(args, int);

   while (!re_event_queue_idle()) {}; // Wait until thread isnt being written to

   // Construct re_event_keyboard_t
   re_event_keyboard_t event = { 0 };
   if      (action == GLFW_PRESS)   { event.type = KEYDOWN; }
   else if (action == GLFW_RELEASE) { event.type = KEYUP; }
   else if (action == GLFW_REPEAT)  { event.type = REPEAT; }
   event.key = re_glfw_to_keycode(key);
   re_event_create_key(&event);
}

// GLFW key callback function
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   re_create_thread(multithreaded_key_callback, window, key, scancode, action, mods);
}

void re_glfw_init()
{
   re_engine_t* engine = re_get_engine();

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, engine->impl.GL_VERSION_MAJOR);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, engine->impl.GL_VERSION_MINOR);

   if (!glfwInit())
   {
      // Glfw initialization failed
      printf("GLFW initalization failed!");
      exit(0);
   }

   engine->impl.window = glfwCreateWindow(engine->app.window_width, engine->app.window_height, engine->app.window_title, NULL, NULL);
   if (!engine->impl.window)
   {
      printf("GLFW window creation failed!");
      exit(0);
   }

   glfwSetKeyCallback(engine->impl.window, key_callback);

   glfwSwapInterval(1);
}

b8 re_should_close()
{
   re_engine_t* engine = re_get_engine();
   return glfwWindowShouldClose(engine->impl.window);
}

void re_glfw_frame_start()
{
   re_engine_t* engine = re_get_engine();
}

void re_glfw_frame_end()
{
   re_engine_t* engine = re_get_engine();
   glfwSwapBuffers(engine->impl.window);
   glfwPollEvents();
}

re_keycode re_glfw_to_keycode(u32 code)
{
    switch (code)
    {
    case GLFW_KEY_A:                return RE_KEYCODE_A; break;
    case GLFW_KEY_B:                return RE_KEYCODE_B; break;
    case GLFW_KEY_C:                return RE_KEYCODE_C; break;
    case GLFW_KEY_D:                return RE_KEYCODE_D; break;
    case GLFW_KEY_E:                return RE_KEYCODE_E; break;
    case GLFW_KEY_F:                return RE_KEYCODE_F; break;
    case GLFW_KEY_G:                return RE_KEYCODE_G; break;
    case GLFW_KEY_H:                return RE_KEYCODE_H; break;
    case GLFW_KEY_I:                return RE_KEYCODE_I; break;
    case GLFW_KEY_J:                return RE_KEYCODE_J; break;
    case GLFW_KEY_K:                return RE_KEYCODE_K; break;
    case GLFW_KEY_L:                return RE_KEYCODE_L; break;
    case GLFW_KEY_M:                return RE_KEYCODE_M; break;
    case GLFW_KEY_N:                return RE_KEYCODE_N; break;
    case GLFW_KEY_O:                return RE_KEYCODE_O; break;
    case GLFW_KEY_P:                return RE_KEYCODE_P; break;
    case GLFW_KEY_Q:                return RE_KEYCODE_Q; break;
    case GLFW_KEY_R:                return RE_KEYCODE_R; break;
    case GLFW_KEY_S:                return RE_KEYCODE_S; break;
    case GLFW_KEY_T:                return RE_KEYCODE_T; break;
    case GLFW_KEY_U:                return RE_KEYCODE_U; break;
    case GLFW_KEY_V:                return RE_KEYCODE_V; break;
    case GLFW_KEY_W:                return RE_KEYCODE_W; break;
    case GLFW_KEY_X:                return RE_KEYCODE_X; break;
    case GLFW_KEY_Y:                return RE_KEYCODE_Y; break;
    case GLFW_KEY_Z:                return RE_KEYCODE_Z; break;
    case GLFW_KEY_LEFT_SHIFT:       return RE_KEYCODE_LEFT_SHIFT; break;
    case GLFW_KEY_RIGHT_SHIFT:      return RE_KEYCODE_RIGHT_SHIFT; break;
    case GLFW_KEY_LEFT_ALT:         return RE_KEYCODE_LEFT_ALT; break;
    case GLFW_KEY_RIGHT_ALT:        return RE_KEYCODE_RIGHT_ALT; break;
    case GLFW_KEY_LEFT_CONTROL:     return RE_KEYCODE_LEFT_CONTROL; break;
    case GLFW_KEY_RIGHT_CONTROL:    return RE_KEYCODE_RIGHT_CONTROL; break;
    case GLFW_KEY_BACKSPACE:        return RE_KEYCODE_BACKSPACE; break;
    case GLFW_KEY_BACKSLASH:        return RE_KEYCODE_BACKSLASH; break;
    case GLFW_KEY_SLASH:            return RE_KEYCODE_SLASH; break;
    case GLFW_KEY_GRAVE_ACCENT:     return RE_KEYCODE_GRAVE_ACCENT; break;
    case GLFW_KEY_COMMA:            return RE_KEYCODE_COMMA; break;
    case GLFW_KEY_PERIOD:           return RE_KEYCODE_PERIOD; break;
    case GLFW_KEY_ESCAPE:           return RE_KEYCODE_ESC; break;
    case GLFW_KEY_SPACE:            return RE_KEYCODE_SPACE; break;
    case GLFW_KEY_LEFT:             return RE_KEYCODE_LEFT; break;
    case GLFW_KEY_UP:               return RE_KEYCODE_UP; break;
    case GLFW_KEY_RIGHT:            return RE_KEYCODE_RIGHT; break;
    case GLFW_KEY_DOWN:             return RE_KEYCODE_DOWN; break;
    case GLFW_KEY_0:                return RE_KEYCODE_0; break;
    case GLFW_KEY_1:                return RE_KEYCODE_1; break;
    case GLFW_KEY_2:                return RE_KEYCODE_2; break;
    case GLFW_KEY_3:                return RE_KEYCODE_3; break;
    case GLFW_KEY_4:                return RE_KEYCODE_4; break;
    case GLFW_KEY_5:                return RE_KEYCODE_5; break;
    case GLFW_KEY_6:                return RE_KEYCODE_6; break;
    case GLFW_KEY_7:                return RE_KEYCODE_7; break;
    case GLFW_KEY_8:                return RE_KEYCODE_8; break;
    case GLFW_KEY_9:                return RE_KEYCODE_9; break;
    case GLFW_KEY_KP_0:             return RE_KEYCODE_KP_0; break;
    case GLFW_KEY_KP_1:             return RE_KEYCODE_KP_1; break;
    case GLFW_KEY_KP_2:             return RE_KEYCODE_KP_2; break;
    case GLFW_KEY_KP_3:             return RE_KEYCODE_KP_3; break;
    case GLFW_KEY_KP_4:             return RE_KEYCODE_KP_4; break;
    case GLFW_KEY_KP_5:             return RE_KEYCODE_KP_5; break;
    case GLFW_KEY_KP_6:             return RE_KEYCODE_KP_6; break;
    case GLFW_KEY_KP_7:             return RE_KEYCODE_KP_7; break;
    case GLFW_KEY_KP_8:             return RE_KEYCODE_KP_8; break;
    case GLFW_KEY_KP_9:             return RE_KEYCODE_KP_9; break;
    case GLFW_KEY_CAPS_LOCK:        return RE_KEYCODE_CAPS_LOCK; break;
    case GLFW_KEY_DELETE:           return RE_KEYCODE_DELETE; break;
    case GLFW_KEY_END:              return RE_KEYCODE_END; break;
    case GLFW_KEY_F1:               return RE_KEYCODE_F1; break;
    case GLFW_KEY_F2:               return RE_KEYCODE_F2; break;
    case GLFW_KEY_F3:               return RE_KEYCODE_F3; break;
    case GLFW_KEY_F4:               return RE_KEYCODE_F4; break;
    case GLFW_KEY_F5:               return RE_KEYCODE_F5; break;
    case GLFW_KEY_F6:               return RE_KEYCODE_F6; break;
    case GLFW_KEY_F7:               return RE_KEYCODE_F7; break;
    case GLFW_KEY_F8:               return RE_KEYCODE_F8; break;
    case GLFW_KEY_F9:               return RE_KEYCODE_F9; break;
    case GLFW_KEY_F10:              return RE_KEYCODE_F10; break;
    case GLFW_KEY_F11:              return RE_KEYCODE_F11; break;
    case GLFW_KEY_F12:              return RE_KEYCODE_F12; break;
    case GLFW_KEY_HOME:             return RE_KEYCODE_HOME; break;
    case GLFW_KEY_EQUAL:            return RE_KEYCODE_EQUAL; break;
    case GLFW_KEY_MINUS:            return RE_KEYCODE_MINUS; break;
    case GLFW_KEY_LEFT_BRACKET:     return RE_KEYCODE_LEFT_BRACKET; break;
    case GLFW_KEY_RIGHT_BRACKET:    return RE_KEYCODE_RIGHT_BRACKET; break;
    case GLFW_KEY_SEMICOLON:        return RE_KEYCODE_SEMICOLON; break;
    case GLFW_KEY_ENTER:            return RE_KEYCODE_ENTER; break;
    case GLFW_KEY_INSERT:           return RE_KEYCODE_INSERT; break;
    case GLFW_KEY_PAGE_UP:          return RE_KEYCODE_PAGE_UP; break;
    case GLFW_KEY_PAGE_DOWN:        return RE_KEYCODE_PAGE_DOWN; break;
    case GLFW_KEY_NUM_LOCK:         return RE_KEYCODE_NUM_LOCK; break;
    case GLFW_KEY_TAB:              return RE_KEYCODE_TAB; break;
    case GLFW_KEY_KP_MULTIPLY:      return RE_KEYCODE_KP_MULTIPLY; break;
    case GLFW_KEY_KP_DIVIDE:        return RE_KEYCODE_KP_DIVIDE; break;
    case GLFW_KEY_KP_ADD:           return RE_KEYCODE_KP_ADD; break;
    case GLFW_KEY_KP_SUBTRACT:      return RE_KEYCODE_KP_SUBTRACT; break;
    case GLFW_KEY_KP_ENTER:         return RE_KEYCODE_KP_ENTER; break;
    case GLFW_KEY_KP_DECIMAL:       return RE_KEYCODE_KP_DECIMAL; break;
    case GLFW_KEY_PAUSE:            return RE_KEYCODE_PAUSE; break;
    case GLFW_KEY_PRINT_SCREEN:     return RE_KEYCODE_PRINT_SCREEN; break;
    default:                        return RE_KEYCODE_COUNT; break;
    }

    // Shouldn't reach here
    return RE_KEYCODE_COUNT;
}

#endif
