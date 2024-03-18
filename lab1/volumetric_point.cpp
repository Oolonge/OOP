#include "cstdio"
#include <cstdlib>
#include "volumetric_point.h"
#include "projection.h"
#include "errors.h"
#include "iterface.h"

int points_alloc(points_data& pts, int len)
{
    pts.n = len;
    pts.arr = (point*) calloc(len, sizeof(point));

    if (!pts.arr)
        return PTR_ALLOC_ERR;

    return NONE;
}


void points_free(points_data &pts)
{
    if (pts.arr)
        free(pts.arr);
}


int read_point(point* dot, FILE* f)
{
    if (fscanf(f, "%lf%lf%lf", &dot->x, &dot->y, &dot->z) != 3)
        return FILE_FORMAT_ERR;

    return NONE;
}


int read_n_points(point *dots, int n, FILE *f)
{
    int err = 0;
    for (int i = 0; i < n && !err; i++)
    {
        if (read_point(&dots[i], f))
            err = FILE_FORMAT_ERR;
    }
    return err;
}


int process_points(points_data &pts, FILE *f)
{
    int n;
    int err = 0;

    err = read_amount(&n, f);
    //не прыгать по полям
    if (!err)
    {
        if (n)
            err = points_alloc(pts, n);
        else
            err = NO_DOTS;

        if (!err)
        {
            if ((err = read_n_points(pts.arr, n, f)) == FILE_FORMAT_ERR)
                points_free(pts);
        }
    }
    return err;
}
