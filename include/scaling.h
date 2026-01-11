#ifndef SCALING_H_
#define SCALING_H_

typedef struct {
    float scale_x;
    float scale_y;
    float offset_x;
    float offset_y;
} Scale;

typedef struct {
    float x;
    float y;
} Point;

Point scaling(Point p_in, Scale s);

#endif // SCALING_H_
