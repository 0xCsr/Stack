/*
 * main.c
 * Exemplo de uso da pilha genérica em stack.h.
 *
 * Autor: 0xCsr
 * Data: 30/06/2025
 *
 * Este programa:
 * 	- Cria uma pilha dinamicamente
 * 	- Insire 5 inteiros alocados dinamicamente
 * 	- Acessa o topo com peek
 * 	- Desempilha todos os elementos, liberando a memória.
 * 	- Verifica se a pilha está vazia ao final.
 * */

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	Stack* stack = newStack();
	if (!stack) return -1;

	for (int i = 0; i < 5; i++) {
		int* value = malloc(sizeof(int));
		if (!value) {
			stack->destroy(stack, 1);
			return -1;
		}
		*value = i * 10;
		stack->push(stack, value);
	}

	int* peek = stack->peek(stack);
	if (peek) {
		printf("Valor do pico: %d\n", *peek);
	}

	while (!stack->isEmpty(stack)) {
		int* data = (int*)stack->pop(stack);	
		if (data) {
			printf("Pop: %d\n", *data);
			free(data);
		}
	}

	printf("A pilha está vazia? [%s]\n", (stack->isEmpty(stack) ? "sim" : "nao"));

	stack->destroy(stack, 0);
	return 0;
}
