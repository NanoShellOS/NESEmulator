#pragma once

// NanoShell doesn't support game pads
#if 0

#include <SDL.h>

#define MAX_PADS 2
#define CONTROLLER_KEY_COUNT 10

typedef SDL_Joystick GamePad;
struct JoyPad;

#endif

void init_pads();

//void gamepad_mapper(struct JoyPad* joyPad, SDL_Event* event);
