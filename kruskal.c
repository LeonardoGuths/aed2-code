#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIST_MAX INT_MAX/2

typedef struct{
    char nome[50];
}Nome;

typedef struct{
    int origem, destino, peso;
}Aresta;

typedef struct{
    int pai, rank;
}Subconjunto;

int menu (void);
void List (int **matriz, Nome *nomes, int qntv);
int Equals (int **matriz, int indi1, int indi2, int qntv);
int **geraMatriz (int qntv);
void insereAresta (Aresta *arestas, int indi1, int indi2, int peso, int index);
void ListArestas (Aresta *arestas, int qnta);
void Kruskal (Aresta *arestas, int qnta, int qntv);
void Sort(Aresta *arestas, int qnta);
int Procura (Subconjunto *auxiliar, int i);
void Uniao (Subconjunto *auxiliar, int x, int y);


int main()
{
    int o, index=0, qntv, indi1, indi2, peso, qual, qnta=0;
    char nome[50], fim[50];
    int **matriz;
    Nome *nomes;
    Aresta *arestas;

    arestas = (Aresta *)malloc(sizeof(Aresta));
    if (!arestas)
    {
        printf ("Erro alocando memoria!\n");
        exit(1);
    }

    printf ("Algoritmo de Kruskal\n");
    printf ("(1) Construir o grafo manualmente\n(2) Utilizar o grafo pre-definido (imagem em anexo)\nOpcao: ");
    scanf ("%d",&o);
    if (o==1)
    {
        printf ("Quantos vertices deseja inserir (max 20): ");
        scanf ("%d",&qntv);

        while (qntv<=0 || qntv>20)
        {
            printf ("Insira uma quantidade valida (de 1 a 20): ");
            scanf ("%d",&qntv);
        }

        matriz = geraMatriz (qntv);
        nomes = (Nome *)malloc(sizeof(Nome)*qntv);
        if (!nomes)
        {
            printf ("Erro alocando memoria!\n");
            exit(1);
        }

        printf ("Digite o nome dos vertices a seguir:\n");
        for (int i=0; i<qntv; i++)
        {
            printf ("V[%d]: ",i);
            setbuf (stdin, NULL);
            scanf ("%[^\n]",nomes[i].nome);
        }
    }
    else
    {
        qntv = 6;
        matriz = geraMatriz (qntv);
        nomes = (Nome *)malloc(sizeof(Nome)*qntv);
        if (!nomes)
        {
            printf ("Erro alocando memoria!\n");
            exit(1);
        }

        strcpy(nomes[0].nome, "A");
        strcpy(nomes[1].nome, "B");
        strcpy(nomes[2].nome, "C");
        strcpy(nomes[3].nome, "D");
        strcpy(nomes[4].nome, "E");
        strcpy(nomes[5].nome, "F");

        qnta = 12;
        matriz[0][1] = 6;
        matriz[0][3] = 15;
        matriz[0][5] = 2;
        matriz[0][4] = 5;
        matriz[1][0] = 4;
        matriz[1][2] = 4;
        matriz[1][5] = 2;
        matriz[2][3] = 3;
        matriz[3][1] = 5;
        matriz[4][3] = 10;
        matriz[5][0] = 1;
        matriz[5][4] = 2;

        arestas = (Aresta *)realloc(arestas, sizeof(Aresta)*qnta);
        if (!arestas)
        {
            printf ("Erro alocando memoria!\n");
            exit(1);
        }
        
        insereAresta(arestas, 0, 1, 6, 1);
        insereAresta(arestas, 0, 3, 15, 2);
        insereAresta(arestas, 0, 5, 2, 3);
        insereAresta(arestas, 0, 4, 5, 4);
        insereAresta(arestas, 1, 0, 4, 5);
        insereAresta(arestas, 1, 2, 4, 6);
        insereAresta(arestas, 1, 5, 2, 7);
        insereAresta(arestas, 2, 3, 3, 8);
        insereAresta(arestas, 3, 1, 5, 9);
        insereAresta(arestas, 4, 3, 10, 10);
        insereAresta(arestas, 5, 0, 1, 11);
        insereAresta(arestas, 5, 4, 2, 12);
    }

    o=0;
    while (o != 5)
    {
        o = menu();
        switch (o)
        {
            case 1:
                List(matriz, nomes, qntv);

                indi1 = -1;
                while (indi1 == -1)
                {
                    setbuf(stdin, NULL);
                    printf ("Nome do vertice inicial: ");
                    scanf ("%[^\n]",nome);

                    //indi1 = -1;
                    for (int i=0; i<qntv; i++)
                    {
                        if (strcmp(nome, nomes[i].nome) == 0)
                            indi1 = i;
                    }
                    if (indi1 == -1)
                        printf (" * Este vertice nao existe! Insira um vertice valido!\n");
                }

                indi2 = -1;
                while (indi2 == -1)
                {
                    setbuf(stdin,NULL);
                    printf ("Nome do vertice adjacente: ");
                    scanf ("%[^\n]",nome);

                    for (int i=0; i<qntv; i++)
                    {
                        if (strcmp(nome, nomes[i].nome) == 0)
                            indi2 = i;
                    }
                    if (indi2 == -1)
                        printf (" * Este vertice nao existe! Insira um vertice valido!\n");
                }
                

                if (matriz[indi1][indi2]>=DIST_MAX)
                {
                    printf ("Peso da aresta: ");
                    scanf ("%d",&peso);
                    matriz[indi1][indi2] = peso;
                    qnta++;

                    arestas = (Aresta *)realloc(arestas, sizeof(Aresta)*qnta);
                    if (!arestas)
                    {
                        printf ("Erro alocando memoria!\n");
                        exit(1);
                    }

                    insereAresta(arestas, indi1, indi2, peso, qnta);
                }
                else
                    printf (" * Estes vertices ja sao adjacentes!\n");
                break;
            case 2:
                printf ("- - LISTA DE ADJACENCIA - -\n");
                List(matriz, nomes, qntv);
                printf ("- - - - - - - - - - - - - -\n");
                printf ("- - - LISTA DE ARESTAS - - -\n");
                ListArestas(arestas, qnta);
                printf ("- - - - - - - - - - - - - -\n");
                break;
            case 3:
                Kruskal (arestas, qnta, qntv);
                break;
            case 4:
                for (int i=0; i<qntv; i++)
                    free(matriz[i]);
                free(matriz);
                free(nomes);
                free(arestas);
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
    printf ("2. Mostra na tela a lista de adjacencia\n");
    printf ("3. Aplicar o algoritmo de Kruskal\n");
    printf ("4. Sair do programa\n");
    printf ("Opcao: ");
    scanf ("%d",&o);
    return o;
}

int **geraMatriz (int qntv)
{
    int **matriz;
    matriz = (int **)malloc(sizeof(int*)*qntv);
    if (!matriz)
    {
        printf ("Erro alocando memória!\n");
        exit(1);
    }

    for (int i=0; i<qntv; i++)
    {
        matriz[i] = (int *)malloc(sizeof(int)*qntv);
        if (!matriz[i])
        {
            printf ("Erro alocando memória!\n");
            exit(1);
        }
    }

    for (int i=0; i<qntv; i++)
        for (int j=0; j<qntv; j++)
            matriz[i][j] = DIST_MAX;

    return matriz;
}

void List (int **matriz, Nome *nomes, int qntv)
{
    for (int i=0; i<qntv; i++)
    {
        printf ("V[%d]: %s -> ",i,nomes[i].nome);
        for (int j=0; j<qntv; j++)
        {
            if (matriz[i][j]<DIST_MAX)
                printf ("%s, %d -> ",nomes[j].nome, matriz[i][j]);
        }
        printf ("NULL\n");
    }
    
}

void insereAresta(Aresta *arestas, int indi1, int indi2, int peso, int index)
{
    arestas[index-1].origem = indi1;
    arestas[index-1].destino = indi2;
    arestas[index-1].peso = peso;
}

void ListArestas (Aresta *arestas, int qnta)
{
    for (int i=0; i<qnta; i++)
    {
        printf ("[%d -> %d]: %d\n",arestas[i].origem, arestas[i].destino, arestas[i].peso);
    }
}

void Kruskal (Aresta *arestas, int qnta, int qntv)
{
    int i, qntaF=0, x, y;
    Aresta *arestasFinal, atual;
    Subconjunto *auxiliar;
    arestasFinal = (Aresta *)malloc(sizeof(Aresta)*qntv);
    auxiliar = (Subconjunto *)malloc(sizeof(Subconjunto)*qntv);
    if (!arestasFinal || !auxiliar)
    {
        printf ("Erro alocando memoria!\n");
        exit(1);
    }

    for (i=0; i<qntv; i++)
    {
        auxiliar[i].pai = i;
        auxiliar[i].rank = 0;
    }
    
    Sort(arestas, qnta);
    //ListArestas(arestas, qnta);

    for (i=0; i<qnta; i++)
    {
        if (qntaF < qntv-1)
        {
            atual = arestas[i];

            x = Procura(auxiliar, atual.origem);
            y = Procura(auxiliar, atual.destino);

            if (x != y)
            {
                arestasFinal[qntaF++] = atual;
                Uniao (auxiliar, x, y);
            }
            
        }
    }
    printf ("ARESTAS FINAIS\n");
    ListArestas(arestasFinal, qntaF);

    free(arestasFinal);
    free(auxiliar);
}

void Sort(Aresta *arestas, int qnta)
{
    int i, j;
    Aresta aux;

    for (i = 1; i < qnta; i++)
        for (j = 0; j < qnta-1; j++)
            if (arestas[j].peso > arestas[j+1].peso) 
            {
                aux = arestas[j];
                arestas[j] = arestas[j+1];
                arestas[j+1] = aux;
            }
}

int Procura (Subconjunto *auxiliar, int i)
{
    if (auxiliar[i].pai != i)
        auxiliar[i].pai = Procura(auxiliar, auxiliar[i].pai);

    return auxiliar[i].pai;
}

void Uniao (Subconjunto *auxiliar, int x, int y)
{
    int raizx = Procura(auxiliar, x);
    int raizy = Procura(auxiliar, y);

    if (auxiliar[raizx].rank < auxiliar[raizy].rank)
        auxiliar[raizx].pai = raizy;
    else if (auxiliar[raizx].rank > auxiliar[raizy].rank)
        auxiliar[raizy].pai = raizx;
    else
    {
        auxiliar[raizy].pai = raizx;
        auxiliar[raizx].rank++;
    }
}
