//
// Created by hb on 9/17/25.
//

#include "InputFile.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

InputFile::InputFile(const string& fileName) {
    this->fileName = fileName;
}

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
        int lines, columns;
        if (ss >> lines >> columns) {
            char extra_char;
            if (!(ss >> extra_char)) {
                cout << "Lines: " << lines << endl;
                cout << "Columns: " << columns << endl;
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
            diagram.push_back(line);
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