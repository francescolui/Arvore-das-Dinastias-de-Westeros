#ifndef TREETAD_H
#define TREETAD_H

template <typename T>
class TreeTDA {
public:
    virtual ~TreeTDA() = default;
    virtual void addChild(TreeTDA<T>* tree) = 0;
    virtual void addChild(int index, TreeTDA<T>* tree) = 0;
    virtual TreeTDA<T>* removeChild(int index) = 0;
    virtual TreeTDA<T>* getChild(int index) = 0;
    virtual int childrenCount() const = 0;
    virtual int size() const = 0;
    virtual T getItem() const = 0;
    virtual TreeTDA<T>* getParent() const = 0;
};

#endif