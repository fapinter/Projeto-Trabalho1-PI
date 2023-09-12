#include <stdio.h>
#include "vendedores.c"
#include "produtos.c"

struct Vendas {codigo_vendedor; codigo_produto; int unidades_vendidas};

struct Vendas VetorVendas[20];

int main(){
    FILE  *vendas;
    vendas = fopen("vendas.txt", "r");

    if ( vendas == NULL){
        printf("Erro ao abrir o arquivo \n");
        
    }




}
