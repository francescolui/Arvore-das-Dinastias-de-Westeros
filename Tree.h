#pragma once

#include "TreeTAD.h"
#include <vector>

class Tree : public TreeTDA {

        private:
            TreeTDA* parent;
            int element;
            std::vector<TreeTDA*> children;

            void preOrderAUX(TreeTDA* node, std::vector<TreeTDA*>& order);
            void posOrderAUX(TreeTDA* node, std::vector<TreeTDA*>& order);
            int heightAUX(TreeTDA* node);

        public:
            Tree(int element);
            ~Tree();
            void addChild(TreeTDA* tree) override;
            void addChild(int index, TreeTDA* tree) override;
            TreeTDA* removeChild(int index) override;
            TreeTDA* getChild(int index) override;
            int childrenCount() const override;
            int size() const override;
            int getItem() const override;
            TreeTDA* getParent() const override;

            std::vector<TreeTDA*> preOrder();
            std::vector<TreeTDA*> posOrder();
            std::vector<TreeTDA*> breadth();
            int height();
            int level();
};