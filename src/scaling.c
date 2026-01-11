#include "scaling.h"

Point scaling (Point p_in, Scale s)
{
    Point p_out = {0};
    p_out.x = p_in.x * s.scale_x + s.offset_x;
    p_out.y = p_in.y * s.scale_y + s.offset_y;

    return p_out;
}
