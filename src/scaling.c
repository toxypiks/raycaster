#include "scaling.h"

/* world -> map */
int world_to_map_x(float world_x, TileSize tile)
{
    return (int)(world_x / tile.w);
}

int world_to_map_y(float world_y, TileSize tile)
{
    return (int)(world_y / tile.h);
}

/* map -> world (e.g. Tile center) */
float map_to_world_x(int map_x, TileSize tile)
{
    return map_x * tile.w + tile.w * 0.5f;
}

float map_to_world_y(int map_y, TileSize tile)
{
    return map_y * tile.h + tile.h * 0.5f;
}

/* map -> minimap */
float map_to_minimap_x(int map_x, MinimapTileSize tile)
{
    return map_x * tile.w;
}

float map_to_minimap_y(int map_y, MinimapTileSize tile)
{
    return map_y * tile.h;
}
