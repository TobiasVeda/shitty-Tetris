//
// Created by tobia on 24.05.2024.
//

#ifndef SHITTY_TETRIS_PDB_ENUMERATIONS_H
#define SHITTY_TETRIS_PDB_ENUMERATIONS_H

enum Directions{Down, Right, Left};
enum Rotation_direction{Clockwise, Counter_clock};
enum Actions{Move_down, Move_right, Move_left, Rotate_clockwise, Rotate_counter_clock, Drop, Hold, Nothing};
enum Block_types{T, O, L, I, J, Z, S, Ndef};
enum Game_states{Setup, Run, End};
enum End_states{Winner, Loser, Tie, Game_over};

#endif //SHITTY_TETRIS_PDB_ENUMERATIONS_H
