#include <nanoshell/nanoshell.h>
#include "controller.h"
#include "gamepad.h"
#include "touchpad.h"


void init_joypad(struct JoyPad* joyPad, uint8_t player){
    joyPad->strobe = 0;
    joyPad->index = 0;
    joyPad->status = 0;
    joyPad->player = player;
}


uint8_t read_joypad(struct JoyPad* joyPad){
    if(joyPad->index > 7)
        return 1;
    uint8_t val = (joyPad->status & (1 << joyPad->index)) != 0;
    if(!joyPad->strobe)
        joyPad->index++;
    return val;
}


void write_joypad(struct JoyPad* joyPad, uint8_t data){
    joyPad->strobe = data & 1;
    if(joyPad->strobe)
        joyPad->index = 0;
}

void keyboard_mapper(struct JoyPad* joyPad, int eventType, long parm1, UNUSED long parm2) {
	if (eventType != EVENT_KEYRAW)
		return;
	
	int isRelease = parm1 & 0x80; // whether it's pressed or released
	int code = parm1 & 0x7F; // the key code
	
    uint16_t key = 0;
    switch (code) {
        case KEY_ARROW_RIGHT:
            key = RIGHT;
            break;
        case KEY_ARROW_LEFT:
            key = LEFT;
            break;
        case KEY_ARROW_DOWN:
            key = DOWN;
            break;
        case KEY_ARROW_UP:
            key = UP;
            break;
        case KEY_ENTER:
            key = START;
            break;
        case KEY_LSHIFT:
        case KEY_Z:
            key = SELECT;
            break;
        case KEY_C:
            key = BUTTON_A;
            break;
        case KEY_X:
            key = BUTTON_B;
            break;
        case KEY_Q:
            key = TURBO_B;
            break;
        case KEY_W:
            key = TURBO_A;
            break;
    }
	
	if (!key) return;
	
    if(isRelease) {
        joyPad->status &= ~key;
        if(key == TURBO_A) {
            // clear button A
            joyPad->status &= ~BUTTON_A;
        }
        if(key == TURBO_B) {
            // clear button B
            joyPad->status &= ~BUTTON_B;
        }
    } else {
        joyPad->status |= key;
        if(key == TURBO_A) {
            // set button A
            joyPad->status |= BUTTON_A;
        }
        if(key == TURBO_B) {
            // set button B
            joyPad->status |= BUTTON_B;
        }
    }
}

//void update_joypad(struct JoyPad* joyPad, SDL_Event* event){
void update_joypad(struct JoyPad* joyPad, int eventType, long parm1, long parm2){
    keyboard_mapper(joyPad, eventType, parm1, parm2);
    //gamepad_mapper(joyPad, eventType, parm1, parm2);
}

void turbo_trigger(struct JoyPad* joyPad){
    // toggle BUTTON_A AND BUTTON_B if TURBO_A and TURBO_B are set respectively
    joyPad->status ^= joyPad->status >> 8;
}