#include "../state/state.hpp"
#include "./minimax.hpp"

int Minimax::evaluate(State* state) {
    return state->evaluate();
}

int Minimax::minimax(State* state, int depth, bool isMaxPlayer) {
    if (depth == 0 || state->game_state != NONE) {
    // Base case: evaluate the state if it's a terminal state or reached maximum depth
        return evaluate(state);
    }

    if (isMaxPlayer) {
        int maxEval = INT_MIN;
        state->get_legal_actions();

        for (const auto& action : state->legal_actions) {
            State* next = state->next_state(action);
            int eval = minimax(next, depth - 1, false);
            maxEval = std::max(maxEval, eval);
            delete next;
        }

        return maxEval;
    } 
    else {
        int minEval = INT_MAX;
        state->get_legal_actions();

        for (const auto& action : state->legal_actions) {
            State* next = state->next_state(action);
            int eval = minimax(next, depth - 1, true);
            minEval = std::min(minEval, eval);
            delete next;
        }

        return minEval;
    }
}

Move Minimax::get_move(State* state, int depth) {
    if (!state->legal_actions.size())
        state->get_legal_actions();

    auto actions = state->legal_actions;
    int maxEval = INT_MIN;
    Move bestMove;

    for (const auto& action : actions) {
        State* next = state->next_state(action);
        int eval = minimax(next, depth - 1, false);
        delete next;

        if (eval > maxEval) {
        maxEval = eval;
        bestMove = action;
        }
    }

    return bestMove;
}
