#include "../state/state.hpp"
#include "./minimax.hpp"

int Minimax::evaluate(State* state, int player) {
    return state->evaluate(player);
}

int Minimax::minimax(State* state, int depth, int isMaxPlayer) {
    if (depth == 0 || !state->legal_actions.size()) {
    // Base case: evaluate the state if it's a terminal state or reached maximum depth
        return evaluate(state, isMaxPlayer);
    }

    if (isMaxPlayer == state->player) {
        int value = INT_MIN;
        state->get_legal_actions();

        for (const auto& action : state->legal_actions) {
            State* next = state->next_state(action);
            value = std::max(value, minimax(next, depth - 1, isMaxPlayer));
        }
        return value;
    } 
    else {
        int value = INT_MAX;
        state->get_legal_actions();

        for (const auto& action : state->legal_actions) {
            State* next = state->next_state(action);
            value = std::min(value, minimax(next, depth - 1, isMaxPlayer));
        }
        return value;
    }
}

Move Minimax::get_move(State* state, int depth) {
    int maxEval = INT_MIN;
    Move bestMove;

    if (!state->legal_actions.size())
        state->get_legal_actions();
 
    for (const auto& action : state->legal_actions) {
        State* next = state->next_state(action);
        int eval = minimax(next, depth - 1, state->player);

        if (eval > maxEval) {
            maxEval = eval;
            bestMove = action;
        }
    }

    return bestMove;
}
