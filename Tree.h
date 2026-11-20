#pragma once

#include "TreeTAD.h"
#include <vector>

class Tree : public TreeTAD {
private:
    TreeTAD* parent;
    int element;
    std::vector<TreeTAD*> children;

    void preOrderAUX(TreeTAD* node, std::vector<TreeTAD*>& order);
    void posOrderAUX(TreeTAD* node, std::vector<TreeTAD*>& order);
    int heightAUX(TreeTAD* node);

public:
    Tree(int element);
    ~Tree();
    void addChild(TreeTAD* tree) override;
    void addChild(int index, TreeTAD* tree) override;
    TreeTAD* removeChild(int index) override;
    TreeTAD* getChild(int index) override;
    int childrenCount() const override;
    int size() const override;
    int getItem() const override;
    TreeTAD* getParent() const override;

    std::vector<TreeTAD*> preOrder();
    std::vector<TreeTAD*> posOrder();
    std::vector<TreeTAD*> breadth();
    int height();
    int level();
};