#ifndef RAYCASTRAY_H_
#define RAYCASTRAY_H_

#include "player.h"
#include "raycastmap.h"

typedef struct {
    float x;
    float y;
    float dist;
    int hit;
} RaycastRay;

void cast_rays(RaycastMap *map, Player *p, int num_rays, RaycastRay rays[], int screen_width, int screen_height);

void draw_rays_on_minimap(RaycastRay rays[], int num_rays, Player *p, RaycastMap *map, int minimap_width, int minimap_height, int width, int height);

void draw_first_person_view(RaycastRay rays[], int num_rays, int screen_width, int screen_height, int minimap_width, int player_view_width);

#endif // RAYCASTRAY_H_
