#include "dlink.h"
typedef DoubleLinkedList Stack;

void push(Stack *s,void * data){
    insertAtBegin(s,data);
}

void * pop(Stack *s){
    if (isEmpty(s)) return ;
    void * data=getElement(s->root);
    deleteRoot(s);
    return data;
}


