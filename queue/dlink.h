#include <stdlib.h>

//typedef struct node node;
typedef struct node {
    void * element;
    struct node* next;
    struct node *prev;
}node;

typedef struct {
    node *root;
    node *last;
} DoubleLinkedList;

int isEmpty(DoubleLinkedList *l){
    return ((l->root) ? 0:1);
}

// free list
int freeList(DoubleLinkedList *l){
   if (isEmpty(l)) return 0;
   node *tofree = l->root;
   while(tofree != 0){
     l->root = (l->root) ->next;
     free(tofree);
     tofree = l->root;
   }
   return 1;
 }


void init(DoubleLinkedList *l){
    l->root = 0;
    l->last = 0;
  //l->c = 0;
}

//make node
node *makeNode(void *  data,node *prev){
    node *newnode;
    newnode  = (node *)malloc(sizeof(node));
    newnode->next = 0;
    newnode->prev = prev;
    newnode->element = data;
    return newnode;
}

// find pev node of node p
/**
node *previousNode(DoubleLinkedList *l,node *p){
  if(l->root == 0) return 0;
  node *previousnode =  l->root;
   if (previousnode == p) return previousnode;
  else {
    while(previousnode != 0){
      if(previousnode->next == p) return previousnode;
      previousnode = previousnode->next;
    }
    return 0;
  }
}
*/
node *previousNode(DoubleLinkedList *l,node *currentnode){
    if(isEmpty(l)) return 0;
    return currentnode->prev;
}
// insert begin of list
node * insertAtBegin(DoubleLinkedList *l,void *  data){
    node *newnode;
    newnode = makeNode(data,0);
    if(isEmpty(l)) {
    /* printf("1"); */
        l->root = newnode;
        l->last = newnode;
    //l->c = p;
    }
    else {
    /* printf("0"); */
        newnode->next =l->root;
        l->root =newnode;
    //l->c = p;
    }
  return newnode;
}

// insert node to end

node * insertAtEnd(DoubleLinkedList *l,void *  data){
    if(isEmpty(l))
    {
        return insertAtBegin(l,data);
    //l->c = p;
    }
    //node *last = *list->last;
    node *newnode;
    newnode = makeNode(data,l->last);
    l->last->next = newnode;
    l->last = newnode;
    //l->c = p;
    return newnode;
}

//del root
int deleteRoot(DoubleLinkedList *l){
    if (isEmpty(l)) return 0;
    node *todel=l->root;
    l->root=(l->root)->next;
    l->root->prev=0;
    free(todel);
}
//del last
int deleteLast(DoubleLinkedList *l){
    if (isEmpty(l)) return 0;
    node *todel=l->last;
    //node *previousnode=previousNode(l,l->last);
    if(!todel->prev){
        deleteRoot(l);
        return 1;
    }
    l->last=l->last->prev;
    l->last->next=0;
    free(todel);
}
// del node p
int deleteNode(DoubleLinkedList *l,node *todel){
    if ((isEmpty(l))|(todel==0)) return 0;
  //l->c = pev;
    if(todel == l->root){
    //l->root = p->next;
        return deleteRoot(l);
    }
    if(todel==l->last){
        return deleteLast(l);
    }
    //node *previousnode = previousNode(l,todel);
    //previousnode->next = todel->next;
    node *prev=todel->prev;
    prev->next=todel->next;
    todel->next->prev=prev;
    free(todel);
}

int listLength(DoubleLinkedList *l){
    if (isEmpty(l)) return 0;
    int count_ = 0;
    //node *nodeindex = l->root;
    /**
    while (nodeindex != 0) {
        count_++;
        nodeindex = nodeindex ->next;
    }
    */
    node *i;
    for(i=l->root;i!=0;i=i->next)
        count_++;
    return count_;
}

node * findNode(DoubleLinkedList *l,int n){
    if (isEmpty(l)) return 0;
    if ((n<0)|(n>=listLength(l))) return 0;
    node *tofind = l->root;
    int c = 0;
    while (tofind != 0) {
        if (c==n) return tofind;
        c++;
        tofind = tofind ->next;
    }
    return 0;
}
node *insertAtPosition(DoubleLinkedList *l,void *  data,int n){
    if (isEmpty(l)){
        return insertAtBegin(l,data);
    }
    if (n<=0) {
        return insertAtBegin(l,data);
    }
    if (n>=listLength(l)-1){
        return insertAtEnd(l,data);
    }
    //node *currentNode=findNode(l,n);
    //node *newnode=makeNode(data);
    //node *previousnode=previousNode(l,currentNode);
    //previousnode->next=newnode;
    //newnode->next=currentNode;
    node *currentnode = findNode(l,n);
    node *newnode = makeNode(data,currentnode->prev);
    currentnode->prev->next=newnode;
    newnode->next=currentnode;
    return newnode;
}
int deleteAtPosition(DoubleLinkedList *l,int n){
    node *todel;
    if(!(todel=findNode(l,n))) return 0;
    else{
        deleteNode(l,todel);
        return 1;
    }
}

node *getRoot(DoubleLinkedList *l){
    return l->root;
}
node *getLast(DoubleLinkedList *l){
    return l->last;
}
void *  getElement(node *p){
    return p->element;
}

// reverse list

int reverseList(DoubleLinkedList *l){

    if (listLength(l)<=1) return 0;
    node *z,*p;
    l->last = l->root;
    p = l->root;
    l->root = l->root->next;
    z = l->root;
    l->root = l->root->next;
    z->next =p;
    while (l->root != 0)
    {
        p = z;
        z = l->root;
        l->root =l->root->next;
        z->next =p ;
    }

    l->root = z;
    l->last->next = 0;
    //l->c = l->root;
    return 1;
}
/**
void swapNode(node *a,node *b){
    node *temp;
    temp=(node*)malloc(sizeof(node));
    temp->element=a->element;
    temp->next=a->next;
    temp->prev=a->prev;
    a->element=b->element;
    a->next=b->next;
    a->prev=b->prev;
    b->element=temp->element;
    b->next=temp->next;
    b->prev=temp->prev;
    free(temp);

}
*/
// delete at position

/**
node *deleteAtPosition(DoubleLinkedList *l,int n){
  if(l->root == 0 ) {
    printf("\n\t\t List hasn't create !!\n");
    return 0;
  }
  if(n < 0 || n > countList(*l) -1) {
    printf("\n\t\t Position dataue invaild !!\n");
    return 0;
  }
  if(n == 0) {
    deleteNode(l,l->root);
  } else if(n == countList(*l)){
    deleteNode(l,l->last);
  } else {
    int c = 0;
    node *p = l->root->next;
    while (p != 0) {
      c++;
      if(c == n) break;
      p = p ->next;
    }
    deleteNode(l,p);
  }
  return 0;
}

// Devide list

DoubleLinkedList *devideList(DoubleLinkedList *l,int p){
  if(l->root == 0) {
    printf("Haven't list insert !!\n");
    return 0;
  }
  if(p < 0 ||  p > countList(*l) -1){
    printf("Positon dataue invaild !!\n");
    return 0;
  }

  DoubleLinkedList *ln;
  ln = (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
  linit(ln);


  int c = 0;
  node *z = l->root->next;
  while (z != 0) {
    c++;
    if(c == p) break;
    z = z ->next;
  }

  ln->root = z->next;
  ln->last = l->last;

  l->last = z;

  z->next = 0;

  l -> c = l -> l;
  ln->c = ln->last;

  return ln;
}

// Extract list

void extractList(DoubleLinkedList *l,int p,int n){
  if(l->root == 0) {
    printf("Haven't list insert !!\n");
    return ;
  }
  if(p < 0 ||  p > countList(*l) -1){
    printf("Positon dataue invaild !!\n");
    return ;
  }
  if(n < 0 ||p+ n-1 > countList(*l) -1){
    printf("number dataue invaild !!\n");
    return ;

  }
  node *r = l->root;
  node *rn = l->root;
  node *ln = l->last;
  int c = 0;
  node *z = l->root->next;
  while (z != 0) {
    c++;
    if(c == p) rn =z;
    if(c == p+n-1) {ln =z;break;}
    z = z ->next;
  }
  l->root = rn;
  l->last = ln;
  if(p != 0){
    previousNode(l,l->root)->next = 0;
    freelist(l->root);
  }
  freelist(z->next);
  ln ->next =0;
  l->c = l->last;
}



// merge list

void mergelist(DoubleLinkedList *l,DoubleLinkedList *l2){
  l->last->next = l2->root;
  l2->root ==  0;

  l->last = l2 -> l;
  l->c = l->last;
}
*/
