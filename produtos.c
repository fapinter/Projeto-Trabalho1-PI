#include <stdio.h>

struct Produtos {int codigo_produto; double preco_produto; char descricao_produto[80];};

struct Produtos VetorProdutos[10];

int main(){
    FILE *produtos;
    produtos = fopen("produtos.txt", "r");

    if (produtos == NULL){
        printf("Erro ao abrir o arquivo \n");
        
    }

    else{
        printf("funciona por favor");
    }




}