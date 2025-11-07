#ifndef	SIB_H
#define	SIB_H

#include	"SIB_includes.h"

void print_signature();
void game_cleanup       (Engine *engine, int exit_status);
bool sdl_initialize     (Engine *engine);
void draw_triangle	(Engine engine, triangle t, int r, int g, int b, int a);

#endif
