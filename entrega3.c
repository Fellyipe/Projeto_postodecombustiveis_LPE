#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

int main(){
    
    int maxcar,oper,operre,caraten=0;
    float preco,lit,litotal=0,vendtotal=0;
    
    setlocale(LC_ALL,NULL);
    
    printf("////////////////////////////////////////"
    "\n           Posto de Gasolina           "
    "\nAutor: Felipe Bueno\n"
    "                                        \n"
    "Este programa serve como uma ferramenta\n"
    "para administrar um posto de gasolina\n"
    "////////////////////////////////////////\n");

    printf("\nInforme o preço da gasolina\n");
    scanf("%f",&preco);
    if(preco < 0){
        printf("Apenas valores positivos!\n");
    }
    printf("Informe a quantidade máxima de carros que o posto suportará\n");
    scanf("%d",&maxcar);
    if(preco < 0){
        printf("Apenas valores positivos!\n");
    }
    
    printf("MENU DE OPERAÇÕES"
    "\n1 - Adicionar um carro na fila"
    "\n2 - Abastecer"
    "\n3 - Exibir carros nas fila de espera"
    "\n4 - Exibir relatórios"
    "\n5 - Encerrar programa");
    
        do{
            printf("\nEscolha uma operação: ");
            scanf("%d",&oper);
            switch(oper){
                case 1:
                    printf("Carro adicionado à fila");
                    break;
                case 2:
                    printf("Quantidade de litros: ");
                    scanf("%f",&lit);
                    litotal += lit;
                    vendtotal += preco*lit;
                    caraten++;
                    printf("Valor total = %.2f R$ (%.2f R$ por litro)",preco*lit,preco);
                    break;
                case 3:
                    printf("Estes são os carros contidos na fila de espera");
                    break;
                case 4:
                    printf("MENU DE RELATÓRIOS"
                    "\n1 - Quantidade de litros vendida"
                    "\n2 - Valor total arrecadado com as vendas"
                    "\n3 - Quantidade de carros atendidos"
                    "\n4 - Quantidade de combustível restante no tanque"
                    "\n5 - Relatório completo"
                    "\n6 - Sair");
                    do{
                        printf("\nEscolha uma opção: ");
                        scanf("%d",&operre);
                        switch(operre){
                            case 1:
                                printf("A quantidade de litros vendida é de %.2f",litotal);
                                break;
                            case 2:
                                printf("O valor total arrecadado é de %.2f R$",vendtotal);
                                break;
                            case 3:
                                printf("A quantidade de carros atendidos é de %d",caraten);
                                break;
                            case 4:
                                printf("A quantidade de gasolina restante é de X");
                                break;
                            case 5:
                                printf("A quantidade de litros vendida é de %.2f\n"
                                "O valor total arrecadado é de %.2f R$\n"
                                "A quantidade de carros atendidos é de %d\n"
                                "A quantidade de gasolina restante é de X",litotal,vendtotal,caraten);
                                break;
                            case 6:
                                printf("Sair");
                                break;
                            default:
                                printf("Opção inválida");
                        }
                    }while(operre!=6);
                    break;
                case 5:
                    printf("Programa encerrado");
                    break;
                default:
                    printf("Operação inválida!");
            }
        }while(oper != 5);

    return 0;
}
