#include <stdio.h>
#include <assert.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "raylib.h"
#include "player.h"
#include "raycastmap.h"
#include "raycastray.h"

#define READ_END 0
#define WRITE_END 1

#define WIDTH 800
#define HEIGHT 600
#define FPS 60

// hack that returns the value of the argument of macro as a string
#define STR2(x) #x
#define STR(x) STR2(x)

int main ()
{
    int pipefd[2];

    if (pipe(pipefd) < 0) {
        fprintf(stderr, "ERROR: could not create pipe: %s\n", strerror(errno));
        return 1;
    }

    pid_t child = fork();
    if (child < 0) {
        fprintf(stderr, "ERROR: could not fork a child: %s\n", strerror(errno));
        return 1;
    }
    if (child == 0) {
        // replace standard input of ffmpeg with the read end of the pipe (pipefd[0])
        // dup2(pipefd[READ_END], STDIN_FILENO);
        if (dup2(pipefd[READ_END], STDIN_FILENO) < 0) {
            fprintf(stderr, "ERROR: could not reopen read end of pipe as stdin: %s\n", strerror(errno));
            return 1;
        }
        close(pipefd[WRITE_END]);
        int ret = execlp("ffmpeg",
                         "ffmpeg",
                         "-loglevel", "verbose",
                         "-y",
                         "-f", "rawvideo",
                         "-pix_fmt", "rgba",
                         "-s", STR(WIDTH) "x" STR(HEIGHT),
                         "-r", STR(FPS),
                         "-an",
                         "-i", "-",
                         "-c:v", "libx264",

                         "../video_output/raycaster_example.mp4",
                         NULL
        );
        if (ret < 0) {
            fprintf(stderr, "ERROR: could not run ffmpeg as a child process: %s\n", strerror(errno));
            return 1;
        }
        assert(0 && "unreachable");
    }
    close(pipefd[READ_END]);

    const int minimap_width = WIDTH / 2;
    const int player_view_width = WIDTH / 2;

    int num_rays = 100;
    RaycastRay rays[num_rays];

    RaycastMap *map = create_raycastmap(10, 10);

    initialize_map(map);

    Player player = {
        .x = 400,
        .y = 225,
        .dir_x = 1.0f,
        .dir_y = 0.0f,
        .angle = 0.0f
    };

    float speed = 2.0f;
    float rot_speed = 0.05f;
    float new_x = player.x;
    float new_y = player.y;
    float player_radius = 5.0f;

    InitWindow(WIDTH, HEIGHT, "Wolfenstein 3D");

    SetTargetFPS(60);

    bool running = true;
    size_t frame_count = 0;
    size_t start_video = 5;

    while(running && !WindowShouldClose())
    {

        if (IsKeyDown(KEY_LEFT))  player.angle -= rot_speed;
        if (IsKeyDown(KEY_RIGHT)) player.angle += rot_speed;

        player.dir_x = cos(player.angle);
        player.dir_y = sin(player.angle);

        new_x = player.x;
        new_y = player.y;

        if (IsKeyDown(KEY_W)) {
            new_x += player.dir_x * speed;
            new_y += player.dir_y * speed;
        }
        if (IsKeyDown(KEY_S)) {
            new_x -= player.dir_x * speed;
            new_y -= player.dir_y * speed;
        }
        if (IsKeyDown(KEY_A)) {
            new_x += player.dir_y * speed;
            new_y -= player.dir_x * speed;
        }
        if (IsKeyDown(KEY_D)) {
            new_x -= player.dir_y * speed;
            new_y += player.dir_x * speed;
        }

        Player test = player;
        test.x = new_x;
        test.y = new_y;

        if (!is_wall(map, test, player_radius, WIDTH, HEIGHT))
        {
            player = test;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        draw_minimap(map, minimap_width, HEIGHT);

        draw_player_on_minimap(&player, map, minimap_width, HEIGHT, WIDTH, HEIGHT);

        cast_rays(map, &player, num_rays, rays, WIDTH, HEIGHT);

        draw_first_person_view(rays, num_rays, WIDTH, HEIGHT, minimap_width, player_view_width);

        draw_rays_on_minimap(rays, num_rays, &player, map, minimap_width, HEIGHT, WIDTH, HEIGHT);

        EndDrawing();

        if (frame_count > start_video) {
            Image screen = LoadImageFromScreen();
            // flip image -> writing rows in reversed order
            for (size_t y = screen.height; y > 0; --y) {
                write(pipefd[WRITE_END], (uint8_t*)screen.data + (y - 1)*screen.width*4, screen.width*4);
            }
            UnloadImage(screen);
        }
        frame_count++;
    }
    CloseWindow();
    return 0;
}
