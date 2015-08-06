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
    size_t size_;//sliplist�а�����Ԫ����Ŀ
    Random rnd_;
};

inline void SlipList::NewNodeWithLevel(const int& level, Node& node){
    size_t total_size = sizeof(nodeStructure) + level * sizeof(Node);
    node = (Node)malloc(total_size);

    assert(node != NULL);
}

inline int SlipList::RandomLevel(){

    /***
    �ڸ÷�����kMaxHeight������height��leveldb����12��
    ͨ��rnd_.Next��kBranching��4���������Ƿ����0������
    ��ͬheight�Ľڵ�������ֲ���
    ���׿���((rnd_.Next() % kBranching) == 0)���ʽΪ��ĸ�����1/4,
    height�ĳ�ʼֵ��1����ô���ص�heightΪ1�ĸ���Ϊ��1-1/4��= 3/4,
    heightΪ2�ĸ�����(1/4)*(3/4), ����һ���������4�ı����ĸ��ʳ���
    �ڶ������������4�ı����ĸ��ʡ��Դ����ƣ�heightΪ3��11�ĸ���
    �ֱ�Ϊ(3/4)*(1/4)^2, (3/4)*(1/4)^3, �� , (3/4)*(1/4)^10��
    heightΪkMaxHeight�ĸ�����(1/4)^11��heightȡֵΪ1��12������ֵ��
    ������ͣ�(3/4)*( (1/4)^0 + (1/4)^1 + (1/4)^2 + �� + (1/4)^10 ) + (1/4)^11 = 1��
    ����ͨ���޸�kBranching��ֵ��������ͬheight�Ľڵ�������ֲ���
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
