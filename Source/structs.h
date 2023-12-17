#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>

// move list structure
typedef struct moves {
  // moves
  int moves[256];

  // move count
  uint32_t count;
} moves;

typedef struct board {
  uint64_t bitboards[12];
  uint64_t occupancies[3];
  uint8_t side;
  uint8_t enpassant;
  uint8_t castle;
  uint64_t hash_key;
} board_t;

typedef struct engine {
  board_t board;
  uint64_t repetition_table[1000];
  uint32_t repetition_index;
  uint32_t ply;
  uint8_t quit;
  uint16_t movestogo;
  int64_t time;
  uint32_t inc;
  uint64_t starttime;
  uint64_t stoptime;
  uint8_t timeset;
  uint8_t stopped;

} engine_t;

#endif
