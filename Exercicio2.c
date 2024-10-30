#include <stdio.h>
#include <stdlib.h>

struct celula {
    int idade;
    float altura;
    struct celula *prox;  
    struct celula *ant;   
};

void inicializa_celula(struct celula *ptr, int idade, float altura) {
    ptr->idade = idade;
    ptr->altura = altura;
    ptr->prox = NULL;
    ptr->ant = NULL;
}

void exclui_celula(struct celula **head, int idade) {
    struct celula *current = *head;

    while (current != NULL && current->idade != idade) {
        current = current->prox;
    }

    if (current == NULL) {
        printf("Nó com idade %d não encontrado.\n", idade);
        return;
    }

    if (current->ant != NULL) {
        current->ant->prox = current->prox;
    } else {
        *head = current->prox;
    }
    if (current->prox != NULL) {
        current->prox->ant = current->ant;
    }

    free(current);
    printf("Nó com idade %d excluído.\n", idade);
}

void imprime_lista(struct celula *head) {
    struct celula *current = head;
    int index = 0;
    while (current != NULL) {
        printf("Célula %d: Idade = %d, Altura = %.2f\n", index, current->idade, current->altura);
        current = current->prox;
        index++;
    }
}

int main() {
    struct celula *head = NULL;
    struct celula *temp = NULL;
    struct celula *prev = NULL;

    for (int i = 0; i < 10; i++) {
        temp = (struct celula*) malloc(sizeof(struct celula));
        if (temp == NULL) {
            fprintf(stderr, "Falha na alocação de memória\n");
            return 1;
        }
        inicializa_celula(temp, 20 + i, 1.60 + (0.05 * i));
        
        if (head == NULL) {
            head = temp;
        } else {
            prev->prox = temp;
            temp->ant = prev;
        }
        prev = temp;
    }

    printf("Lista original:\n");
    imprime_lista(head);

    int idade_para_excluir;
    printf("\nDigite a idade do nó a ser excluído: ");
    scanf("%d", &idade_para_excluir);
    exclui_celula(&head, idade_para_excluir);

    printf("\nLista após exclusão:\n");
    imprime_lista(head);

    struct celula *current = head;
    struct celula *next;
    while (current != NULL) {
        next = current->prox;
        free(current);
        current = next;
    }

    return 0;
}
