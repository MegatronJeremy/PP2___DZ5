#include <stdio.h>
#include <stdlib.h>
#include "dz5.h"

int main(int argc, const char **argv)
{
    if (argc < MIN_ARG) {
        printf("ARG_GRESKA");
        return 0;
    }

    double start_wid, start_lon, end_wid, end_lon;
    char *end_ptr = NULL;
    SF_STRTOD(start_wid, argv[2], end_ptr);
    SF_STRTOD(start_lon, argv[3], end_ptr);
    SF_STRTOD(end_wid, argv[4], end_ptr);
    SF_STRTOD(end_lon, argv[5], end_ptr);

    for (int i = 6; i < argc; i++) {
        char dir_a[MAX_LEN], dir_b[MAX_LEN], cur_dir = 0;
        sprintf(dir_a, "%s_dirA.txt", argv[i]);
        sprintf(dir_b, "%s_dirB.txt", argv[i]);
        Node *bus_list_A = read_bus_list(dir_a);
        Node *bus_list_B = read_bus_list(dir_b);
        Node *bus_path = find_bus_path(bus_list_A, bus_list_B, start_wid, start_lon, end_wid, end_lon, &cur_dir);
        write_and_free(bus_path, argv[1], argv[i], cur_dir);
    }

    return 0;
}
