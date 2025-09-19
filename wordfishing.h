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

class wordfishing {
public:
    wordfishing(const InputFile& file);
    vector<string> solve();
    const vector<vector<bool>>& getHighlightGrid() const;

private:
    const vector<string>& diagram;
    const vector<string>& words_to_find;
    const int& rows;
    const int& cols;
    vector<vector<bool>> highlight_grid;

    vector<string> result_diagram;

    vector<vector<pair<int, int>>> found_word_coords;
    mutex mtx_results;

    void search_direction(int direction_index);
};

#endif // WORDFISHING_H