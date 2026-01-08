#ifndef RAYCASTMAP_H_
#define RAYCASTMAP_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct RaycastMap {
    int width;
    int height;
    int **cells;
} RaycastMap;

RaycastMap *create_raycastmap(int width, int height);
void initialize_map(RaycastMap *map);

#endif // RAYCASTMAP_H_
