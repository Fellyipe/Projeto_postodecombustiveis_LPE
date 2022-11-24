#include"header.h"

void addVeiculo(struct TVeiculo *Veiculo, int combustivel){
    int valido=0;
    float copia;
    
    Veiculo->combustivel = combustivel;
    printf("Informe o tipo do veículo\n");
    fgets(Veiculo->tipo,30,stdin);
    Veiculo->tipo[strcspn(Veiculo->tipo,"\n")] = 0;
    printf("Outras informações sobre o veiculo do cliente (digite 0 caso a informação seja desconhecida)\n");
    do{
        printf(IMG "Digite o ano: ");
        valido = scanf("%d",&Veiculo->ano);
        copia = Veiculo->ano;
        valido = apenasNum(valido,copia);
        limpaBuffer();
    }while(valido!=1);
    printf("Digite a cor: ");
    fgets(Veiculo->cor,15,stdin);
    Veiculo->cor[strcspn(Veiculo->cor,"\n")] = 0;
    printf("Digite o modelo: ");
    fgets(Veiculo->modelo,30,stdin);
    Veiculo->modelo[strcspn(Veiculo->modelo,"\n")] = 0;
    printf("Informe se há alguma especificação a mais\n");
    fgets(Veiculo->especificacao,50,stdin);
    Veiculo->especificacao[strcspn(Veiculo->especificacao,"\n")] = 0;
    system("clear");
    printf(IVD "Carro adicionado!\n");
}

int apenasNum(float scan, float valor){
    int valido = 0;

    if(scan==1){
        if(valor < 0){
            printf(NVM "Apenas valores positivos!\n");
        }else{
            valido = 1;
        }
    }else{
        printf(NVM "Digite apenas números!\n");
        limpaBuffer();
    }

    return valido;
}

int arquivo(int quant, char relatorio[1500]){
    FILE *arq;
    char nome[15];
    quant++;
    
    system("clear");
    sprintf(nome,"arquivo%d.txt",quant);
    printf("Esse será o nome do arquivo: %s\n",nome);
    enter();
    
    arq = fopen(nome, "w");
    fputs(relatorio,arq);
    fclose(arq);
    
    return quant;
}

const char* definirGerente(char gerente[30]){
    printf("Gerente atual: %s\n"
    "Novo gerente: ",gerente);
    fgets(gerente,30,stdin);
    gerente[strcspn(gerente,"\n")] = 0;
    return gerente;
}

float compra(float total){
    int valido;
    float preco;
    
    system("clear");
    printf(IMG "Informe o preço do produto\n" RESET);
    valido = scanf("%f",&preco);
    setbuf(stdin,NULL);
    valido = apenasNum(valido,preco);
    if(valido==1){
        total += preco;
        printf(IVD "Compra no valor de %.2fR$ registrada\n",total);
    }
    return total;
}

int definirFila(int fila){
    int tamanhoFila,valido;
    float copia;

    do{
        if(fila == 1)
            printf(ICN "Fila 1 - gasolina (comum ou aditivada) e etanol: ");
        else if(fila == 2)
            printf(ICN "Fila 2 - diesel (comum ou S10): ");
        else if(fila == 3)
            printf(ICN "Fila 3 - carregador elétrico: ");
        valido = scanf("%d",&tamanhoFila);
        if(valido!=1){
            tamanhoFila = 0;
        }
        copia = tamanhoFila;
        valido = apenasNum(valido,copia);
        limpaBuffer();
    }while(valido!=1);
    
    return tamanhoFila;
}

float definirPreco(int combustivel){
    int valido;
    float preco;
    char mensagem[6][35] = {"da Gasolina Comum","da Gasolina Aditivada",
        "do Etanol","do Diesel Comum",
        "do Diesel S10","da Eletricidade (preço por KWh)"
    };
    do{
        printf(ICN "Informe o preço %s\n",mensagem[combustivel]);
        printf(SCN "Utilize ponto (.) ao invés de vírgula (,) para decimais\n" RESET);
        valido = scanf("%f",&preco);
        if(valido!=1){
            preco = 0;
        }
        valido = apenasNum(valido,preco);
        limpaBuffer();
    }while(valido!=1);
    
    return preco;
}

int despache(int fila){
    int quant,valido;
    float copia;
    printf("Digite 0 para despachar todos os veículos"
    "\nOu então, digite o número da posição do veículo na fila que será despachado: ");
    valido = scanf("%d",&quant);
    copia = quant;
    valido = apenasNum(valido,copia);
    if(valido==1){
        if(quant>fila){
            printf("Não há nenhum veículo nessa posição");
        }else{
            return quant;
        }
    }
    limpaBuffer();
    return -1;
}

void enter(){
    printf(SVD "\nAperte Enter para continuar\n" RESET);
    getchar();
}

void limpaBuffer(){
    while ((getchar()) != '\n');
}

void nivelDoCombustivel(float litrosRestantes, int combustivel){
    char comb[5][20] = {"gasolina comum","gasolina aditivada","etanol","diesel comum","diesel S10"};
    
    if(combustivel<4){
        if(litrosRestantes >= 100)
            printf(NIVD "Quantidade de litros de %s restantes: %.2f\n",comb[combustivel],litrosRestantes);
        else if(litrosRestantes >= 50)
            printf(NAM "Quantidade de litros de %s restantes: %.2f\n",comb[combustivel],litrosRestantes);
        else if(litrosRestantes >= 10)
            printf(NVM "Quantidade de litros de %s restantes: %.2f\n",comb[combustivel],litrosRestantes);
        else{
            printf(NIVM "Quantidade de litros restantes: %.2f\n"
            "ATENÇÃO! - Há menos de 10 litros de %s restantes!\n"
            "Esvaziar a bomba poderá danificá-la.\n"
            "É necessário reabastecer o tanque de %s.",litrosRestantes,comb[combustivel],comb[combustivel]);
        }
    }else{
        if(litrosRestantes >= 300)
            printf(NIVD "Quantidade de litros de %s restantes: %.2f\n",comb[combustivel],litrosRestantes);
        else if(litrosRestantes >= 150)
            printf(NAM "Quantidade de litros de %s restantes: %.2f\n",comb[combustivel],litrosRestantes);
        else if(litrosRestantes >= 30)
            printf(NVM "Quantidade de litros de %s restantes: %.2f\n",comb[combustivel],litrosRestantes);
        else{
            printf(NIVM "Quantidade de litros restantes: %.2f\n"
            "ATENÇÃO! - Há menos de 30 litros de %s restantes!\n"
            "Esvaziar a bomba poderá danificá-la.\n"
            "É necessário reabastecer o tanque de %s.",litrosRestantes,comb[combustivel],comb[combustivel]);
        }
    }
}

void opcaoInvalida(int valido){
    if(valido!=1)
        limpaBuffer();
    printf(NVM "Opção inválida!");
}

int reabastecerReservatorio(int combustivel, float quantidadeCombustivel,int tamanhoFila, int fila){
    float capacidadeMaxima[5] = {200,200,200,600,600};
    char comb[5][20] = {"gasolina comum","gasolina aditivada","etanol","diesel comum","diesel S10"};
    int valido = 1;
    
    if(quantidadeCombustivel >= (capacidadeMaxima[combustivel] * 0.25)){
        printf(NVM "O reservatório de %s deve estar abaixo de %.2f para ser reabastecido\n",comb[combustivel],capacidadeMaxima[combustivel]*0.25);
        valido = 0;
    }
    if(tamanhoFila!=0){
        printf(NVM "Não deve haver nenhum carro na fila %d para reabastecer o reservatório de %s",fila,comb[combustivel]);
        valido = 0;
    }
    if(valido==1){
        quantidadeCombustivel = capacidadeMaxima[combustivel];
        printf(NIVD "Reservatório reabastecido");
    }
    return quantidadeCombustivel;
}

int retornaFila(int combustivel){
    if(combustivel<=3)
        return 1;
    if(combustivel<=5)
        return 2;
    else
        return 3;
}

