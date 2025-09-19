//
// Created by hb on 9/18/25.
//

#include "wordfishing.h"
#include <iostream>
#include <cctype>

using namespace std;

wordfishing::wordfishing(const InputFile& rawData)
    : diagram(rawData.getDiagram()), words_to_find(rawData.getWords()),
    cols(rawData.getDiagramColumns()), rows(rawData.getDiagramLines()) {
    this->result_diagram = this->diagram;
    this->highlight_grid.resize(rows, vector<bool>(cols, false));
}

const vector<vector<bool>>& wordfishing::getHighlightGrid() const {
    return highlight_grid;
}


void wordfishing::search_direction(int direction_index) {
    const int dr[] = {0, 0, 1, -1, 1, -1, 1, -1};
    const int dc[] = {1, -1, 0, 0, 1, -1, -1, 1};

    int move_r = dr[direction_index];
    int move_c = dc[direction_index];

    for (const string& word : words_to_find) {
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                int k;
                vector<pair<int, int>> path;
                for (k = 0; k < word.length(); ++k) {
                    int current_r = r + k * move_r;
                    int current_c = c + k * move_c;

                    if (current_r < 0 || current_r >= rows || current_c < 0 || current_c >= cols) {
                        break;
                    }
                    if (diagram[current_r][current_c] != word[k]) {
                        break;
                    }
                    path.push_back({current_r, current_c});
                }

                if (k == word.length()) {
                    lock_guard<mutex> lock(mtx_results);
                    found_word_coords.push_back(path);
                }
            }
        }
    }
}

vector<string> wordfishing::solve() {
    vector<thread> threads;

    for (int i = 0; i < 8; ++i) {
        threads.emplace_back(&wordfishing::search_direction, this, i);
    }

    for (thread& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    for (const auto& path : found_word_coords) {
        for (const auto& coord : path) {
            int r = coord.first;
            int c = coord.second;
            result_diagram[r][c] = toupper(result_diagram[r][c]);
            highlight_grid[r][c] = true;
        }
    }

    return result_diagram;
}