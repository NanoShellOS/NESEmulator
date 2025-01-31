#include <nanoshell/nanoshell.h>

#include "gfx.h"
#include "utils.h"
#include "font.h"

#ifdef __ANDROID__
#include "touchpad.h"
#endif

void run_one_frame(struct Emulator* emu);
void do_keyboard_input(struct Emulator* emu, int eventType, long parm1, long parm2);

void graphics_wnd_proc(Window* window, int eventType, long parm1, long parm2)
{
	struct Emulator* emu = (struct Emulator*) GetWindowData(window);
	
	switch (eventType)
	{
		case EVENT_USER:
			run_one_frame(emu);
			break;
		
		case EVENT_KEYRAW:
			do_keyboard_input(emu, eventType, parm1, parm2);
			break;
		
		default:
			DefaultWindowProc(window, eventType, parm1, parm2);
			break;
	}
}


void get_graphics_context(GraphicsContext* ctx, struct Emulator* emul){

    //SDL_Init(SDL_INIT_EVERYTHING);
    //TTF_Init();
	
    //SDL_RWops* rw = SDL_RWFromMem(font_data, sizeof(font_data));
    //ctx->font = TTF_OpenFontRW(rw, 1, 11);
    //if(ctx->font == NULL){
    //    LOG(ERROR, SDL_GetError());
    //}
    ctx->window = CreateWindow(
        "NES Emulator",
        CW_AUTOPOSITION,
        CW_AUTOPOSITION,
        ctx->width * (int)ctx->scale,
        ctx->height * (int)ctx->scale,
		graphics_wnd_proc,
		0
    );

    if(ctx->window == NULL){
        LOG(ERROR, "Error while creating window");
        quit(EXIT_FAILURE);
    }

	SetWindowData (ctx->window, emul);
	
	// also add a timer that will update like every ms.  We don't *actually* need to update
	// every ms, but doing it this way ensures a little bit of consistency, I hope
	AddTimer(ctx->window, 1, EVENT_USER);

    LOG(DEBUG, "Initialized nanoshell subsystem");
}

void render_graphics(GraphicsContext* g_ctx, const uint32_t* buffer){
	Image img;
	img.width = g_ctx->width;
	img.height = g_ctx->height;
	img.framebuffer = buffer;
	
	VidBlitImageResize(&img, 0, 0, g_ctx->width * (int)g_ctx->scale, g_ctx->height * (int)g_ctx->scale);
}

void free_graphics(UNUSED GraphicsContext* ctx){
    //TTF_CloseFont(ctx->font);
    //TTF_Quit();
    //SDL_DestroyTexture(ctx->texture);
    //SDL_DestroyRenderer(ctx->renderer);
    //SDL_DestroyWindow(ctx->window);
    //SDL_CloseAudioDevice(ctx->audio_device);
    //SDL_Quit();
    //LOG(DEBUG, "Graphics clean up complete");
	
	// note: window automatically cleans itself up upon the last HandleMessages() call (emulator.c)
}
