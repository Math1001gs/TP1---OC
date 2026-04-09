#include "func.h"

//Função para printar o binário pois se o número fosse 0000000, o printf printaria só um 0
void printBin(int n, int bits){
    for(int i = bits-1; i >= 0; i--)
        printf("%d", (n >> i) & 1);
}

//Função para converter transistores para binário (x0,x1,x2,x3, ..., x31)
int xNparaBin(const char *str, char out_bin[MAX]){
    if (str[0] != 'x') return -1;

    int n = atoi(str + 1);

    if (n < 0 || n > 31) return -1;

    for (int i = 4; i >= 0; i--) {
        out_bin[4 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    out_bin[5] = '\0';

    return n;
}

//Função para converter números inteiros em binários (Imediatos)
int NumparaBin(const char *str, char out_bin[MAX]){
    int n = atoi(str);

    for (int i = 11; i >= 0; i--) {
        out_bin[11 - i] = ((n >> i) & 1) ? '1' : '0';
    }
    out_bin[12] = '\0';

    return n;
}
