#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define CONTROLE 2
#define MODO 2
const int CONTROLE = MODO *2;
//const int MODO = CONTROLE/2;
/*
Modo 5
3 24 36 60 64 [78] 79 102 109 125 131 

Modo 4
3 24 36 60 [78] 79 102 125 131

Modo 3
3 24 36 [78] 79 102 131

Modo 2
3 24 [78] 79 102 

3 24 [78] 79 102 103

*/
struct nob
{   char qtd;
    int codigos[CONTROLE];
    int posicoes[CONTROLE];
    int filhos[CONTROLE+1];
} no, noMaior, noPai;

struct Pilha
{   int endereco;
    struct Pilha *prox;
} *pilha = NULL;

void empilha(struct Pilha *&p, int end)
{   struct Pilha *novo = new(struct Pilha);
    novo->prox = p;
    novo->endereco = end;
    p = novo;
}

int desempilha(struct Pilha *&p)
{   if (p==NULL) return -1;
    int end = p->endereco;
    struct Pilha *i = p;
    p = p->prox;
    delete(i);
    return end;
}

void inicializar(struct Pilha *&p)
{   struct Pilha *t, *i = p;
    while (i != NULL)
    {   t = i;
        i = i->prox;
        delete(t);
    }
    p = NULL;
}

void inicializaNo()
{   no.qtd = 0;
    for (int i = 0; i < CONTROLE+1; i++)
    {   no.filhos[i] = -1;
        if (i < CONTROLE)
        {   no.codigos[i] = 0;
            no.posicoes[i] = -1;
        }
    }
}

void inicializaNoMaior()
{   noMaior.qtd = 0;
    for (int i = 0; i < CONTROLE+1; i++)
    {   noMaior.filhos[i] = -1;
        if (i < CONTROLE)
        {   noMaior.codigos[i] = 0;
            noMaior.posicoes[i] = -1;
        }
    }
}

void inicializaNoPai()
{   noPai.qtd=0;
    for (int i = 0; i < CONTROLE+1; i++)
    {   noPai.filhos[i] = -1;
        if (i < CONTROLE)
        {   noPai.codigos[i] = 0;
            noPai.posicoes[i] = -1;
        }
    }
}
/*
INDEXA  INDEXA  INDEXA  INDEXA  INDEXA  INDEXA  INDEXA  INDEXA  INDEXA 
*/ 
//fseek()       Procura por um byte específico (Começo do arquivo   SEEK_SET    0)
//fread()       le um bloco de dados
//fwrite        escreve um bloco de dados
//fgets()       são funções para ler e escrever strings.
//ftell         retorna a posição corrente de leitura ou escrita no arquivo (em bytes)
void explodir(int codigo, int posicao, int filhoMaior, int enderecoNo, int enderecoPai)
{   //filhoMaior, posicao do maior novo nó maior a direira do que explodiu
    FILE *indice = fopen("indice.ind", "r+");
    fseek(indice, enderecoNo, SEEK_SET);
    fread(&no, sizeof(struct nob), 1, indice);
    int codigos[CONTROLE+1], posicoes[CONTROLE+1], filhos[CONTROLE+2];

    //Carrega o nó pro vetor
    for (int i=0; i<CONTROLE; i++)
    {   codigos[i] = no.codigos[i];
        posicoes[i] = no.posicoes[i];
        filhos[i] = no.filhos[i];
    }
    //posiciona o ultimo filho do nó no vetor
    filhos[CONTROLE] = no.filhos[CONTROLE];
    
    //Testa se precisa ordenar o nó pra quem subiu
    int i;
    for (i=0; i<CONTROLE+1; i++)
    {   if (i==CONTROLE)
        {   i++;
            break;
        }
        if (no.codigos[i] > codigo) break;
    }
    //Temos um vetor de CONTROLE+1 Posicoes ordenados
    if (i==CONTROLE+1)
    {   codigos[CONTROLE] = codigo;
        posicoes[CONTROLE] = posicao;
        filhos[CONTROLE+1] = filhoMaior;
    }
    else
    {   for (int j=CONTROLE; j>i; j--)
        {   codigos[j] = codigos[j-1];
            posicoes[j] = posicoes[j-1];
        }
        for (int j=CONTROLE; j>i; j--)
        {   filhos[j+1] = filhos[j];
        }
        filhos[i+1] = filhoMaior;
        codigos[i] = codigo;
        posicoes[i] = posicao;
    }
    
    inicializaNo();
    no.qtd = MODO;
    
    for (int k = 0; k < MODO; k++)
    {   no.codigos[k] = codigos[k];
        no.posicoes[k] = posicoes[k];
        no.filhos[k] = filhos[k];        
    }
    no.filhos[MODO] = filhos[MODO];

    //Organiza a Explosão
    inicializaNoMaior();
    noMaior.qtd = MODO;
    
    for (int k = 0,c = MODO+1; k < MODO; k++, c++)
    {   noMaior.codigos[k] = codigos[c];
        noMaior.posicoes[k] = posicoes[c];
        noMaior.filhos[k] = filhos[c];
    }
    noMaior.filhos[MODO] = filhos[CONTROLE+1];
     /*
         [1][2][3][4] 5
       [1][2] [3] [4][5] 6
         3     2    3

        [0][1][2][3][4][5][6][7][8][9]
      [0][1][2][3][4] [5] [6][7][8][9][10] 12
             6         2         6
    */
   
    //carrega no arquivo 
    fseek(indice, enderecoNo, SEEK_SET);
    fwrite(&no, sizeof(struct nob), 1, indice);
    fseek(indice, 0, SEEK_END);
    int filhoDireitaPai = (int) ftell(indice);
    //novo Pai/Raiz
    fwrite(&noMaior, sizeof(struct nob), 1, indice);
    
    if (enderecoPai == -1)
    {   //Cria novo Nó para Inicio da Arvore, novaRaiz
        inicializaNoPai();
        noPai.qtd = 1;
        noPai.codigos[0] = codigos[MODO];
        noPai.posicoes[0] = posicoes[MODO];
        //filho Menor
        noPai.filhos[0] = enderecoNo;
        // Filho Maior
        noPai.filhos[1] = filhoDireitaPai;
        
        fseek(indice, 0, SEEK_END);
        int novaRaiz = ftell(indice);
        fwrite(&noPai, sizeof(struct nob), 1, indice);
        fseek(indice, 0, SEEK_SET);
        //Atualiza a Raiz no Arquivo
        fwrite(&novaRaiz, sizeof(int), 1, indice);
    }
    else
    {   fseek(indice, enderecoPai, SEEK_SET);
        //Carrega o Blogo Pai
        fread(&noPai, sizeof(struct nob), 1, indice);
        //Se o pai ja tiver CONTROLE nro de codigos, explode de novo
        if (noPai.qtd == CONTROLE)
        {   //Explode o Meio do vetor, por ser a nova raiz.
            explodir(codigos[MODO], posicoes[MODO], filhoDireitaPai, enderecoPai, desempilha(pilha));
        } 
        else
        {   int i;
            for (i = noPai.qtd-1; i >= 0; i--)
            {   if (noPai.codigos[i] > codigos[MODO])
                {   noPai.codigos[i+1] = noPai.codigos[i];
                    noPai.posicoes[i+1] = noPai.posicoes[i];
                    noPai.filhos[i+MODO] = noPai.filhos[i+1];
                    noPai.filhos[i+1] = noPai.filhos[i];
                }
                else break;
            }
            if (i==-1)
            {   noPai.codigos[0] = codigos[MODO];
                noPai.posicoes[0] = posicoes[MODO];
                noPai.filhos[0] = enderecoNo;
                noPai.filhos[1] = filhoDireitaPai;
            }
            else
            {   i++;
                noPai.codigos[i] = codigos[MODO];
                noPai.posicoes[i] = posicoes[MODO];
                noPai.filhos[i] = enderecoNo;
                noPai.filhos[i+1] = filhoDireitaPai;
            }
            
            noPai.qtd++;
            //grava NoPai
            fseek(indice, enderecoPai, SEEK_SET);
            fwrite(&noPai, sizeof(struct nob), 1, indice);
        }
    }
    fclose(indice);
}


void indexa(int codigo, int posicaoCursor, int endRaiz)
{   char inseriuCodigo = 0;
    char explodiu = 0;
    FILE *indice = fopen("indice.ind", "r+");
    inicializaNo();
    //Posiciona na Raiz
    fseek(indice, endRaiz, SEEK_SET);  
    //Carrega uma estrutura
    fread(&no, sizeof(struct nob), 1, indice);

    int i;
    for (i = 0; i < no.qtd; i++)
    {   //organiza
        if (no.codigos[i] > codigo)
        {   if (no.filhos[i] != -1)
            {  //empilhaRaiz e indexa
                empilha(pilha, endRaiz);
                indexa(codigo, posicaoCursor, no.filhos[i]);
            }
            else
            {   if (no.qtd == CONTROLE)
                {   //Explode
                    explodiu = 1;                    
                    int desempilhaMODO = desempilha(pilha);
                    explodir(codigo, posicaoCursor, -1, endRaiz, desempilhaMODO);
                }
                else
                {   for (int j = CONTROLE-1; j>i; j--)
                    {   //Organiza de traz pra frente, se tem espaco
                        no.codigos[j] = no.codigos[j-1];
                        no.posicoes[j] = no.posicoes[j-1];
                        no.filhos[j+1] = no.filhos[j];
                        no.filhos[j] = no.filhos[j-1];
                    }
                    //Depois de organizar, insere na posicao
                    no.codigos[i] = codigo;
                    no.posicoes[i] = posicaoCursor;
                    inseriuCodigo = 1;
                }
            }
            break;
        }
    }
    if (i == no.qtd && !explodiu)
    {   if (no.filhos[i] != -1)
        {   empilha(pilha, endRaiz);
            indexa(codigo, posicaoCursor, no.filhos[i]);
        }
        else
        {   if (i == CONTROLE)
            {   explodir(codigo, posicaoCursor, -1, endRaiz, desempilha(pilha));
            }
            else
            {   no.codigos[no.qtd] = codigo;
                no.posicoes[no.qtd] = posicaoCursor;
                inseriuCodigo = 1;
            }
        }
    }
    if (inseriuCodigo)
    {   //Se conseguiu inserir, Grava o no
        no.qtd++;
        fseek(indice, endRaiz, SEEK_SET);
        fwrite(&no, sizeof(struct nob), 1, indice);
    }
    fclose(indice);
}
/*
INDEXA  INDEXA  INDEXA  INDEXA  INDEXA  INDEXA  INDEXA  INDEXA  INDEXA 
*/ 

/*
PROCURA PROCURA PROCURA PROCURA
*/
int procura(int codigo, int pos)
{   FILE *indice = fopen("indice.ind", "r");
    fseek(indice, pos, SEEK_SET);
    fread(&no, sizeof(struct nob), 1, indice);
    int i;
    for (i=0; i<no.qtd; i++)
    {   if (no.codigos[i] >= codigo) break;
    }
    if (i != no.qtd && no.codigos[i] == codigo) return no.posicoes[i];
    if (no.filhos[i] < 0) return -1;
    return procura(codigo, no.filhos[i]);
}
/*
PROCURA PROCURA PROCURA PROCURA
*/


/*
APAGAR APAGAR APAGAR APAGA RAPAGAR
*/
void apagar(int codigo, int posicao)
{   if (posicao < 0) return;
    FILE *indice = fopen("indice.ind", "r+");
    fseek(indice, posicao, SEEK_SET);
    fread(&no, sizeof(struct nob), 1, indice);
    int i;
    for (i=0; i<no.qtd; i++)
    {   if (no.codigos[i] >= codigo) break;
    }
    if (no.codigos[i] == codigo)
    {   no.posicoes[i] = -2;
        fseek(indice, posicao, SEEK_SET);
        fwrite(&no, sizeof(struct nob), 1, indice);
    }
    else apagar(codigo, no.filhos[i]);
    fclose(indice);
}
/*
APAGAR APAGAR APAGAR APAGA RAPAGAR
*/


/*
EDITAR EDITAR
*/
int procuraEdita(int codigo, int posicao)
{   FILE *index = fopen("indice.ind", "r");
    fseek(index, posicao, SEEK_SET);
    fread(&no, sizeof(struct nob), 1, index);
    int i;
    for (i=0; i<no.qtd; i++)
    {   if (no.codigos[i] >= codigo) break;
    }
    if (i != no.qtd && no.codigos[i] == codigo)
    {   if (no.posicoes[i] < 0) return -1;
        return posicao;
    }
    if (no.filhos[i] == -1) return -1;
    return procuraEdita(codigo, no.filhos[i]);
}
/* EDITAR EDITAR */


/*
VACUUM VACUUM VACUUM VACUUM
*/
void vacuum(int posicao, FILE *arquivo, char *novo)
{   if (posicao == -1) return;
    struct nob no;
    FILE *indice = fopen("indice.ind", "r");
    fseek(indice, posicao, SEEK_SET);
    fread(&no, sizeof(struct nob), 1, indice);
    fclose(indice);
    FILE *novoArqCSV = fopen(novo, "r+");

    char linha[85] = "";
    for (int i=0; i<no.qtd; i++)
    {   if (no.posicoes[i] != -2){
            fseek(arquivo, no.posicoes[i], SEEK_SET);
            fseek(novoArqCSV, 0, SEEK_END);
            fgets(linha, 85, arquivo);
            fwrite(linha, sizeof(char), strlen(linha), novoArqCSV);
        }
    }
    
    fclose(novoArqCSV);
    
    for (int i=0; i<=no.qtd; i++)
    {   vacuum(no.filhos[i], arquivo, novo);
    }
}
/* VACUUM VACUUM VACUUM */

int indexar()
{
    FILE *arquivo;
    if ((arquivo = fopen("arq.csv", "rt")) == NULL)
    {   printf("ERROR: O arquivo não existe!\n");
        return 0;
    }

    char linha[85];
    int codigo, posicaoCursor;

    inicializaNo();
    posicaoCursor = (int) ftell(arquivo);
    while ((fgets(linha, 85, arquivo)) != NULL)
    {   sscanf(linha, "%d", &codigo);
        FILE *indice = fopen("indice.ind", "r+");
        int endRaiz;
        
        if (indice == NULL)
        {   indice = fopen("indice.ind", "w+");
            endRaiz = CONTROLE;
            fwrite(&endRaiz, sizeof(int), 1, indice);
        }
        else
        {   //Atualiza Raiz da Arv p endRaiz
            fread(&endRaiz, sizeof(int), 1, indice);
        }

        fclose(indice);
        inicializar(pilha);
        indexa(codigo, posicaoCursor, endRaiz);
        posicaoCursor = (int) ftell(arquivo);
    }
    fclose(arquivo);
    printf("\nArquivo Indexado com Sucesso!\nConsulte o novo Aquivo ('indice.ind').\n");
}

int procurar(FILE *arquivo)
{
    FILE *indice;
    if ((arquivo == NULL))
    {   printf("o arquivo especificado não existe\n");
        return 0;
    } else if ((indice = fopen("indice.ind", "r+")) == NULL)
    {   printf("o arquivo indice não existe\n");
        return 0;
    }

    int endereco;
    //Posiciona no Inicio
    fseek(indice, 0, SEEK_SET);
    //Le a Raiz
    fread(&endereco, sizeof(int), 1, indice);
    fclose(indice);
    
    int codigo;
    printf("\nBuscar Codigo: ");
    scanf("%d", &codigo);
    
    inicializaNo();
    char linha[1001];
    
    int posicao = procura(codigo, endereco);
    if (posicao < 0) printf("Codigo não foi encontrado\n");
    else
    {   //Posiciona
        fseek(arquivo, posicao, SEEK_SET);
        //Le a linha 
        fgets(linha, 1000, arquivo);
        printf("%s", linha);
    }
    fclose(arquivo);
}

int editar()
{   
    FILE *arquivo, *index;
    if ((arquivo = fopen("arq.csv", "r+")) == NULL)
    {   printf("ERROR: O Arquivo não existe!\n");
        return 0;
    } 
    if ((index = fopen("indice.ind", "r+")) == NULL)
    {   printf("ERROR: O arquivo não existe!\n");
        return 0;
    }
    
    int endereco, codigo, posicao;
    fseek(index, 0, SEEK_SET);
    fread(&endereco, sizeof(int), 1, index);
    
    printf("\nBuscar Codigo: ");
    scanf("%d", &codigo);
    
    inicializaNo();
    
    
    posicao = procuraEdita(codigo, endereco);
    if (posicao < 0) printf("ERROR: Codigo não encontrado!\n");
    else
    {   int i;
        //%[^\n]s
        printf("Entre com o Nome:\n");
        
        char novaLinha[85] = "", nome[50], sexo[2], dataNasc[10], sal[14], cod[7];
        sprintf(cod, "%d", codigo);
        for (i=0; no.codigos[i]!=codigo; i++);
        printf("Editando Pessoa:\n");
        
        strcat(novaLinha, cod);
        strcat(novaLinha, ";");
        printf("Digite o novo Nome:\n");
        scanf("%s", nome);
        strcat(novaLinha, nome);
        strcat(novaLinha, ";");
        printf("Digite o novo Sexo:\n");
        scanf("%s", sexo);
        strcat(novaLinha, sexo);
        strcat(novaLinha, ";");
        printf("Digite a nova data de Nascimento:\n");
        scanf("%s", dataNasc);
        strcat(novaLinha, dataNasc);
        strcat(novaLinha, ";");
        printf("Digite o novo Salario:\n");
        scanf("%s", sal);
        strcat(novaLinha, sal);
        strcat(novaLinha, "\n");
        fseek(arquivo, 0, SEEK_END);
        int novoEndereco = ftell(arquivo);
        fwrite(novaLinha, sizeof(char), strlen(novaLinha), arquivo);
        
        no.posicoes[i] = novoEndereco;
        fseek(index, posicao, SEEK_SET);
        fwrite(&no, sizeof(struct nob), 1, index);
        printf("\nEditado com Sucesso!\n\n");

    }
    fclose(index);
    fclose(arquivo);
}

int apagar()
{
    FILE *indice;
    if ((indice = fopen("indice.ind", "r")) == NULL)
    {   printf("ERROR: O arquivo não existe!\n");
        return 0;
    }
    int endereco, codigo;
    fseek(indice, 0, SEEK_SET);
    fread(&endereco, sizeof(int), 1, indice);
    fclose(indice);
    
    printf("\nApagar Pessoa\n\n");
    printf("Entre com o Codigo: ");
    scanf("%d", &codigo);
    
    inicializaNo();
    apagar(codigo, endereco);
    printf("\nApagado com Sucesso!\n\n");
}

int fazVacuum(char arq[])
{   
    FILE *arquivo, *indice, *novoArqCSV;
    if ((arquivo = fopen("arq.csv", "r+")) == NULL)
    {   printf("ERROR: O Arquivo não existe!\n");
        return 0;
    } 
    if ((indice = fopen("indice.ind", "r+")) == NULL)
    {   printf("ERROR: O Arquivo não existe!\n");
        return 0;
    }

    novoArqCSV = fopen(arq, "w");
    
    int endereco;
    fseek(indice, 0, SEEK_SET);
    fread(&endereco, sizeof(int), 1, indice);
    
    fclose(novoArqCSV);
    fclose(indice);
    vacuum(endereco, arquivo,arq);
    fclose(arquivo);
    printf("\nVacuum gerado com Sucesso!\nConsulte o novo Aquivo ('arqVacuum.csv').\n\n");
    fflush (arquivo);
    rename("arq2.csv", "arq.csv");
}



int main()
{   

    FILE *arquivo = fopen("arq.csv", "r+");

    int o;
    do
    {   printf("1)Indexa 2)Busca 3)Edita 4)Apaga 5)Vacuum  0)sai: ");
        scanf("%d",&o);
        switch (o)
        {   case 1: indexar();
                    break;
            case 2: procurar(arquivo);
                    break;
            case 3: editar();
                    break;
            case 4: apagar();
                    break;
            case 5: char arq[20] = "arq2.csv";
                    
                    fazVacuum(arq);
                    //delete("indice.ind");
                    indexar();
                    break;
        }
    }
    while (o);

    

}