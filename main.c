#include <stdio.h>
#include <string.h>
#include <time.h>

#define TamanhoVendedores 5
#define TamanhoProdutos 10

void formatString(char *str)
{
  str[strcspn(str, "\n")] = '\0';

  int count = 0;

  for (int i = 0; str[i]; i++)
    if (str[i] != ' ')
      str[count++] = str[i];

  str[count] = '\0';
}

void ler_hora_atual()
{
  FILE *file_out;
  file_out = fopen("totais.txt", "a");

  time_t agora;
  struct tm *infoTempo;

  time(&agora);
  infoTempo = localtime(&agora);

  fprintf(file_out, "[ LOG ] %04d-%02d-%02d | Hour: %02d:%02d:%02d\n",
          infoTempo->tm_year + 1900, infoTempo->tm_mon + 1, infoTempo->tm_mday,
          infoTempo->tm_hour, infoTempo->tm_min, infoTempo->tm_sec);
  fclose(file_out);
}

/*
  Vendedores Section

  Action: Read given file and creates a structure to storage Vendedor ID and
  Name for further use
*/

struct Vendedores
{
  int codigo_vendedor;
  char nome_vendedor[80];
  float lucro_total;
};

struct Vendedores VetorVendedores[TamanhoVendedores];

void ler_vendedores()
{
  FILE *file, *file_out;
  file = fopen("vendedores.txt", "r");
  file_out = fopen("totais.txt", "a");

  if (file && file_out)
  {
    fprintf(file_out, "\nLista de Vendedores:\n");
    for (int i = 0; !feof(file); i++)
    {
      fscanf(file, "%d", &(VetorVendedores[i].codigo_vendedor));
      fgets(VetorVendedores[i].nome_vendedor, 80, file);

      formatString(VetorVendedores[i].nome_vendedor);

      fprintf(file_out, "[%d] %d %s\n", i, VetorVendedores[i].codigo_vendedor, VetorVendedores[i].nome_vendedor);
    }

    fclose(file);
    fclose(file_out);
  }
  else
  {
    printf("Erro ao abrir o arquivo\n");
  }
}

/*
  Produtos Section

  Action: Read given file and creates structure to storage Product ID, Price and
  Description for further use
*/

struct Produtos
{
  int codigo_produto;
  float preco_produto;
  char descricao_produto[80];
  float lucro_total;
};

struct Produtos VetorProdutos[TamanhoProdutos];

void ler_produtos()
{
  FILE *file, *file_out;
  file = fopen("produtos.txt", "r");
  file_out = fopen("totais.txt", "a");

  if (file && file_out)
  {
    fprintf(file_out, "\nCatalogo de Produtos:\n");
    for (int i = 0; !feof(file); i++)
    {
      fscanf(file, "%d %f", &(VetorProdutos[i].codigo_produto), &(VetorProdutos[i].preco_produto));

      fgets(VetorProdutos[i].descricao_produto, 80, file);

      formatString(VetorProdutos[i].descricao_produto);

      fprintf(file_out, "[%d] %d %.2f %s\n", i, VetorProdutos[i].codigo_produto, VetorProdutos[i].preco_produto, VetorProdutos[i].descricao_produto);

      VetorProdutos[i].lucro_total = 0;
    }

    fclose(file);
    fclose(file_out);
  }

  else
  {
    printf("Erro ao abrir o arquivo\n");
  }
}

/*
  Vendas Section

  Action: Read given file with historic of sales and returns/prints:
  - Final Profit
  - Most sold product
  - Who sold more products (Best seller)
*/

struct Vendas
{
  int codigo_produto_venda;
  int codigo_vendedor_venda;
  int numeros_produtos_vendidos;
};

struct Vendas VetorVendas[20];

int ler_vendas()
{
  FILE *file, *file_out;
  file = fopen("vendas.txt", "r");
  file_out = fopen("totais.txt", "a");

  int i = 0;

  if (file && file_out)
  {

    fprintf(file_out, "\nLog de Vendas:\n");

    for (; !feof(file); i++)
    {
      fscanf(file, "%d %d %d", &(VetorVendas[i].codigo_produto_venda), &(VetorVendas[i].codigo_vendedor_venda), &(VetorVendas[i].numeros_produtos_vendidos));

      fprintf(file_out, "[%d] %d %d %d\n", i, VetorVendas[i].codigo_produto_venda, VetorVendas[i].codigo_vendedor_venda, VetorVendas[i].numeros_produtos_vendidos);
    }
    
    fclose(file);
    fclose(file_out);
    return i;
  }
  else
  {
    printf("Erro ao abrir o arquivo\n");
    return 0;
  }
}

/*
  Gerando estatisticas sobre as vendas
*/
void verificar_vendas(int tamanhoVendas)
{
  FILE *file, *file_out;
  file = fopen("vendas.txt", "r");
  file_out = fopen("totais.txt", "a");

  float lucroTotal = 0;

  for (int i = 0; i < tamanhoVendas; i++)
  {


    // Lucro total de cada produto vendido + Lucro total de cada vendedor
    for (int j = 0; j < TamanhoProdutos; j++)
    {
      if (VetorProdutos[j].codigo_produto == VetorVendas[i].codigo_produto_venda)
      {
        VetorProdutos[j].lucro_total += VetorVendas[i].numeros_produtos_vendidos * VetorProdutos[j].preco_produto;

        for (int x = 0; x < TamanhoVendedores; x++)
        {
          if (VetorVendedores[x].codigo_vendedor == VetorVendas[i].codigo_vendedor_venda) 
          {  
            VetorVendedores[x].lucro_total +=VetorVendas[i].numeros_produtos_vendidos * VetorProdutos[j].preco_produto;
          }
        }
      }
    }
  }

  for (int x = 0; x < TamanhoProdutos; x++ )
  {
    // Lucro total do dia
    lucroTotal += VetorProdutos[x].lucro_total;
  }

  fprintf(file_out, "\nTotal geral vendido: %.2f\n", lucroTotal);

  fprintf(file_out, "\nLucro Total de cada produto:\n");
  for (int j = 0; j < TamanhoProdutos; j++)
  {
    if (VetorProdutos[j].codigo_produto != NULL)
      fprintf(file_out, "Produto %d (%s) : R$%.2f\n", VetorProdutos[j].codigo_produto, VetorProdutos[j].descricao_produto, VetorProdutos[j].lucro_total);
  }

  fprintf(file_out, "\nLucro Total de cada vendedor:\n");
  for (int x = 0; x < TamanhoVendedores; x++)
  {
    if (VetorVendedores[x].codigo_vendedor != NULL)
      fprintf(file_out, "Vendedor %d (%s) : R$%.2f\n", VetorVendedores[x].codigo_vendedor, VetorVendedores[x].nome_vendedor, VetorVendedores[x].lucro_total);
  }

  fprintf(file_out, "\n"); // Organizar formatação

  fclose(file);
  fclose(file_out);
}

/*
  File Logic
*/

int main()
{
  printf("Starting..\n\n");

  ler_hora_atual();

  int tamanhoVendas = ler_vendas();
  printf("TamanhoVendas: %d", tamanhoVendas);

  ler_produtos();
  ler_vendedores();

  verificar_vendas(tamanhoVendas);

  printf("Finished!");

  return 0;
}
