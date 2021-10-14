#include <math.h>
#include <stdlib.h>
#include "dz5.h"

double haversine(double lat1, double lon1, double lat2, double lon2)
{
    double d, t1, t2;

    t1 = pow(sin((TO_RAD(lat1) - TO_RAD(lat2)) / 2.), 2);
    t2 = pow(sin((TO_RAD(lon1) - TO_RAD(lon2)) / 2.), 2);

    d = 2 * R * asin(sqrt(t1 + t2 * cos(lat1) * cos(lat2)));

    return d;
}

Node *create_bus_path(Node *dir, int start, int end)
{
    Node *current;
    for (int i = 0; i < start; i++) {
        dir = dir->next;
        free(dir->previous);
        dir->previous = NULL;
    }

    for (current = dir; current->next; current = current->next, end--);
    for (int i = 0; i < start - end; i++) {
        current = current->previous;
        free(current->next);
        current->next = NULL;
    }

    return dir;
}

void find_start_and_end(Node *current, double start_wid, double start_len, double end_wid, double end_len, int *start, int *end)
{
    double min_sd = 0, min_ed = 0, start_d, end_d;
    int i;

    for (*start = 0, *end = 0, i = 0; current; current = current->next, i++) {
        start_d = haversine(start_wid, start_len, current->bus_stop.width, current->bus_stop.length);
        end_d = haversine(end_wid, end_len, current->bus_stop.width, current->bus_stop.length);
        if (!min_sd) {
            min_sd = start_d;
        } else if (start_d < min_sd) {
            min_sd = start_d;
            *start = i;
        }
        if (!min_ed) {
            min_ed = end_d;
        } else if (end_d < min_ed) {
            min_ed = end_d;
            *end = i;
        }
    }
}

Node *find_bus_path(Node *dir_A, Node *dir_B, double start_wid, double start_len, double end_wid, double end_len, char *dir)
{
    Node *bus_path = NULL;
    int start, end;

    find_start_and_end(dir_A, start_wid, start_len, end_wid, end_len, &start, &end);
    if (start <= end) {
        bus_path = create_bus_path(dir_A, start, end);
        *dir = 'A';
        free_list(dir_B);
    } else {
        find_start_and_end(dir_B, start_wid, start_len, end_wid, end_len, &start, &end);
        bus_path = create_bus_path(dir_B, start, end);
        *dir = 'B';
        free_list(dir_A);
    }

    return bus_path;
}