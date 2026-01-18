#include "raycastray.h"
#include "scaling.h"

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

            Scale s_pixel_to_map = {
                .scale_x = (float)map->width / screen_width,
                .scale_y = (float)map->height / screen_height,
                .offset_x = 0,
                .offset_y = 0
            };

            // scale pixel to map
            Point p_map = scaling((Point){.x=ray_x,.y=ray_y},s_pixel_to_map);
            int mx = (int)(p_map.x);
            int my = (int)(p_map.y);

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
