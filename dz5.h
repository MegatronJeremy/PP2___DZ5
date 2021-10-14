#ifndef DZ5_H
#define DZ5_H

#define MIN_ARG 7
#define MAX_LEN 256
#define R 6371

#define SF_STRTOD(num, str, end_ptr)            \
    num = strtod(str, &(end_ptr));              \
    if (*(end_ptr) != '\0') {                   \
        printf("ARG_GRESKA");                   \
        return 0;                               \
    }                                           \
    (end_ptr) = NULL;

#define TO_RAD(degrees)                         \
    ((degrees) * 3.14 / 180.)

#define SF_FOPEN(file, name, mode)              \
    file = fopen(name, mode);                   \
    if ((file) == NULL) {                       \
        printf("DAT_GRESKA");                   \
        exit(0);                                \
    }

#define SF_MALLOC(p, len)                       \
    p = malloc((len) * sizeof(*(p)));           \
    if ((p) == NULL) {                          \
        printf("MEM_GREKSA");                   \
        exit(0);                                \
    }

typedef struct bus_stop {
    int num;
    char name[MAX_LEN];
    double width, length;
    int zone;
} Bus_stop;

typedef struct node {
    Bus_stop bus_stop;
    struct node *next;
    struct node *previous;
} Node;

Node *read_bus_stop(char *);
Node *read_bus_list(char *);
double haversine(double, double, double, double);
Node *find_bus_path(Node *, Node *, double, double, double, double, char *);
Node *create_bus_path(Node *, int, int);
void free_list(Node *);
void write_and_free(Node *, const char*, const char*, char);
void find_start_and_end(Node *, double, double, double, double, int *, int *);

#endif