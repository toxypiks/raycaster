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
void draw_player_on_minimap(Player *p, RaycastMap *map, int minimap_width, int minimap_height, int width, int height);

#endif // PLAYER_H_
