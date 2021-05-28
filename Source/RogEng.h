#pragma once

#pragma region Documentation
/*  RogEng!

    TODO:
        * Write input system documentation

        * Finish rewriting input system

        * Only call update on keypress

        * Document:
            - re_dyn_loop / re_dynp_loop

        *  Some impl functions are pointed to by #define,
           whereas some are pointed to by re_func_void

        * Instead of many different states for dynamic array, have
          a single b8

    Planned:
        * Animation system
        * Map system
        * Sprite/image loading
        * Custom font
        * Entity system

    Before including, in just ONE C++ file, please add the define:

        #define RE_IMPL

    All files include RogEng should simply include the headers without the define

    You can avoid RogEng hijacking main with the define:

        #define RE_NO_HIJACK_MAIN

    However, this is not advised

    Internal functions will not be documented in this comment block. However,
    they may be commented or explain withined this header file by comment
    blocks preceding the function.

    Multiple typedefs are defined throughout this header. Typedefs that are not
    for function pointers are as follows:
        uint8_t     | u8
        uint32_t    | u32
        const char* | cstr
        char    | b8
    Note:
        b8 is used as a boolean type. Use with RE_TRUE and RE_FALSE

    Contents:
        -= Defines =-
            - Settable -
                * RE_IMPL
                * RE_NO_HIJACK_MAIN
                * RE_IMPL_GLFW
            - Preset -
                * RE_TRUE
                * RE_FALSE
        -= Functions =-
            * re_create_engine
            * re_set_engine
            * re_get_engine
            * re_should_close
        -= Structs =-
            * re_dyn_array_t
            * re_app_t
            * re_engine_t

    --- DEFINES ---
    RE_IMPL:
        Tells RogEng that this is a RogEng app and to hijack main
        Main hijacking can be overridden with RE_NO_HIJACK_MAIN

    RE_NO_HIJACK_MAIN:
        Tells RogEng not to hijack main and to allow the app
        to set the main() function.
        You could be able to implement your own main() function,
        however this is NOT reccomended as rogeng handles
        much of the back end work in main(), and the
        app will have to do it itself.

        If you *really* wanted to, a small example is:

            #define RE_IMPL
            #define RE_NO_HIJACK_MAIN
            #include <RogEng.h>

            int main()
            {
                CREATE_APP(app);
                re_engine_t engine;
                re_create_engine(&engine, &app);
                re_set_engine(&engine);
                while (!re_should_close())
                {
                    re_new_frame();
                }
                return 0;
            }

    RE_IMPL_GLFW
        Tells RogEng to use GLFW as a back end for graphics, input, etc.

    RE_TRUE:
        Will always be set to 1. Used with b8.

    RE_FALSE:
        Will always be set to 0. Used with b8.

    --- FUNCTIONS ---
    re_create_engine:
        Returns a filled re_engine_t out of an re_app_t. Unset
        variables will be filled in by the engine. Will also
        fill out everything needed for re_engine_t (e.g
        re_platform, etc)

    re_set_engine:
        This should only be called ONCE. Will set the global
        engine that can be retrieved with re_get_engine. This
        will be called with the default main function, so only
        use if you're defining RE_NO_HIJACK_MAIN

    re_get_engine:
        Returns a re_engine_t pointer to the global engine instance

    re_should_close:
        This is implementation dependant, but most closely mirrors
        glfw's glfwWindowShouldClose() function. Essentially tells
        RogEng if we should shutdown or not.

    --- STRUCTS---
    re_dyn_array_t:
        Dynamic array implementation, can grow or resize as needed.
        Functions and macros that are important to re_dyn_array_t will
        also be covered here.

        - ARGS -
        data:
            A pointer to the data managed by re_dyn_array. Do NOT access
            using this pointer, doing so could have unintended
            consequences and is not supported or implemented

        length:
            Total length of the dynamic array in numer of elements.
            Not in bytes

        length_allocated:
            Length of elements that are allocated, even ones that arent in use

        grow_length:
            How many new elements to create when the dynamic array
            needs to grow in order to support being pushed onto

        size:
            The size of a single element in the dynamic array

        state:
            Internal enum telling RogEng what the dynamic array is currently doing (Used for multithreading)

        - FUNCTIONS / MACROS -

        Each re_dyn_* macro will pass a reference to the dynamic array
        specified by the <arr> argument. If the dynamic array is already
        a pointer, re_dyn_* macros wont work. For dynamic array pointers,
        use re_dynp_* macros

        re_dyn_array_new(type):
            Will create a new dynamic array with the type specified.
            For example, you can create a dynamic array of ints with:

                re_dyn_array_t arr = re_dyn_array_new(int);

        re_dyn_array_delete(arr):
            Will free the memory held by the array and delete the array.
            MUST call before the array goes out of bounds or there
            will be a memory leak.

        re_dyn_array_empty(arr):
            Will return RE_TRUE if the array specified by <arr> is empty,
            otherwise will return RE_FALSE.

        re_dyn_grow_length(arr, length):
            Will set the grow length of the dynamic array to the length
            specified by <length>. The grow length is how much
            the dynamic array grows when push_back is called and it needs
            to be reallocated.

        re_dyn_push_back(arr, val):
            Will push a value to the back of the dynamic array,
            and resize if necessary.

        re_dyn_push_back_ref(arr, val):
            Pushes a value to the back of the dynamic array using
            memcpy, instead of simply pushing by copy. Will reference
            the <val> argument, so make sure to dereference if <val> is
            alreadya pointer, or you'll end up with memory trouble.

            Example (This will pass by reference instead of copying the struct):

                struct s;
                re_dyn_push_back_ref(arr, s);

        re_dyn_pop_back(arr):
            Will remove the value at the back of the dynamic array,
            and resize if necessary.

            Will simply return if the current length of the dynamic
            array is 0.

        re_dyn_access(arr, index, type):
            Returns a variable of type <type> to the data at the
            index specified by <index>.

    re_app_t:
        window_width:
            width of the window that will be created

         window_height:
            height of the window that will be created

        init:
            A function pointer to init code that will be called once on
            start of the app.

        update:
            A function pointer to update code that will be called once
            every frame.

        shutdown:
            A function pointer to shutdown code that will be called once
            on shutdown. Can be called with re_shutdown() function.

        Note:
            The re_main function isnt responsible for returning an
            entire engine context. Everything inside re_app_t is
            what will be set by the user.

    re_engine_t:
        app:
            The re_app_t returned by re_main andfilled out by
            re_create_engine
*/
#pragma endregion

#ifdef __cplusplus
extern "C" {
#endif
// Visual studio tabbing fix
#ifdef false
}
#endif

#pragma region Defines
// =========== Default defines ===========
#define RE_IMPL_GLFW

#ifdef _WIN32
#define RE_IMPL_WINDOWS
#elif _WIN64
#define RE_IMPL_WINDOWS
#elif __APPLE__
#define RE_IMPL_APPLE
#elif __linux__
#define RE_IMPL_LINUX
#endif

#define RE_TRUE  1
#define RE_FALSE 0
#pragma endregion

#pragma region Includes
#include <stdint.h>  // Standard types
#include <stdlib.h>  // Malloc, free
#include <assert.h>  // Assert
#include <string.h>  // Memcpy
#include <stdio.h>   // Printf
#include <stdarg.h>  // va_list

#ifdef RE_IMPL_GLFW
#include <GLFW/glfw3.h>
#endif
#pragma endregion

#pragma region Macros
// =========== Helpful macros ===========
#define      CREATE_APP(...)      re_app_t __VA_ARGS__ = {0}
#define      MEMZERO(...)         memset(__VA_ARGS__, 0, sizeof(__VA_ARGS__))

#define      re_dyn_loop(ARR)     for (u32 i = 0; i < ARR.length; i++)
#define      re_dynp_loop(ARR)    for (u32 i = 0; i < ARR->length; i++)

// Internal macros
#define      RE_THROW_ERROR(MSG) { re_pop_up_message("RogEng Error!", MSG); exit(0); }
#pragma endregion

#pragma region Types and Enums
// =========== Typedefs ===========
typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef const char* cstr; // Const string, not c-string
typedef char        b8;   // Single byte boolean

typedef void (*re_func_void)();
typedef void (*re_func_thread)(va_list args);

typedef enum re_keycode
{
    RE_KEYCODE_INVALID,
    RE_KEYCODE_SPACE,
    RE_KEYCODE_APOSTROPHE,  /* ' */
    RE_KEYCODE_COMMA,  /* , */
    RE_KEYCODE_MINUS,  /* - */
    RE_KEYCODE_PERIOD,  /* . */
    RE_KEYCODE_SLASH,  /* / */
    RE_KEYCODE_0,
    RE_KEYCODE_1,
    RE_KEYCODE_2,
    RE_KEYCODE_3,
    RE_KEYCODE_4,
    RE_KEYCODE_5,
    RE_KEYCODE_6,
    RE_KEYCODE_7,
    RE_KEYCODE_8,
    RE_KEYCODE_9,
    RE_KEYCODE_SEMICOLON,  /* ; */
    RE_KEYCODE_EQUAL,  /* = */
    RE_KEYCODE_A,
    RE_KEYCODE_B,
    RE_KEYCODE_C,
    RE_KEYCODE_D,
    RE_KEYCODE_E,
    RE_KEYCODE_F,
    RE_KEYCODE_G,
    RE_KEYCODE_H,
    RE_KEYCODE_I,
    RE_KEYCODE_J,
    RE_KEYCODE_K,
    RE_KEYCODE_L,
    RE_KEYCODE_M,
    RE_KEYCODE_N,
    RE_KEYCODE_O,
    RE_KEYCODE_P,
    RE_KEYCODE_Q,
    RE_KEYCODE_R,
    RE_KEYCODE_S,
    RE_KEYCODE_T,
    RE_KEYCODE_U,
    RE_KEYCODE_V,
    RE_KEYCODE_W,
    RE_KEYCODE_X,
    RE_KEYCODE_Y,
    RE_KEYCODE_Z,
    RE_KEYCODE_LEFT_BRACKET,  /* [ */
    RE_KEYCODE_BACKSLASH,  /* \ */
    RE_KEYCODE_RIGHT_BRACKET,  /* ] */
    RE_KEYCODE_GRAVE_ACCENT,  /* ` */
    RE_KEYCODE_WORLD_1, /* non-US #1 */
    RE_KEYCODE_WORLD_2, /* non-US #2 */
    RE_KEYCODE_ESC,
    RE_KEYCODE_ENTER,
    RE_KEYCODE_TAB,
    RE_KEYCODE_BACKSPACE,
    RE_KEYCODE_INSERT,
    RE_KEYCODE_DELETE,
    RE_KEYCODE_RIGHT,
    RE_KEYCODE_LEFT,
    RE_KEYCODE_DOWN,
    RE_KEYCODE_UP,
    RE_KEYCODE_PAGE_UP,
    RE_KEYCODE_PAGE_DOWN,
    RE_KEYCODE_HOME,
    RE_KEYCODE_END,
    RE_KEYCODE_CAPS_LOCK,
    RE_KEYCODE_SCROLL_LOCK,
    RE_KEYCODE_NUM_LOCK,
    RE_KEYCODE_PRINT_SCREEN,
    RE_KEYCODE_PAUSE,
    RE_KEYCODE_F1,
    RE_KEYCODE_F2,
    RE_KEYCODE_F3,
    RE_KEYCODE_F4,
    RE_KEYCODE_F5,
    RE_KEYCODE_F6,
    RE_KEYCODE_F7,
    RE_KEYCODE_F8,
    RE_KEYCODE_F9,
    RE_KEYCODE_F10,
    RE_KEYCODE_F11,
    RE_KEYCODE_F12,
    RE_KEYCODE_F13,
    RE_KEYCODE_F14,
    RE_KEYCODE_F15,
    RE_KEYCODE_F16,
    RE_KEYCODE_F17,
    RE_KEYCODE_F18,
    RE_KEYCODE_F19,
    RE_KEYCODE_F20,
    RE_KEYCODE_F21,
    RE_KEYCODE_F22,
    RE_KEYCODE_F23,
    RE_KEYCODE_F24,
    RE_KEYCODE_F25,
    RE_KEYCODE_KP_0,
    RE_KEYCODE_KP_1,
    RE_KEYCODE_KP_2,
    RE_KEYCODE_KP_3,
    RE_KEYCODE_KP_4,
    RE_KEYCODE_KP_5,
    RE_KEYCODE_KP_6,
    RE_KEYCODE_KP_7,
    RE_KEYCODE_KP_8,
    RE_KEYCODE_KP_9,
    RE_KEYCODE_KP_DECIMAL,
    RE_KEYCODE_KP_DIVIDE,
    RE_KEYCODE_KP_MULTIPLY,
    RE_KEYCODE_KP_SUBTRACT,
    RE_KEYCODE_KP_ADD,
    RE_KEYCODE_KP_ENTER,
    RE_KEYCODE_KP_EQUAL,
    RE_KEYCODE_LEFT_SHIFT,
    RE_KEYCODE_LEFT_CONTROL,
    RE_KEYCODE_LEFT_ALT,
    RE_KEYCODE_LEFT_SUPER,
    RE_KEYCODE_RIGHT_SHIFT,
    RE_KEYCODE_RIGHT_CONTROL,
    RE_KEYCODE_RIGHT_ALT,
    RE_KEYCODE_RIGHT_SUPER,
    RE_KEYCODE_MENU,
    RE_KEYCODE_COUNT
} re_keycode;

typedef struct re_app_t
{
    u16          window_width;
    u16          window_height;
    u16          window_fps_max;
    cstr         window_title;
    re_func_void init;
    re_func_void update;
    re_func_void shutdown;
} re_app_t;

#ifdef RE_IMPL_GLFW
typedef struct re_impl_t
{
    u8          GL_VERSION_MAJOR;
    u8          GL_VERSION_MINOR;
    GLFWwindow* window;
} re_impl_t;
#endif

typedef struct re_input_t
{
    b8 key_map[RE_KEYCODE_COUNT];
    b8 last_key_map[RE_KEYCODE_COUNT];
} re_input_t;

// Input structs / enums for internal use
typedef enum re_event_keboard_type_e
{
    KEYDOWN,
    KEYUP,
    REPEAT
} re_event_keyboard_type_e;

typedef struct re_event_keyboard_t
{
    re_event_keyboard_type_e type;
    re_keycode               key;
} re_event_keyboard_t;

typedef struct re_event_t
{
    re_event_keyboard_t key;
} re_event_t; // Internal struct for input polling

typedef struct re_engine_t
{
    re_app_t   app;
    re_impl_t  impl; // Implementation specific struct
    re_input_t input;
} re_engine_t;
#pragma endregion

#pragma region Dynamic Array
// --- Dynamic Array ---
#define RE_DEFAULT_DYN_ARRAY_GROW_RATE 2

typedef enum re_dyn_array_state_e
{
   READING,
   WRITING,
   GROWING,
   DEGROWING,
   IDLE,
} re_dyn_array_state_e;

struct re_dyn_array_t
{
    void*  data;
    u32    length;
    u32    length_allocated;
    u8    grow_length;
    size_t  size;
    re_dyn_array_state_e state;
};
typedef struct  re_dyn_array_t                  re_dyn_array_t;

#define      re_dyn_array_new(TYPE)             re_dyn_array_impl_new(sizeof(TYPE))

#define      re_dyn_array_empty(ARR)            re_dyn_array_impl_empty(&ARR);
#define      re_dyn_array_free(ARR)             re_dyn_array_impl_free(&ARR);
#define      re_dyn_grow_length(ARR, RATE)      re_dyn_array_impl_grow_length(&ARR, RATE)
#define      re_dyn_push_back(ARR, VAL)         re_dyn_array_impl_push_back(&ARR, VAL)
#define      re_dyn_push_back_ref(ARR, VAL)     re_dyn_array_impl_push_back_ref(&ARR, &VAL)
#define      re_dyn_pop_back(ARR)               re_dyn_array_impl_pop_back(&ARR)
#define      re_dyn_remove(ARR, INDEX)          re_dyn_array_impl_remove(&ARR, INDEX)
#define      re_dyn_access(ARR, INDEX, TYPE)    *(TYPE*)(re_dyn_array_impl_access(&ARR, INDEX))
// #define      re_dyn_access_pointer(ARR, INDEX)  re_dyn_array_impl_access(&ARR, INDEX)

#define      re_dynp_array_empty(ARR)           re_dyn_array_impl_empty(ARR);
#define      re_dynp_array_free(ARR)            re_dyn_array_impl_free(ARR);
#define      re_dynp_grow_length(ARR, RATE)     re_dyn_array_impl_grow_length(ARR, RATE)
#define      re_dynp_push_back(ARR, VAL)        re_dyn_array_impl_push_back(ARR, VAL)
#define      re_dynp_push_back_ref(ARR, VAL)    re_dyn_array_impl_push_back_ref(ARR, &VAL)
#define      re_dynp_pop_back(ARR)              re_dyn_array_impl_pop_back(ARR)
#define      re_dynp_remove(ARR, INDEX)         re_dyn_array_impl_remove(ARR, INDEX)
#define      re_dynp_access(ARR, INDEX, TYPE)   *(TYPE*)(re_dyn_array_impl_access(ARR, INDEX))
#define      re_dynp_access_pointer(ARR, INDEX) re_dyn_array_impl_access(ARR, INDEX)

re_dyn_array_t re_dyn_array_impl_new            (size_t size);                     // Implementation dependant
b8           re_dyn_array_impl_empty            (re_dyn_array_t* arr);             // Implementation dependant
void         re_dyn_array_impl_free             (re_dyn_array_t* arr);             // Implementation dependant
void         re_dyn_array_impl_grow_length      (re_dyn_array_t* arr, u8 rate);    // Implementation dependant
void         re_dyn_array_impl_push_back        (re_dyn_array_t* arr, void* data); // Implementation dependant
void         re_dyn_array_impl_push_back_ref    (re_dyn_array_t* arr, void* data); // Implementation dependant
void         re_dyn_array_impl_pop_back         (re_dyn_array_t* arr);             // Implementation dependant
void         re_dyn_array_impl_remove           (re_dyn_array_t* arr, u32 index);  // Implementation dependant
void         re_dyn_array_impl_grow             (re_dyn_array_t* arr);             // Implementation dependant
void         re_dyn_array_impl_degrow           (re_dyn_array_t* arr);             // Implementation dependant
void*        re_dyn_array_impl_access           (re_dyn_array_t* arr, u32 index);  // Implementation dependant
#pragma endregion

#pragma region Engine Functions
void          re_create_engine                  (re_engine_t* engine, re_app_t* app);  // CreateEngine.c
re_engine_t*  re_get_engine                     ();                                    // SetGetEngine.c
void          re_set_engine                     (re_engine_t* engine);                 // SetGetEngine.c
# pragma endregion

#pragma region Window Functions
// Window functions
b8            re_should_close                   ();                           // Implementation dependant
void          re_new_frame                      ();                           // NewFrame.c
# pragma endregion

#pragma region Input
// Input functions
b8           re_key_pressed                     (re_keycode key);            // Input.c
# pragma endregion

#pragma region Events
// Internal event functions
void      re_event_setup                        ();                           // Event.c
b8        re_event_queue_empty                  ();                           // Event.c
b8        re_event_queue_idle                   ();                           // Event.c
void      re_raise_event                        (re_event_t* event);          // Event.c
void      re_poll_event                         (re_event_t* event);          // Event.c
void      re_event_create_key                   (re_event_keyboard_t* key);   // Event.c
void      re_event_loop                         ();                           // EventLoop.c
#pragma endregion

#pragma region Implementation Specific
// Implementation specific defines
#define re_create_thread(func, ...)                  re_impl_create_thread_void(func, __VA_ARGS__);

// Implementation-specific functions
#pragma region Windows
#ifdef RE_IMPL_WINDOWS
void       re_impl_create_thread_void                (re_func_thread func, ...);
// Internal function to pop up a message, mostly used for errors
void       re_impl_pop_up_message                    (unsigned short* title, unsigned short* msg);
#define    re_pop_up_message(TITLE, MSG)             re_impl_pop_up_message(L ## TITLE, L ## MSG);
#endif
#pragma endregion
#pragma region GLFW
#ifdef RE_IMPL_GLFW
void       re_glfw_init                         ();                           // Impl/GLFW/GLFW.c
void       re_glfw_frame_start                  ();                           // Impl/GLFW/GLFW.c
void       re_glfw_frame_end                    ();                           // Impl/GLFW/GLFW.c
re_keycode re_glfw_to_keycode                   (u32 code);                   // Impl/GLFW/GLFW.c

static re_func_void re_graphics_init            = re_glfw_init;               // Avoid having to use ifdefs for each Implementation
static re_func_void re_graphics_frame_start     = re_glfw_frame_start;        // Instead, have re_init_graphics point to whatever the
static re_func_void re_graphics_frame_end       = re_glfw_frame_end;          // current graphics Implementation is.
#endif
# pragma endregion
# pragma endregion

#pragma region Default Functions
// Default app functions
static void    re_app_default_init     ()  { printf("Init");     };
static void    re_app_default_update   ()  { printf("Update");   };
static void    re_app_default_shutdown ()  { printf("Shutdown"); };
#pragma endregion

#pragma region Entry Point
// =========== ENTRY POINT ===========
void      re_entry_point    (int argc, char** argv, re_app_t app);  // Main.c
extern re_app_t re_main        (int argc, char** argv); // Defined by user

#ifdef RE_IMPL
#ifndef RE_NO_HIJACK_MAIN
int main(int argc, char** argv)
{
    re_app_t app = re_main(argc, argv);
    re_entry_point(argc, argv, app);
}
#endif
#endif
#pragma endregion

#ifdef __cplusplus
}
#endif
