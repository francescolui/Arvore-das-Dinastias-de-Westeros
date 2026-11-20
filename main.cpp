#include "Tree.h"
#include <fstream>
#include <iostream>
#include <string>

void lerArquivo() {
    std::ifstream arquivo("relacoes_got.txt");

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return;
    }
    std::string linha;
        while (std::getline(arquivo, linha)) {
            std::cout << linha << std::endl;
        }
    arquivo.close();
    }

int main() {

}