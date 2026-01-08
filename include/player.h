#ifndef PLAYER_H_
#define PLAYER_H_

#include "raycastmap.h"
#include <math.h>

typedef struct Player {
    float x;
    float y;
    float dir_x;
    float dir_y;
    float angle;
} Player;

int is_wall(RaycastMap *map, Player p, float player_radius, int screen_width, int screen_height);

#endif // PLAYER_H_
