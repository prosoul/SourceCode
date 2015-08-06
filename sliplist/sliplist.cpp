#include "sliplist.h"
#include <string>
#include <iostream>

using namespace  std;

void SlipList::InitList(){
    //setting NIL
    NewNodeWithLevel(0,NIL_);
    NIL_->key = 0x7fffffff;

    //setting List
    list_ = (List)malloc(sizeof(listStructure));
    list_->level = 0;

    //settting header
    NewNodeWithLevel(MAX_LEVEL,list_->header);
    for(int i = 0; i < MAX_LEVEL; i++)
        list_->header->forward[i] = NIL_;

    size_ = 0;
}

void SlipList::FreeList(){
    Node p = list_->header;
    Node q;

    while(p != NIL_){
        q = p->forward[0];
        free(p);
        p = q;
    }

    free(p);
    free(list_);
}

bool SlipList::Search(const KeyType& key, ValueType& value){
    Node x = list_->header;
    int i;
    for(i = list_->level; i >= 0; i--){
        while(x->forward[i]->key < key){
            x = x->forward[i];
        }
    }
    x = x->forward[0];

    if(x->key == key){
        value = x->value;
        return true;
    }else{
        return false;
    }
}

bool SlipList::Insert(const KeyType& key, const ValueType& value){
    Node x = list_->header;
    Node update[MAX_LEVEL];
    int i;

    for(i = list_->level; i >= 0; i--){
        while(x->forward[i]->key < key){
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];

    if(x->key == key){
        x->value = value;
        std::cout << "your input key " << key << " exists in the sliplist!" << std::endl;
        return false;
    }else{
        //随机生成结点层数
        int level = RandomLevel();
        if(level > list_->level){
            level = ++list_->level;
            update[level] = list_->header;
        }

        //新建新结点
        Node newNode;
        NewNodeWithLevel(level,newNode);
        newNode->key = key;
        newNode->value = value;

        //调整forward指针
        for(i = level; i >= 0; --i){
            x = update[i];
            newNode->forward[i] = x->forward[i];
            x->forward[i] = newNode;
        }

        ++size_;

        return true;
    }
}

bool SlipList::Delete(const KeyType& key, ValueType& value){
    Node x = list_->header;
    Node update[MAX_LEVEL];
    int i;

    for(i = list_->level; i >= 0; --i){
        while(x->forward[i]->key < key){
            x = x ->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];

    if(x->key != key){
        return false;
    }else{
        value =  x->value;
        for(i = 0; i <= list_->level; i++){
            if(update[i]->forward[i] != x)
                break;
            update[i]->forward[i] = x ->forward[i];
        }
        free(x);//delete the node

        //update list level
        while(list_->level > 0 && list_->header->forward[list_->level] == NIL_)
            --list_->level;

        --size_;

    }

    return true;
}
