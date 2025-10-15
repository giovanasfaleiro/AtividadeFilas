#include <stdio.h>
#include <stdlib.h> 

typedef struct No {
    int val;
    struct No* prox;
} No;

// Estrutura da Fila Encadeada 
typedef struct LQueue {
    No* head; 
    No* tail; 
    int size;
} LQueue;

// Inicializa a estrutura da fila 
void lq_init(LQueue* q) {
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

// Verifica se a fila está vazia 
int lq_is_empty(LQueue* q) {
    return (q->head == NULL);
}

// Insere um elemento no final da fila (enqueue)
int lq_enqueue(LQueue* q, int x) {
    // Aloca um novo nó
    No* novo = (No*) malloc(sizeof(No));
    if (novo == NULL) { 
        return 0; 
    }

    // Preenche o nó
    novo->val = x;
    novo->prox = NULL;

    // Conecta o nó na fila
    if (lq_is_empty(q)) {
        q->head = novo;
        q->tail = novo;
    } else {
        q->tail->prox = novo;
        q->tail = novo;
    }

    // Atualiza o tamanho
    q->size++;
    return 1; 
}


// Remove o primeiro elemento da fila (dequeue)
int lq_dequeue(LQueue* q, int* out) {
    // Verifica underflow
    if (lq_is_empty(q)) {
        return 0; // Retorna 0 para erro de underflow
    }

    // Salva o valor de saída
    *out = q->head->val;

    // Guarda o nó que será removido
    No* temp = q->head;

    // Avança o head
    q->head = q->head->prox;

    // Caso especial: a fila ficou vazia
    if (q->head == NULL) {
        q->tail = NULL; // Atualiza o tail também
    }

    // Libera a memória do nó antigo
    free(temp);

    // Decrementa o tamanho
    q->size--;
    return 1; // Retorna 1 para sucesso
}

int lq_front(LQueue* q, int* out) {
    // Verifica se a fila está vazia
    if (lq_is_empty(q)) {
        return 0; 
    }
    // Atribui o valor do primeiro elemento (head) ao ponteiro de saída
    *out = q->head->val;
    return 1;
}

// Esvazia a fila, liberando toda a memória 
void lq_clear(LQueue* q) {
    No* atual = q->head;
    while (atual != NULL) {
        No* temp = atual; // Guarda o nó atual
        atual = atual->prox; // Avança para o próximo
        free(temp); // Libera o nó guardado
    }
    // Reseta a fila para o estado inicial
    lq_init(q);
}


// Imprime os elementos da fila do início ao fim
void lq_imprimir(LQueue* q) {
    if (lq_is_empty(q)) {
        printf("[vazia]\n");
        return;
    }
    
    No* atual = q->head; // Começa pelo primeiro nó
    printf("[ ");
    while (atual != NULL) {
        printf("%d ", atual->val);
        atual = atual->prox; // Avança para o próximo
    }
    printf("]\n");
}


int main() {
    int valor; // Variável para receber o valor do dequeue

    // Teste 1: Operações Básicas 
    printf("Teste 1: Operacoes Basicas\n\n");
    LQueue fila_encadeada;
    lq_init(&fila_encadeada);

    lq_enqueue(&fila_encadeada, 10);
    lq_enqueue(&fila_encadeada, 20);
    printf("Estado atual da fila: ");
    lq_imprimir(&fila_encadeada);

    lq_dequeue(&fila_encadeada, &valor);
    lq_enqueue(&fila_encadeada, 30);
    printf("Estado atual da fila: ");
    lq_imprimir(&fila_encadeada);

    lq_dequeue(&fila_encadeada, &valor);
    lq_enqueue(&fila_encadeada, 1);

    lq_front(&fila_encadeada, &valor);
    printf("Olhando o proximo elemento com front: %d\n", valor);
    
    printf("\nLimpando a lista para iniciar teste 2...\n\n");
    lq_clear(&fila_encadeada);

    // Teste 2: Teste de Underflow (esvaziamento da fila) 
    printf("\nTeste 2: Teste de Underflow\n\n");
    lq_enqueue(&fila_encadeada, 5);
    printf("Estado atual da fila: ");
    lq_imprimir(&fila_encadeada);

    if (lq_dequeue(&fila_encadeada, &valor)) {
        printf("Valor removido: %d\n", valor);
    }
    printf("Estado atual da fila: ");
    lq_imprimir(&fila_encadeada);

    // Tenta remover de uma fila já vazia
    if (!lq_dequeue(&fila_encadeada, &valor)) {
        printf("Falha ao remover. Fila vazia (underflow).\n");
    }
    printf("Estado atual da fila: ");
    lq_imprimir(&fila_encadeada);

    printf("A fila esta vazia? %s \n", lq_is_empty(&fila_encadeada) ? "Verdadeiro" : "Falso");

    printf("\nLimpando a lista para iniciar teste 3...\n\n");
    lq_clear(&fila_encadeada);

   // Teste 3: Teste de Capacidade (sem overflow)
    printf("\nTeste 3: Teste de Capacidade (Listas nao tem overflow)\n\n");

    printf("Enfileirando 1, 2, 3, 4, 5...\n");
    lq_enqueue(&fila_encadeada, 1);
    lq_enqueue(&fila_encadeada, 2);
    lq_enqueue(&fila_encadeada, 3);
    lq_enqueue(&fila_encadeada, 4);
    lq_enqueue(&fila_encadeada, 5);
    printf("   Fila atual: ");
    lq_imprimir(&fila_encadeada);
    printf("\n");

    printf("Tentando enfileirar 6...\n");
    if (lq_enqueue(&fila_encadeada, 6)) {
        printf("   Sucesso ao inserir 6. A fila cresce dinamicamente.\n");
    }
    printf("   Fila atual: ");
    lq_imprimir(&fila_encadeada);

    printf("\nLimpando a lista para iniciar teste 4...\n\n");
    lq_clear(&fila_encadeada);

    // Teste 4: Teste de Sequência Mista (equivalente ao wrap-around)
    printf("\nTeste 4: Teste de Sequencia Mista\n\n");

    printf("Enfileirando 10, 20...\n");
    lq_enqueue(&fila_encadeada, 10); 
    lq_enqueue(&fila_encadeada, 20);

    printf("Fila apos ENQ(10), ENQ(20): ");
    lq_imprimir(&fila_encadeada);

    if(lq_dequeue(&fila_encadeada, &valor)) { 
        printf("Valor removido: %d \n", valor); // Deve remover 10
    }
    
    printf("Enfileirando 30, 40...\n");
    lq_enqueue(&fila_encadeada, 30); 
    lq_enqueue(&fila_encadeada, 40); 
    
    printf("Fila apos ENQ(30), ENQ(40): ");
    lq_imprimir(&fila_encadeada);

    if(lq_dequeue(&fila_encadeada, &valor)) { 
        printf("Valor removido: %d \n", valor); // Deve remover 20
    }
    if(lq_dequeue(&fila_encadeada, &valor)) { 
        printf("Valor removido: %d\n", valor); // Deve remover 30
    }
    
    printf("Adicionando 50...\n");
    lq_enqueue(&fila_encadeada, 50); 
    
    printf("Estado final da fila: ");
    lq_imprimir(&fila_encadeada);


    printf("\n\nTestes finalizados.\n\n");
    return 0;
}


