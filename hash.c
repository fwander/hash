#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"



//LinkedList Stuff

LLNode* newLLNode(char* key, int data, LLNode* next, LLNode* prev){
  LLNode* new = (LLNode*) malloc(sizeof(LLNode));
  new->next = next;
  new->prev = prev;
  new->data = data;
  strcpy(new->key, key);

  return new;
}

LinkedList* newLL(){
  LinkedList* new = (LinkedList*) malloc(sizeof(LinkedList));
  new->head = newLLNode("",0,NULL,NULL);
  new->tail = newLLNode("",0,NULL,new->head);
  new->head->next = new->tail;
  return new;
}

void addNodeLL(LinkedList* LL, LLNode* LLN){
  LLN->next = LL->tail;
  LLN->prev = LL->tail->prev;
  LL->tail->prev->next = LLN;
  LL->tail->prev = LLN;
}

LLNode* findLL(LinkedList* LL, char* key){
  LLNode* lookingAt = LL->head;
  while ((lookingAt = lookingAt->next) != LL->tail){
    if (strcmp(lookingAt->key,key) == 0){
      return lookingAt;
    }
  }
  return NULL;
}

int removeLL(LLNode* node){
  if(!node){
    return 0;
  }
  node->prev->next = node->next;
  node->next->prev = node->prev;
  free(node);
  return 1;
}

int addPairLL(LinkedList* LL, char* key, int data){
  LLNode* node;
  if ((node = findLL(LL, key)) == NULL){
    addNodeLL(LL, newLLNode(key, data, NULL, NULL));
    return 1;
  }
  else{
    node->data = data;
    return 0;
  }
}

void printLL(LinkedList* LL){
  LLNode* lookingAt = LL->head;
  while ((lookingAt = lookingAt->next) != LL->tail){
    printf("%s : %d\n", lookingAt->key, lookingAt->data);
  }
}

//HashMap Stuff



HashMap* newHM(int size){
  HashMap* new = (HashMap*)malloc(sizeof(HashMap));
  new->slots = (LinkedList**)malloc(sizeof(LinkedList*) * size);
  for (int i = 0; i < size; i++){
    (*(new->slots + i)) = newLL();
  }
  new->size = size;
  new->elements = 0;
}

unsigned long hash(unsigned char *str)
//I got this from http://www.cse.yorku.ca/~oz/hash.html by Dan Bernstein.
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

void put(HashMap* HM, char* key, int value){
  unsigned long index = hash(key)%(HM->size);
  HM->elements += addPairLL(*((HM->slots)+index), key, value);
}

void del(HashMap* HM, char* key){
  unsigned long index = hash(key)%(HM->size);

  HM->elements -= removeLL(findLL(*((HM->slots)+index), key));
}

LLNode* find(HashMap* HM, char* key){
  unsigned long index = hash(key)%(HM->size);
  return findLL(*((HM->slots)+index), key);
}

int getOrDefault(HashMap* HM, char* key, int d){
  unsigned long index = hash(key)%(HM->size);
  LLNode* back = find(HM,key);
  if(back){
    return back->data;
  }
  else{
    return d;
  }
}

int get(HashMap* HM, char* key){
  return getOrDefault(HM, key, 0);
}
