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

#endif // RAYCASTRAY_H_
