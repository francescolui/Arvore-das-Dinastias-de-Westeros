#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Tree.h"

Tree<std::string>* buscarNo(const std::vector<Tree<std::string>*>& nos, const std::string& nome) {
    for(Tree<std::string>* no : nos) {
        if(no->getItem() == nome) {
            return no;
        }
    }
    return nullptr;
}

std::vector<Tree<std::string>*> lerArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    std::vector<Tree<std::string>*> raizes;

    if(!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return raizes;
    }

    std::string linha;
    int qtdRelacoes = 0;

    if(std::getline(arquivo, linha)) {
        qtdRelacoes = std::stoi(linha);
    }

    std::vector<Tree<std::string>*> nos;

    for(int i = 0; i < qtdRelacoes && std::getline(arquivo, linha); i++) {
        if(linha.empty()) {
            continue;
        }

        std::stringstream ss(linha);
        std::string nomePai, nomeFilho;

        if(ss >> std::quoted(nomePai) >> std::quoted(nomeFilho)) {
            Tree<std::string>* pai = buscarNo(nos, nomePai);
            if(pai == nullptr) {
                pai = new Tree<std::string>(nomePai);
                nos.push_back(pai);
            }

            Tree<std::string>* filho = buscarNo(nos, nomeFilho);
            if(filho == nullptr) {
                filho = new Tree<std::string>(nomeFilho);
                nos.push_back(filho);
            }

            pai->addChild(filho);
        }
    }
    arquivo.close();

    for(Tree<std::string>* no : nos) {
        if(no->getParent() == nullptr) {
            raizes.push_back(no);
        }
    }

    return raizes;
}

int main() {
    std::vector<Tree<std::string>*> raizes = lerArquivo("relacoes_got.txt");

    if(raizes.empty()) {
        return 1;
    }

    std::cout << "Total de arvores (casas): " << raizes.size() << "\n" << std::endl;

    for(Tree<std::string>* raiz : raizes) {
        std::cout << "Raiz: " << raiz->getItem()
                  << " | Nos(filhos): " << raiz->size()
                  << " | Altura(geracoes): " << raiz->height() << std::endl;

        for(TreeTDA<std::string>* no : raiz->preOrder()) {
            std::cout << "  - " << no->getItem() << std::endl;
        }
        std::cout << std::endl;
    }

    //libera memória
    for(Tree<std::string>* raiz : raizes) {
        delete raiz;
    }

    return 0;
}