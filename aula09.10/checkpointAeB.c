#include <stdio.h>
#include <stdlib.h>

#define CAP 3 


// Define a estrutura da fila
typedef struct {
    int f[CAP];
    int head;
    int tail;
    int size;
} Fila;

// Inicializa a fila
void init(Fila* q) {
    q->head = 0;
    q->tail = 0;
    q->size = 0;
}


// Verifica se a fila está vazia
int is_empty(Fila* q) {
    return q->size == 0;
}


// Verifica se a fila está cheia
int is_full(Fila* q) {
    return q->size == CAP;
}


// Insere um elemento no fim da fila
int enqueue(Fila* q, int x) {
    if (is_full(q)) {
        return 0; // Erro: overflow
    }
    q->f[q->tail] = x;
    q->tail = (q->tail + 1) % CAP;
    q->size++;
    return 1;
}


// Remove um elemento do início da fila
int dequeue(Fila* q, int* out) {
    if (is_empty(q)) {
        return 0; // Erro: underflow
    }
    *out = q->f[q->head];
    q->head = (q->head + 1) % CAP;
    q->size--;
    return 1;
}


// Olha o próximo elemento da fila sem remover
int front(Fila* q, int* out) {
    if (is_empty(q)) {
        return 0;
    }
    *out = q->f[q->head];
    return 1;
}


// Imprime os elementos da fila
void imprimir(Fila* q) {
    if (is_empty(q)) {
        printf("Fila vazia.");
    }
    // Itera do 'head' até o 'tail' respeitando a circularidade
    for (int i = 0; i < q->size; i++) {
        int index = (q->head + i) % CAP;
        printf("%d ", q->f[index]);
    }
    printf("\n");
}

// Esvazia a fila (Array) em tempo O(1)
void clear(Fila* q) {
    q->head = 0;
    q->tail = 0;
    q->size = 0;
}

// Retorna a quantidade atual de elementos na fila (O(1)) 
int size(Fila* q){
    return q->size;
}




int main() {
    int valor; // Variável para receber o valor do dequeue


    //teste 1:
    printf("Teste 1:\n\n");
    Fila fila_arr;
    init(&fila_arr);


    enqueue(&fila_arr, 10);
    enqueue(&fila_arr, 20);
    printf("\nEstado atual da fila: ");
    imprimir(&fila_arr);

    dequeue(&fila_arr, &valor);
    enqueue(&fila_arr, 30);
    printf("\nEstado atual da fila: ");
    imprimir(&fila_arr);

    dequeue(&fila_arr, &valor);
    enqueue(&fila_arr, 1);

    front(&fila_arr,&valor);
    printf("\nOlhando o proximo elemento com front: %d\n", valor);
    
    printf("\nLimpando a lista para iniciar teste 2...\n\n");
    clear(&fila_arr);


    //teste 2:
    printf("\nTeste 2:\n\n");
    enqueue(&fila_arr, 5);
    printf("\nEstado atual da fila: ");
    imprimir(&fila_arr);

    if (dequeue(&fila_arr, &valor)) {
        printf("Valor removido: %d\n", valor);
    }
    printf("\nEstado atual da fila: ");
    imprimir(&fila_arr);

    if (!dequeue(&fila_arr, &valor)) {
        printf("Falha ao remover.\n");
    }
    printf("\nEstado atual da fila: ");
    imprimir(&fila_arr);

    printf("A fila esta vazia? %s \n", is_empty(&fila_arr) ? "Verdadeiro" : "Falso");

    printf("\nEstado final da fila: ");
    imprimir(&fila_arr);

    printf("\nLimpando a lista para iniciar teste 3...\n\n");
    clear(&fila_arr);

    //teste 3:
    printf("\nTeste 3:\n\n");

    printf("Enfileirando 1, 2, 3...\n");
    enqueue(&fila_arr, 1);
    enqueue(&fila_arr, 2);
    enqueue(&fila_arr, 3);
    printf("   Fila atual: ");
    imprimir(&fila_arr);
    printf("\n");

    printf("Tentando enfileirar 4...\n");
    if (!enqueue(&fila_arr, 4)) {
        printf("   Falha ao inserir 4.\n");
    }
    printf("Verificando se a fila esta cheia...\n");
    printf("   A fila esta cheia? %s \n", is_full(&fila_arr) ? "Verdadeiro" : "Falso");
    printf("\n");


    printf("\nLimpando a lista para iniciar teste 4...\n\n");
    clear(&fila_arr);

    //teste 4:
    printf("\nTeste 4:\n\n");

    printf("Enfileirando A,B...\n");
    enqueue(&fila_arr, 10); 
    enqueue(&fila_arr, 20);

    printf("Fila apos ENQ(10), ENQ(20): ");
    imprimir(&fila_arr);
    printf("\n");


    if(dequeue(&fila_arr, &valor)) { 
        printf("Valor removido: %d \n", valor);
    }
    
    printf("Enfileirando C, D...\n");
    enqueue(&fila_arr, 30); 
    enqueue(&fila_arr, 40); 
    
    printf("Fila apos ENQ(30), ENQ(40): ");
    imprimir(&fila_arr);
    printf("\n");

    if(dequeue(&fila_arr, &valor)) { 
        printf("Valor removido: %d \n", valor);
    }
    if(dequeue(&fila_arr, &valor)) { 
        printf("Valor removido: %d\n", valor);
    }
    
    printf("Adicionando 50... ");
    enqueue(&fila_arr, 50); 
    
    printf("Estado final da fila: ");
    imprimir(&fila_arr);


    printf("\n\n\n\n");
    return 0;
    }

