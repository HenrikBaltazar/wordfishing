//
// Created by hb on 9/17/25.
//

#include "InputFile.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

InputFile::InputFile(string fileName)
: fileName(fileName) {}

bool InputFile::readFile() {
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Erro: Nao foi possivel abrir o arquivo " << fileName << endl;
        return false;
    }

    diagram.clear();

    string firstLine;
    if (getline(file, firstLine)) {
        stringstream ss(firstLine);
        int lines, columns, lineCounter=0;
        if (ss >> lines >> columns) {
            char extra_char;
            if (!(ss >> extra_char)) {
                diagramLines = lines;
                diagramColumns = columns;
            }else {
                cerr << "Erro: Formato do cabeçalho inválido em " << fileName << endl;
                return false;
            }
        }else {
            cerr << "Erro: Nao foi possivel ler os números do cabeçalho em " << fileName << endl;
            return false;
        }
        string line;
        while (getline(file, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (!line.empty()) {
                if (lineCounter<diagramLines) {
                    diagram.push_back(line);
                }else {
                    words.push_back(line);
                }
            }
            lineCounter++;
        }
    }else {
        cerr << "Erro: Nao foi possivel ler a primeira linha (cabeçalho linha x coluna) do arquivo " << fileName << endl;
        return false;
    }

    file.close();
    return true;
}

const vector<string>& InputFile::getDiagram() const {
    return diagram;
}

const int& InputFile::getDiagramLines() const {
    return diagramLines;
}

const int& InputFile::getDiagramColumns() const {
    return diagramColumns;
}

const vector<string>& InputFile::getWords() const {
    return words;
}