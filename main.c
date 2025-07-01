/*
 * main.c
 * Exemplo de uso da pilha genérica em stack.h.
 *
 * Autor: 0xCsr
 * Data: 30/06/2025
 *
 * Este programa:
 * 	- Cria duas pilhas dinamicamente.
 * 	- Insire 5 pessoas alocadas dinamicamente na primeira pilha.
 * 	- Insere 5 inteiros alocados dinamicamente na segunda pilha.
 * 	- Acessa o topo da primeira pilha com peek.
 * 	- Desempilha elementos da primeira pilha, liberando a memória.
 * 	- Verifica se a pilha está vazia ao final.
 * 	- Destrói a primeira pilha e seus dados restantes.
 * 	- Limpa a segunda pilha.
 * 	- Destrói a segunda pilha.
 * */

#include "stack.h"
#include "person.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
	char buffer_first_name[128];
	char buffer_last_name[128];

	Stack* stack = newStack(destroyPersonWrapper);
	Stack* stack2 = newStack(NULL);

	if (!stack) return -1;

	for (int i = 1; i <= 5; i++) {
		sprintf(buffer_first_name, "%d", i * 3);
		sprintf(buffer_last_name, "%d", i * 5);
		Person* p = newPerson(buffer_first_name, buffer_last_name, i);
		if (!p) {
			return -1;
		}
		stack->push(stack, p);

		int* value = malloc(sizeof(int));
		*value = i + 1;
		stack2->push(stack2, value);
	}
	
	printf("Tamanho da stack: %d\n", stack->size(stack));

	Person* peek = stack->peek(stack);
	if (peek) {
		peek->show(peek);
	}

	for (int i = 0; i < 3; i++) {
		if (!stack->isEmpty(stack)) {
			void* top = (Person*) stack->pop(stack);
			stack->destroy_data(top);
		}
	}

	printf("A pilha está vazia? [%s]\n", (stack->isEmpty(stack) ? "sim" : "nao"));

	stack->destroy(stack, 1);

	stack2->clear(stack2, 1);
	stack2->destroy(stack2, 0);

	return 0;
}
