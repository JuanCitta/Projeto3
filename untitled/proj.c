#include "proj.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int criarTarefa(ListaDeTarefas *lt){


    // Abrindo o arquivo
    FILE *f = fopen("arquivo.bin", "ab");
    //

    // Se o Arquivo não é encontrado retorna um código de erro
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    //
    //Inicializa o Struct com o nome de nova tarefa e inicia a prioridade como -1 para que
    // o Loop de pedir a prioridade do usuario funcione corretamente
    Tarefa novatarefa;
    novatarefa.prioridade = -1;
    //

    //Checka se a lista ja tem 100 objetos
    if (lt->qtd >= 100){
        printf("Limite maximo de tarefas atingido, delete uma antes de continuar\n");
        fclose(f);
        return 1;
    }
    //


    // Por algum motivo o codigo funciona com um fgets a mais, eu acho que eh por
    // que ele limpa o buffer de entrada e assim aceita a categoria, que estava sendo pulada pelo fgets
fgets(novatarefa.categoria, sizeof(novatarefa.categoria), stdin);

    // Pedindo Categoria, Descrição e Prioriade ao usuário
    printf("Escreva a categoria da tarefa (ate 300 caracteres):\n");
    fgets(novatarefa.categoria, sizeof(novatarefa.categoria), stdin);


    printf("Descreva sua tarefa (ate 300 caracteres):\n");
    fgets(novatarefa.descricao, sizeof(novatarefa.descricao), stdin);

    while(novatarefa.prioridade>10 || novatarefa.prioridade<0){

        printf("Qual a prioridade(de 0 a 10): \n");
        scanf("%d",&novatarefa.prioridade);
    }
    printf("Qual o andamento da tarefa (1: completa, 2: em andamento, 3: nao inciado)? \n");
    fflush(stdin);
    scanf("%d", &novatarefa.estado);

    //

    // Contando o número de tarefas
    lt->tarefas[lt->qtd] = novatarefa;
    lt->qtd++;
    //

    // Indicação de Sucesso
    return 0;
    //
}



int deletarTarefa(ListaDeTarefas *lt){

    int resposta;

    // Mensagem para o usuário
    printf("Qual tarefa deseja deletar?\n");
    //

    // Scan para ver a resposta do usuario
    scanf("%d",&resposta);
    //

    // Verificar se o número fornecido é válido
    if (resposta >= 0 && resposta < lt->qtd) {
        // Remover a tarefa da lista
        for (int i = resposta; i < lt->qtd - 1; i++) {
            lt->tarefas[i] = lt->tarefas[i + 1];
        }
        lt->qtd--;
        printf("Tarefa excluida com sucesso!\n");
    }
    else {
        printf("Numero de tarefa invalido. Nenhuma tarefa foi excluida.\n");
    }


    // Indicação de Sucesso
    return 0;
    //
}
int alterarTarefa(ListaDeTarefas *lt) {
    //Inicializacao da variavel do pedido do usuario
    int resposta;

    printf("Qual tarefa deseja alterar? ");
    scanf("%d", &resposta);
    // Check para ver se o valor eh valido
    if (resposta >= 0 && resposta < lt->qtd) {
        int escolha;
        do {
            //Bloco de repeticao em formato do - while para uso continuo ate o usuario desejar sair
            printf("O que deseja alterar na tarefa %d?\n", resposta);
            printf("1. Categoria\n");
            printf("2. Descricao\n");
            printf("3. Prioridade\n");
            printf("4. Andamento\n");
            printf("5. Concluir\n");
            fflush(stdin);
            scanf("%d", &escolha);

            switch (escolha) {
                // Cases para as escolhas que o usuario pode tomar
                case 1:
                    printf("Digite a nova categoria: ");
                    fflush(stdin);
                    scanf("%s", lt->tarefas[resposta].categoria);
                    break;
                case 2:
                    printf("Digite a nova descricao: ");
                    fflush(stdin);
                    scanf("%s", lt->tarefas[resposta].descricao);
                    break;
                case 3:
                    do {
                        int novaPrioridade = -1;
                        printf("Digite a nova prioridade (entre 0 e 10): ");
                        if (scanf("%d", &novaPrioridade) == 1 && novaPrioridade >= 0 && novaPrioridade <= 10) {
                            lt->tarefas[resposta].prioridade = novaPrioridade;
                            break; // Se a prioridade for válida, saia do loop
                        } else {
                            printf("Prioridade inválida. Deve ser um número entre 0 e 10.\n");
                        }
                    } while (1); // Loop infinito, sairá apenas quando a prioridade for válida
                    break;
                case 4:
                    do{
                        int novoandamento;
                        printf("Digite o novo andamento (completa, nao iniciada, em andamento)\n");
                        if( scanf("%d", &novoandamento) == 1 && novoandamento == 1|| novoandamento == 2|| novoandamento ==3){
                            lt->tarefas[resposta].estado = novoandamento;
                            break;
                        }
                        else {
                            printf("Estado invalido, digite 1 para tarefa completa, 2 para tarefa em andamento e 3 para nao iniciada");
                        }

                    } while(1);

                    break;
                case 5:
                    printf("Alteracoes concluidas.\n");
                    break;
                default:
                    printf("Opcao invalida.\n");
            }
        } while (escolha != 5); // Codigo de saida do do - while eh 4
    } else {
        printf("Numero de tarefa invalido. Nenhuma alteracao foi feita.\n");
    }

    return 1;
}

int listarTarefas(ListaDeTarefas lt){
    int prioridadeescolhida, estadoescolhido, prioridadecategoria;
    char categoriaescolhida[300], categoriaprioridade[300];
    int i = 0;
    int escolha;
    printf("Deseja listar as tarefas com qual filtro?\n");
    printf("1 para mostrar as tarefas com a prioridade escolhida. \n");
    printf("2 para mostrar as tarefas com o estado escolhido. \n");
    printf("3 para mostrar as tarefas por a categoria escolhida. \n");
    printf("4 para mostrar as tarefas pela categoria escolhida e em ordem decrescente de prioridade. \n");
    scanf("%d", &escolha);
switch (escolha){
    case 1:
        printf("Digite a prioridade (0-10) que deve ser listada: ");
        scanf("%d", &prioridadeescolhida);
        while(i<lt.qtd){
            if(lt.tarefas[i].prioridade == prioridadeescolhida){
                printf("-----------------------\n");
                printf("Numero da Tarefa: %d\n", i);
                printf("Categoria: %s\n", lt.tarefas[i].categoria);
                printf("Descricao: %s\n", lt.tarefas[i].descricao);
                printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
                if(lt.tarefas[i].estado == 1){
                    printf("Estado: Completa\n");
                }
                else if(lt.tarefas[i].estado == 2){
                    printf("Estado: Em andamento\n");
                }
                else if(lt.tarefas[i].estado == 3){
                    printf("Estado: Nao iniciada\n");
                }

            }
            i++;
        }
        break;
    case 2:
        printf("Digite o estado a ser procurado nas tarefas (1,2 ou 3): ");
        scanf("%d", &estadoescolhido);
        while(i<lt.qtd){
            if(lt.tarefas[i].estado == estadoescolhido){
                printf("-----------------------\n");
                printf("Numero da Tarefa: %d\n", i);
                printf("Categoria: %s\n", lt.tarefas[i].categoria);
                printf("Descricao: %s\n", lt.tarefas[i].descricao);
                printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
                if(lt.tarefas[i].estado == 1){
                    printf("Estado: Completa\n");
                }
                else if(lt.tarefas[i].estado == 2){
                    printf("Estado: Em andamento\n");
                }
                else if(lt.tarefas[i].estado == 3){
                    printf("Estado: Nao iniciada\n");
                }

            }
            i++;
        }
        break;
//    case 3:
//        printf("Digite a categoria a ser procurada:");
//        scanf("%s", categoriaescolhida);
//        printf("%s", categoriaescolhida);
//        // Ordenar as tarefas por prioridade em ordem decrescente
//        for (int j = 0; j < lt.qtd - 1; j++) {
//            for (int k = j + 1; k < lt.qtd; k++) {
//                if (lt.tarefas[j].prioridade < lt.tarefas[k].prioridade) {
//                    // Troca as tarefas se a prioridade for maior
//                    Tarefa temp = lt.tarefas[j];
//                    lt.tarefas[j] = lt.tarefas[k];
//                    lt.tarefas[k] = temp;
//                }
//            }
//        }

        // Exibir as tarefas ordenadas
        for (i = 0; i < lt.qtd; i++) {
            if(strcmp(lt.tarefas[i].categoria, categoriaescolhida) ==0){
            printf("-----------------------\n");
            printf("Numero da Tarefa: %d\n", i);
            printf("Categoria: %s\n", lt.tarefas[i].categoria);
            printf("Descricao: %s\n", lt.tarefas[i].descricao);
            printf("Prioridade: %d\n", lt.tarefas[i].prioridade);

            if (lt.tarefas[i].estado == 1) {
                printf("Estado: Completa\n");
            } else if (lt.tarefas[i].estado == 2) {
                printf("Estado: Em andamento\n");
            } else if (lt.tarefas[i].estado == 3) {
                printf("Estado: Nao iniciada\n");
            }
        }}
        break;
    case 4:
        printf("Digite a categoria das tarefas que deseja ver: ");
        scanf("%s", categoriaprioridade);

        int tarefasEncontradas = 0; // Variável para contar as tarefas encontradas

        for (i = 0; i < lt.qtd; i++) {
            printf("Categoria da tarefa %d: %s\n", i, lt.tarefas[i].categoria);
            printf("Categoria a buscar: %s\n", categoriaprioridade);

            if (strcasecmp(lt.tarefas[i].categoria, categoriaprioridade) == 0) {
                printf("-----------------------\n");
                printf("Numero da Tarefa: %d\n", i);
                printf("Categoria: %s\n", lt.tarefas[i].categoria);
                printf("Descricao: %s\n", lt.tarefas[i].descricao);
                printf("Prioridade: %d\n", lt.tarefas[i].prioridade);

                if (lt.tarefas[i].estado == 1) {
                    printf("Estado: Completa\n");
                } else if (lt.tarefas[i].estado == 2) {
                    printf("Estado: Em andamento\n");
                } else if (lt.tarefas[i].estado == 3) {
                    printf("Estado: Nao iniciada\n");
                }

                tarefasEncontradas++; // Incrementa o contador de tarefas encontradas
            }
        }

        // Verifica se nenhuma tarefa foi encontrada
        if (tarefasEncontradas == 0) {
            printf("Nenhuma tarefa encontrada com a categoria especificada.\n");
        }
        break;




    default:
        // Código para opção inválida
        printf("Opcao invalida. Tente novamente (1 a 4)\n");
        break;
}

//    // Mensagem para o usuário
//    printf("Tarefas cadastradas: \n");
//    //
//
//    //Loop de repetição para leitura de cada Tarefa dentro da ListaDeTarefas no endereço lt
//    while (i<lt.qtd){
//        printf("-----------------------\n");
//        printf("Numero da Tarefa: %d\n", i);
//        printf("Categoria: %s\n", lt.tarefas[i].categoria);
//        printf("Descricao: %s\n", lt.tarefas[i].descricao);
//        printf("Prioridade: %d\n", lt.tarefas[i].prioridade);
//        if(lt.tarefas[i].estado == 1){
//            printf("Estado: Completa\n");
//        }
//        else if(lt.tarefas[i].estado == 2){
//            printf("Estado: Em andamento\n");
//        }
//        else if(lt.tarefas[i].estado == 3){
//            printf("Estado: Nao iniciada\n");
//        }
//
//        i++;
//    }
    //

    // Indicação de Sucesso
    return 0;
    //
}

void printMenu(){
    printf("Menu:\n ");
    printf("1. Criar Tarefa\n ");
    printf("2. Deletar Tarefa\n ");
    printf("3. Listar Tarefas\n ");

}
int salvarLista(ListaDeTarefas lt, char nome[]){

    // Abrindo o arquivo no modo WB
    FILE *f= fopen("arquivo.bin", "wb");
    //

    if(f==NULL){
        return 1;
    }
    // Escrevendo a lista atualizada no arquivo
    fwrite(&lt, sizeof(ListaDeTarefas), 1, f);
    //

    // Fechando o arquivo
    fclose(f);
    //

    // Indicação de Sucesso
    return 0;}
    //

int carregarLista(ListaDeTarefas *lt,char nome[]){

    // Abrindo o arquivo como read
    FILE *f = fopen("arquivo.bin", "rb");
    //

    if(f==NULL)
        return 1;

    //Comando para leitura de cada Tarefa dentro da ListaDeTarefas no endereço de lt
    fread(lt,sizeof(ListaDeTarefas),1,f);
    //

    //Fecha o arquivo
    fclose(f);
    //

    // Indicação de Sucesso
    return 0;}
    //