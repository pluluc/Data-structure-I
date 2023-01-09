#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura de data, contendo dia, mês e ano (int);
typedef struct
{
    int day, month, year;
} date;

// Estrutura de ticket, contendo localizador, data, preço e destino;
typedef struct
{
    int tracker;
    date date;
    float price;
    char destiny[30];
} ticket;

// Estrutura de nó de árvore, contendo um ticket e ponteiros para direita e esquerda;
typedef struct tree_node
{
    ticket new_ticket;
    struct tree_node *right;
    struct tree_node *left;
} node;

// Estrutura de raiz de árvore, contendo um node e contadores para relatório;
typedef struct tree_root
{
    node *root = NULL;
    float total_income = 0;
    int total_tickets = 0;
} ntr;

// Definição das raízes das 3 árvores que serão utilizadas;
ntr br, arg, report;

// Função que aloca memória pro nó da árvore, preenche seus dados e retorna o próprio;
node *create_node();

// Função que recebe raiz e nó, realiza testes e organiza o nó na estrutura de árvore;
void insert_node(node *root, node *node);

/*Função que pergunta ao usuário o país destino e com base nisso realiza a criação
e organização dos nós (através de create e insert node), além de realizar a contagem de lucro e registros
da árvore;*/
void insert();

// Função que recebe uma raiz, um inteiro e realiza a impressão da própria;
void show(node *root, int tab = 0)
{
    if (root == NULL)
        return;

    show(root->right, tab + 1);
    for (int i = 0; i < tab; i++)
    {
        printf("\t");
    }
    printf("%d\n", root->new_ticket.tracker);
    show(root->left, tab + 1);
}

// Função que recebe uma raiz e uma string, percorre a árvore e printa as células que contém a mesma string;
bool search_node(node *root, char *name);

// Função que solicita uma string ao usuário e chama a search_node nas duas árvores;
void search_destiny();

// Função que mostra as informações para relatório contidas dentro das duas árvores;
void record();

//Função que recebeu uma raíz e testa se ela tem ramificações apenas para um lado;
bool one_side(node *root);

//Função que recebe o ramo esquerdo de uma raiz, procura o maior elemento e retorna o próprio;
node *higher_left(node *left);

//Função que recebe uma raíz e retorna o elemento da própria, fazendo as devidas reorganizações na árvore;
node *pop_root(node **root);

/*Função que faz a junção dos dados de relatório em uma terceira árvore e zera os contadores das outras, além de
utilizar de insert_node e pop_root para juntar as duas primeiras árvores na terceira.*/
void final_report();

// menu(menu);
void menu();

int main(void)
{
    srand(time(NULL));
    int loop = -1;
    while (loop != 0)
    {
        menu();
        scanf("%i", &loop);
        getchar();
        switch (loop)
        {
        case 1:
            insert();
            break;
        case 2:
            printf("Brasil:\n");
            show(br.root);
            printf("Argentina:\n");
            show(arg.root);
            break;
        case 3:
            search_destiny();
            break;
        case 4:
            record();
            break;
        case 5:
            final_report();
            printf("Relatorio:\n");
            show(report.root);
            printf("Total de tickets:%i\n", report.total_tickets);
            printf("Total arrecadado:$ %2.f\n", report.total_income);
            break;
        case 0:
            printf("Encerrando...");
            break;
        default:
            printf("Insira uma opcao valida.");
            break;
        }
    }
    return 0;
}



node *create_node()
{
    node *new_node = (node *)malloc(sizeof(node));

    new_node->new_ticket.tracker = rand() % 100;
    printf("O localizador e:%i\n", new_node->new_ticket.tracker);
    printf("Informe o dia:\n");
    scanf("%i", &new_node->new_ticket.date.day);
    getchar();
    printf("Informe o mes:\n");
    scanf("%i", &new_node->new_ticket.date.month);
    getchar();
    printf("Informe o ano:\n");
    scanf("%i", &new_node->new_ticket.date.year);
    getchar();
    printf("Informe o preco:\n");
    scanf("%f", &new_node->new_ticket.price);
    printf("Informe o destino:\n");
    scanf("%s", new_node->new_ticket.destiny);
    getchar();
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void insert_node(node *root, node *node)
{
    if (root == NULL)
    {
        printf("ERRO.\n");
        return;
    }
    if (root->new_ticket.tracker == node->new_ticket.tracker)
    {
        printf("Localizador ja existe.\n");
        return;
    }
    if (root->new_ticket.tracker < node->new_ticket.tracker)
    {
        if (root->right == NULL)
        {
            root->right = node;
            return;
        }
        insert_node(root->right, node);
    }
    else
    {
        if (root->left == NULL)
        {
            root->left = node;
            return;
        }
        insert_node(root->left, node);
    }
}

void insert()
{
    int choose = -1;
    printf("Selecione o pais no qual esta sendo realizada a compra:\n1- Brasil\n2- Argentina\n");
    scanf("%i", &choose);
    switch (choose)
    {

    case 1:
    {
        if (br.root == NULL)
        {
            br.root = create_node();
            br.total_tickets++;
            br.total_income = br.root->new_ticket.price;
            return;
        }
        node *new_br = create_node();
        insert_node(br.root, new_br);
        br.total_tickets++;
        br.total_income = br.total_income + new_br->new_ticket.price;
        break;
    }
    case 2:
    {
        if (arg.root == NULL)
        {
            arg.root = create_node();
            arg.total_tickets++;
            arg.total_income = arg.root->new_ticket.price;
            return;
        }
        node *new_arg = create_node();
        insert_node(arg.root, new_arg);
        arg.total_tickets++;
        arg.total_income = arg.total_income + new_arg->new_ticket.price;
        break;
    }

    default:
        printf("Insira uma opcao valida");
        break;
    }
}

void menu()
{
    printf("\n\n");
    printf("*******\t\tTAM\t********\n");
    printf("*\t1 - Registrar passagem\t*\n");
    printf("*\t2 - Imprimir arvores\t*\n");
    printf("*\t3 - Buscar por destino\t*\n");
    printf("*\t4 - Relatorio de ganhos e voos\t*\n");
    printf("*\t5 - Relatorio anual\t*\n");
    printf("*\t0 - Sair\t\t*\n");
}

bool search_node(node *root, char *name)
{
    if (root == NULL)
        return false;

    if(search_node(root->right, name) == true){
        return true;
    }

    if (strcmp(root->new_ticket.destiny, name) == 0)
    {
        printf("Ticket info:\nLocalizador:%i\nData:%i/%i/%i\nPreco:%2.f\nDestino:%s\n\n", root->new_ticket.tracker, root->new_ticket.date.day, root->new_ticket.date.month, root->new_ticket.date.year, root->new_ticket.price, root->new_ticket.destiny);
        return true;
    }
    if(search_node(root->left, name) == true){
        return true;
    }
    return false;
}

void search_destiny()
{
    char name[30];
    printf("Informe o destino:\n");
    scanf("%s", name);
    getchar();

    printf("\nNo Brasil:\n");
    search_node(br.root, name);

    printf("\n\nNa Argentina:\n");
    search_node(arg.root, name);
}

void record()
{
    printf("Brasil:\n");
    printf("Valor total: %.2f\n", br.total_income);
    printf("Total de tickets: %i\n\n", br.total_tickets);

    printf("Argentina:\n");
    printf("Valor total: %.2f\n", arg.total_income);
    printf("Total de tickets: %i\n", arg.total_tickets);
}

bool one_side(node *root)
{
    if (((root->left != NULL) && (root->right == NULL)) || ((root->right != NULL) && (root->left == NULL)))
    {
        return true;
    }
    return false;
}

node *higher_left(node *left)
{
    node *aux = left;

    while (aux->right->right != NULL)
    {
        aux = aux->right;
    }
    return aux;
}

node *pop_root(node **root)
{
    if (*root == NULL)
        return NULL;

    node *removed = *root;

    if (((*root)->right == NULL) && ((*root)->left == NULL))
    {
        (*root) = NULL;
        return removed;
    }

    if (one_side(*root) == true)
    {
        if ((*root)->left == NULL)
        {
            *root = (*root)->right;
            removed->right = NULL;
            return removed;
        }
        else
        {
            *root = (*root)->left;
            removed->left = NULL;
            return removed;
        }
    }

    if ((*root)->left->right == NULL)
    {
        (*root)->left->right = (*root)->right;
        (*root) = (*root)->left;
        removed->left = NULL;
        removed->right = NULL;
        return removed;
    }

    node *dad_sub = higher_left((*root)->left);
    node *sub = dad_sub->right;

    if ((sub->left == NULL))
    {
        dad_sub->right= NULL;
        sub->right = (*root)->right;
        sub->left = (*root)->left;
        *root = sub;
        removed->left = NULL;
        removed->right = NULL;
        return removed;
    }
    else
    {
        dad_sub->right = sub->left;
        sub->right = (*root)->right;
        sub->left = (*root)->left;
        *root = sub;
        removed->left = NULL;
        removed->right = NULL;
        return removed;
    }
}

void final_report()
{
    if ((br.root == NULL) && (arg.root == NULL))
    {
        printf("As listas estao vazias");
        return;
    }

    report.total_income = report.total_income + br.total_income + arg.total_income;
    report.total_tickets = report.total_tickets + br.total_tickets + arg.total_tickets;

    br.total_income = 0;
    arg.total_income = 0;

    br.total_tickets = 0;
    arg.total_tickets = 0;

    if (report.root == NULL)
    {
        if ((br.root == NULL) && (arg.root != NULL))
        {
            report.root = pop_root(&arg.root);
        }
        else
        {
            report.root = pop_root(&br.root);
        }
    }

    while (br.root != NULL)
    {
        insert_node(report.root, pop_root(&br.root));
    }

    while (arg.root != NULL)
    {
        insert_node(report.root, pop_root(&arg.root));
    }
}