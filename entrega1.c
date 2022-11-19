#include <stdio.h>

int main(){
    
    int maxcar;
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
    printf("Informe a quantidade máxima de carros que o posto suportará\n");
    scanf("%d",&maxcar);

    return 0;
}
