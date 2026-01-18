#ifndef DRAWING_FUNCTIONS_H_
#define DRAWING_FUNCTIONS_H_

#include "player.h"
#include "raycastmap.h"
#include "raycastray.h"

void draw_mini_window(RaycastMap *map, int mini_window_width, int mini_window_height);

void draw_player_on_mini_window(Player *p, int mini_window_width, int mini_window_height, int window_width, int window_height);

void draw_rays_on_mini_window(RaycastRay rays[], int num_rays, Player *p, RaycastMap *map, int mini_window_width, int mini_window_height, int window_width, int window_height);

void draw_first_person_view(RaycastRay rays[], int num_rays,
                            int player_view_width, int width, int height);
#endif // DRAWING_FUNCTIONS_H_
