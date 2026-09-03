#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class ChampionshipPredictor {
    const char PLAYER_A_ADVANCES = '0';
    const char PLAYER_B_ADVANCES = '1';
    const char UNKNOWN_OUTCOME = '?';
    
    int participant_count;
    vector<char> round_results;
    vector<int> possible_path_count;
    vector<int> query_to_internal_map;

public:
    ChampionshipPredictor(int total_phases, const string& initial_status) {
        participant_count = 1 << total_phases;

        round_results.resize(participant_count);
        possible_path_count.resize(2 * participant_count);
        query_to_internal_map.resize(participant_count);

        establish_index_mapping(total_phases);
        apply_initial_data(initial_status);
        build_initial_tree_state();
    }

    void adjust_game_outcome(int game_index, char new_status_char) {
        int internal_node_index = query_to_internal_map[game_index];
        round_results[internal_node_index] = new_status_char;
        propagate_update_upwards(internal_node_index);
    }

    int retrieve_valid_paths() const {
        return possible_path_count[1];
    }

private:
    void establish_index_mapping(int total_phases_param) {
        int current_external_position = 1;
        for (int current_round_num = 1; current_round_num <= total_phases_param; ++current_round_num) {
            int matches_this_round = 1 << (total_phases_param - current_round_num);
            int first_internal_node_for_round = 1 << (total_phases_param - current_round_num);
            
            for (int j = 0; j < matches_this_round; ++j) {
                query_to_internal_map[current_external_position++] = first_internal_node_for_round + j;
            }
        }
    }

    void apply_initial_data(const string& status_data) {
        for (int external_pos_idx = 1; external_pos_idx < participant_count; ++external_pos_idx) {
            int node_idx = query_to_internal_map[external_pos_idx];
            round_results[node_idx] = status_data[external_pos_idx - 1];
        }
    }

    void build_initial_tree_state() {
        for (int team_idx = 0; team_idx < participant_count; ++team_idx) {
            possible_path_count[participant_count + team_idx] = 1;
        }

        for (int current_parent_node = participant_count - 1; current_parent_node > 0; --current_parent_node) {
            recalculate_node_value(current_parent_node);
        }
    }

    void propagate_update_upwards(int starting_node) {
        while (starting_node > 0) {
            recalculate_node_value(starting_node);
            starting_node /= 2;
        }
    }

    void recalculate_node_value(int node_to_update) {
        if (round_results[node_to_update] == PLAYER_A_ADVANCES) {
            possible_path_count[node_to_update] = possible_path_count[2 * node_to_update];
        } 
        else if (round_results[node_to_update] == PLAYER_B_ADVANCES) {
            possible_path_count[node_to_update] = possible_path_count[2 * node_to_update + 1];
        } 
        else {
            possible_path_count[node_to_update] = possible_path_count[2 * node_to_update] + possible_path_count[2 * node_to_update + 1];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int total_phases;
    cin >> total_phases;

    string starting_outcomes_string;
    cin >> starting_outcomes_string;

    ChampionshipPredictor prediction_system(total_phases, starting_outcomes_string);

    int num_adjustments;
    cin >> num_adjustments;

    while (num_adjustments--) {
        int game_index;
        char new_status_char;
        cin >> game_index >> new_status_char;

        prediction_system.adjust_game_outcome(game_index, new_status_char);
        cout << prediction_system.retrieve_valid_paths() << '\n';
    }

    return 0;
}
