#include "cstdio"
#include <cstdlib>
#include "io.h"
#include "projection.h"
#include "errors.h"
#include "iterface.h"

int read_amount(int* n, FILE* f)
{
    int err = 0;

    if (fscanf(f, "%d", n) != 1)
        err = FILE_FORMAT_ERR;

    if (*n < 0)
        err = FILE_CONTENT_ERR;
    else if (*n == 0)
        err = NO_CONNECTIONS;

    return err;
}


int connections_alloc(connections_data &connections, int n)
{
    connections.n = n;

    connections.arr = (connection*) calloc(connections.n, sizeof(connection));
    if (!connections.arr)
        return PTR_ALLOC_ERR;

    return NONE;
}


void connections_free(connections_data &connections)
{
    if (connections.arr)
        free(connections.arr);
}


int read_connection(connection* joints, FILE* f)
{
    if (fscanf(f, "%d%d", &joints->p1, &joints->p2) != 2)
        return FILE_FORMAT_ERR;

    return NONE;
}

int read_connections(connections_data &connections, FILE *f)
{
    int err = 0;
    for (int i = 0; i < connections.n && !err; i++)
    {
        if (read_connection(&connections.arr[i], f))
            err = FILE_FORMAT_ERR;
    }

    return err;
}

//поменял функцию на соответствие уровням абстракций

int process_connections(connections_data& connections, FILE* f)
{
    int n;

    int err = read_amount(&n, f);
    if (err)
        return err;

    err = connections_alloc(connections, n);
    if (err)
        return err;

    if ((err = read_connections(connections, f)) == FILE_FORMAT_ERR)
        connections_free(connections);

    return err;
}
