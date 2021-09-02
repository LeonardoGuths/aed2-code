#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIST_MAX INT_MAX/2

typedef struct{
    char nome[50];
}Nome;

int menu (void);
void List (int **matriz, Nome *nomes, int qntv);
int Equals (int **matriz, int indi1, int indi2, int qntv);
int **geraMatriz (int qntv);
void Dijkstra (int **matriz, Nome *nomes, int qntv, int ini, int fim);


int main()
{
    int o=0, index=0, qntv, indi1, indi2, peso, qual;
    char nome[50], fim[50];
    int **matriz;
    Nome *nomes;

    printf ("Algoritmo de Dijkstra\n");
    printf ("%d\n",DIST_MAX);
    printf ("Quantos vertices deseja inserir (max 20): ");
    scanf ("%d",&qntv);

    while (qntv<=0 || qntv>20)
    {
        printf ("Insira uma quantidade valida (de 1 a 20): ");
        scanf ("%d",&qntv);
    }

    matriz = geraMatriz (qntv);
    nomes = (Nome *)malloc(sizeof(Nome)*qntv);

    printf ("Digite o nome dos vertices a seguir:\n");
    for (int i=0; i<qntv; i++)
    {
        //pLista[i].pFirst = NULL;
        printf ("V[%d]: ",i);
        setbuf (stdin, NULL);
        scanf ("%[^\n]",nomes[i].nome);
    }

    //*hard code pra um grafo inventado
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

                    //indi2 = -1;
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
                }
                else
                    printf (" * Estes vertices ja sao adjacentes!\n");
                break;
            case 2:
                printf ("- - LISTA DE ADJACENCIA - -\n");
                List(matriz, nomes, qntv);
                printf ("- - - - - - - - - - - - - -\n");
                break;
            case 3:
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
                    printf ("Nome do vertice final: ");
                    scanf ("%[^\n]",nome);

                    //indi2 = -1;
                    for (int i=0; i<qntv; i++)
                    {
                        if (strcmp(nome, nomes[i].nome) == 0)
                            indi2 = i;
                    }
                    if (indi2 == -1)
                        printf (" * Este vertice nao existe! Insira um vertice valido!\n");
                }

                Dijkstra (matriz, nomes, qntv, indi1, indi2);
                break;
            case 4:
                for (int i=0; i<qntv; i++)
                    free(matriz[i]);
                free(matriz);
                free(nomes);
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
    printf ("3. Aplicar o algoritmo de Dijkstra\n");
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

void Dijkstra (int **matriz, Nome *nomes, int qntv, int ini, int fim)
{
    int i, *dist, *antec, *visitado, cont=0, DMenor, IMenor=ini, *aux;
    dist = (int *)malloc(sizeof(int)*qntv);
    antec = (int *)malloc(sizeof(int)*qntv);
    visitado = (int *)malloc(sizeof(int)*qntv);
    aux = (int *)malloc(sizeof(int)*qntv);

    //inicializa os vetores dist[x](distancia do vertice x ate o ponto inicial),
    //                      antec[x](antecessor do vertice x no caminho dist[x])
    //                    e seta todos vertices como não visitados (visitado[x]).
    for (i=0; i<qntv; i++)
    {
        dist[i] = matriz[ini][i];
        antec[i] = ini;
        visitado[i] = 0;
    }
    dist[ini] = 0;
    visitado[ini] = 1;
    cont++;

    while (cont < qntv)
    {
        DMenor = DIST_MAX;

        //pega a distancia e o indice do vertice que possui
        //a menor distancia até o p inicial e ainda não foi visitado
        for (i=0; i<qntv; i++)
        {
            if (!(visitado[i]) && dist[i] < DMenor)
            {
                DMenor = dist[i];
                IMenor = i;
            }
        }

        visitado[IMenor] = 1;
        
        //se a distancia do p inicial até um vertice nao visitado (VNV) for maior
        //do que a distancia somada do p inicial ao IM e do IM ao VNV, atualiza
        //a distancia do p inicial ao VNV e coloca como antecessor do VNV o IM
        for (i=0; i<qntv; i++)
        {
            if (!(visitado[i]) && DMenor + matriz[IMenor][i] < dist[i])
            {
                dist[i] = DMenor + matriz[IMenor][i];
                antec[i] = IMenor;
            }
        }
        cont++;
    }


    if (dist[fim] < DIST_MAX)
    {
        printf ("START | %s -> ", nomes[ini].nome);
        cont=0;
        do
        {
            aux[cont] = fim;
            fim = antec[fim];
            cont++;
        }while (fim != ini);

        for (i=(cont-1); i>0; i--)
        {
            printf ("%s -> ",nomes[aux[i]].nome);
        }
        printf ("%s | END\n", nomes[aux[i]].nome);
        printf ("Distancia total: %d\n",dist[aux[i]]);
    }
    else
    {
        printf ("Nao existe caminho possivel entre estes dois pontos!\n");
    }

    free(dist);
    free(antec);
    free(visitado);
    free(aux);
}