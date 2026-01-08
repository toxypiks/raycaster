#include "drawing_functions.h"
#include "raylib.h"

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

void draw_player_on_minimap(Player *p, RaycastMap *map, int minimap_width, int minimap_height, int width, int height)
{
    float cell_w = (float)minimap_width / map->width;
    float cell_h = (float)minimap_height / map->height;

    float player_map_x = (p->x / width) * map->width;
    float player_map_y = (p->y / height) * map->height;

    DrawCircle((int)(player_map_x * cell_w), (int)(player_map_y * cell_h), 5, GREEN);
}

// TODO scaling factor/working with normalized values
void draw_rays_on_minimap(RaycastRay rays[], int num_rays, Player *p, RaycastMap *map, int minimap_width, int minimap_height, int width, int height)
{
    float cell_w = (float)minimap_width / map->width;
    float cell_h = (float)minimap_height / map->height;

    float player_map_x = (p->x / width) * minimap_width;
    float player_map_y = (p->y / height) * minimap_height;

    for (int r = 0; r < num_rays; r++) {
        int px = (int)(rays[r].x / width * minimap_width);
        int py = (int)(rays[r].y / height * minimap_height);

        DrawLine((int)player_map_x, (int)player_map_y, px, py, GREEN);
    }
}

void draw_first_person_view(RaycastRay rays[], int num_rays,
                            int screen_width, int screen_height,
                            int minimap_width, int player_view_width)
{
    // calc ray width by dividing screen width by number of rays
    int ray_width = player_view_width / num_rays;

    for (int r = 0; r < num_rays; r++) {
        float dist = rays[r].dist;

        // calc hight of wall (inversely proportional)
        // the closer the wall the bigger line_height -> the smaller distance the bigger line_height
        int line_height = (int)(screen_height / dist * 50); // 50 = scalingfactor randomly chosen, test
        int line_top = (screen_height - line_height) / 2;

        // x-position of line in window
        int screen_x = minimap_width + r * ray_width;

        // dim color relating to distance (closer = brighter)
        int shade = (int)(255.0f / (dist + 1.0f) * 50); // randomly chosen, test
        if (shade > 255) shade = 255;
        if (shade < 50) shade = 50;  // minimal brightness

        Color wall_color = (Color){shade, shade, shade, 255};

        DrawRectangle(screen_x, line_top, ray_width, line_height, wall_color);
    }
}
