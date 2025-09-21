#include <iostream>
#include <cstdlib>
#include <fstream>

#include "InputFile.h"
#include "wordfishing.h"

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool checkFileInputFailed(string input) {
    if (input.length() > 4 && input.ends_with(".txt") ) {
        ifstream f(input.c_str());
        if (f.good()) {
            cout << "File already exists" << endl;
            f.close();
            return false;
        }
    }
    if (input.empty() || input == "" || input == " " || input == "\n") {
        return false;
    }
    return true;
}

int main() {

    const string HIGHLIGHT_ON = "\033[1;32m";
    const string HIGHLIGHT_OFF = "\033[0m";
    bool running = true;
    string input;
    while (running) {
        clearScreen();
        cout << HIGHLIGHT_ON;
        cout << "------------------------------------" << endl;
        cout << "--         CAÇA PALAVRAS          --" << endl;
        cout << "------------------------------------" << endl;
        cout << HIGHLIGHT_OFF;
        do {
            cout << "Insira o nome do arquivo (cacapalavras.txt): ";
            getline(cin, input);
        }while (checkFileInputFailed(input));
        if (input.empty() || input == "" || input == " " || input == "\n") {
            input = "cacapalavras.txt";
        }
        InputFile entryFile(input);
        if (entryFile.readFile()) {
            if (entryFile.getDiagramColumns()<entryFile.getDiagram().size() && !entryFile.getWords().empty()) {
                wordfishing solver(entryFile);
                vector<string> solved_diagram = solver.solvedDiagram();
                string wordsum = solver.getSummary();
                const auto& highlight = solver.getHighlightGrid();

                cout << "Conteudo do arquivo lido com sucesso:" << endl;
                cout << "------------------------------------" << endl;


                int selection = 0;
                do {
                    cout << "Selecione a opção desejada:" <<endl;
                    cout << "1: Ver diagrama original" << endl;
                    cout << "2: Ver palavras a encontrar" << endl;
                    cout << "3: Ver sumário de palavras encontradas" << endl;
                    cout << "4: Ver diagrama com palavras encontradas" << endl;
                    cout << "5: Iniciar nova procura" << endl;
                    cout << "6: Sair" << endl;
                    cin >> selection;
                    switch (selection) {
                        case 1:
                            for (int r = 0; r < entryFile.getDiagramLines(); ++r) {
                                for (int c = 0; c < entryFile.getDiagramColumns(); ++c) {
                                    cout<<entryFile.getDiagram()[r][c];
                                }
                                cout<<endl;
                            }
                            break;
                        case 2:
                            cout << "Palavras a encontrar: "<<endl;
                            for (auto word : entryFile.getWords()) {
                                cout<<word<<endl;
                            }
                            break;
                        case 3:
                            cout << wordsum << endl;
                            break;
                        case 4:
                            cout << HIGHLIGHT_ON << "--- Diagrama Resolvido ---"<< HIGHLIGHT_OFF << endl;
                            for (int r = 0; r < entryFile.getDiagramLines(); ++r) {
                                for (int c = 0; c < entryFile.getDiagramColumns(); ++c) {
                                    if (highlight[r][c]) {
                                        cout << HIGHLIGHT_ON << solved_diagram[r][c] << HIGHLIGHT_OFF;
                                    } else {
                                        cout << solved_diagram[r][c];
                                    }
                                }
                                cout << endl;
                            }
                            break;
                        case 5:
                            cin.ignore();
                            break;
                        case 6:
                            return 0;
                        default:
                            break;
                    }
                }while (selection != 5);
            }else {
                cout << "Arquivo mal-formatado" << endl;
            }
        } else {
            cout << "Falha ao processar o arquivo." << endl;
        }
    }
    return 0;
}