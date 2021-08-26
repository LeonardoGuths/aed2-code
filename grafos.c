#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    int peso;
}Info;

typedef struct sNodo{
    Info info;
    struct sNodo *pNext;
}Nodo;

typedef struct{
    Nodo *pFirst;
    char nome[50];
}Lista;

int menu (void);
void Clear (Lista *pLista);
void Reset (Lista *pLista);
int Push (Lista *pLista, Nodo *pNodo, int index);
void Pop (Lista *pLista, char *rmv);
void List (Lista *pLista, int qntv);

int main()
{
    int o=0, index=0, qntv, indi1, indi2, peso, qual;
    char nome[50];
    Nodo *pNodo;
    Lista *pLista;
    printf ("Trabalho de Implementacao de Grafos\n");
    printf ("Quantos vertices deseja inserir (max 20): ");
    scanf ("%d",&qntv);

    while (qntv<=0 || qntv>20)
    {
        printf ("Insira uma quantidade valida (de 1 a 20): ");
        scanf ("%d",&qntv);
    }

    pLista = (Lista *)malloc(sizeof(Lista)*qntv);
    printf ("Digite o nome dos vertices a seguir:\n");
    for (int i=0; i<qntv; i++)
    {
        pLista[i].pFirst = NULL;
        printf ("V[%d]: ",i);
        setbuf (stdin, NULL);
        scanf ("%[^\n]",pLista[i].nome);
    }


    while (o != 5)
    {
        o = menu();
        switch (o)
        {
            case 1:
                List(pLista, qntv);
                setbuf(stdin, NULL);
                printf ("Nome do vertice inicial: ");
                scanf ("%[^\n]",nome);

                indi1 = -1;
                for (int i=0; i<qntv; i++)
                {
                    if (strcmp(nome, pLista[i].nome) == 0)
                        indi1 = i;
                }

                if (indi1 == -1)
                {
                    printf ("Este vertice nao existe!\n");
                    break;
                }

                setbuf(stdin,NULL);
                printf ("Nome do vertice adjacente: ");
                scanf ("%[^\n]",nome);

                indi2 = -1;
                for (int i=0; i<qntv; i++)
                {
                    if (strcmp(nome, pLista[i].nome) == 0)
                        indi2 = i;
                }

                if (indi2 == -1)
                {
                    printf ("Este vertice nao existe!\n");
                    break;
                }

                pNodo = (Nodo *)malloc(sizeof(Nodo));
                strcpy(pNodo->info.nome, nome);

                printf ("Peso da aresta: ");
                scanf ("%d",&pNodo->info.peso);
                peso = pNodo->info.peso;

                Push(&pLista[indi1], pNodo, 0);

                pNodo = (Nodo *)malloc(sizeof(Nodo));

                strcpy(pNodo->info.nome, &pLista[indi1].nome);
                pNodo->info.peso = peso;
                Push(&pLista[indi2], pNodo, 0);
                break;
            case 2:
                printf ("Qual vertice deseja remover: ");
                setbuf(stdin,NULL);
                scanf ("%[^\n]",nome);

                //Pop(&pLista[vatual], nome);
                break;
            case 3:
                printf ("- - LISTA DE ADJACENCIA - -\n");
                List(pLista, qntv);
                printf ("- - - - - - - - - - - - - -\n");
                break;
            case 4:
                for (int i=0; i<qntv; i++)
                    Clear(&pLista[i]);
                exit(0);
                break;
        }
    }
return 0;
}

int menu (void)
{
    int o;
    printf ("1. Adicionar vertice adjacente\n");
    printf ("2. Remover um vertice adjacente\n");
    printf ("3. Lista na tela a lista de adjacencia\n");
    printf ("4. Sair do programa\n");
    printf ("Opcao: ");
    scanf ("%d",&o);
    return o;
}

void Reset (Lista *pLista)
{
    Clear (pLista);
    pLista = (Lista *)malloc(sizeof(Lista));
    pLista->pFirst = NULL;
}

void Clear (Lista *pLista)
{
    Nodo *atual, *prox;
    if (pLista->pFirst != NULL)
    {
        atual = pLista->pFirst;
        prox = atual->pNext;

        while (prox != NULL)
        {
            free(atual);
            atual = prox;
            prox = prox->pNext;
        }
        free(atual);
    }
    free(pLista);
}

int Push (Lista *pLista, Nodo *pNodo, int index)
{
    Nodo *anterior, *atual;
    int pos;

    if (pLista->pFirst == NULL && index != 0)
        return 0;   //indice invalido
    else if (pLista->pFirst == NULL && index == 0)
    {
        pLista->pFirst = pNodo;
        pLista->pFirst->pNext = NULL;
        return 1;
    }
    else if (index == 0)
    {
        pNodo->pNext = pLista->pFirst;
        pLista->pFirst = pNodo;
        return 1;
    }

    atual = pLista->pFirst;
    for (pos = 0; pos < index && atual != NULL; pos++)
    {
        anterior = atual;
        atual = atual->pNext;
    }

    if (atual == NULL)
    {
        printf ("INDICE INVALIDO\n");
        return 0;
    }
    
    pNodo->pNext = atual;
    anterior->pNext = pNodo;
}

void Pop (Lista *pLista, char *rmv)
{
    Nodo *anterior, *atual;

    if (pLista->pFirst != NULL)
    {
        atual = pLista->pFirst;

        while (strcmp(atual->info.nome, rmv) != 0)
        {
            anterior = atual;
            atual = atual->pNext;
        }   

        if (atual == pLista->pFirst)
        {
            pLista->pFirst = pLista->pFirst->pNext;
            free(atual);
        }
        else
        {
            anterior->pNext = atual->pNext;
            free(atual);
        }
    }
    else
        printf ("Lista vazia!\n");
}

void List (Lista *pLista, int qntv)
{
    Nodo *atual;
    
    for (int i=0; i<qntv; i++)
    {
        atual = pLista[i].pFirst;
        printf ("V[%d]: %s -> ",i,pLista[i].nome);

        if (atual != NULL)
        {
            while(atual != NULL)
            {
                printf ("%s, %d -> ",atual->info.nome,atual->info.peso);
                atual = atual->pNext;
            }
            printf ("NULL\n");
        }
        else
            printf ("NULL\n");
    }
    
}

//conferir se ja n ta na lista
//verificar se tem memory leaks