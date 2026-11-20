#include "Tree.h"
#include <stdexcept>

Tree::Tree(int element) : parent(nullptr), element(element), children() {} //children é opcional, pois std::vector é uma classe também e o construtor padrao dela inicializa o vector como vazio.

Tree::~Tree() {
    for(TreeTAD* child : children) {
        delete child;
    }
}

void Tree::addChild(TreeTAD* tree) {
    children.push_back(tree);
    Tree* tree2 = dynamic_cast<Tree*>(tree);
    if(tree2 != nullptr) {
        tree2->parent = this;
    }
}

void Tree::addChild(int index, TreeTAD* tree) {
    if(index < 0 || index > static_cast<int>(children.size())) {
        throw std::out_of_range("Index out of range");
    }
    children.insert(children.begin() + index, tree);
    Tree* tree2 = dynamic_cast<Tree*>(tree);
    if(tree2 != nullptr) {
        tree2->parent = this;
    }
}

TreeTAD* Tree::removeChild(int index) {
    if(index >= 0 && index < children.size()) {
        Tree* removedChild = dynamic_cast<Tree*>(children[index]);
        children.erase(children.begin() + index);
        if(removeChild != nullptr) {
            removedChild->parent = nullptr;
        }
        return removedChild;
    }
    return nullptr;
}

TreeTAD* Tree::getChild(int index) {
    if(index >= 0 && index < static_cast<int>(children.size())) {
        return children.at(index);
    }
    return nullptr;
}

int Tree::childrenCount() const {
    return children.size();
}

int Tree::size() const { //quantidade de filhos
    int t = 1;
    for(TreeTAD* child : children) {
        t += child->size();
    }
    return t;
}

int Tree::getItem() const {
    return this->element;
}

TreeTAD* Tree::getParent() const {
    return this->parent;
}

void Tree::preOrderAUX(TreeTAD* node, std::vector<TreeTAD*>& order) {
    if(node == nullptr) return;
    order.push_back(node);
    for(int i = 0; i < node->childrenCount(); i++) {
        preOrderAUX(node->getChild(i), order);
    }
}

std::vector<TreeTAD*> Tree::preOrder() {
    std::vector<TreeTAD*> order;
    preOrderAUX(this, order);
    return order;
}

void posOrderAUX(TreeTAD* node, std::vector<TreeTAD*>& order) {
    if(node == nullptr) return;
    for(int i = 0; i < node->childrenCount(); i++) {
        posOrderAUX(node->getChild(i), order);
    }
    order.push_back(node);
}

std::vector<TreeTAD*> Tree::posOrder() {
    std::vector<TreeTAD*> order;
    posOrderAUX(this, order);
    return order;
}

std::vector<TreeTAD*> Tree::breadth() {
    
}

int Tree::heightAUX(TreeTAD* node) {

}

int Tree::height() {

}

int Tree::level() {
    
}