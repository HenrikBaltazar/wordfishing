//
// Created by hb on 9/17/25.
//

#ifndef WORDFISHING_INPUTFILE_H
#define WORDFISHING_INPUTFILE_H

#include <string>
#include <vector>

using namespace std;

class InputFile {
public:
    explicit InputFile(string fileName);

    bool readFile();
    const vector<string>& getDiagram() const;
    const int& getDiagramLines() const;
    const int& getDiagramColumns() const;
    const vector<string>& getWords() const;


private:
    string fileName;
    vector<string> diagram;
    vector<string> words;
    int diagramLines{}, diagramColumns{};
};

#endif