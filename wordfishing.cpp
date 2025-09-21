//
// Created by hb on 9/18/25.
//

#include "wordfishing.h"
#include <unordered_set>
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


void wordfishing::search(int direction_index) {
    const int dr[] = {0, 0, 1, -1, 1, -1, 1, -1};
    const int dc[] = {1, -1, 0, 0, 1, -1, -1, 1};
    const Direction directions[] = {
        DIREITA, ESQUERDA, BAIXO, CIMA,
        DIREITA_BAIXO, ESQUERDA_CIMA, DIREITA_CIMA, ESQUERDA_BAIXO
    };

    int move_r = dr[direction_index];
    int move_c = dc[direction_index];
    Direction current_direction = directions[direction_index];

    for (const string& word : words_to_find) {
        if (word.empty()) continue;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                vector<pair<int, int>> path;
                int k;
                for (k = 0; k < word.length(); ++k) {
                    int current_r = r + k * move_r;
                    int current_c = c + k * move_c;
                    if (current_r < 0 || current_r >= rows || current_c < 0 || current_c >= cols || diagram[current_r][current_c] != word[k]) {
                        break;
                    }
                    path.push_back({current_r, current_c});
                }

                if (k == word.length()) {
                    FoundWordInfo info;
                    info.word = word;
                    info.start_row = r;
                    info.start_col = c;
                    info.direction = current_direction;
                    info.path = path;

                    std::lock_guard<std::mutex> lock(mtx_results);
                    findings.push_back(info);
                }
            }
        }
    }
}

string directionToString(Direction dir) {
    switch (dir) {
        case DIREITA: return "DIREITA";
        case ESQUERDA: return "ESQUERDA";
        case BAIXO: return "BAIXO";
        case CIMA: return "CIMA";
        case DIREITA_BAIXO: return "DIAGONAL DIREITA-BAIXO";
        case ESQUERDA_CIMA: return "DIAGONAL ESQUERDA-CIMA";
        case DIREITA_CIMA: return "DIAGONAL DIREITA-CIMA";
        case ESQUERDA_BAIXO: return "DIAGONAL ESQUERDA-BAIXO";
        default: return "DESCONHECIDA";
    }
}

string wordfishing::getSummary() {
    const string HIGHLIGHT_ON = "\033[1;32m";
    const string HIGHLIGHT_OFF = "\033[0m";
    if (findings.empty()) {
        return "Nenhuma palavra foi encontrada.";
    }
    string summary_text = HIGHLIGHT_ON + "--- SUMARIO DE PALAVRAS ENCONTRADAS ---" +HIGHLIGHT_OFF + "\n";
    for (const auto& info : findings) {
        summary_text += HIGHLIGHT_ON + info.word + HIGHLIGHT_OFF + " em (" + std::to_string(info.start_row) + "," + std::to_string(info.start_col) + ")";
        summary_text += " - " + directionToString(info.direction) + "\n";
    }
    unordered_set<string> found_words_set;
    for (const auto& info : findings) {
        found_words_set.insert(info.word);
    }
    vector<string> words_not_found;
    for (const string& word : words_to_find) {
        if (found_words_set.find(word) == found_words_set.end()) {
            words_not_found.push_back(word);
        }
    }
    if (!words_not_found.empty()) {
        summary_text += HIGHLIGHT_ON + "\n--- PALAVRAS NAO ENCONTRADAS ---\n" + HIGHLIGHT_OFF;
        for (const std::string& word : words_not_found) {
            summary_text += word + "\n";
        }
    }
    return summary_text;
}

vector<string> wordfishing::solvedDiagram() {
    vector<thread> threads;
    for (int i = 0; i < 8; ++i) {
        threads.emplace_back(&wordfishing::search, this, i);
    }

    for (thread& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    for (const auto& info : findings) {
        for (const auto& coord : info.path) {
            result_diagram[coord.first][coord.second] = toupper(result_diagram[coord.first][coord.second]);
            highlight_grid[coord.first][coord.second] = true;
        }
    }
    return result_diagram;
}