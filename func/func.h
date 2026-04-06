#ifndef func
#define func
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 15

typedef struct{
    char *nome;
    int funct7;
    int funct3;
    int opcode;
    char tipo;  
}instrucao;

void printBin(int n, int bits);
int xNparaBin(const char *str, char out_bin[MAX]);
int NumparaBin(const char *str, char out_bin[MAX]);

#endif