#include <stdio.h>
#include <stdlib.h>
#include "dz5.h"

void free_list(Node *head)
{
    while(head) {
        Node *old = head;
        head = head->next;
        free(old);
    }
}

void write_and_free(Node *bus_path, const char *output_file, const char *line, char cur_dir)
{
    FILE *out;
    SF_FOPEN(out, output_file, "a");

    if (cur_dir)
        fprintf(out, "%s!%c\n", line, cur_dir);
    for (Node *current = bus_path; current; current = current->next) {
        fprintf(out, "%d!%s!%lf!%lf!%d\n",
                current->bus_stop.num, current->bus_stop.name, current->bus_stop.width,
                current->bus_stop.length, current->bus_stop.zone);
    }

    free_list(bus_path);
    fclose(out);
}