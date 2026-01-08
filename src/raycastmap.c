#include "raycastmap.h"
#include "raylib.h"

RaycastMap *create_raycastmap(int width, int height)
{
    RaycastMap *rm = malloc(sizeof(RaycastMap));
    if (!rm) return NULL;

    rm->width = width;
    rm->height = height;
    rm->cells = malloc(height*sizeof(int*));
    if (!rm->cells) {
        free(rm);
        return NULL;
    }
    for (int y = 0; y < height; ++y) {
        rm->cells[y] = malloc(width*sizeof(int));
    }
    return rm;
}

void initialize_map(RaycastMap *map)
{
    int tmp[10][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,1,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}};

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            map->cells[y][x] = tmp[y][x];
        }
    }
}

void draw_minimap(RaycastMap *map, int minimap_width, int minimap_height)
{
    float cellsize_x = (float)minimap_width / map->width;
    float cellsize_y = (float)minimap_height / map->height;

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->cells[y][x] == 1) {
                DrawRectangle(
                    x * cellsize_x,
                    y * cellsize_y,
                    cellsize_x,
                    cellsize_y,
                    DARKGRAY
                );
            }
        }
    }
}
