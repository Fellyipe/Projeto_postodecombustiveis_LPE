#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<stdbool.h>

#define RESET "\e[0m"
//Normal
#define VM "\e[0;31m"
#define AM "\e[0;33m"
#define AZ "\e[34m"
//Negrito
#define NVM "\e[1;31m"
#define NVD "\e[1;32m"
#define NAM "\e[1;33m"
#define NAZ "\e[1;34m"
#define NCN "\e[1;36m"
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
#define HVM "\e[0;91m"
#define IAM "\e[0;93m"
#define IAZ "\e[0;94m"
#define IMG "\e[0;95m"
#define ICN "\e[0;96m"
//Negrito e intenso
#define NIVM "\e[1;91m"
#define NIVD "\e[1;92m"
#define BIAM "\e[1;93m"
#define BIAZ "\e[1;94m"
#define BIMG "\e[1;95m"
#define BICN "\e[1;96m"

int main(void){
    
    int maxcar,oper,operre,caraten=0,carfila=0,valido;
    float preco,lit,litrest=200,vendtotal=0;
    char enter[50] = SVD "\nAperte Enter para continuar\n" RESET;
    
    setlocale(LC_ALL,NULL);
    
    printf(NIVD "////////////////////////////////////////////////////////////////"
    "\n                       Posto de Gasolina                             "
    "\nAutor: Felipe Bueno\n"
    "\nEste programa serve como uma ferramenta para administrar um"
    "\nposto de gasolina\n"
    "////////////////////////////////////////////////////////////////\n" RESET);
    printf("%s",enter);

    getchar();
    setbuf(stdin,NULL);

    while(true){
        system("clear");
        printf(ICN "Informe o preço da gasolina\n" 
        SCN "Utilize ponto (.) ao invés de vírgula (,) para decimais\n" RESET);
        if(scanf("%f",&preco)==1){
            setbuf(stdin,NULL);
            if(preco < 0){
                printf(NVM "Apenas valores positivos!\n");
            }else if(preco == 0){
                printf(IMG "Gasolina gratuita?\n"
                SMG "Se sim, digite 0, se não, digite qualquer coisa\n" RESET);
                scanf("%d",&valido);
                if(valido==0){
                    break;
                }
            }else{
                break;
            }
        }else{
            printf(NVM "Digite apenas números!\n");
            preco = 0;
            while ((getchar()) != '\n');
        }
        printf("%s",enter);
        getchar();
    }
    while(true){
        system("clear");
        printf(ICN "Informe a quantidade máxima de carros que o posto suportará\n" RESET);
        if(scanf("%d",&maxcar)==1){
            if(maxcar < 0){
                printf(NVM "Apenas valores positivos!\n");
                getchar();
            }else if(maxcar == 0){
                printf(VM "Tem certeza?\nÉ um inútil para um posto não suportar nenhum veículo\n"
                SVM "Se sim, digite 0, se não, digite qualquer coisa\n" RESET);
                scanf("%d",&valido);
                if(valido==0){
                    break;
                }
            }else{
                break;
            }
        }else{
            printf(NVM "Digite apenas números!\n");
            maxcar = 0;
            while((getchar()) != '\n');
        }
        printf("%s",enter);
        getchar();
    }
    
    system("clear");
    setbuf(stdin,NULL);
    printf(NAM "Preço da gasolina: %.2f\n",preco);
    printf("Quantidade máxima de carros na fila: %d\n",maxcar);
    printf("%s",enter);
    getchar();
    setbuf(stdin,NULL);
    
    do{
        system("clear");
        printf(RESET AMB "\tMENU DE OPERAÇÕES" IAZ
        "\n1 - Adicionar um carro na fila"
        "\n2 - Abastecer"
        "\n3 - Exibir carros na fila de espera"
        "\n4 - Exibir relatórios"
        "\n5 - Encerrar programa");
        setbuf(stdin,NULL);
        printf(AZ "\nEscolha uma operação: ");
        valido = scanf("%d",&oper);
        setbuf(stdin,NULL);
        system("clear");
        switch(oper){
            case 1:
                if(carfila < maxcar){
                    printf(RESET NAZ "Carro adicionado à fila\n");
                    carfila++;
                }else{
                    printf(NVM "Máximo de carros atingido!\n");
                }
                printf("Quantidade de carros na fila: %d\n",carfila);
                printf("%s",enter);
                getchar();
                break;
            case 2:
                if(litrest == 0){
                    printf(RESET NVM "Não há gasolina restante!\n");
                    printf("%s",enter);
                    getchar();
                    break;
                }else if(carfila == 0){
                    printf(NVM "Não há nenhuma carro na fila!\n");
                    printf("%s",enter);
                    getchar();
                    break;
                }else{
                    if(litrest >= 100)
                        printf(NVD "Quantidade de litros restante: %.2f\n",litrest);
                    else if(litrest >= 50)
                        printf(NAM "Quantidade de litros restante: %.2f\n",litrest);
                    else if(litrest >= 10)
                        printf(NVM "Quantidade de litros restante: %.2f\n",litrest);
                    else if(litrest > 0){
                        printf(NIVM "ATENÇÃO! - Há menos de 10 litros de gasolina restantes!"
                        "\nEsvaziar a bomba poderá danificá-la, quer prosseguir?"
                        "\nSe sim, digite 0, se não, digite qualquer coisa\n");
                        scanf("%d",&valido);
                        if(valido != 0)
                            break;
                    }
                    printf(NAZ "Quantidade de litros: ");
                    if(scanf("%f",&lit)==1){
                        if(lit < 0){
                            printf(NVM "Apenas valores positivos!\n");
                        }else if(lit<=litrest){
                            litrest -= lit;
                            vendtotal += preco*lit;
                            caraten++;
                            carfila--;
                            printf(NCN "\nValor total = %.2f R$ (%.2f R$ por litro)\n",preco*lit,preco);
                            setbuf(stdin,NULL);
                            }else{
                                printf(NVM "Não há gasolina suficiente!\n");
                            }
                    }else{
                        printf(NVM "Digite apenas números!\n");
                        lit = 0;
                        while ((getchar()) != '\n');
                    }
                }
                setbuf(stdin,NULL);
                printf("%s",enter);
                getchar();
                break;
            case 3:
                printf(IMG "Quantidade de carros na fila: %d\n",carfila);
                if(carfila==0)
                    printf("Não há nenhum carro na fila\n");
                else if(carfila==1)
                    printf("Este é carro contido na fila de espera\n");
                else
                    printf("Estes são os carros contidos na fila de espera\n");
                printf("%s",enter);
                getchar();
                break;
            case 4:
                do{ 
                    system("clear");
                    printf(RESET VDB "\tMENU DE RELATÓRIOS\t" IAM
                    "\n1 - Quantidade de litros vendida"
                    "\n2 - Valor total arrecadado com as vendas"
                    "\n3 - Quantidade de carros atendidos"
                    "\n4 - Quantidade de combustível restante no tanque"
                    "\n5 - Relatório completo"
                    "\n6 - Sair");
                    printf(AM "\nEscolha uma opção: ");
                    valido = scanf("%d",&operre);
                    system("clear");
                    setbuf(stdin,NULL);
                    switch(operre){
                        case 1:
                            printf("Quantidade de gasolina vendida: %.2fL\n",200-litrest);
                            printf("%s",enter);
                            getchar();
                            break;
                        case 2:
                            printf("Valor total arrecadado: %.2f R$\n",vendtotal);
                            printf("%s",enter);
                            getchar();
                            break;
                        case 3:
                            printf("Quantidade de carros atendidos: %d\n",caraten);
                            printf("%s",enter);
                            getchar();
                            break;
                        case 4:
                            printf("Quantidade de gasolina restante: %.2fL\n",litrest);
                            printf("%s",enter);
                            getchar();
                            break;
                        case 5:
                            printf("Quantidade de gasolina vendida: %.2fL\n"
                            "Valor total arrecadado: %.2f R$\n"
                            "Quantidade de carros atendidos: %d\n"
                            "Quantidade de gasolina restante: %.2fL\n",200-litrest,vendtotal,caraten,litrest);
                            printf("%s",enter);
                            getchar();
                            break;
                        case 6:
                            break;
                        default:
                            if(valido != 1)
                                while((getchar()) != '\n');
                            printf(NVM "Opção inválida\n");
                            printf("%s",enter);
                            getchar();
                    }
                }while(operre!=6);
                break;
            case 5:
                printf(NIVD "Programa encerrado");
                break;
            default:
                if(valido != 1)
                    while((getchar()) != '\n');
                printf(NVM "Operação inválida!\n");
                printf("%s",enter);
                getchar();
        }
    }while(oper != 5);
    return 0;
}    
