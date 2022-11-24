#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

#define RESET "\e[0m"
//Negrito
#define NVM "\e[1;31m"
#define NAM "\e[1;33m"
#define NAZ "\e[1;34m"
//Sublinhado
#define SVM "\e[4;31m"
#define SVD "\e[4;32m"
#define SMG "\e[4;35m"
#define SCN "\e[4;36m"
//Background
#define VMB "\e[41m"
#define VDB "\e[42m"
#define AMB "\e[43m"
//Intenso
#define IVD "\e[0;92m"
#define IAM "\e[0;93m"
#define IAZ "\e[0;94m"
#define IMG "\e[0;95m"
#define ICN "\e[0;96m"

//Negrito e intenso
#define NIVM "\e[1;91m"
#define NIVD "\e[1;92m"

struct TVeiculo{
    char cor[15];
    char modelo[30];
    char especificacao[50];
    char tipo[30];
    int combustivel;
    int ano;
};

struct TVenda{
    float quantidade;
    float total;
    float preco;
    int combustivel;
};

void addVeiculo(struct TVeiculo *Veiculo, int combustivel);

int apenasNum(float scan, float valor);

int arquivo(int quant, char relatorio[400]);

const char* definirGerente(char gerente[30]);

float compra(float total);

void enter();

int definirFila(int fila);

float definirPreco(int combustivel);

int despache(int fila);

void limpaBuffer();

void nivelDoCombustivel(float litrosRestantes, int combustivel);

void opcaoInvalida(int valido);

int reabastecerReservatorio(int combustivel, float quantidadeCombustivel,int tamanhoFila, int fila);

int retornaFila(int combustivel);