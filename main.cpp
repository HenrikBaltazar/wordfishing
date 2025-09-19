#include <iostream>
#include "InputFile.h" // Inclui a nossa classe para poder usá-la
#include "wordfishing.h"

using namespace std;

int main() {
    InputFile entryFile("cacapalavras.txt");

    if (entryFile.readFile()) {
        cout << "Conteudo do arquivo lido com sucesso:" << endl;
        cout << "------------------------------------" << endl;
    /*    cout << "Linhas: "<< entryFile.getDiagramLines() << endl;
        cout << "Colunas: "<< entryFile.getDiagramColumns() << endl;


        cout << endl << "Palavras:" << endl;
        cout << "------------------------------------" << endl;
        const auto& findWords = entryFile.getWords();
        for (const string& word : findWords) {
            cout << word << endl;
        }

        cout << endl  << "Diagrama:" << endl;
        cout << "------------------------------------" << endl;
        const auto& findDiagram = entryFile.getDiagram();
        for (const string& line : findDiagram) {
            cout << line << endl;
        }
*/
        wordfishing solver(entryFile);
        vector<std::string> solved_diagram = solver.solve();

        cout << "--- Diagrama Resolvido ---" << endl;
        for (const std::string& line : solved_diagram) {
            cout << line << endl;
        }

    } else {
        cerr << "Falha ao processar o arquivo." << endl;
        return 1;
    }

    return 0;
}