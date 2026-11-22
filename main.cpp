#include "Tree.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<Tree<std::string>*> raizesGlobal;

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
    for(Tree<std::string>* raiz : raizesGlobal) {
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
            std::cout << "O ancestral em comum de " << nome1 << " e " << nome2 << " é " << ancestral1 << "." << std::endl;
            return true;
        }
        ancestral1 = dynamic_cast<Tree<std::string>*>(ancestral1->getParent());
    }
    while(ancestral2 != nullptr) {
        if(ancestral2 == ancestral1) {
            std::cout << "O ancestral em comum de " << nome1 << " e " << nome2 << " é " << ancestral1 << "." << std::endl;
            return true;
        }
        ancestral2 = dynamic_cast<Tree<std::string>*>(ancestral2->getParent());
    }
    std::cout << nome1 << " e " << nome2 << " não tem ancestral em comum." << std::endl;
    return false;
}

bool saoIrmaos(std::string nome1, std::string nome2) {
    Tree<std::string>* pessoa1 = dynamic_cast<Tree<std::string>*>(buscarNaFloresta(nome1));
    Tree<std::string>* pessoa2 = dynamic_cast<Tree<std::string>*>(buscarNaFloresta(nome2));

    if(pessoa1 == pessoa2 || pessoa1 == nullptr || pessoa2 == nullptr) {
        std::cout << nome1 << " e " << nome2 << " nao sao irmaos." << std::endl;
        return false;
    }

    if(pessoa1->getParent() != nullptr && pessoa1->getParent() == pessoa2->getParent()) {
        std::cout << nome1 << " e " << nome2 << " sao irmaos." << std::endl;
        return true;
    } else {
        std::cout << nome1 << " e " << nome2 << " nao sao irmaos." << std::endl;
        return false;
    }
}

bool saoPrimos(std::string nome1, std::string nome2) {
    Tree<std::string>* pessoa1 = dynamic_cast<Tree<std::string>*>(buscarNaFloresta(nome1));
    Tree<std::string>* pessoa2 = dynamic_cast<Tree<std::string>*>(buscarNaFloresta(nome2));

    if(pessoa1 == pessoa2 || pessoa1 == nullptr || pessoa2 == nullptr) {
        std::cout << nome1 << " e " << nome2 << " nao sao primos." << std::endl;
        return false;
    }

    Tree<std::string>* pai1 = dynamic_cast<Tree<std::string>*>(pessoa1->getParent());
    Tree<std::string>* pai2 = dynamic_cast<Tree<std::string>*>(pessoa2->getParent());

    if(pai1 == pai2 || pai1 == nullptr || pai2 == nullptr) {
        std::cout << nome1 << " e " << nome2 << " nao sao primos." << std::endl;
        return false;
    }
    
    Tree<std::string>* avo1 = dynamic_cast<Tree<std::string>*>(pai1->getParent());
    Tree<std::string>* avo2 = dynamic_cast<Tree<std::string>*>(pai2->getParent());

    if(avo1 != nullptr && avo1 == avo2) {
        std::cout << nome1 << " e " << nome2 << " sao primos." << std::endl;
        return true;
    } else {
        std::cout << nome1 << " e " << nome2 << " nao sao primos." << std::endl;
        return false;
    }
}

int main() {
    raizesGlobal = lerArquivo("relacoes_got.txt");

    if(raizesGlobal.empty()) {
        return 1;
    }

    std::cout << "Total de arvores (casas): " << raizesGlobal.size() << "\n" << std::endl;

    for(Tree<std::string>* raiz : raizesGlobal) {
        std::cout << "Raiz: " << raiz->getItem()
                  << " | Nos(filhos): " << raiz->size()
                  << " | Altura(geracoes): " << raiz->height() << std::endl;

        for(TreeTDA<std::string>* no : raiz->preOrder()) {
            std::cout << "  - " << no->getItem() << std::endl;
        }
        std::cout << std::endl;
    }

    ehAncestral("Rickard Stark", "Robb Stark"); //verdadeiro
    ehAncestral("Rickard Stark", "Jon Snow"); //verdadeiro
    ehAncestral("Aerys II Targaryen", "Jon Snow"); //verdadeiro
    saoIrmaos("Robb Stark", "Sansa Stark"); //verdadeiro
    saoIrmaos("Robb Stark", "Jon Snow"); //falso
    saoIrmaos("Doran Martell", "Elia Martell"); //verdadeiro
    saoPrimos("Robb Stark", "Jon Snow"); //verdadeiro
    saoPrimos("Cersei Lannister", "Martyn Lannister"); //verdadeiro
    saoPrimos("Rodrik Greyjoy", "Theon Greyjoy"); //falso

    //libera memória
    for(Tree<std::string>* raiz : raizesGlobal) {
        delete raiz;
    }

    return 0;
}