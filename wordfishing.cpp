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
}


void wordfishing::search_word(const string& word) {
    if (word.empty()) return;

    int dr[] = {0, 0, 1, -1, 1, -1, 1, -1};
    int dc[] = {1, -1, 0, 0, 1, -1, -1, 1};

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (diagram[r][c] == word[0]) {
                for (int i = 0; i < 8; ++i) {
                    int current_r = r;
                    int current_c = c;
                    int k;
                    
                    vector<pair<int, int>> path;

                    for (k = 0; k < word.length(); ++k) {
                        if (current_r < 0 || current_r >= rows || current_c < 0 || current_c >= cols) {
                            break; 
                        }
                        if (diagram[current_r][current_c] != word[k]) {
                            break;
                        }
                        path.push_back({current_r, current_c});
                        current_r += dr[i];
                        current_c += dc[i];
                    }

                    if (k == word.length()) {
                        lock_guard<mutex> lock(mtx_results);
                        found_word_coords.push_back(path);
                        return;
                    }
                }
            }
        }
    }
}

vector<string> wordfishing::solve() {
    vector<thread> threads;

    for (const string& word : words_to_find) {
        threads.emplace_back(&wordfishing::search_word, this, word);
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
        }
    }

    return result_diagram;
}