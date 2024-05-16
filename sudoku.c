#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n) {
   
   return 1;
}


List* get_adj_nodes(Node* n) {
   List* list=createList();
   int i, j;
   
   for (i = 0; i < 9; i++) {
      for (j = 0; j < 9; j++) {
         if (n->sudo[i][j] == 0) {
            for (int k = 1; k <= 9; k++) {
               Node* adj_node = copy(n);
               adj_node->sudo[i][j] = k;
               if (is_valid(adj_node)) {
                  pushBack(list, adj_node);
               }
            }
            return list;
         }
      }  
   }
   return list;
}


int is_final(Node* n){
   int i, j;
   for (i = 0; i < 9; i++) {
      for (j = 0; j < 9; j++) {
         if (n->sudo[i][j] == 0) {
            return 0;
         }
      }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont){
   Stack* S = createStack();
   push(S, initial);
   while (!is_empty(S)) {
      Node* n = top(S);
      pop(S);
      if (is_final(n)) {
         return n;
      }
      List* adj = get_adj_nodes(n);
      Node* adj_node = first(adj);
      while (adj_node) {
         Node* next_adj_node = next(adj);
         push(S, adj_node);
         adj_node = next_adj_node;
      } 
      free(n);
   } 
   return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/