#ifndef INPUTCALLBACKS_H
#define INPUTCALLBACKS_H


#include <vector>


using namespace std;


#define KEY_A				0x0000
#define KEY_B				0x0001
#define KEY_C				0x0002
#define KEY_D				0x0003
#define KEY_E				0x0004
#define KEY_F				0x0005
#define KEY_G				0x0006
#define KEY_H				0x0007
#define KEY_I				0x0008
#define KEY_J				0x0009
#define KEY_K				0x000a
#define KEY_L				0x000b
#define KEY_M				0x000c
#define KEY_N				0x000d
#define KEY_O				0x000e
#define KEY_P				0x000f
#define KEY_Q				0x0010
#define KEY_R				0x0011
#define KEY_S				0x0012
#define KEY_T				0x0013
#define KEY_U				0x0014
#define KEY_V				0x0015
#define KEY_W				0x0016
#define KEY_X				0x0017
#define KEY_Y				0x0018
#define KEY_Z				0x0019
#define KEY_ESC				0x001a
#define KEY_F1				0x001b
#define KEY_F2				0x001c
#define KEY_F3				0x001d
#define KEY_F4				0x001e
#define KEY_F5				0x001f
#define KEY_F6				0x0020
#define KEY_F7				0x0021
#define KEY_F8				0x0022
#define KEY_F9				0x0023
#define KEY_F10				0x0024
#define KEY_F11				0x0025
#define KEY_F12				0x0026
#define KEY_TILDE			0x0027
#define KEY_1				0x0028
#define KEY_2				0x0029
#define KEY_3				0x002a
#define KEY_4				0x002b
#define KEY_5				0x002c
#define KEY_6				0x002d
#define KEY_7				0x002e
#define KEY_8				0x002f
#define KEY_9				0x0030
#define KEY_0				0x0031
#define KEY_MINUS			0x0032
#define KEY_EQUAL			0x0033
#define KEY_BACKSPACE		0x0034
#define KEY_LEFTBRACKET		0x0035
#define KEY_RIGHTBRACKET	0x0036
#define KEY_BACKSLASH		0x0037
#define KEY_SEMICOLON		0x0038
#define KEY_SINGLEQUOTE		0x0039
#define KEY_RETURN			0x003a
#define KEY_COMMA			0x003b
#define KEY_PERIOD			0x003c
#define KEY_FOWARDSLASH		0x003d
#define KEY_SPACE			0x003e
#define KEY_LEFT			0x003f
#define KEY_RIGHT			0x0040
#define KEY_UP				0x0041
#define KEY_DOWN			0x0042
#define KEY_INSERT			0x0043
#define KEY_DELETE			0x0044
#define KEY_HOME			0x0045
#define KEY_END				0x0046
#define KEY_PAGEUP			0x0047
#define KEY_PAGEDOWN		0x0048

#define MOUSE_LEFT			0x0001
#define MOUSE_RIGHT			0x0002
#define MOUSE_MIDDLE		0x0003


void KeyboardUpdateCallback(unsigned char key, int x, int y);
void KeyboardSpecialUpdateCallback(int key, int x, int y);
void MouseButtonUpdateCallback(int button, int state, int x, int y);
void MouseMoveUpdateCallback(int x, int y);


#endif // INPUTCALLBACKS_H