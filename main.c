#include "func/func.h"

instrucao tabela[]={
    {"lb",  -1,  0b000, 0b0000011, 'I'},
    {"lh",  -1,  0b001, 0b0000011, 'I'},
    {"lw",  -1,  0b010, 0b0000011, 'I'},
    {"sb",  -1,  0b000, 0b0100011, 'S'},
    {"sh",  -1,  0b001, 0b0100011, 'S'},
    {"sw",  -1,  0b010, 0b0100011, 'S'},
    {"add", 0b0000000, 0b000, 0b0110011, 'R'},
    {"sub", 0b0100000, 0b000, 0b0110011, 'R'},
    {"and", 0b0000000, 0b111, 0b0110011, 'R'},
    {"or",  0b0000000, 0b110, 0b0110011, 'R'},
    {"xor", 0b0000000, 0b100, 0b0110011, 'R'},
    {"addi",-1,  0b000, 0b0010011, 'I'},
    {"andi",-1,  0b111, 0b0010011, 'I'},
    {"ori", -1,  0b110, 0b0010011, 'I'},
    {"sll", 0b0000000, 0b001, 0b0110011, 'R'},
    {"srl", 0b0000000, 0b101, 0b0110011, 'R'},
    {"bne", -1,  0b001, 0b1100011, 'B'},
    {"beq", -1,  0b000, 0b1100011, 'B'}
};

int main(int argc, char *argv[]){

    if(argc < 2){
        printf("Uso: %s arquivo.asm\n", argv[0]);
        return 1;
    }

    if(freopen(argv[1], "r", stdin) == NULL){
        printf("Erro ao abrir o arquivo: %s\n", argv[1]);
        return 1;
    }

    char atual[MAX];

    while(scanf("%s", atual) == 1){

        if (strcmp(atual,"li")==0)  strcpy(atual, "addi");
        if (strcmp(atual,"mv")==0)  strcpy(atual, "addi");
        if (strcmp(atual,"and")==0) strcpy(atual, "andi");

        int pos=-1;
        for(int i=0; i<18; i++){
            if(strcmp(atual, tabela[i].nome) == 0){
                pos=i;
                break;
            }
        }

        if(pos == -1){
            printf("Instrução nao reconhecida: %s\n", atual);
            continue;
        }

        switch(tabela[pos].tipo){
            case 'I':{
                char im[MAX], rs1[MAX], rd[MAX];
                char sim[MAX], srs1[MAX], srd[MAX];

                if(strcmp(tabela[pos].nome, "lb") == 0 ||
                strcmp(tabela[pos].nome, "lh") == 0 ||
                strcmp(tabela[pos].nome, "lw") == 0){
                    scanf(" %[^,], ", rd);
                    scanf(" %[^(] ", im);
                    scanf(" (%[^)])", rs1);
                }

                else{
                    scanf(" %[^,], ", rd);
                    scanf(" %[^,], ", rs1);
                    scanf(" %s", im);
                }

                xNparaBin(rd,srd);
                xNparaBin(rs1,srs1);
                NumparaBin(im, sim);

                printf("%s", sim);
                printf("%s", srs1);
                printBin(tabela[pos].funct3, 3);
                printf("%s", srd);
                printBin(tabela[pos].opcode, 7);
                printf("\n");

                break;
            }
            case 'S':{
                char im[MAX], rs1[MAX], rs2[MAX];
                char sim[MAX], srs1[MAX], srs2[MAX];

                scanf(" %[^,], ", rs2);
                scanf(" %[^(] ", im);
                scanf(" (%[^)])", rs1);

                xNparaBin(rs2,srs2);
                xNparaBin(rs1,srs1);
                NumparaBin(im, sim);

                printf("%.7s", sim);
                printf("%s", srs2);
                printf("%s", srs1);
                printBin(tabela[pos].funct3, 3);
                printf("%s", sim+7);
                printBin(tabela[pos].opcode, 7);
                printf("\n");

                break;
            }
            case 'R':{
                char rs2[MAX], rs1[MAX], rd[MAX];
                char srs2[MAX], srs1[MAX], srd[MAX];

                scanf(" %[^,], ", rd);
                scanf(" %[^,], ", rs1);
                scanf(" %s", rs2);

                xNparaBin(rd, srd);
                xNparaBin(rs1, srs1);
                xNparaBin(rs2, srs2);

                printBin(tabela[pos].funct7, 7);
                printf("%s", srs2);
                printf("%s", srs1);
                printBin(tabela[pos].funct3, 3);
                printf("%s", srd);
                printBin(tabela[pos].opcode, 7);
                printf("\n");

                break;
            }

            case 'B':{
                char rs2[MAX], rs1[MAX], im[MAX];
                char srs2[MAX], srs1[MAX], sim[MAX];

                scanf(" %[^,], ", rs1);
                scanf(" %[^,], ", rs2);
                scanf(" %s", im);

                xNparaBin(rs1,srs1);
                xNparaBin(rs2,srs2);
                NumparaBin(im,sim);

                printf("%.1s", sim);
                printf("%.6s", sim+1);
                printf("%s", srs2);
                printf("%s", srs1);
                printBin(tabela[pos].funct3, 3);
                printf("%.4s", sim+7);
                printf("%.1s", sim+11);
                printBin(tabela[pos].opcode, 7);
                printf("\n");

                break;
            }
        }
    }

    return 0;
}