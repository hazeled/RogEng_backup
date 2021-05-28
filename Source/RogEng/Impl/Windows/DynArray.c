#include "../../../RogEng.h"
#ifdef RE_IMPL_WINDOWS

/* TODO: If the dynamic array's state somehow gets locked in GROWING or DEGROWING,
   any calls to re_dyn_array_grow or re_dyn_array_degrow will hang indefinetly.
   This could possibly be fixed by adding a maximum wait time for the function's
   idleing, but a more elegant solution would be preferable.
*/

// Helper functions exclusive to DynArray.c
static void move_elem(re_dyn_array_t* arr, u32 src, u32 dst)
    { memcpy(re_dynp_access_pointer(arr, src), re_dynp_access_pointer(arr, dst), arr->size); }

// Realloc too unreliable
static void reallocate(void** ptr, size_t size)
{
   void* new_ptr = malloc(size);
}

re_dyn_array_t re_dyn_array_impl_new(size_t size)
{
   re_dyn_array_t retarr = { 0 };
   retarr.grow_length = RE_DEFAULT_DYN_ARRAY_GROW_RATE;
   retarr.size = size;
   retarr.length = 0;
   retarr.length_allocated = RE_DEFAULT_DYN_ARRAY_GROW_RATE;
   retarr.data = calloc(RE_DEFAULT_DYN_ARRAY_GROW_RATE, size);
   retarr.state = IDLE;
   return retarr;
}

void re_dyn_array_impl_free(re_dyn_array_t* arr)
{
   free(arr->data);
}

b8 re_dyn_array_impl_empty(re_dyn_array_t* arr)
{
   if (arr->length == 0)
   {
      return RE_TRUE;
   }
   else
   {
      return RE_FALSE;
   }
}

void re_dyn_array_impl_grow_rate(re_dyn_array_t* arr, u8 rate)
{
   arr->grow_length = rate;
}

void re_dyn_array_impl_grow(re_dyn_array_t* arr)
{
   while (arr->state != IDLE) {};
   arr->state = GROWING;
   // void* new_data = realloc(arr->data, arr->size * (arr->length_allocated + arr->grow_length));
   reallocate(&arr->data, arr->size * (arr->length_allocated + arr->grow_length));
   if (arr->data == NULL)
   {
      RE_THROW_ERROR("Dynamic array out of space!!");
   }
   arr->length_allocated += arr->grow_length;
   arr->state = IDLE;
}

void re_dyn_array_impl_degrow(re_dyn_array_t* arr)
{
   while (arr->state != IDLE) {};
   arr->state = DEGROWING;
   // void* new_data = realloc(arr->data, arr->size * (arr->length_allocated - arr->grow_length));
   reallocate(&arr->data, arr->size * (arr->length_allocated - arr->grow_length));
   if (arr->data == NULL)
   {
      RE_THROW_ERROR("Dynamic array out of space!!");
   }
   arr->length_allocated -= arr->grow_length;
   arr->state = IDLE;
}

void re_dyn_array_impl_push_back(re_dyn_array_t* arr, void* data)
{
   if (arr->length == arr->length_allocated)
   {
      re_dyn_array_impl_grow(arr);
   }
   void* new_data_location = (char*)(arr->data) + (arr->length * arr->size);
   memcpy(new_data_location, &data, arr->size);
   arr->length++;
}

// Near identical copy of push_back except it pushes by reference
void re_dyn_array_impl_push_back_ref(re_dyn_array_t* arr, void* data)
{
   if (arr->length == arr->length_allocated)
   {
      re_dyn_array_impl_grow(arr);
   }
   void* new_data_location = (char*)(arr->data) + (arr->length * arr->size);
   memcpy(new_data_location, data, arr->size);
   arr->length++;
}

void re_dyn_array_impl_pop_back(re_dyn_array_t* arr)
{
   if (arr->length == 0)
   {
      return;
   }
   if (arr->length % arr->grow_length == 0)
   {
      re_dyn_array_impl_degrow(arr);
   }
   arr->length--;
}

void re_dyn_array_impl_remove(re_dyn_array_t* arr, u32 index)
{
   if (arr->length == 0) { return; }

   arr->length--;
   if (index < arr->length)
   {
      for (u32 i = index + 1; i < arr->length; i++)
      {
         move_elem(arr, index, index - 1);
      }
   }
   if (arr->length % arr->grow_length == 0)
   {
      re_dyn_array_impl_degrow(arr);
   }
}

void* re_dyn_array_impl_access(re_dyn_array_t* arr, u32 index)
{
   if (index < 0 || index >= arr->length)
   {
      printf("DynArray: Index out of bounds!!\n");
      return NULL;
   }
   return (char*)arr->data + (index * arr->size);
}

#endif
