class TreeTDA {
public:
    virtual void addChild(TreeTDA* tree) = 0;
    virtual void addChild(int index, TreeTDA* tree) = 0;
    virtual TreeTDA* removeChild(int index) = 0;
    virtual TreeTDA* getChild(int index) = 0;
    virtual int childrenCount() const = 0;
    virtual int size() const = 0;
    virtual int getItem() const = 0;
    virtual TreeTDA* getParent() const = 0;
};