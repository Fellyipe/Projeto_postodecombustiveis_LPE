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
#define IAM "\e[0;93m"
#define IAZ "\e[0;94m"
#define IMG "\e[0;95m"
#define ICN "\e[0;96m"
//Negrito e intenso
#define NIVM "\e[1;91m"
#define NIVD "\e[1;92m"

void enter(){
    printf(SVD "\nAperte Enter para continuar\n" RESET);
    getchar();
}

void limpaBuffer(){
    while ((getchar()) != '\n');
}

int apenasNum(float scan, float *valor){
    int valido = 0;
    
    if(scan==1){
        if(*valor < 0){
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

int validoAbastecer(float litrosRest, int fila){
    int valido = 1;
    if(litrosRest==0){
        printf(RESET NVM "Não há gasolina restante!\n");
        return valido = 0;
    }
    if(litrosRest >= 100)
        printf(NIVD "Quantidade de litros restante: %.2f\n",litrosRest);
    else if(litrosRest >= 50)
        printf(NAM "Quantidade de litros restante: %.2f\n",litrosRest);
    else if(litrosRest >= 10)
        printf(NVM "Quantidade de litros restante: %.2f\n",litrosRest);
    else if(litrosRest > 0){
        printf(NIVM "Quantidade de litros restante: %.2f\n"
        "ATENÇÃO! - Há menos de 10 litros de gasolina restantes!"
        "\nEsvaziar a bomba poderá danificá-la, quer prosseguir?"
        "\nSe sim, digite 1, se não, digite qualquer coisa\n",litrosRest);
        if(scanf("%d",&valido)!=1)
            valido = 0;
    }
    if(fila==0){
        printf(NVM "\nNão há nenhuma carro na fila!\n");
        valido = 0;
    }
    return valido;
}

void exibeCar(int *fila){
    printf(IMG "Quantidade de carros na fila: %d\n",*fila);
    if(*fila==0)
        printf("Não há nenhum carro na fila\n");
    else if(*fila==1)
        printf("Este é carro contido na fila de espera\n");
    else
        printf("Estes são os carros contidos na fila de espera\n");
}

void addCar(int *fila, int max){
    if(*fila < max){
        printf(RESET NAZ "Carro adicionado à fila\n");
        *fila+=1;
    }else{
        printf(NVM "Máximo de carros atingido!\n");
    }
    printf("Quantidade de carros na fila: %d\n",*fila);
}

int arquivo(int quant, char relatorio[400]){
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
    return gerente;
}

float definirPreco(){
    int valido;
    float preco;
    do{
        preco = 1;
        system("clear");
        printf(ICN "Informe o preço da gasolina\n" 
        SCN "Utilize ponto (.) ao invés de vírgula (,) para decimais\n" RESET);
        valido = apenasNum(scanf("%f",&preco),&preco);
        if(preco==0){
            printf(IMG "Gasolina gratuita?\n"
            SMG "Se sim, digite 1, se não, digite qualquer coisa\n" RESET);
            if(scanf("%d",&valido)!=1)
                valido = 0;
        }
        limpaBuffer();
        enter();
    }while(valido!=1);
    
    return preco;
}

int definirFila(){
    int maxCar,valido;
    float copia;
    do{
        maxCar = 1;
        system("clear");
        printf(ICN "Informe a quantidade máxima de carros que o posto suportará\n" RESET);
        valido = scanf("%d",&maxCar);
        copia = maxCar;
        valido = apenasNum(valido,&copia);
        if(maxCar==0){
            printf(NVM "Tem certeza?\nÉ inútil para um posto não suportar nenhum veículo\n"
            SVM "Se sim, digite 1, se não, digite qualquer coisa\n" RESET);
            if(scanf("%d",&valido)!=1)
                valido = 0;
        }
        limpaBuffer();
        enter();
    }while(valido!=1);
    
    return maxCar;
}

int despache(int fila){
    int quant,valido;
    float copia;
    printf("Digite 0 para despachar todos os carros"
    "\nOu então, digite o número da posição do carro na fila que será despachado: ");
    valido = scanf("%d",&quant);
    copia = quant;
    valido = apenasNum(valido,&copia);
    if(valido==1){
        if(quant==0){
            fila = 0;
        }else{
            fila--;
        }
    }
    limpaBuffer();
    return fila;
}

float compra(float total){
    int valido;
    float preco;
    
    system("clear");
    printf(IMG "Informe o preço do produto\n" RESET);
    valido = apenasNum(scanf("%f",&preco),&preco);
        if(valido==1){
            total += preco;
        }
        limpaBuffer();
    return total;
}

int main(int argc, char** argv){
    
    int maxCar,oper,operRA,carAten=0,carFila=0,valido=0,contArq=0;
    float preco,lit,litRest=200,litVend=0,vendGas=0,vendLoja=0,copia;
    char relatorio[400],gerente[30];
    
    setlocale(LC_ALL,NULL);
    
    printf(NIVD "////////////////////////////////////////////////////////////////"
    "\n                       Posto de Gasolina                             "
    "\nAutor: Felipe Bueno\n"
    "\nEste programa serve como uma ferramenta para administrar um"
    "\nposto de gasolina\n"
    "////////////////////////////////////////////////////////////////\n" RESET);
    enter();
    
    system("clear");
    printf(ICN "Nome do gerente: ");
    fgets(gerente,30,stdin);
	enter();
	
	preco = definirPreco();
    maxCar = definirFila();
    
    system("clear");
    setbuf(stdin,NULL);
    printf(NAM "Preço da gasolina: %.2f\n"
    "Quantidade máxima de carros na fila: %d\n"
    "Gerente: %s",preco,maxCar,gerente);
    enter();
    setbuf(stdin,NULL);
    
    do{
        system("clear");
        printf(RESET AMB "\tMENU DE OPERAÇÕES" IAZ
        "\n1 - Adicionar um carro na fila"
        "\n2 - Abastecer"
        "\n3 - Exibir carros na fila de espera"
        "\n4 - Exibir relatórios"
        "\n5 - Opções avançadas"
        "\n6 - Encerrar programa");
        setbuf(stdin,NULL);
        printf(NAZ "\nEscolha uma operação: ");
        valido = scanf("%d",&oper);
        setbuf(stdin,NULL);
        system("clear");
        switch(oper){
            case 1:
                if(litRest==0){
                    printf(NVM "Não está permitido adicionar carros na fila\n");
                    enter();
                    break;
                }
                addCar(&carFila, maxCar);
                enter();
                break;
            case 2:
                valido = validoAbastecer(litRest,carFila);
                if(valido!=1){
                    enter();
                    break;
                }
                printf(NAZ "Quantidade de litros: ");
                valido = apenasNum(scanf("%f",&lit),&lit);
                if(valido==1){
                    if(lit<=litRest){
                        litRest -= lit;
                        litVend += lit;
                        vendGas += preco*lit;
                        carAten++;
                        carFila--;
                        printf(ICN "\nValor total = %.2f R$ (%.2f R$ por litro)\n",preco*lit,preco);
                        setbuf(stdin,NULL);
                        }else{
                            printf(NVM "\nNão há gasolina suficiente!");
                        }
                }
                if(litRest==0){
                    printf(NVM "\nA gasolina acabou!"
                    "\nTodos os veículos serão despachados!");
                    carFila = 0;
                }
                setbuf(stdin,NULL);
                enter();
                break;
            case 3:
                exibeCar(&carFila);
                enter();
                break;
            case 4:
                do{ 
                    system("clear");
                    snprintf(relatorio,400,"Quantidade de gasolina vendida: %.2fL\n"
                        "Valor arrecadado pela venda de gasolina: %.2f R$\n"
                        "Valor arrecadado pelas vendas da loja de conveniência: %.2f R$\n"
                        "Valor total arrecadado: %.2f R$\n"
                        "Quantidade de carros atendidos: %d\n"
                        "Quantidade de gasolina restante: %.2fL\n"
                        "Gerente: %s",litVend,vendGas,vendLoja,vendGas+vendLoja,carAten,litRest,gerente);
                    printf(RESET VDB "\tMENU DE RELATÓRIOS\t" IAM
                    "\n1 - Quantidade de litros vendida"
                    "\n2 - Valor arrecadado pela venda de gasolina"
                    "\n3 - Valor arrecadado pelas vendas da loja de conveniência"
                    "\n4 - Valor total arrecadado com as vendas"
                    "\n5 - Quantidade de carros atendidos"
                    "\n6 - Quantidade de combustível restante no tanque"
                    "\n7 - Relatório completo"
                    "\n8 - Criar arquivo do relatório completo"
                    "\n9 - Sair");
                    printf(NAM "\nEscolha uma opção: ");
                    valido = scanf("%d",&operRA);
                    system("clear");
                    setbuf(stdin,NULL);
                    switch(operRA){
                        case 1:
                            printf("Quantidade de gasolina vendida: %.2fL\n",litVend);
                            enter();
                            break;
                        case 2:
                            printf("Valor arrecadado pela venda de gasolina: %.2f R$\n",vendGas);
                            enter();
                            break;
                        case 3:
                            printf("Valor arrecadado pelas vendas da loja de conveniência: %.2f R$\n",vendLoja);
                            enter();
                            break;
                        case 4:
                            printf("Valor total arrecadado: %.2f R$\n",vendGas+vendLoja);
                            enter();
                            break;
                        case 5:
                            printf("Quantidade de carros atendidos: %d\n",carAten);
                            enter();
                            break;
                        case 6:
                            printf("Quantidade de gasolina restante: %.2fL\n",litRest);
                            enter();
                            break;
                        case 7:
                            printf("%s",relatorio);
                            enter();
                            break;
                        case 8:
                            printf(NAZ "Um arquivo .txt será criado com as informações\n"
                            "do relatório completo e salvo automaticamente.\n"
                            "\nOBS: os arquivos apenas serão criados ao fim da execução do programa\n"
                            "Prosseguir? Se sim, digite 1, se não, digite qualquer coisa\n");
                            if(scanf("%d",&valido)!=1){
                                valido = 0;
                            }
                            if(valido==1){
                                contArq = arquivo(contArq,relatorio);
                            }
                            limpaBuffer();
                            break;
                        case 9:
                            break;
                        default:
                            if(valido != 1)
                                limpaBuffer();
                            printf(NVM "Opção inválida\n");
                            enter();
                    }
                }while(operRA!=9);
                break;
            case 5:
                do{
                    system("clear");
                    printf(RESET VDB "\tOPÇÕES AVANÇADAS\t" IAM
                    "\n1 - Reabastecer reservatório de gasolina"
                    "\n2 - Alterar gerente"
                    "\n3 - Alterar preço da gasolina"
                    "\n4 - Alterar quantidade máxima de carros na fila"
                    "\n5 - Despachar carros"
                    "\n6 - Gegistrar compra na loja de conveniência"
                    "\n7 - Sair");
                    printf(NAM "\nEscolha uma opção: ");
                    valido = scanf("%d",&operRA);
                    setbuf(stdin,NULL);
                    system("clear");
                    
                    switch(operRA){
                        case 1:
                            if(carFila!=0){
                                printf(NVM "É necessário despachar todos os carros antes de reabastecer o reservatório");
                            }else if(litRest>=50){
                                printf(NVM "O nível do reservatório deve estar abaixo de 50 litros para reabastecer");
                            }else{
                                litRest = 200;
                                printf(NAZ "Reservatório totalmente reabastecido\n");
                            }
                            enter();
                            break;
                        case 2:
                            definirGerente(gerente);
                            enter();
                            break;
                        case 3:
                            if(carFila!=0){
                                printf(NVM "É necessário despachar todos os carros antes de alterar o preço\n");
                                enter();
                            }else{
                            preco = definirPreco();
                            }
                            break;
                        case 4:
                            if(carFila!=0){
                                printf(NVM "É necessário despachar todos os carros antes de alterar o tamanho máximo da fila\n");
                                enter();
                            }else{
                            maxCar = definirFila();
                            }
                            break;
                        case 5:
                            carFila = despache(carFila);
                            enter();
                            break;
                        case 6:
                            vendLoja = compra(vendLoja);
                            enter();
                            break;
                        case 7:
                            break;
                        default:
                            if(valido != 1)
                                limpaBuffer();
                            printf(NVM "Opção inválida\n");
                            enter();
                    }
                }while(operRA!=7);
                break;
            case 6:
                if(contArq==0){
                    printf("Nenhum arquivo de relatório foi expedido\n"
                    "Deseja criar um antes de sair do programa?\n"
                    "Se sim, digite 1, se não, digite qualquer coisa\n");
                    if(scanf("%d",&valido)!=1)
                        valido = 0;
                    limpaBuffer();
                    if(valido==1){
                        snprintf(relatorio,400,"Quantidade de gasolina vendida: %.2fL\n"
                        "Valor arrecadado pela venda de gasolina: %.2f R$\n"
                        "Valor arrecadado pelas vendas da loja de conveniência: %.2f R$\n"
                        "Valor total arrecadado: %.2f R$\n"
                        "Quantidade de carros atendidos: %d\n"
                        "Quantidade de gasolina restante: %.2fL\n"
                        "Gerente: %s",litVend,vendGas,vendLoja,vendGas+vendLoja,carAten,litRest,gerente);
                        contArq = arquivo(contArq,relatorio);
                    }
                }
                system("clear");
                printf(NIVD "Programa encerrado");
                break;
            default:
                if(valido != 1)
                    limpaBuffer();
                setbuf(stdin,NULL);
                printf(NVM "Operação inválida!\n");
                enter();
        }
    }while(oper!=6);
    return 0;
}
