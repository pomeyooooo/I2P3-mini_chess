#include "../state/state.hpp"
#include "./submission.hpp"
#include <climits>

int Submission::evaluate(State* state, int player) {
    return state->evaluate(player);
}

int Submission::alphabeta(State* state, int depth, int alpha, int beta, int Player) {
    if (depth == 0 || !state->legal_actions.size()) {
        // Base case: evaluate the state
        return evaluate(state, Player);
    }

    if (Player == state->player) {
        int value = INT_MIN;
        state->get_legal_actions();

        for (const auto& action : state->legal_actions) {
            State* next = state->next_state(action);
            value = std::max(value, alphabeta(next, depth - 1, alpha, beta, Player));
            alpha = std::max(alpha, value);
            if (alpha >= beta)
                break; // Beta cut-off
        }
        return value;
    } else {
        int value = INT_MAX;
        state->get_legal_actions();

        for (const auto& action : state->legal_actions) {
            State* next = state->next_state(action);
            value = std::min(value, alphabeta(next, depth - 1, alpha, beta, Player));
            beta = std::min(beta, value);
            if (alpha >= beta)
                break; // Alpha cut-off
        }
        return value;
    }
}

Move Submission::get_move(State* state, int depth) {
    int alpha = INT_MIN;
    int beta = INT_MAX;
    int maxEval = INT_MIN;
    Move bestMove;

    state->get_legal_actions();

    for (const auto& action : state->legal_actions) {
        State* next = state->next_state(action);
        int eval = alphabeta(next, depth - 1, alpha, beta, state->player);

        if (eval > maxEval) {
            maxEval = eval;
            bestMove = action;
        }
        alpha = std::max(alpha, maxEval);
    }

    return bestMove;
}
