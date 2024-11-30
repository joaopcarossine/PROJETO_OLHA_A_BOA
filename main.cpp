#include <iostream>
#include <string>

using namespace std;

struct CartelaBingo {
    string linha[5] = {"B", "I", "N", "G", "O"};
    int cartela[5][5];
    bool marcado[5][5];
};

int main() {
    CartelaBingo bingo;
    int opcao;

    do {
        cout << "Menu de Opcoes:" << endl;
        cout << "1- Pedir Cartela" << endl;
        cout << "0- Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch(opcao) {
            case 1: 
                cout << "Cartela de Bingo: " << endl;
                for (int i = 0; i < 5; i++) {
                    cout << bingo.linha[i] << " ";
                }
                cout << endl;
                break;


            case 0:
                cout << "Saindo do Bingo" << endl;
                break;

            default:
                cout << "Opção invalida." << endl;
                break;
        }

    } while (opcao != 0);

    return 0;
}

