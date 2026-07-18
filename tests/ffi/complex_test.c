#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int32_t id;
    double value;
    char* label;
} DataPacket;

DataPacket* create_packet(int32_t id, double value, const char* label) {
    printf("C: create_packet(id=%d, value=%f, label=%s)\n", id, value, label);
    fflush(stdout);
    DataPacket* p = (DataPacket*)malloc(sizeof(DataPacket));
    if (!p) return NULL;
    p->id = id;
    p->value = value;
    p->label = strdup(label);
    return p;
}

void update_packet(DataPacket* p, int32_t new_id, double new_value) {
    if (p) {
        printf("C: update_packet(id=%d -> %d, value=%f -> %f)\n", p->id, new_id, p->value, new_value);
        fflush(stdout);
        p->id = new_id;
        p->value = new_value;
    }
}

void free_packet(DataPacket* p) {
    if (p) {
        printf("C: free_packet(id=%d)\n", p->id);
        fflush(stdout);
        if (p->label) free(p->label);
        free(p);
    }
}
