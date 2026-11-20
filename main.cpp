#include "Tree.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<Tree<std::string>*> raizes;

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

TreeTDA<std::string>* buscarNaFloresta(const std::string& nome) {
    for(Tree<std::string>* raiz : raizes) {
        for(TreeTDA<std::string>* no : raiz->breadth()) {
            if(no->getItem() == nome) {
                return no;
            }
        }
    }
    return nullptr;
}

bool ehAncestral(std::string nome1, std::string nome2) {
    Tree<std::string>* pessoa1 = dynamic_cast<Tree<std::string>*>(buscarNaFloresta(nome1));
    Tree<std::string>* pessoa2 = dynamic_cast<Tree<std::string>*>(buscarNaFloresta(nome2));
    Tree<std::string>* ancestral1 = dynamic_cast<Tree<std::string>*>(pessoa1->getParent());
    Tree<std::string>* ancestral2 = dynamic_cast<Tree<std::string>*>(pessoa2->getParent());
    while(ancestral1 != nullptr) {
        if(ancestral1 == ancestral2) {
            return true;
        }
        ancestral1 = dynamic_cast<Tree<std::string>*>(ancestral1->getParent());
    }
    while(ancestral2 != nullptr) {
        if(ancestral2 == ancestral1) {
            return true;
        }
        ancestral2 = dynamic_cast<Tree<std::string>*>(ancestral2->getParent());
    }
    return false;
}

bool saoIrmaos(std::string nome1, std::string nome2) {
    Tree<std::string>* pessoa1 = dynamic_cast<Tree<std::string>*>(buscarNaFloresta(nome1));
    Tree<std::string>* pessoa2 = dynamic_cast<Tree<std::string>*>(buscarNaFloresta(nome2));

    if(pessoa1 == pessoa2 || pessoa1 == nullptr || pessoa2 == nullptr) return false;

    return pessoa1->getParent() != nullptr && pessoa1->getParent() == pessoa2->getParent();
}

bool saoPrimos(std::string nome1, std::string nome2) {
    Tree<std::string>* pessoa1 = dynamic_cast<Tree<std::string>*>(buscarNaFloresta(nome1));
    Tree<std::string>* pessoa2 = dynamic_cast<Tree<std::string>*>(buscarNaFloresta(nome2));

    if(pessoa1 == pessoa2 || pessoa1 == nullptr || pessoa2 == nullptr) return false;

    Tree<std::string>* pai1 = dynamic_cast<Tree<std::string>*>(pessoa1->getParent());
    Tree<std::string>* pai2 = dynamic_cast<Tree<std::string>*>(pessoa2->getParent());

    if(pai1 == pai2 || pai1 == nullptr || pai2 == nullptr) return false;
    
    Tree<std::string>* avo1 = dynamic_cast<Tree<std::string>*>(pai1->getParent());
    Tree<std::string>* avo2 = dynamic_cast<Tree<std::string>*>(pai2->getParent());

    if(avo1 == avo2 || avo1 == nullptr || avo2 == nullptr) return false;

    return avo1 != nullptr && avo1 == avo2;

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