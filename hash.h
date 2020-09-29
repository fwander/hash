#ifndef HASH
#define HASH

typedef struct LLNode LLNode;
typedef struct HashMap HashMap;
struct LLNode{
  LLNode* next;
  LLNode* prev;
  char key[32];
  void* pocket;
  int data;
};

typedef struct{
  LLNode* head;
  LLNode* tail;
} LinkedList;

struct HashMap{
  LinkedList** slots;
  int size;
  int elements;
};

LLNode* newLLNode(char* key, int data, LLNode* next, LLNode* prev);
LinkedList* newLL();
void addNodeLL(LinkedList* LL, LLNode* LLN);
LLNode* findLL(LinkedList* LL, char* key);
int removeLL(LLNode* node);
int addPairLL(LinkedList* LL, char* key, int data);
void printLL(LinkedList* LL);
HashMap* newHM(int size);
unsigned long hash(unsigned char *str);
void put(HashMap* HM, char* key, int value);
void del(HashMap* HM, char* key);
LLNode* find(HashMap* HM, char* key);
int getOrDefault(HashMap* HM, char* key, int d);
int get(HashMap* HM, char* key);

#endif
