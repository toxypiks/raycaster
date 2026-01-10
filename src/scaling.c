#include "scaling.h"

Point scaling (Point p_in, ScaleFactor sf)
{
    Point p_out = {0};
    p_out.x = p_in.x * sf.scale_x + sf.offset_x;
    p_out.y = p_in.y * sf.scale_y + sf.offset_y;

    return p_out;
}
