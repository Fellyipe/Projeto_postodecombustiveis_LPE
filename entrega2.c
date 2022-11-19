include <stdio.h>

int main(){
    
    int maxcar, oper;
    float preco;
    
    printf("////////////////////////////////////////////////////////////////"
    "\n                       Posto de Gasolina                             "
    "\nAutor: Felipe Bueno\n"
    "                                                                     \n"
    "Este programa serve como uma ferramenta para administrar um"
    "\nposto de gasolina\n"
    "////////////////////////////////////////////////////////////////\n");

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
    "\nEscolha a operação:"
    "\n1 - Adicionar um carro na fila"
    "\n2 - Abastecer"
    "\n3 - Exibir carros nas fila de espera"
    "\n4 - Exibir relatórios"
    "\n5 - Encerrar programa\n");
    scanf("%d",&oper);

    switch(oper){
        case 1:
            printf("Carro adicionado à fila");
            break;
        case 2:
            printf("Carro abastecido");
            break;
        case 3:
            printf("Estes são os carros contidos na fila de espera");
            break;
        case 4:
            printf("Quantidade de litros vendida:\n"
            "Valor total arrecadado com as vendas:\n"
            "Quantidade de carros atendidos:\n"
            "Quantidade de combustível restante no tanque:\n");
            break;
        case 5:
		        printf("Programa encerrado");
            break;
        default:
            printf("Operação inválida!");
    }

    return 0;
}
