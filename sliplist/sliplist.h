#ifndef SLIPLISTDEMO_SLIPLIST_H
#define SLIPLISTDEMO_SLIPLIST_H

#include <stddef.h>
#include <assert.h>
#include "random.h"

const int MAX_LEVEL = 16;

//define key and value type
typedef int KeyType;
typedef int ValueType;

//define node
typedef struct nodeStructure* Node;
struct nodeStructure{
    KeyType key;
    ValueType value;
    Node forward[1];
};

//define sliplist list
typedef struct listStructure* List;
struct listStructure{
    int level;
    Node header;
};

class SlipList{
public:
    SlipList():rnd_(0xdeadbeef){ InitList(); }

    ~SlipList(){ FreeList();}

    bool Search(const KeyType& key, ValueType& value);

    bool Insert(const KeyType& key, const ValueType& value);

    bool Delete(const KeyType& key, ValueType& value);

    //get current max level;
    int GetMaxHeight() { return list_->level;}

    size_t size() { return size_;}

private:
    //init sliplist
    void InitList();

    //free sliplist
    void FreeList();

    //generate a level
    int RandomLevel();

    //create a new node with level
    void NewNodeWithLevel(const int& level, Node& node);

    List list_;
    Node NIL_;
    size_t size_;//sliplist中包含的元素数目
    Random rnd_;
};

inline void SlipList::NewNodeWithLevel(const int& level, Node& node){
    size_t total_size = sizeof(nodeStructure) + level * sizeof(Node);
    node = (Node)malloc(total_size);

    assert(node != NULL);
}

inline int SlipList::RandomLevel(){

    /***
    在该方法中kMaxHeight是最大的height，leveldb中是12。
    通过rnd_.Next与kBranching（4）的余数是否等于0来控制
    不同height的节点的数量分布。
    容易看出((rnd_.Next() % kBranching) == 0)表达式为真的概率是1/4,
    height的初始值是1，那么返回的height为1的概率为（1-1/4）= 3/4,
    height为2的概率是(1/4)*(3/4), 即第一个随机数是4的倍数的概率乘以
    第二个随机数不是4的倍数的概率。以此类推，height为3～11的概率
    分别为(3/4)*(1/4)^2, (3/4)*(1/4)^3, … , (3/4)*(1/4)^10。
    height为kMaxHeight的概率是(1/4)^11。height取值为1…12的所有值的
    概率求和：(3/4)*( (1/4)^0 + (1/4)^1 + (1/4)^2 + … + (1/4)^10 ) + (1/4)^11 = 1。
    可以通过修改kBranching的值来调整不同height的节点的数量分布。
    ***/
    static const unsigned int kBranching = 4;
    int height = 1;
    while(height < MAX_LEVEL && (rnd_.Next() % kBranching == 0))
        height++;

    assert(height > 0);
    assert(height <= MAX_LEVEL);

    /*
    int level = static_cast<int>(rnd_.Uniform(MAX_LEVEL));

    if(level == 0)
        level = 1;
    return level;
    */
    return height;
}
#endif // SLIPLISTDEMO_SLIPLIST_H
