#ifndef UCI_H
#define UCI_H

#include "structs.h"

extern const char *square_to_coordinates[];
extern char promoted_pieces[];

void uci_loop(engine_t *engine, tt_t* hash_table);
void print_move(int move);

#endif
