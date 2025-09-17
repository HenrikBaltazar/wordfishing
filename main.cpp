#include <iostream>
#include "InputFile.h" // Inclui a nossa classe para poder usá-la

using namespace std;

int main() {
    InputFile entryFile("cacapalavras.txt");

    if (entryFile.readFile()) {
        cout << "Conteudo do arquivo lido com sucesso:" << endl;
        cout << "------------------------------------" << endl;

        const auto& content = entryFile.getDiagram();

        /*for (const string& linha : content) {
            cout << linha << endl;
        }*/

    } else {
        cerr << "Falha ao processar o arquivo." << endl;
        return 1;
    }

    return 0;
}