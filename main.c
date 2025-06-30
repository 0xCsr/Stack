/*
 * main.c
 * Exemplo de uso da pilha genérica em stack.h.
 *
 * Autor: 0xCsr
 * Data: 30/06/2025
 *
 * Este programa:
 * 	- Cria uma pilha dinamicamente
 * 	- Insire 5 pessoas alocadas dinamicamente na pilha
 * 	- Acessa o topo com peek
 * 	- Desempilha todos os elementos, liberando a memória.
 * 	- Verifica se a pilha está vazia ao final.
 * */

#include "stack.h"
#include "person.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
	char buffer_first_name[128];
	char buffer_last_name[128];

	Stack* stack = newStack();
	if (!stack) return -1;

	for (int i = 1; i <= 5; i++) {
		sprintf(buffer_first_name, "%d", i * 3);
		sprintf(buffer_last_name, "%d", i * 5);
		Person* p = newPerson(buffer_first_name, buffer_last_name, i);
		if (!p) {
			return -1;
		}
		stack->push(stack, p);
	}

	Person* peek = stack->peek(stack);
	if (peek) {
		peek->show(peek);
	}

	while (!stack->isEmpty(stack)) {
		Person* data = (Person*)stack->pop(stack);	
		if (data) {
			printf("Pop: first_name: %s\tlast_name: %s\tage: %d\n", data->first_name, data->last_name, data->age);
			//free(data);
			data->destroy(data);
		}
	}

	printf("A pilha está vazia? [%s]\n", (stack->isEmpty(stack) ? "sim" : "nao"));

	stack->destroy(stack, 0);
	return 0;
}
