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

char re_key_to_char(re_keycode key)
{
   char ret;
   switch (re_keycode)
   {
   case RE_KEYCODE_SPACE: ret = ' ';
   case RE_KEYCODE_APOSTROPHE: ret = '\'';
   case RE_KEYCODE_COMMA: ret = ',';
   case RE_KEYCODE_MINUS: ret = '-';
   case RE_KEYCODE_PERIOD: ret = '.';
   case RE_KEYCODE_SLASH: ret = '/';
   case RE_KEYCODE_0: ret = '0';
   case RE_KEYCODE_1: ret = '1';
   case RE_KEYCODE_2: ret = '2';
   case RE_KEYCODE_3: ret = '3';
   case RE_KEYCODE_4: ret = '4';
   case RE_KEYCODE_5: ret = '5';
   case RE_KEYCODE_6: ret = '6';
   case RE_KEYCODE_7: ret = '7';
   case RE_KEYCODE_8: ret = '8';
   case RE_KEYCODE_9: ret = '9';
   case RE_KEYCODE_SEMICOLON: ret = ';';
   case RE_KEYCODE_EQUAL: ret = '=';
   case RE_KEYCODE_A: ret = 'A';
   case RE_KEYCODE_B: ret = 'B';
   case RE_KEYCODE_C: ret = 'C';
   case RE_KEYCODE_D: ret = 'D';
   case RE_KEYCODE_E: ret = 'E';
   case RE_KEYCODE_F: ret = 'F';
   case RE_KEYCODE_G: ret = 'G';
   case RE_KEYCODE_H: ret = 'H';
   case RE_KEYCODE_I: ret = 'I';
   case RE_KEYCODE_J: ret = 'J';
   case RE_KEYCODE_K: ret = 'K';
   case RE_KEYCODE_L: ret = 'L';
   case RE_KEYCODE_M: ret = 'M';
   case RE_KEYCODE_N: ret = 'N';
   case RE_KEYCODE_O: ret = 'O';
   case RE_KEYCODE_P: ret = 'P';
   case RE_KEYCODE_Q: ret = 'Q';
   case RE_KEYCODE_R: ret = 'R';
   case RE_KEYCODE_S: ret = 'S';
   case RE_KEYCODE_T: ret = 'T';
   case RE_KEYCODE_U: ret = 'U';
   case RE_KEYCODE_V: ret = 'V';
   case RE_KEYCODE_W: ret = 'W';
   case RE_KEYCODE_X: ret = 'X';
   case RE_KEYCODE_Y: ret = 'Y';
   case RE_KEYCODE_Z: ret = 'Z';
   case RE_KEYCODE_LEFT_BRACKET: ret = '[';
   case RE_KEYCODE_BACKSLASH: ret = '\\';
   case RE_KEYCODE_RIGHT_BRACKET: ret = ']';
   case RE_KEYCODE_GRAVE_ACCENT: ret = '`';
   case RE_KEYCODE_ENTER: ret = '\n';
   case RE_KEYCODE_TAB: ret = '\t'
   }
   // Check if shift or caps lock?
   return ret;
}
