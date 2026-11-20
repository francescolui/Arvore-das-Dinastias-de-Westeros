class TreeTAD {
public:
    virtual void addChild(TreeTAD *tree) = 0;
    virtual void addChild(int index, TreeTAD *tree) = 0;
    virtual TreeTAD *removeChild(int index) = 0;
    virtual TreeTAD *getChild(int index) = 0;
    virtual int childrenCount() const = 0;
    virtual int size() const = 0;
    virtual int getItem() const = 0;
    virtual TreeTAD *getParent() const = 0;
};