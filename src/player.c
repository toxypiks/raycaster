#include "player.h"
#include "raylib.h"

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

void draw_player_on_minimap(Player *p, RaycastMap *map, int minimap_width, int minimap_height, int width, int height)
{
    float cell_w = (float)minimap_width / map->width;
    float cell_h = (float)minimap_height / map->height;

    float player_map_x = (p->x / width) * map->width;
    float player_map_y = (p->y / height) * map->height;

    DrawCircle((int)(player_map_x * cell_w), (int)(player_map_y * cell_h), 5, GREEN);
}
