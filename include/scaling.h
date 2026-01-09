#ifndef SCALING_H_
#define SCALING_H_

typedef struct {
    float w;
    float h;
} TileSize;

typedef struct {
    float w;
    float h;
} MinimapTileSize;

/* world <-> map */
int   world_to_map_x(float world_x, TileSize tile);
int   world_to_map_y(float world_y, TileSize tile);
float map_to_world_x(int map_x, TileSize tile);
float map_to_world_y(int map_y, TileSize tile);

/* map <-> minimap */
float map_to_minimap_x(int map_x, MinimapTileSize tile);
float map_to_minimap_y(int map_y, MinimapTileSize tile);

#endif // SCALING_H_
