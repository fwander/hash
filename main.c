#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int next(char* str, int index){
  if(index < 0){
    return 0;
  }
  int cha = *(str + index) - 'a';
  cha = (cha + 1)%26;
  *(str + index) = 'a' + cha;
  if (*(str + index) == 'a'){
    return next(str, --index);
  }
  return 1;

}

int main(){
  HashMap* map = newHM(99999997);
  char key[5] = "aaaaa"; // 11,881,376 different words

  int i = 0;
  while(next(key,4)){
    //printf("%s\n", key);
    put(map,key,i++);
  }

  char key2[5] = "aaaaa";

  while(next(key2,4)){
    get(map,key2);
  }

  return 0;
}
