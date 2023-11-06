#include <stdio.h>
#include "proj.h"




int main() {
    int cod;
    char arquivo[] = "tarefas";
    ListaDeTarefas lt;

    cod = carregarLista(&lt,arquivo);
    if (cod == 1)
        lt.qtd = 0;

    int opcao;
    do{
        printMenu();
        scanf("%d", &opcao);

        if(opcao ==0){}
        else if(opcao ==1){
            criarTarefa(&lt);
        }
        else if(opcao ==2){
            deletarTarefa(&lt);
        }
        else if(opcao ==3){
            listarTarefas(lt);
        }
        else if(opcao ==4){
            alterarTarefa(&lt);
        }
        else{
            printf("Opcao nao existe\n");
        }

    }while(opcao !=0);

    cod = salvarLista(lt,arquivo);
    if (cod !=0)
        printf("Erro ao salvar as tarefas");


}
