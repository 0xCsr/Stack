/* *
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
 * 	- Usa o método foreach para mostrar todas pessoas da pilha.
 * 	- Desempilha elementos da primeira pilha, liberando a memória.
 * 	- Verifica se a pilha está vazia ao final.
 * 	- Destrói a primeira pilha e seus dados restantes.
 * 	- Limpa a segunda pilha.
 * 	- Destrói a segunda pilha.
 * */

#include "stack.h"
#include "person.h"
#include "array.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
	char buffer_first_name[128];
	char buffer_last_name[128];

	Stack* stack = newStack(destroyPersonWrapper);
	Stack* stack2 = newStack(NULL);
	int* data;

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
		if (i == 1) {
			data = value;
		}	
		stack2->push(stack2, value);
	}
	
	printf("Tamanho da stack: %d\n", stack->size(stack));

	Person* peek = stack->peek(stack);
	if (peek) {
		peek->show(peek);
	}

	printf("\n\n\n");
	stack->foreach(stack, showPersonWrapper);	

	for (int i = 0; i < 3; i++) {
		if (!stack->isEmpty(stack)) {
			void* top = (Person*) stack->pop(stack);
			stack->destroy_data(top);
		}
	}

	int pos = stack2->search(stack2, data);
	printf("stack2: Posicao em %d\n", pos);
	
	Array* array = stack2->toArray(stack2);
	printf("Array criado a partir do stack\n");

	/*Node* temp = array[0];
	while (temp) {
		printf("Array: %d\n", *(int*)temp->data);
		temp = temp->next;
	}*/

	printf("A pilha está vazia? [%s]\n", (stack->isEmpty(stack) ? "sim" : "nao"));

	stack->destroy(stack, 1);
	array->destroy(array, 1);

	//stack2->clear(stack2, 1);
	printf("A segunda pilha está vazia? [%s]\n", (stack2->isEmpty(stack2)) ? "sim" : "nao");

	stack2->destroy(stack2, 0);

	return 0;
}
