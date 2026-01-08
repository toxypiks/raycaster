#include "raycastray.h"
#include "raylib.h"

void cast_rays(RaycastMap *map, Player *p, int num_rays, RaycastRay rays[], int screen_width, int screen_height)
{
    float fov = 60.0f;
    float step = 0.5f;

    for (int r = 0; r < num_rays; ++r) {
        // deg in rad = deg * (pi/180)
        // -fov/2 start fov/2 end
        float angle_offset = (-fov/2.0f + ((float)r / (num_rays-1)) * fov) * (M_PI / 180.0f);

        // use offset to calc vector of ray (player vector * offset)
        // rotation of vector (x, y) with angle alpha:
        // x' = (cos alpha - sin alpha) * x
        // y' = (sin alpha + cos alpha) * y
        float ray_dir_x = p->dir_x * cos(angle_offset) - p->dir_y * sin(angle_offset);
        float ray_dir_y = p->dir_x * sin(angle_offset) + p->dir_y * cos(angle_offset);

        // start ray where player is
        float ray_x = p->x;
        float ray_y = p->y;

        // let ray take steps
        while (1) {
            ray_x += ray_dir_x * step;
            ray_y += ray_dir_y * step;

            // scale pixel to map
            int mx = (int)(ray_x / (screen_width / map->width));
            int my = (int)(ray_y / (screen_height / map->height));

            // stop if out of bounds map
            if (mx < 0 || mx >= map->width || my < 0 || my >= map->height)
                break;

            // break when wall hit
            if (map->cells[my][mx] == 1)
                break;

            }
            float dx = ray_x - p->x;
            float dy = ray_y - p->y;
            rays[r].x = ray_x;
            rays[r].y = ray_y;

            // correction fish-eye:
            // ray in the middle measurs right distance, others are too long
            // angle correction adjacent = hypotenuse * cos(alpha)
            float raw_dist = sqrtf(dx*dx + dy*dy);
            rays[r].dist = raw_dist * cosf(angle_offset);

            rays[r].hit = 1;
    }
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
