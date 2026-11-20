#ifndef TREE_H
#define TREE_H

#include "TreeTAD.h"
#include <queue>
#include <stdexcept>
#include <vector>

template <typename T>
class Tree : public TreeTDA<T> {
private:
    TreeTDA<T>* parent;
    T element;
    std::vector<TreeTDA<T>*> children;

    void preOrderAux(TreeTDA<T>* node, std::vector<TreeTDA<T>*>& order);
    void posOrderAux(TreeTDA<T>* node, std::vector<TreeTDA<T>*>& order);
    int heightAux(TreeTDA<T>* node);

public:
    Tree(T element);
    ~Tree();
    void addChild(TreeTDA<T>* tree) override;
    void addChild(int index, TreeTDA<T>* tree) override;
    TreeTDA<T>* removeChild(int index) override;
    TreeTDA<T>* getChild(int index) override;
    int childrenCount() const override;
    int size() const override;
    T getItem() const override;
    TreeTDA<T>* getParent() const override;

    std::vector<TreeTDA<T>*> preOrder();
    std::vector<TreeTDA<T>*> posOrder();
    std::vector<TreeTDA<T>*> breadth();
    int height();
    int level();
};

template <typename T>
Tree<T>::Tree(T element) : parent(nullptr), element(element), children() {}

template <typename T>
Tree<T>::~Tree() {
    for (TreeTDA<T>* child : children) {
        delete child;
    }
}

template <typename T>
void Tree<T>::addChild(TreeTDA<T>* tree) {
    if (tree == nullptr) {
        return;
    }
    children.push_back(tree);
    Tree<T>* tree2 = dynamic_cast<Tree<T>*>(tree);
    if (tree2 != nullptr) {
        tree2->parent = this;
    }
}

template <typename T>
void Tree<T>::addChild(int index, TreeTDA<T>* tree) {
    if (index < 0 || index > static_cast<int>(children.size())) {
        throw std::out_of_range("Index out of range");
    }
    if (tree == nullptr) {
        return;
    }
    children.insert(children.begin() + index, tree);
    Tree<T>* tree2 = dynamic_cast<Tree<T>*>(tree);
    if (tree2 != nullptr) {
        tree2->parent = this;
    }
}

template <typename T>
TreeTDA<T>* Tree<T>::removeChild(int index) {
    if (index >= 0 && index < static_cast<int>(children.size())) {
        TreeTDA<T>* removed = children[index];
        children.erase(children.begin() + index);
        Tree<T>* removedTree = dynamic_cast<Tree<T>*>(removed);
        if (removedTree != nullptr) {
            removedTree->parent = nullptr;
        }
        return removed;
    }
    return nullptr;
}

template <typename T>
TreeTDA<T>* Tree<T>::getChild(int index) {
    if (index >= 0 && index < static_cast<int>(children.size())) {
        return children.at(index);
    }
    return nullptr;
}

template <typename T>
int Tree<T>::childrenCount() const {
    return static_cast<int>(children.size());
}

template <typename T>
int Tree<T>::size() const {
    int t = 1;
    for (TreeTDA<T>* child : children) {
        t += child->size();
    }
    return t;
}

template <typename T>
T Tree<T>::getItem() const {
    return this->element;
}

template <typename T>
TreeTDA<T>* Tree<T>::getParent() const {
    return this->parent;
}

template <typename T>
void Tree<T>::preOrderAux(TreeTDA<T>* node, std::vector<TreeTDA<T>*>& order) {
    if (node == nullptr) {
        return;
    }
    order.push_back(node);
    for (int i = 0; i < node->childrenCount(); i++) {
        preOrderAux(node->getChild(i), order);
    }
}

template <typename T>
std::vector<TreeTDA<T>*> Tree<T>::preOrder() {
    std::vector<TreeTDA<T>*> order;
    preOrderAux(this, order);
    return order;
}

template <typename T>
void Tree<T>::posOrderAux(TreeTDA<T>* node, std::vector<TreeTDA<T>*>& order) {
    if (node == nullptr) {
        return;
    }
    for (int i = 0; i < node->childrenCount(); i++) {
        posOrderAux(node->getChild(i), order);
    }
    order.push_back(node);
}

template <typename T>
std::vector<TreeTDA<T>*> Tree<T>::posOrder() {
    std::vector<TreeTDA<T>*> order;
    posOrderAux(this, order);
    return order;
}

template <typename T>
std::vector<TreeTDA<T>*> Tree<T>::breadth() {
    std::vector<TreeTDA<T>*> order;
    std::queue<TreeTDA<T>*> q;
    q.push(this);

    while (!q.empty()) {
        TreeTDA<T>* current = q.front();
        q.pop();
        order.push_back(current);

        for (int i = 0; i < current->childrenCount(); i++) {
            TreeTDA<T>* child = current->getChild(i);
            if (child != nullptr) {
                q.push(child);
            }
        }
    }
    return order;
}

template <typename T>
int Tree<T>::heightAux(TreeTDA<T>* node) {
    if (node == nullptr || node->childrenCount() == 0) {
        return 0;
    }
    int maxChildHeight = 0;
    for (int i = 0; i < node->childrenCount(); i++) {
        int h = heightAux(node->getChild(i));
        if (h > maxChildHeight) {
            maxChildHeight = h;
        }
    }
    return 1 + maxChildHeight;
}

template <typename T>
int Tree<T>::height() {
    return heightAux(this);
}

template <typename T>
int Tree<T>::level() {
    int lvl = 0;
    TreeTDA<T>* current = this->parent;
    while (current != nullptr) {
        lvl++;
        current = current->getParent();
    }
    return lvl;
}

#endif