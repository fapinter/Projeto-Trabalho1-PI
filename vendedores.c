#include <stdio.h>

struct Vendedores {int codigo_vendedor; char nome_vendedor[80];}; // informacoes que serao extraidas

struct  Vendedores VetorVendedores[5]; // vetor onde as informacoes serao armazenadas

int main(){
//escanear primeira linha para ver quantas linhas abaixo tem,
// inserir no for (i) para realizar o loop

    FILE *vendedores;

    char nomeArquivo[] = "vendedores.txt";
    
    vendedores = fopen(nomeArquivo,"r");


    if (vendedores == NULL){
        printf("Erro ao abrir o arquivo \n");
    }
    else{
        fscanf(vendedores, "%d %c", &(VetorVendedores[0].codigo_vendedor), VetorVendedores[0].nome_vendedor);
        printf("codigo vendedor %d, nome dele %s\n", VetorVendedores[0].codigo_vendedor,VetorVendedores[0].nome_vendedor);
    }
}