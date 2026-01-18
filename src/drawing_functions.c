#include "drawing_functions.h"
#include "scaling.h"
#include "raylib.h"

void draw_mini_window(RaycastMap *map, int mini_window_width, int mini_window_height)
{
    Scale s_minimap = {
        .scale_x = (float)mini_window_width / map->width,
        .scale_y = (float)mini_window_height / map->height,
        .offset_x = 0,
        .offset_y = 0
    };

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            if (map->cells[y][x] == 1) {
                Point p_mm = scaling((Point){.x=x,.y=y},s_minimap);
                DrawRectangle(
                    p_mm.x,
                    p_mm.y,
                    s_minimap.scale_x,
                    s_minimap.scale_y,
                    DARKGRAY
                );
            }
        }
    }
}

void draw_player_on_mini_window(Player *p, int mini_window_width, int mini_window_height, int width, int height)
{
    Scale s = {
        .scale_x = ((float)mini_window_width)/width,
        .scale_y = ((float)mini_window_height)/height,
        .offset_x = 0,
        .offset_y = 0
    };

    Point player_pos = scaling((Point){.x=p->x, .y=p->y}, s);
    DrawCircle(player_pos.x, player_pos.y, 5, GREEN);
}

void draw_rays_on_mini_window(RaycastRay rays[], int num_rays, Player *p, RaycastMap *map, int mini_window_width, int mini_window_height, int width, int height)
{
    Scale s = {
        .scale_x = ((float)mini_window_width)/((float)width),
        .scale_y = ((float)mini_window_height)/((float)height),
        .offset_x = 0,
        .offset_y = 0
    };

    Point player_pos = scaling((Point){.x=p->x, .y= p->y}, s);

    for (int r = 0; r < num_rays; r++) {
        Point ray_pos = scaling((Point){.x=rays[r].x, .y=rays[r].y}, s);
        DrawLine((int)player_pos.x, (int)player_pos.y, (int)ray_pos.x, (int)ray_pos.y, GREEN);
    }
}

void draw_first_person_view(RaycastRay rays[], int num_rays,
                            int player_view_width, int width, int height)
{
    // calc ray width by dividing screen width by number of rays
    int rect_width = player_view_width / num_rays;

    for (int r = 0; r < num_rays; r++) {
        float dist = rays[r].dist;

        int rect_height = (int)(height / dist * 50); // 50 = scalingfactor randomly chosen, test
        int rect_top = (height - rect_height) / 2;

        // x-position of line in window
        int screen_x = width + r * rect_width;

        // dim color relating to distance (closer = brighter)
        int shade = (int)(255.0f / (dist + 1.0f) * 50); // randomly chosen, test
        if (shade > 255) shade = 255;
        if (shade < 50) shade = 50;  // minimal brightness

        Color wall_color = (Color){shade, shade, shade, 255};

        DrawRectangle(screen_x, rect_top, rect_width, rect_height, wall_color);
    }
}
