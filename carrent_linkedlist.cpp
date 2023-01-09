#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Pedro Lucas da Silva Oliveira

typedef struct celula
{
  char nome[30];
  int ano;
  float preco;
  struct celula *prox;
  struct celula *ant;
} cel;

void imprimir_menu()
{
  printf("\n\n");
  printf("*******\t\tTROCA-TROCA Veiculos usados\t********\n");
  printf("*\t1 - Registrar veiculo\t*\n");
  printf("*\t2 - Exibir estoque\t*\n");
  printf("*\t3 - Vender\t*\n");
  printf("*\t4 - Buscar por valor\t*\n");
  printf("*\t5 - Buscar por ano\t*\n");
  printf("*\t6 - Lucro total\t*\n");
  printf("*\t0 - Sair\t\t*\n");
}

void inserir(cel **anunciados)
{
  cel *novo = (cel *)malloc(sizeof(cel));
  novo->ant = NULL;

  printf("Informe o nome do carro:\n ");
  scanf("%s", novo->nome);
  getchar();
  printf("Informe o ano do carro:\n ");
  scanf("%i", &novo->ano);
  getchar();
  printf("Informe o preco do carro:\n");
  scanf("%f", &novo->preco);
  novo->preco = novo->preco * 1.2;
  if (*anunciados == NULL)
  {
    novo->prox = *anunciados;
    *anunciados = novo;
  }
  else
  {
    cel *aux = *anunciados;

    while (aux != NULL)
    {
      if (strcmp(novo->nome, aux->nome) < 0)
      {
        if (novo->ant != NULL)
        {
          novo->ant->prox = novo;
        }
        else
        {
          *anunciados = novo;
        }
        novo->prox = aux;
        return;
      }
      novo->ant = aux;
      aux = aux->prox;
    }
    novo->ant->prox = novo;
    novo->prox = aux;
  }
}

void imprimir(cel *cabeca)
{
  printf("---------------\n");
  while (cabeca != NULL)
  {
    printf("Nome: %s\n", cabeca->nome);
    printf("Ano: %i\n", cabeca->ano);
    printf("Preco de venda: %.2f\n", cabeca->preco);
    cabeca = cabeca->prox;
    printf("\n\n");
  }
}

void vender(cel **lista, cel **vendidos, char *nome, float novo_valor)
{
  cel *aux, *remover = NULL;

  if (*lista != NULL)
  {

    if (strcmp((*lista)->nome, nome) == 0)
    {
      remover = *lista;
      *lista = remover->prox;
      remover->prox = *vendidos;
      remover->ant = NULL;

      if (*vendidos != NULL)
      {

        (*vendidos)->ant = NULL;
      }
      *vendidos = remover;
    }

    if (*lista != NULL)
    {
      (*lista)->ant = NULL;
    }

    else
    {

      aux = *lista;

      while (aux->prox != NULL && aux->prox->nome != nome)
      {

        aux = aux->prox;
      }

      if (aux->prox != NULL)
      {

        remover = aux->prox;
        aux->prox = remover->prox;
        remover->prox = *vendidos;
        remover->ant = NULL;

        if (*vendidos != NULL)
        {

          (*vendidos)->ant = remover;
        }

        *vendidos = remover;

        if (aux->prox != NULL)
        {

          aux->prox->ant = aux;
        }
      }
    }
  }
}

void busca_valor(cel *lista, float teto)
{
  cel *aux = lista;
  if (aux == NULL)
  {
    return;
  }
  printf("Os carros disponiveis abaixo desse valor sao:\n");
  while (aux != NULL)
  {
    if ((aux->preco) < teto)
    {
      printf("Carro:%s\n valor:%.2f\n\n", aux->nome, aux->preco);
    }
    aux = aux->prox;
  }
}

void busca_ano(cel *lista, int ano)
{
  cel *aux = lista;
  if (aux == NULL)
  {
    return;
  }
  printf("Os carros desse ano sao:\n");
  while (aux != NULL)
  {
    if ((aux->ano) == ano)
    {
      printf("Carro:%s\n ano:%i\n\n", aux->nome, aux->ano);
    }
    aux = aux->prox;
  }
}

void lucro_total(cel *anunciados, cel *vendidos, float lucro)
{
  cel *aux = anunciados;
  cel *aux2 = vendidos;
  while (aux != NULL)
  {
    lucro = lucro + (aux->preco - aux2->preco);
    aux = aux->prox;
    aux2 = aux2->prox;
  }
}

int main(void)
{
  cel *em_anuncio = NULL;
  cel *vendidos = NULL;
  int opc = 100;
  char nome[30];
  float gasto = 0;
  int ano = 0;
  float lucro = 0, novo_valor = 0;
  while (opc != 0)
  {
    imprimir_menu();
    scanf("%d", &opc);
    fflush(stdin);
    switch (opc)
    {
    case 1:
      inserir(&em_anuncio);
      break;

    case 2:
      imprimir(em_anuncio);
      break;

    case 3:
      printf("Informe o nome do carro que ira vender:\n");
      scanf("%s", nome);
      getchar();
      printf("Qual o valor negociado?\n");
      scanf("%f", &novo_valor);
      vender(&em_anuncio, &vendidos, nome, novo_valor);
      break;

    case 4:
      printf("Informe o valor maximo que planeja gastar:\n");
      scanf("%f", &gasto);
      getchar();
      busca_valor(em_anuncio, gasto);
      break;
    case 5:
      printf("Informe o ano do carro que deseja comprar:\n");
      scanf("%i", &ano);
      busca_ano(em_anuncio, ano);
      getchar();
      break;
    case 6:

    case 0:
      printf("Encerrando...");
      break;

    default:
      printf("Opção inválida\n");
      break;
    }
  }
  return 0;
}
