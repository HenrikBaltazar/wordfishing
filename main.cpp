#include <iostream>
#include "InputFile.h" // Inclui a nossa classe para poder usá-la
#include "wordfishing.h"

using namespace std;

int main() {
    InputFile entryFile("cacapalavras.txt");
    const string BOLD_ON = "\033[1m";
    const string BOLD_OFF = "\033[0m";

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
        vector<string> solved_diagram = solver.solve();
        const auto& highlight = solver.getHighlightGrid();

        cout << "--- Diagrama Resolvido ---" << endl;
        for (int r = 0; r < solved_diagram.size(); ++r) {
            for (int c = 0; c < solved_diagram[r].size(); ++c) {
                if (highlight[r][c]) {
                    cout << BOLD_ON << solved_diagram[r][c] << BOLD_OFF;
                } else {
                    cout << solved_diagram[r][c];
                }
            }
            cout << endl;
        }

    } else {
        cerr << "Falha ao processar o arquivo." << endl;
        return 1;
    }

    return 0;
}