#include "proj.h"
#include <stdio.h>


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
int listarTarefas(ListaDeTarefas lt){
    int i = 0;

    // Mensagem para o usuário
    printf("Tarefas cadastradas: \n");
    //

    //Loop de repetição para leitura de cada Tarefa dentro da ListaDeTarefas no endereço lt
    while (i<lt.qtd){
        printf("-----------------------\n");
        printf("Numero da Tarefa: %d\n", i);
        printf("Categoria: %s\n", lt.tarefas[i].categoria);
        printf("Descricao: %s\n", lt.tarefas[i].descricao);
        printf("Prioridade: %d\n", lt.tarefas[i].prioridade);

        i++;
    }
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