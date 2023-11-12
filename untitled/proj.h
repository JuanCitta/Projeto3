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
int comparaTarefas(const void* a, const void* b);
int exportarTarefa(ListaDeTarefas *lt);
void printMenu();
void removerQuebrasDeLinha(char *str);
int salvarLista(ListaDeTarefas lt,char nome[]);
int carregarLista(ListaDeTarefas *lt, char nome[]);