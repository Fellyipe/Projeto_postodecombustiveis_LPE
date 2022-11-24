#include"header.h"

int main(int argc, char** argv){
    
    int maxFilas[3],maiorFila,filas[3]={0,0,0},veiculosAten=0;
    int oper,operRA,valido=0,contArq=0,i,j,k,l,fila,comb;
    float precos[6]={-1,-1,-1,-1,-1,-1},combRestante[5]={200,200,200,600,600};
    float combVendido[6]={0,0,0,0,0,0},combVendaTotal[6]={0,0,0,0,0,0};
    float lit,min,kWh,total,vendLoja=0,copia;
    char relatorio[1500],parte1Relatorio[400],parte2Relatorio[400],parte3Relatorio[400],gerente[30]="";
    char combustiveis[6][20]={"gasolina comum","gasolina aditivada","etanol","diesel comum","diesel S10","eletricidade"};
    struct TVeiculo *VeiculosF1, *VeiculosF2, *VeiculosF3, *VeiculosA, CopiaVeiculo, *CopiaDaFila, *ptrVeiculosF;
    struct TVenda *Vendas,*Vendas2;
    
    VeiculosA = (struct TVeiculo *) calloc(5,sizeof(struct TVeiculo));
    Vendas = (struct TVenda *) calloc(5,sizeof(struct TVenda));
    if(VeiculosA==NULL || Vendas==NULL){
        printf(NIVM "Memória insuficiente!");
    }
    
    setlocale(LC_ALL,NULL);
    
    printf(NIVD "////////////////////////////////////////////////////////////////"
    "\n                       Posto de Combustíveis                             "
    "\nAutor: Felipe Bueno\n"
    "\nEste programa serve como uma ferramenta para administrar um"
    "\nposto de combustiveis\n"
    "////////////////////////////////////////////////////////////////\n" RESET);
    enter();
    
    system("clear");
    printf(ICN "Nome do gerente: ");
    fgets(gerente,30,stdin);
    gerente[strcspn(gerente,"\n")] = 0;
	enter();
	system("clear");
	printf(ICN "Informe a capacidade máxima de veículos de cada fila\n");
    for(i=0;i<3;i++){
        maxFilas[i] = definirFila(i+1);
    }
    if(maxFilas[0]>maxFilas[1]){
        if(maxFilas[0]>maxFilas[2]){
            maiorFila = maxFilas[0];
        }else{
            maiorFila = maxFilas[2];
        }
    }else{
        if(maxFilas[1]>maxFilas[2]){
            maiorFila = maxFilas[1];
        }else{
            maiorFila = maxFilas[2];
        }
    }
    VeiculosF1 = (struct TVeiculo *) calloc(maxFilas[0],sizeof(struct TVeiculo));
    VeiculosF2 = (struct TVeiculo *) calloc(maxFilas[1],sizeof(struct TVeiculo));
    VeiculosF3 = (struct TVeiculo *) calloc(maxFilas[2],sizeof(struct TVeiculo));
    CopiaDaFila = (struct TVeiculo *) calloc(maiorFila,sizeof(struct TVeiculo));
    enter();
    system("clear");
    for(i=0;i<6;i++){
        precos[i] = definirPreco(i);
    }
    enter();
    
    system("clear");
    setbuf(stdin,NULL);
    printf(NAM "Gerente: %s\n",gerente);
    printf("Preço da Gasolina Comum: %.2fR$ por litro\n"
    "Preço da Gasolina Aditivada: %.2fR$ por litro\n"
    "Preço do Etanol: %.2fR$ por litro\n"
    "Preço do Diesel Comum: %.2fR$ por litro\n"
    "Preço do Diesel Comum: %.2fR$ por litro\n"
    "Preço da Eletricidade: %.2fR$ por kWh\n",precos[0],precos[1],precos[2],precos[3],precos[4],precos[5]);
    for(i=0;i<3;i++){
        printf("Capacidade máxima de carros na fila %d: %d\n",i+1,maxFilas[i]);
    }
    setbuf(stdin,NULL);
    enter();
    
    do{
        system("clear");
        printf(RESET AMB "\tMENU DE OPERAÇÕES" IAZ
        "\n1 - Adicionar veículo para abastecer"
        "\n2 - Abastecer"
        "\n3 - Exibir veículos na espera"
        "\n4 - Relatórios"
        "\n5 - Opções avançadas"
        "\n6 - Encerrar programa");
        oper = 0;
        setbuf(stdin,NULL);
        printf(NAZ "\nEscolha uma operação: ");
        valido = scanf("%d",&oper);
        setbuf(stdin,NULL);
        system("clear");
        switch(oper){
            case 1:
                comb = 0;
                printf(IMG "Informe qual o combustível utilizado pelo veículo\n"
                "1 - Gasolina Comum; 2 - Gasolina Aditivada; 3 - Etanol\n"
                "4 - Diesel Comum; 5 - Diesel S10; 6 - Eletricidade\n");
                valido = scanf("%d",&comb);
                setbuf(stdin,NULL);
                if(comb<=0 || comb>6){
                    opcaoInvalida(valido);
                    enter();
                    break;
                }
                if(combRestante[comb-1]==0 && comb != 6){
                    printf(NVM "Não há mais desse combustível restante!\n"
                    "Não está permitido adicionar carros com esse combustível");
                    enter();
                    break;
                }
                fila = retornaFila(comb) - 1;
                if(fila == 0)
                    ptrVeiculosF = VeiculosF1;
                if(fila == 1)
                    ptrVeiculosF = VeiculosF2;
                if(fila == 2)
                    ptrVeiculosF = VeiculosF3;
                    
                if(filas[fila] < maxFilas[fila]){
                    addVeiculo(&ptrVeiculosF[filas[fila]],comb);
                    filas[fila]+=1;
                }else{
                    printf(NVM "Máximo de veículos atingidos na fila %d!\n",fila+1);
                }
                for(i=0;i<3;i++){
                printf(ICN "Quantidade de carros na fila %d: %d\n",i+1,filas[i]);
                }
                enter();
                break;
            case 2:
                fila = 0;
                total = 0;
                printf("Digite o número da fila que está o veículo que será abastecido\n");
                valido = scanf("%d",&fila);
                fila--;
                if(fila>=0 && fila<3){
                    if(filas[fila]==0){
                        printf(NVM "Não há nenhum carro na fila %d\n",fila+1);
                        limpaBuffer();
                        enter();
                        break;
                    }
                    if(fila == 0)
                        ptrVeiculosF = VeiculosF1;
                    if(fila == 1)
                        ptrVeiculosF = VeiculosF2;
                    if(fila == 2)
                        ptrVeiculosF = VeiculosF3;
                    comb = ptrVeiculosF[0].combustivel;
                    comb -= 1;
                    if(comb!=5){
                        nivelDoCombustivel(combRestante[comb],comb);
                        printf(NAZ "Quantidade de litros: ");
                        valido = scanf("%f",&lit);
                        setbuf(stdin,NULL);
                        valido = apenasNum(valido,lit);
                        if(valido!=1){
                            enter();
                            break;
                        }else{
                            if(lit<=combRestante[comb]){
                                combRestante[comb] -= lit;
                                combVendido[comb] += lit;
                                total += lit * precos[comb];
                                combVendaTotal[comb] = total;
                                Vendas = (struct TVenda *) realloc(Vendas,(veiculosAten+1) * sizeof(struct TVenda));
                                Vendas[veiculosAten].quantidade = lit;
                                Vendas[veiculosAten].total = total;
                                Vendas[veiculosAten].preco = precos[comb];
                                Vendas[veiculosAten].combustivel = comb;
                                VeiculosA = (struct TVeiculo *) realloc(VeiculosA,(veiculosAten+1) * sizeof(struct TVeiculo));
                                VeiculosA[veiculosAten] = ptrVeiculosF[0];
                                veiculosAten++;
                                for(int k=0;k<(filas[fila]-1);k++){
                                    ptrVeiculosF[k] = ptrVeiculosF[k+1];
                                }
                                k = filas[fila] - 1;
                                strcpy(ptrVeiculosF[k].cor,"");
                                strcpy(ptrVeiculosF[k].modelo,"");
                                strcpy(ptrVeiculosF[k].tipo,"");
                                strcpy(ptrVeiculosF[k].especificacao,"");
                                ptrVeiculosF[k].combustivel = 0;
                                ptrVeiculosF[k].ano = 0;
                                filas[fila]--;
                                
                                printf(ICN "\nValor total = %.2f R$ (%.2f R$ por litro)\n",precos[comb]*lit,precos[comb]);
                                setbuf(stdin,NULL);
                            }else{
                                printf(NVM "Não há %s suficiente!\n",combustiveis[comb]);
                                printf("Despachar veiculo? Se sim, digite 1, se não, digite qualquer coisa\n");
                                
                                if(scanf("%d",&valido)!=1){
                                    valido = 0;
                                    limpaBuffer();
                                }
                                if(valido != 1){
                                    enter();
                                    break;
                                }else{
                                    for(int k=0;k<(filas[fila]-1);k++){
                                        ptrVeiculosF[k] = ptrVeiculosF[k+1];
                                    }
                                    k = filas[fila] - 1;
                                    strcpy(ptrVeiculosF[k].cor,"");
                                    strcpy(ptrVeiculosF[k].modelo,"");
                                    strcpy(ptrVeiculosF[k].tipo,"");
                                    strcpy(ptrVeiculosF[k].especificacao,"");
                                    ptrVeiculosF[k].combustivel = 0;
                                    ptrVeiculosF[k].ano = 0;
                                    filas[fila]--;
                                }
                            }
                        }
                    }else{
                        printf(NAZ "Quantidade de minutos que o veículo ficará carregando: ");
                        valido = apenasNum(scanf("%f",&min),min);
                        if(valido==1){
                            kWh = 100 * (min/60);
                            combVendido[5] += kWh;
                            total += kWh * precos[5];
                            combVendaTotal[5] = total;
                            Vendas = (struct TVenda *) realloc(Vendas,(veiculosAten+1) * sizeof(struct TVenda));
                            Vendas[veiculosAten].quantidade = min;
                            Vendas[veiculosAten].total = total;
                            Vendas[veiculosAten].preco = precos[5];
                            Vendas[veiculosAten].combustivel = 6;
                            VeiculosA = (struct TVeiculo *) realloc(VeiculosA,(veiculosAten+1) * sizeof(struct TVeiculo));
                            VeiculosA[veiculosAten] = ptrVeiculosF[0];
                            veiculosAten++;
                            for(int k=0;k<(filas[2]-1);k++){
                                ptrVeiculosF[k] = ptrVeiculosF[k+1];
                            }
                            k = filas[2] - 1;
                            strcpy(ptrVeiculosF[k].cor,"");
                            strcpy(ptrVeiculosF[k].modelo,"");
                            strcpy(ptrVeiculosF[k].tipo,"");
                            strcpy(ptrVeiculosF[k].especificacao,"");
                            ptrVeiculosF[k].combustivel = 0;
                            ptrVeiculosF[k].ano = 0;
                            
                            filas[2]--;
                            printf(ICN "\nValor total = %.2f R$ (%.2f R$ por minuto - carregador operando a 100kW de potência)\n",total,(precos[5] * 100)/60);
                            setbuf(stdin,NULL);
                        }
                    }
                    if(combRestante[comb]==0 && comb != 5){ 
                        printf(NVM "\nO tanque de %s está vazio!"
                        "\nTodos os veículos com esse combustível serão despachados!",combustiveis[comb]);
                        l=0;
                        for(k=0;k<filas[fila];k++){
                            if(ptrVeiculosF[k].combustivel!=comb+1){
                                CopiaDaFila[l] = ptrVeiculosF[k];
                                l++;
                            }
                        }
                        ptrVeiculosF = CopiaDaFila;
                        filas[fila] = l;
                    }
                    
                }else{
                printf(NVM "Opção inválida!\n");
                }
                if(valido != 1)
                    limpaBuffer();
                setbuf(stdin,NULL);
                enter();
                break;
            case 3:
                fila = 0;
                printf("Digite qual a fila que deverá ser exibida: ");
                valido = scanf("%d",&fila);
                setbuf(stdin,NULL);
                fila -= 1;
                if(fila>=0 && fila<3){
                    if(fila == 0)
                        ptrVeiculosF = VeiculosF1;
                    if(fila == 1)
                        ptrVeiculosF = VeiculosF2;
                    if(fila == 2)
                        ptrVeiculosF = VeiculosF3;
                    printf(SMG "Quantidade de veículos na fila: %d\n",filas[fila]);
                    if(filas[fila]==0)
                        printf("Não há nenhum veículo na fila\n");
                    else if(filas[fila]==1){
                        printf("Este é veículo contido na fila de espera\n");
                        printf("%s, modelo %s, cor %s, ano de %d.\n"
                        "Combustível: %s. Especificações: %s",
                        ptrVeiculosF[0].tipo,ptrVeiculosF[0].modelo,ptrVeiculosF[0].cor,ptrVeiculosF[0].ano,
                        combustiveis[(ptrVeiculosF[0].combustivel-1)],ptrVeiculosF[0].especificacao);
                    }else{
                        printf("Estes são os veículos contidos na fila de espera\n");
                        for(int i=0;i<filas[fila];i++){
                            printf("%s, modelo %s, cor %s, ano de %d.\n"
                            "Combustível: %s. Especificações: %s\n",
                            ptrVeiculosF[i].tipo,ptrVeiculosF[i].modelo,ptrVeiculosF[i].cor,ptrVeiculosF[i].ano,
                            combustiveis[ptrVeiculosF[i].combustivel],ptrVeiculosF[i].especificacao);
                        }
                    }
                }else{
                    opcaoInvalida(valido);    
                    enter();
                    break;
                }
                enter();
                break;
            case 4:
                do{ 
                    system("clear");
                    total = 0;
                    for(i=0;i<6;i++){
                        total += combVendaTotal[i];
                    }
                    snprintf(parte1Relatorio,400,"Valor arrecadado pela venda de Gasolina Comum: %.2fR$\n"
                        "Valor arrecadado pela venda de Gasolina Aditivada: %.2fR$\n"
                        "Valor arrecadado pela venda de Etanol: %.2fR$\n"
                        "Valor arrecadado pela venda de Diesel Comum: %.2fR$\n"
                        "Valor arrecadado pela venda de Diesel S10: %.2fR$\n"
                        "Valor arrecadado pela venda de Eletricidade: %.2fR$\n",
                        combVendaTotal[0],combVendaTotal[1],combVendaTotal[2],combVendaTotal[3],combVendaTotal[4],combVendaTotal[5]);
                    snprintf(parte2Relatorio,400,"Quantidade de Gasolina Comum vendida: %.2fL\n"
                        "Quantidade de Gasolina Aditivada vendida: %.2fL\n"
                        "Quantidade de Etanol vendido: %.2fL\n"
                        "Quantidade de Diesel Comum vendido: %.2fL\n"
                        "Quantidade de Diesel S10 vendido: %.2fL\n"
                        "Quantidade de Eletricidade (kWh) vendida: %.2fL\n",
                        combVendido[0],combVendido[1],combVendido[2],combVendido[3],combVendido[4],combVendido[5]);
                    snprintf(parte3Relatorio,400,"Quantidade de Gasolina Comum restante: %.2fL\n"
                        "Quantidade de Gasolina Aditivada restante: %.2fL\n"
                        "Quantidade de Etanol restante: %.2fL\n"
                        "Quantidade de Diesel Comum restante: %.2fL\n"
                        "Quantidade de Diesel S10 restante: %.2fL\n",
                        combRestante[0],combRestante[1],combRestante[2],combRestante[3],combRestante[4]);
                    snprintf(relatorio,1500,"%s"
                        "Valor arrecadado pelas vendas da loja de conveniência: %.2fR$\n"
                        "Valor total arrecadado: %.2f R$\n"
                        "Quantidade de Veículos atendidos: %d\n"
                        "%s"
                        "%s"
                        "Gerente: %s",parte1Relatorio,vendLoja,total+vendLoja,veiculosAten,parte2Relatorio,parte3Relatorio,gerente);
                    printf(RESET VDB "\tMENU DE RELATÓRIOS\t" IAM
                    "\n1 - Quantidade de combustivel vendida"
                    "\n2 - Valor arrecadado pela venda de combustiveis"
                    "\n3 - Valor arrecadado pelas vendas da loja de conveniência"
                    "\n4 - Valor total arrecadado com as vendas"
                    "\n5 - Quantidade de veículos atendidos"
                    "\n6 - Quantidade de combustível restante no tanque"
                    "\n7 - Relatório Geral completo"
                    "\n8 - Criar arquivo do relatório completo"
                    "\n9 - Registros de vendas"
                    "\n10 - Lista de veículos atendidos"
                    "\n11 - Sair");
                    operRA = 0;
                    printf(NAM "\nEscolha uma opção: ");
                    valido = scanf("%d",&operRA);
                    system("clear");
                    setbuf(stdin,NULL);
                    switch(operRA){
                        case 1:
                            printf("%s",parte2Relatorio);
                            enter();
                            break;
                        case 2:
                            printf("%s\nValor total: %.2fR$\n",parte1Relatorio,total);
                            enter();
                            break;
                        case 3:
                            printf("Valor arrecadado pelas vendas da loja de conveniência: %.2f R$\n",vendLoja);
                            enter();
                            break;
                        case 4:
                            printf("Valor total arrecadado: %.2f R$\n",total + vendLoja);
                            enter();
                            break;
                        case 5:
                            printf("Quantidade de veículos atendidos: %d\n",veiculosAten);
                            enter();
                            break;
                        case 6:
                            printf("%s",parte3Relatorio);
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
                            printf("Lista de vendas por ordem de atendimento\n");
                            for(int i=0;i<veiculosAten;i++){
                                printf("%d - Combustível: %s - %.2f (quantidade) × %.2fR$ (preço) = total %.2fR$\n",
                                i+1,combustiveis[(Vendas[i].combustivel - 1)],Vendas[i].quantidade,Vendas[i].preco,Vendas[i].total);
                            }
                            enter();
                            break;
                        case 10:
                            printf("Lista de carros atendidos por ordem de atendimento\n");
                            for(int i=0;i<veiculosAten;i++){
                                printf("%s, modelo %s, cor %s, ano de %d.\n"
                                "Combustível: %s. Especificações: %s\n",
                                VeiculosA[i].tipo,VeiculosA[i].modelo,VeiculosA[i].cor,VeiculosA[i].ano,
                                combustiveis[(VeiculosA[i].combustivel - 1)],VeiculosA[i].especificacao);
                            }
                            enter();
                            break;
                        case 11:
                            break;
                        default:
                            opcaoInvalida(valido);
                            enter();
                    }
                }while(operRA!=11);
                break;
            case 5:
                do{
                    system("clear");
                    printf(RESET VDB "\tOPÇÕES AVANÇADAS\t" IAM
                    "\n1 - Reabastecer reservatório de combustível"
                    "\n2 - Alterar gerente"
                    "\n3 - Alterar preço do combustível"
                    "\n4 - Alterar quantidade máxima de veículos na fila"
                    "\n5 - Despachar veículos"
                    "\n6 - Gegistrar compra na loja de conveniência"
                    "\n7 - Sair");
                    operRA = 0;
                    printf(NAM "\nEscolha uma opção: ");
                    valido = scanf("%d",&operRA);
                    setbuf(stdin,NULL);
                    system("clear");
                    
                    switch(operRA){
                        case 1:
                            comb = 0;
                            printf("Digite de qual combustível cujo tanque será abastecido\n"
                            "Quantidade de litros restante de cada reservatório:\n"
                            "1 - Gasolina Comum: %.2fL; 2 - Gasolina Aditivada: %.2fL;\n"
                            "3 - Etanol: %.2fL; 4 - Diesel Comum: %.2fL; 5 - Diesel S10: %.2fL\n",
                            combRestante[0],combRestante[1],combRestante[2],combRestante[3],combRestante[4]);
                            valido = scanf("%d",&comb);
                            setbuf(stdin,NULL);
                            if(comb<1 || comb>5){
                                opcaoInvalida(valido);
                                enter();
                                break;
                            }
                            fila = retornaFila(comb);
                            combRestante[comb-1] = reabastecerReservatorio(comb-1,combRestante[comb-1],filas[fila-1],fila);
                            enter();
                            break;
                        case 2:
                            definirGerente(gerente);
                            enter();
                            break;
                        case 3:
                            comb = 0;
                            printf("Digite qual combustível terá seu preço alterado\n"
                            "Tabela de preços atual:\n"
                            "1 - Gasolina Comum: %.2fR$; 2 - Gasolina Aditivada: %.2fR$; 3 - Etanol: %.2fR$\n"
                            "4 - Diesel Comum: %.2fR$; 5 - Diesel S10: %.2fR$; 6 - Eletricidade: %.2fR$\n"
                            ,precos[0],precos[1],precos[2],precos[3],precos[4],precos[5]);
                            valido = scanf("%d",&comb);
                            setbuf(stdin,NULL);
                            if(comb<1 || comb>6){
                                opcaoInvalida(valido);
                                enter();
                                break;
                            }
                            fila = retornaFila(comb) - 1;
                            if(fila == 0)
                                ptrVeiculosF = VeiculosF1;
                            if(fila == 1)
                                ptrVeiculosF = VeiculosF2;
                            if(fila == 2)
                                ptrVeiculosF = VeiculosF3;
                            valido = 0;
                            for(i=0;i<filas[fila];i++){
                                if(ptrVeiculosF[i].combustivel == comb){
                                    valido = 1;
                                    break;
                                }
                            }
                            if(valido == 1){
                                printf("É necessário despachar todos os veículos a %s da fila %d\n" ,combustiveis[comb-1],fila+1);
                                printf("Despachar todos os veículos a %s da fila %d?\n"
                                "Se sim, digite 1, se não, digite qualquer coisa\n",combustiveis[comb-1],fila+1);
                                if(scanf("%d",&valido)!=1)
                                    valido = 0;
                                limpaBuffer();
                                if(valido==1){
                                    j=0;
                                    for(i=0;i<filas[fila];i++){
                                        if(ptrVeiculosF[i].combustivel!=comb+1){
                                            CopiaDaFila[j] = ptrVeiculosF[i];
                                            j++;
                                        }
                                    }
                                    ptrVeiculosF = CopiaDaFila;
                                    filas[fila] = j;
                                }
                            }else{
                                precos[comb-1] = definirPreco(comb-1);
                            }
                            enter();
                            break;
                        case 4:
                            fila = -1;
                            printf("Digite qual fila será alterada (Digite 0 se todas as filas serão alteradas)\n");
                            valido = scanf("%d",&fila);
                            setbuf(stdin,NULL);
                            if(fila<0 || fila>3){
                                opcaoInvalida(valido);
                                enter();
                                break;
                            }
                            if(fila == 0)
                                    ptrVeiculosF = VeiculosF1;
                                if(fila == 1)
                                    ptrVeiculosF = VeiculosF2;
                                if(fila == 2)
                                    ptrVeiculosF = VeiculosF3;
                            if(filas[fila-1]!=0){
                                printf(NVM "É necessário despachar todos os veículos da fila %d para alterar o tamanho máximo dela\n",fila);
                                enter();
                            }else{
                                maxFilas[fila-1] = definirFila(fila);
                                if(fila==1){
                                    VeiculosF1 = (struct TVeiculo *) realloc(VeiculosF1,maxFilas[fila-1] * sizeof(struct TVeiculo));
                                }
                                if(fila==2){
                                    VeiculosF2 = (struct TVeiculo *) realloc(VeiculosF2,maxFilas[fila-1] * sizeof(struct TVeiculo));
                                }
                                if(fila==3){
                                    VeiculosF3 = (struct TVeiculo *) realloc(VeiculosF3,maxFilas[fila-1] * sizeof(struct TVeiculo));
                                }
                                   
                                if(filas[fila-1]>maiorFila){
                                    maiorFila = filas[fila];
                                    CopiaDaFila = (struct TVeiculo *) realloc(CopiaDaFila,maiorFila * sizeof(struct TVeiculo));
                                }
                                printf(IVD "Capacidade máxima da fila %d alterada\n",fila);
                            }
                            enter();
                            break;
                        case 5:
                            fila = 0;
                            printf("Digite de qual fila será despachado(s) o(s) veículo(s)\n");
                            valido = scanf("%d",&fila);
                            setbuf(stdin,NULL);
                            if(fila<1 || fila>3){
                                opcaoInvalida(valido);
                                enter();
                                break;
                            }
                            j = despache(filas[fila-1]);
                            if(fila-1 == 0)
                                    ptrVeiculosF = VeiculosF1;
                                if(fila-1 == 1)
                                    ptrVeiculosF = VeiculosF2;
                                if(fila-1 == 2)
                                    ptrVeiculosF = VeiculosF3;
                            
                            if(j==0){
                                for(int i=0;i<filas[fila-1];i++){
                                    strcpy(ptrVeiculosF[i].cor,"");
                                    strcpy(ptrVeiculosF[i].modelo,"");
                                    strcpy(ptrVeiculosF[i].tipo,"");
                                    strcpy(ptrVeiculosF[i].especificacao,"");
                                    ptrVeiculosF[i].combustivel = 0;
                                    ptrVeiculosF[i].ano = 0;
                                }
                                filas[fila-1] = 0;
                                printf("Todos os veículos da fila %d foram despachados\n",fila);
                            }
                            if(j>0){
                                    j--;
                                    strcpy(ptrVeiculosF[j].cor,"");
                                    strcpy(ptrVeiculosF[j].modelo,"");
                                    strcpy(ptrVeiculosF[j].tipo,"");
                                    strcpy(ptrVeiculosF[j].especificacao,"");
                                    ptrVeiculosF[j].combustivel = 0;
                                    ptrVeiculosF[j].ano = 0;
                                    for(i=j;i<(filas[fila-1]-1);i++){
                                        ptrVeiculosF[i] = ptrVeiculosF[i+1];
                                    }
                                    k = filas[fila-1] - 1;
                                    strcpy(ptrVeiculosF[k].cor,"");
                                    strcpy(ptrVeiculosF[k].modelo,"");
                                    strcpy(ptrVeiculosF[k].tipo,"");
                                    strcpy(ptrVeiculosF[k].especificacao,"");
                                    ptrVeiculosF[k].combustivel = 0;
                                    ptrVeiculosF[k].ano = 0;
                                    filas[fila-1]-=1;
                                    printf("O veículo da posição %d da fila %d foi despachado\n",j+1,fila);
                            }
                            limpaBuffer();
                            enter();
                            break;
                        case 6:     
                            vendLoja = compra(vendLoja);
                            enter();
                            break;
                        case 7:
                            break;
                        default:
                            opcaoInvalida(valido);
                            enter();
                    }
                }while(operRA!=7);
                break;
            case 6:
                if(contArq==0){
                    printf("Nenhum arquivo de relatório foi expedido\n"
                    "Deseja criar um antes de sair do programa?\n"
                    "Você será enviado de volta para o menu principal onde poderá acessar a opção de Relatórios e Imprimir relatório\n"
                    "Se sim, digite 1, se não, digite qualquer coisa\n");
                    if(scanf("%d",&valido)!=1)
                        valido = 0;
                    limpaBuffer();
                    if(valido==1){
                        oper = 0;
                        break;
                    }
                }
                system("clear");
                printf(NIVD "Programa encerrado");
                break;
            default:
                opcaoInvalida(valido);
                enter();
        }
        setbuf(stdin,NULL);
    }while(oper!=6);
    free(VeiculosA);
    VeiculosA = NULL;
    free(VeiculosF1);
    VeiculosF1 = NULL;
    free(VeiculosF2);
    VeiculosF2 = NULL;
    free(VeiculosF3);
    VeiculosF3 = NULL;
    free(Vendas);
    Vendas = NULL;
    return 0;
}