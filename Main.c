#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SLList.c"

typedef struct
{
    char nome[30];
    int numCamisa;
    float altura;
} Jogador;

void imprimirJogador(Jogador *jogador)
{
    if (jogador != NULL)
    {
        printf("\nNome: %s, Numero da Camisa: %d, Altura: %.2f\n", jogador->nome, jogador->numCamisa, jogador->altura);
    }
}

int inserirJogador(SLList *colecao, Jogador *jogador)
{
    return sllInsertFirst(colecao, jogador);
}

void listarJogadores(SLList *colecao)
{
    Jogador *jogador = (Jogador *)sllGetFirst(colecao);
    while (jogador != NULL)
    {
        imprimirJogador(jogador);
        jogador = (Jogador *)sllGetNext(colecao);
    }
}

void esvaziarColecao(SLList *colecao)
{
    while (sllRemoveFirst(colecao) != NULL)
        ;
}

int cmpJogadorNome(void *key, void *data)
{
    char *nomeKey = (char *)key;
    Jogador *jogador = (Jogador *)data;
    return strcmp(nomeKey, jogador->nome) == 0;
}

int cmpJogadorNumCamisa(void *key, void *data)
{
    int *numKey = (int *)key;
    Jogador *jogador = (Jogador *)data;
    return *numKey == jogador->numCamisa;
}

int cmpJogadorAltura(void *key, void *data)
{
    float *alturaKey = (float *)key;
    Jogador *jogador = (Jogador *)data;
    return *alturaKey == jogador->altura;
}

void *buscarJogador(SLList *time, void *key, int (*cmp)(void *, void *))
{
    return sllQuery(time, key, cmp);
}

void *removerJogador(SLList *time, void *key, int (*cmp)(void *, void *))
{
    return sllRemoveSpec(time, key, cmp);
}

int main()
{
    SLList *time = NULL;
    int opc;
    do
    {
        printf("\n\n------- Menu: -------");
        printf("\n________________________\n");
        printf("| 1. Criar time        |\n");
        printf("| 2. Colocar jogador   |\n");
        printf("| 3. Consultar jogador |\n");
        printf("| 4. Remover jogador   |\n");
        printf("| 5. Listar jogadores  |\n");
        printf("| 6. Esvaziar time     |\n");
        printf("| 7. Destruir time     |\n");
        printf("| 8. Sair              |\n");
        printf("|______________________|\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            if (time == NULL)
            {
                time = sllCreate();
                printf("\nTime criado com sucesso!\n");
            }
            else
            {
                printf("\nTime ja existente!\n");
            }
            break;

        case 2:
            if (time != NULL)
            {
                Jogador *novoJogador = (Jogador *)malloc(sizeof(Jogador));
                if (novoJogador != NULL)
                {
                    printf("\nDigite o nome do jogador: ");
                    scanf("%s", novoJogador->nome);
                    int numCamisa;
                    do {
                        printf("Digite o numero da camisa: ");
                        scanf("%d", &numCamisa);
                        if (buscarJogador(time, &numCamisa, cmpJogadorNumCamisa) != NULL) {
                            printf("\nNumero da camisa ja esta sendo usado. Por favor, escolha outro numero.\n");
                        }
                    } while (buscarJogador(time, &numCamisa, cmpJogadorNumCamisa) != NULL);
                    
                    novoJogador->numCamisa = numCamisa;
                    printf("Digite a altura do jogador: ");
                    scanf("%f", &novoJogador->altura);

                    inserirJogador(time, novoJogador);
                    printf("\nJogador inserido com sucesso!\n");
                }
                else
                {
                    printf("\nErro ao criar jogador.\n");
                }
            }
            else
            {
                printf("\nCrie um time primeiro.\n");
            }
            break;

        case 3:
            if (time != NULL)
            {
                int criterio;
                printf("\nBuscar jogador por: \n1. Nome \n2. Numero da camisa \n3. Altura \n\nEscolha uma opcao: ");
                scanf("%d", &criterio);

                if (criterio == 1)
                {
                    char nome[30];
                    printf("\nNome do jogador procurado: ");
                    scanf("%s", nome);
                    Jogador *jogador = (Jogador *)buscarJogador(time, nome, cmpJogadorNome);

                    if (jogador != NULL)
                    {
                        printf("\nJogador encontrado: \n");
                        imprimirJogador(jogador);
                    }
                    else
                    {
                        printf("\nJogador nao encontrado. \n");
                    }
                }
                else if (criterio == 2)
                {
                    int numCamisa;
                    printf("\nNumero da camisa do jogador procurado: ");
                    scanf("%d", &numCamisa);
                    Jogador *jogador = (Jogador *)buscarJogador(time, &numCamisa, cmpJogadorNumCamisa);

                    if (jogador != NULL)
                    {
                        printf("\nJogador encontrado: \n");
                        imprimirJogador(jogador);
                    }
                    else
                    {
                        printf("\nJogador nao encontrado. \n");
                    }
                }
                else if (criterio == 3)
                {
                    float altura;
                    printf("\nAltura do jogador procurado: ");
                    scanf("%f", &altura);
                    Jogador *jogador = (Jogador *)buscarJogador(time, &altura, cmpJogadorAltura);

                    if (jogador != NULL)
                    {
                        printf("\nJogador encontrado: \n");
                        imprimirJogador(jogador);
                    }
                    else
                    {
                        printf("\nJogador nao encontrado. \n");
                    }
                }
                else
                {
                    printf("\nCriterio de busca invalido. \n");
                }
            }
            else
            {
                printf("\nCrie um time primeiro. \n");
            }
            break;

        case 4:
            if (time != NULL)
            {
                int criterio;
                printf("\nRemover jogador por: \n1. Nome \n2. Numero da camisa \n3. Altura \n\nEscolha uma opcao: ");
                scanf("%d", &criterio);

                if (criterio == 1)
                {
                    char nome[30];
                    printf("\nNome do jogador a ser removido: ");
                    scanf("%s", nome);
                    Jogador *jogador = (Jogador *)removerJogador(time, nome, cmpJogadorNome);

                    if (jogador != NULL)
                    {
                        printf("\nJogador removido: \n");
                        imprimirJogador(jogador);
                        free(jogador);
                    }
                    else
                    {
                        printf("\nJogador nao encontrado. \n");
                    }
                }
                else if (criterio == 2)
                {
                    int numCamisa;
                    printf("\nNumero da camisa do jogador a ser removido: ");
                    scanf("%d", &numCamisa);
                    Jogador *jogador = (Jogador *)removerJogador(time, &numCamisa, cmpJogadorNumCamisa);

                    if (jogador != NULL)
                    {
                        printf("\nJogador removido: \n");
                        imprimirJogador(jogador);
                        free(jogador);
                    }
                    else
                    {
                        printf("\nJogador nao encontrado. \n");
                    }
                }
                else if (criterio == 3)
                {
                    float altura;
                    printf("\nAltura do jogador a ser removido: ");
                    scanf("%f", &altura);
                    Jogador *jogador = (Jogador *)removerJogador(time, &altura, cmpJogadorAltura);

                    if (jogador != NULL)
                    {
                        printf("\nJogador removido: \n");
                        imprimirJogador(jogador);
                        free(jogador);
                    }
                    else
                    {
                        printf("\nJogador nao encontrado. \n");
                    }
                }
                else
                {
                    printf("\nCriterio de busca invalido. \n");
                }
            }
            else
            {
                printf("\nCrie um time primeiro. \n");
            }
            break;

        case 5:
            if (time != NULL)
            {
                printf("\nLista de Jogadores: \n");
                listarJogadores(time);
            }
            else
            {
                printf("\nCrie um time primeiro.\n");
            }
            break;

        case 6:
            if (time != NULL)
            {
                esvaziarColecao(time);
                printf("\nTime esvaziado com sucesso!\n");
            }
            else
            {
                printf("\nCrie um time primeiro.\n");
            }
            break;

        case 7:
            if (time != NULL)
            {
                if (sllDestroy(time))
                {
                    printf("\nTime destruido com sucesso!\n");
                    time = NULL;
                }
                else
                {
                    printf("\nEsvazie o time primeiro.\n");
                }
            }
            else
            {
                printf("\nCrie um time primeiro.\n");
            }
            break;

        case 8:
            if (time != NULL)
            {
                esvaziarColecao(time);
                sllDestroy(time);
            }
            printf("\nSaindo...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
        }
    } while (opc != 8);

    return 0;
}
