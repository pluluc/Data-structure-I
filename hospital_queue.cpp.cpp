#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo tipo paciente:
typedef struct pacient
{
    char name[30];
    char cpf[15];
    struct pacient *prox;
} pac;
// Declarando variáveis universais para os extremos das filas e seus contadores:
pac *head_emergency = NULL;
pac *tail_emergency = NULL;

pac *head_urgency = NULL;
pac *tail_urgency = NULL;

pac *head_regular = NULL;
pac *tail_regular = NULL;

int in_emergency = 0, in_urgency = 0, in_regular = 0;
int out_emergency = 0, out_urgency = 0, out_regular = 0;
int urgent_loop = 0;

// Funções:
pac *insert_pacient();
void menu();
void relatorio();
bool isEmpty();

void registrar(pac **head, pac **tail, pac *paciente);
void pop(pac **top, pac **tail);
void next(pac **head_emer, pac **head_urg, pac **head_reg, pac **tail_emer, pac **tail_urg, pac **tail_reg);
void print(pac *aux);
void buscar(pac *head_emer, pac *head_urg, pac *head_reg);

int main(void)
{

    int op = -1, level = 0;

    while (op != 0)
    {

        menu();
        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            printf("Qual a situacao do paciente?\n\n1 para emergencia\n\n2 para urgencia\n\n3 para eletivo.\n");
            scanf("%i", &level);
            getchar();
            switch (level)
            {
            case 1:
                registrar(&head_emergency, &tail_emergency, insert_pacient());
                in_emergency++;
                break;
            case 2:
                registrar(&head_urgency, &tail_urgency, insert_pacient());
                in_urgency++;
                break;
            case 3:
                registrar(&head_regular, &tail_regular, insert_pacient());
                in_regular++;
                break;
            default:
                printf("Insira uma opcao valida");
                break;
            }
            level = 0;
            break;

        case 2:
            printf("Qual fila deseja visualizar?\n1 para emergencia\n2 para urgencia\n3 para eletivos\n");
            scanf("%i", &level);
            getchar();
            switch (level)
            {
            case 1:
                print(head_emergency);
                break;
            case 2:
                print(head_urgency);
                break;
            case 3:
                print(head_regular);
                break;
            default:
                printf("Insira uma opcao valida");
                break;
            }
            break;

        case 3:
            next(&head_emergency, &head_urgency, &head_regular, &tail_emergency, &tail_urgency, &tail_regular);
            break;

        case 4:
            relatorio();
            break;
        case 5:
            buscar(head_emergency, head_urgency, head_regular);
            break;
        case 0:
            printf("Encerrando...");
            break;

        default:
            printf("Opcao invalida\n");
            break;
        }
    }
    return 0;
}

// Função que cria, preenche e retorna um paciente;
pac *insert_pacient()
{
    pac *nova = (pac *)malloc(sizeof(pac));

    printf("Informe o nome do paciente:\n");
    scanf("%s", nova->name);
    getchar();
    printf("Informe o CPF do paciente:\n");
    scanf("%s", nova->cpf);
    getchar();

    return nova;
}

// Função isEmpty: Testa se há algum elemento em todas as listas e retorna true or false.
bool isEmpty()
{
    return (in_emergency) == 0 && (in_urgency) == 0 && (in_regular == 0);
}

// menu (menu);
void menu()
{
    printf("\n\n");
    printf("*******\t\tFila de atendimento\t********\n");
    printf("*\t1 - Inserir paciente\t*\n");
    printf("*\t2 - Exibir filas\t*\n");
    printf("*\t3 - Proximo paciente\t*\n");
    printf("*\t4 - Relatorio de atendimentos\t*\n");
    printf("*\t5 - Buscar paciente por cpf\t*\n");
    printf("*\t0 - Sair\t\t*\n");
    return;
}

// Função relatorio: Exibe quantos elementos foram retirados de cada lista com base nos contadores universais;
void relatorio()
{
    printf("---------Relatorio---------\n");
    printf("Atentidos na emergencia: %i\nAtendidos na urgencia: %i\nAtendidos na eletiva: %i\n", out_emergency, out_urgency, out_regular);
}

// Função print: recebe uma lista e exibe o conteúdo de suas células;
void print(pac *aux)
{
    while (aux != NULL)
    {
        printf("\tNome: %s\n", aux->name);
        printf("\tCPF: %s\n\n", aux->cpf);
        aux = aux->prox;
    }
    printf("--------------------------\n");
    return;
}

// Função que recebe os extremos de uma lista, um paciente via função insert_pacient e adiciona o próprio na lista;
void registrar(pac **head, pac **tail, pac *paciente)
{
    paciente->prox = NULL;

    if (*head == NULL)
    {
        *head = paciente;
        *tail = paciente;
        return;
    }
    else
    {
        (*tail)->prox = paciente;
        *tail = paciente;
        return;
    }
}

// Função pop, recebe os extremos de uma lista, retira o primeiro e retorna o próprio;
void pop(pac **top, pac **tail)
{
    pac *out = NULL;

    if (strcmp((*top)->cpf, (*tail)->cpf) == 0)
    {
        out = *top;
        *top = NULL;
        out->prox = NULL;
        tail = NULL;
        printf("o proximo paciente a ser atendido e:\n\nnome: %s\ncpf:%s", out->name, out->cpf);
        free(out);
        return;
    }
    else
    {
        out = *top;
        *top = (*top)->prox;
        out->prox = NULL;
        printf("o proximo paciente a ser atendido e:\n\nnome: %s\ncpf:%s", out->name, out->cpf);
        free(out);
        return;
    }
}

/*Função next: Recebe as cabeças e caudas das listas, e remove os elementos que estão nas cabeças das filas
utilizando a função pop e obedecendo a ordem de prioridade(Emergência primeiro e para cada 3 urgentes, 1 eletivo);*/

void next(pac **head_emer, pac **head_urg, pac **head_reg, pac **tail_emer, pac **tail_urg, pac **tail_reg)
{
    if (isEmpty() == true)
    {
        printf("A fila esta vazia.");
        return;
    }
    if (in_emergency > 0)
    {
        pop(head_emer, tail_emer);
        in_emergency--;
        out_emergency++;
        return;
    }

    if (in_urgency != 0)
    {
        if (urgent_loop < 3)
        {
            pop(head_urg, tail_urg);
            in_urgency--;
            out_urgency++;
            urgent_loop++;
            return;
        }

        urgent_loop = 0;

        pop(head_reg, tail_reg);
        in_regular--;
        out_regular++;
        return;
    }

    else
    {
        pop(head_reg, tail_reg);
        in_regular--;
        out_regular++;
        urgent_loop = 0;
        return;
    }
}

/*Função buscar: recebe as 3 listas, passa para auxiliares, recebe uma string e passa em cada lista procurando
caso encontre, realiza a conta de quantos tem na frente do cpf, com base nos contadores, e caso não, exibe a men-
sagem dizendo que não encontrou.*/
void buscar(pac *head_emer, pac *head_urg, pac *head_reg)
{

    if (isEmpty() == true)
    {
        printf("A fila esta vazia.");
        return;
    }

    pac *auxE = head_emer;
    pac *auxU = head_urg;
    pac *auxR = head_reg;

    char cpf[15];
    int cont = 0, cont_urg = 0, cont_reg = 0;

    printf("Digite o cpf do paciente:\n");
    scanf("%s", cpf);
    getchar();

    while (auxE != NULL)
    {
        if ((strcmp(cpf, auxE->cpf)) == 0)
        {
            printf("Tem %i pessoas na frente de %s", cont, auxE->name);
            return;
        }
        cont++;
        auxE = auxE->prox;
    }

    int loop_cont = -1;
    int qnt_reg = in_regular;
    while (auxU != NULL)
    {
        loop_cont++;
        if (loop_cont == 3 && qnt_reg != 0)
        {
            qnt_reg--;
            cont_urg++;
            loop_cont = 0;
        }
        if ((strcmp(cpf, auxU->cpf)) == 0)
        {
            cont_urg = cont_urg + in_emergency;
            printf("Tem %i pessoas na frente de %s", cont_urg, auxU->name);
            return;
        }
        cont_urg++;
        auxU = auxU->prox;
    }

    loop_cont = 0;
    int qnt_urg = in_urgency;

    while (auxR != NULL)
    {
        if(qnt_urg !=0 && qnt_urg%3 == 0){
            
        }

        if ((strcmp(cpf, auxR->cpf)) == 0)
        {
            cont_reg = cont_reg + in_emergency;
            printf("Tem %i pessoas na frente de %s", cont_reg, auxR->name);
            return;
        }
        cont_reg++;
        auxR = auxR->prox;
    }
    printf("O paciente nao foi encontrado.\n");
}