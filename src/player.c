#include "player.h"

int is_wall(RaycastMap *map, Player p, float player_radius,
               int screen_width, int screen_height)
{
    float cell_w = (float)screen_width / map->width;
    float cell_h = (float)screen_height / map->height;

    int cell_x = (int)(p.x / cell_w);
    int cell_y = (int)(p.y / cell_h);

    int left   = (int)((p.x - player_radius) / cell_w);
    int right  = (int)((p.x + player_radius) / cell_w);
    int top    = (int)((p.y - player_radius) / cell_h);
    int bottom = (int)((p.y + player_radius) / cell_h);

    if (left < 0 || right >= map->width ||
        top < 0 || bottom >= map->height)
        return 1;

    if (map->cells[top][left] == 1 ||
        map->cells[top][right] == 1 ||
        map->cells[bottom][left] == 1 ||
        map->cells[bottom][right] == 1)
        return 1;

    return 0;
}
