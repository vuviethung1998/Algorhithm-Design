#include "dlink.h"
typedef DoubleLinkedList Queue;

void EnQueue(Queue *q,void * data){
    insertAtEnd(q,data);
}

void * DeQueue(Queue *q){
    if (isEmpty(q)) return ;
    void * data=getElement(q->root);
    deleteRoot(q);
    return data;
}

void * Front(Queue *q){
    return getElement(q->root);
}
