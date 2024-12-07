#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <set>
#include <vector>
#include <fstream> // Necessário para operações com arquivos

using namespace std;

struct CartelaBingo {
    string linha[5] = {"B", "I", "N", "G", "O"};
    int cartela[5][5];
    bool marcado[5][5] = {{false}};  // Inicializa todos os valores como falso (não marcado)
};

// Declaração dos protótipos
void gerarCartela(CartelaBingo* bingo);
void imprimirCartela(const CartelaBingo* bingo);
void exibirCartelas(const vector<CartelaBingo*>& cartelas);
void inserirNumero(vector<int>& numerosChamados, vector<CartelaBingo*>& cartelas);
void exibirJogo(const vector<int>& numerosChamados, const vector<CartelaBingo*>& cartelas);
void verificarVitoria(CartelaBingo* bingo);
void exportarCartelas(const vector<CartelaBingo*>& cartelas);

int main() {
    vector<CartelaBingo*> cartelas; // Armazena ponteiros para as cartelas geradas
    vector<int> numerosChamados;    // Armazena os números chamados
    int opcao;
    int qntCartelas;

    // Inicializar a semente do gerador de números aleatórios uma única vez
    srand(time(0));

    do {
        cout << "Menu de Opcoes:" << endl;
        cout << "1- Pedir Cartela" << endl;
        cout << "2- Exibir Cartelas" << endl;
        cout << "3- Inserir Numero" << endl;
        cout << "4- Exibir Numeros Chamados e Cartela Marcada" << endl;
        cout << "5- Exportar Cartelas para TXT" << endl; // Nova opção
        cout << "0- Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch(opcao) {
            case 1: 
                cout << "Quantas cartelas voce deseja pedir? ";
                cin >> qntCartelas;
                for (int i = 0; i < qntCartelas; i++) {
                    CartelaBingo* bingo = new CartelaBingo; // Aloca dinamicamente uma nova cartela
                    gerarCartela(bingo);
                    cartelas.push_back(bingo); // Armazena o ponteiro no vetor
                    cout << "Cartela de Bingo #" << cartelas.size() << " gerada!" << endl;
                }
                break;

            case 2:
                exibirCartelas(cartelas);
                break;

            case 3:
                inserirNumero(numerosChamados, cartelas);
                break;

            case 4:
                exibirJogo(numerosChamados, cartelas);
                break;

            case 5: // Chamada da nova função
                exportarCartelas(cartelas);
                break;

            case 0:
                cout << "Saindo do Bingo" << endl;
                break;

            default:
                cout << "Opcao invalida." << endl;
                break;
        }

    } while (opcao != 0);

    // Liberando a memória alocada para as cartelas
    for (size_t i = 0; i < cartelas.size(); ++i) {
        delete cartelas[i];  // Desaloca a memória de cada cartela
    }

    return 0;
}

// Função para gerar uma nova cartela de bingo
void gerarCartela(CartelaBingo* bingo) {
    int intervalos[5][2] = {
        {1, 15}, {16, 30}, {31, 45}, {46, 60}, {61, 75}
    };

    for (int coluna = 0; coluna < 5; coluna++) {
        set<int> numerosGerados;
        for (int linha = 0; linha < 5; linha++) {
            if (coluna == 2 && linha == 2) {
                bingo->cartela[linha][coluna] = 0; // "FREE" no centro
                continue;
            }
            int numero;
            do {
                numero = rand() % (intervalos[coluna][1] - intervalos[coluna][0] + 1) + intervalos[coluna][0];
            } while (numerosGerados.find(numero) != numerosGerados.end());
            numerosGerados.insert(numero);
            bingo->cartela[linha][coluna] = numero;
        }
    }
}

// Função para imprimir a cartela de bingo
void imprimirCartela(const CartelaBingo* bingo) {
    for (int i = 0; i < 5; i++) {
        cout << bingo->linha[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 2 && j == 2) {
                cout << "FREE\t";
            } else if (bingo->marcado[i][j]) {
                cout << "X\t";  // Marca como "X" se estiver marcado
            } else {
                cout << bingo->cartela[i][j] << "\t";
            }
        }
        cout << endl;
    }
}

// Função para exibir todas as cartelas
void exibirCartelas(const vector<CartelaBingo*>& cartelas) {
    if (cartelas.empty()) {
        cout << "Nenhuma cartela foi gerada ainda!" << endl;
        return;
    }

    for (size_t i = 0; i < cartelas.size(); i++) {
        cout << "Cartela de Bingo #" << i + 1 << ":" << endl;
        imprimirCartela(cartelas[i]);
        cout << endl;
    }
}

// Função para inserir um número na cartela e marcar a posição
void inserirNumero(vector<int>& numerosChamados, vector<CartelaBingo*>& cartelas) {
    if (cartelas.empty()) {
        cout << "Nenhuma cartela foi gerada ainda!" << endl;
        return;
    }

    int numero;
    cout << "Digite um numero (1-75): ";
    cin >> numero;

    if (numero < 1 || numero > 75) {
        cout << "Numero invalido! Digite um numero entre 1 e 75." << endl;
        return;
    }

    // Verificar se o número já foi chamado
    for (int chamado : numerosChamados) {
        if (chamado == numero) {
            cout << "Numero ja foi chamado!" << endl;
            return;
        }
    }

    // Adiciona o número à lista de chamados
    numerosChamados.push_back(numero);

    // Marca o número nas cartelas, se presente
    for (CartelaBingo* bingo : cartelas) {
        bool numeroEncontrado = false;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (bingo->cartela[i][j] == numero) {
                    bingo->marcado[i][j] = true;
                    numeroEncontrado = true;
                    cout << "Numero " << numero << " marcado na cartela!" << endl;
                }
            }
        }
        if (!numeroEncontrado) {
            cout << "Numero " << numero << " nao encontrado na cartela." << endl;
        }
    }

    // Verifica se algum bingo, linha ou coluna foi atingido
    for (CartelaBingo* bingo : cartelas) {
        verificarVitoria(bingo);
    }
}

// Função para verificar se há vitória na cartela
void verificarVitoria(CartelaBingo* bingo) {
    // Verificar se há uma linha completa
    for (int i = 0; i < 5; i++) {
        bool linhaCompleta = true;
        for (int j = 0; j < 5; j++) {
            if (!bingo->marcado[i][j]) {
                linhaCompleta = false;
                break;
            }
        }
        if (linhaCompleta) {
            cout << "LINHA! Linha " << i + 1 << " completa!" << endl;
            return;
        }
    }

    // Verificar se há uma coluna completa
    for (int j = 0; j < 5; j++) {
        bool colunaCompleta = true;
        for (int i = 0; i < 5; i++) {
            if (!bingo->marcado[i][j]) {
                colunaCompleta = false;
                break;
            }
        }
        if (colunaCompleta) {
            cout << "COLUNA! Coluna " << j + 1 << " completa!" << endl;
            return;
        }
    }

    // Verificar se há o bingo completo
    bool bingoCompleto = true;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (!bingo->marcado[i][j]) {
                bingoCompleto = false;
                break;
            }
        }
        if (!bingoCompleto) break;
    }

    if (bingoCompleto) {
        cout << "BINGO! Cartela completa!" << endl;
    }
}

// Função para exibir os números chamados e a cartela atualizada
void exibirJogo(const vector<int>& numerosChamados, const vector<CartelaBingo*>& cartelas) {
    if (cartelas.empty()) {
        cout << "Nenhuma cartela foi gerada ainda!" << endl;
        return;
    }

    if (numerosChamados.empty()) {
        cout << "Nenhum numero foi chamado ainda!" << endl;
        return;
    }

    cout << "Numeros chamados: ";
    for (int numero : numerosChamados) {
        cout << numero << " ";
    }
    cout << endl;

    cout << "Cartelas atuais:" << endl;
    for (size_t i = 0; i < cartelas.size(); ++i) {
        cout << "Cartela #" << i + 1 << ":" << endl;
        imprimirCartela(cartelas[i]);
        cout << "Numeros marcados: ";

        // Listar os números marcados na cartela
        for (int linha = 0; linha < 5; ++linha) {
            for (int coluna = 0; coluna < 5; ++coluna) {
                if (cartelas[i]->marcado[linha][coluna]) {
                    if (linha == 2 && coluna == 2) continue; // Ignorar o espaço "FREE"
                    cout << cartelas[i]->cartela[linha][coluna] << " ";
                }
            }
        }
        cout << endl << endl;
    }
}


// Função para exportar cartelas para arquivos de texto
void exportarCartelas(const vector<CartelaBingo*>& cartelas) {
    if (cartelas.empty()) {
        cout << "Nenhuma cartela foi gerada ainda para exportar!" << endl;
        return;
    }

    for (size_t i = 0; i < cartelas.size(); ++i) {
        string nomeArquivo = "Cartela_" + to_string(i + 1) + ".txt";
        ofstream arquivo(nomeArquivo);

        if (arquivo.is_open()) {
            arquivo << "Cartela de Bingo #" << i + 1 << ":\n";
            for (int j = 0; j < 5; ++j) {
                arquivo << cartelas[i]->linha[j] << "\t";
            }
            arquivo << "\n";

            for (int linha = 0; linha < 5; ++linha) {
                for (int coluna = 0; coluna < 5; ++coluna) {
                    if (linha == 2 && coluna == 2) {
                        arquivo << "FREE\t"; // Espaço central
                    } else {
                        arquivo << cartelas[i]->cartela[linha][coluna] << "\t";
                    }
                }
                arquivo << "\n";
            }

            arquivo.close();
            cout << "Cartela #" << i + 1 << " exportada para " << nomeArquivo << endl;
        } else {
            cout << "Erro ao criar o arquivo " << nomeArquivo << endl;
        }
    }
}
