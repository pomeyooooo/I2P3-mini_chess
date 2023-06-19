#pragma once
#include "../state/state.hpp"
#include <algorithm>
#include <climits>

/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Minimax {
public:
    static int evaluate(State* state, int);
    static int minimax(State* state, int depth, int Player);
    static Move get_move(State* state, int depth);
};