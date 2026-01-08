#ifndef DRAWING_FUNCTIONS_H_
#define DRAWING_FUNCTIONS_H_

#include "player.h"
#include "raycastmap.h"
#include "raycastray.h"

void draw_minimap(RaycastMap *map, int minimap_width, int minimap_height);

void draw_player_on_minimap(Player *p, RaycastMap *map, int minimap_width, int minimap_height, int width, int height);

void draw_rays_on_minimap(RaycastRay rays[], int num_rays, Player *p, RaycastMap *map, int minimap_width, int minimap_height, int width, int height);

void draw_first_person_view(RaycastRay rays[], int num_rays, int screen_width, int screen_height, int minimap_width, int player_view_width);

#endif // DRAWING_FUNCTIONS_H_
