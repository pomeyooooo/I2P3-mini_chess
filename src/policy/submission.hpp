#pragma once
#include "../state/state.hpp"
#include <algorithm>
#include <climits>

/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Submission {
public:
    static int evaluate(State* state, int player);
    static int alphabeta(State* state, int depth, int alpha, int beta, int Player);
    static Move get_move(State* state, int depth);
};