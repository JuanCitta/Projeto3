typedef struct {
    int prioridade;
    char categoria[100];
    char descricao[300];
    int estado;
} Tarefa;

typedef struct {
    Tarefa tarefas[100];
    int qtd;
} ListaDeTarefas;

int criarTarefa(ListaDeTarefas *lt);
int deletarTarefa(ListaDeTarefas *lt);
int listarTarefas(ListaDeTarefas lt);
int alterarTarefa(ListaDeTarefas *lt);

void printMenu();
int salvarLista(ListaDeTarefas lt,char nome[]);
int carregarLista(ListaDeTarefas *lt, char nome[]);