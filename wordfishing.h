//
// Created by hb on 9/18/25.
//

#ifndef WORDFISHING_H
#define WORDFISHING_H

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <utility>

#include "InputFile.h"

using namespace std;

enum Direction {
    DIREITA, ESQUERDA, BAIXO, CIMA,
    DIREITA_BAIXO, ESQUERDA_CIMA, DIREITA_CIMA, ESQUERDA_BAIXO
};

struct FoundWordInfo {
    std::string word;
    int start_row;
    int start_col;
    Direction direction;
    std::vector<std::pair<int, int>> path;
};

class wordfishing {
public:
    wordfishing(const InputFile& file);
    vector<string> solvedDiagram();
    const vector<vector<bool>>& getHighlightGrid() const;
    string getSummary();

private:
    const vector<string>& diagram;
    const vector<string>& words_to_find;
    const int& rows;
    const int& cols;
    vector<vector<bool>> highlight_grid;

    vector<string> result_diagram;
    vector<FoundWordInfo> findings;
    mutex mtx_results;

    void search(int direction_index);
    void setDirection(int direction_index);

    string getDirection(Direction dir);
};

#endif // WORDFISHING_H