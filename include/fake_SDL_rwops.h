#pragma once

#include <stdio.h>

typedef FILE SDL_RWops;

#define SDL_RWFromFile(fn, mod) fopen(fn, mod)
#define SDL_RWread(ctx, ptr, sz, max) fread(ptr, sz, max, ctx)
#define SDL_RWclose(ctx) fclose(ctx)
