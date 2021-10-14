#include <stdio.h>
#include <stdlib.h>
#include "dz5.h"

Node *read_bus_stop(char *line)
{
    Node *elem = NULL;
    Bus_stop bus_stop;
    char *format = "%d!%[^!]!%lf!%lf!%d\n";

    if (sscanf(line, format, &bus_stop.num, bus_stop.name, &bus_stop.width, &bus_stop.length, &bus_stop.zone) == 5) {
        SF_MALLOC(elem, 1);
        elem->bus_stop = bus_stop;
        elem->previous = NULL;
        elem->next = NULL;
    }

    return elem;
}

Node *read_bus_list(char *file_name)
{
    Node *head = NULL, *tail = head, *elem;
    char line[MAX_LEN];
    FILE *in;

    SF_FOPEN(in, file_name, "r");
    while (fgets(line, MAX_LEN, in) && (elem = read_bus_stop(line)) != NULL) {
        if (!head) {
            head = elem;
        } else {
            tail->next = elem;
            elem->previous = tail;
        }
        tail = elem;
    }

    fclose(in);
    return head;
}