#ifndef _4_DETERMINIZE_H_
#define _4_DETERMINIZE_H_

#include "3-combine.h"
#include "bitset.h"

// STEP 4 - DETERMINIZE

struct bracket_transition {
    struct bitset transition_symbols;
    symbol_id deterministic_transition_symbol;
};
struct bracket_transitions {
    // Sorted by transition_symbols.
    struct bracket_transition *transitions;
    uint32_t transitions_allocated_bytes;
    uint32_t number_of_transitions;
};
struct action_map_entry {
    state_id target_nfa_state;
    state_id dfa_state;
    symbol_id dfa_symbol;
    state_id nfa_state;
    symbol_id nfa_symbol;
    uint32_t action_index;
};
struct action_map {
    // Sorted lexicographically by target_nfa_state, then by dfa_state, then by
    // dfa_symbol.  "Initial" entries with no dfa_state or dfa_symbol are
    // encoded using UINT32_MAX for both fields.
    struct action_map_entry *entries;
    uint32_t entries_allocated_bytes;
    uint32_t number_of_entries;

    // Action lists are null-terminated.
    uint16_t *actions;
    uint32_t actions_allocated_bytes;
    uint32_t number_of_actions;
};
struct deterministic_grammar {
    struct automaton automaton;
    struct automaton bracket_automaton;

    struct action_map action_map;
    struct action_map bracket_action_map;
};

void determinize(struct combined_grammar *grammar,
 struct deterministic_grammar *result, struct bracket_transitions *transitions);

void determinize_bracket_transitions(struct bracket_transitions *result,
 struct combined_grammar *grammar);

struct action_map_entry *action_map_find(struct action_map *map,
 state_id target_nfa_state, state_id dfa_state, symbol_id dfa_symbol);

// Step 2 (build) uses this function to determinize and minimize rules.
void determinize_minimize(struct automaton *input, struct automaton *result);

#endif
