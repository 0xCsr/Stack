/* *
 * stack.c
 * Implementação de uma pilha dinâmica genérica em C.
 *
 * Autor: @0xCsr
 * Data: 30/06/2025
 * 
 * Esta pilha suporta operações básicas, como:
 * 	- push: adiciona elemento ao topo,
 * 	- pop: retira um elemento do topo e retorna o mesmo,
 * 	- peek: acessa o elemento do topo e retorna,
 * 	- isEmpty: verifica se a pilha está vazia,
 * 	- destroy: destrói a pilha, liberando memória, com a opção de liberar também os dados (freeData).
 * 	- size: retorna a quantidade de elementos da pilha.
 * 	- clear: limpa todos elementos da pilha. Mas não desaloca a pilha.
 * 	- foreach: percorre toda a pilha e também faz chamada por (*callback).
 * */

#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "stack.h"

static void _push(Stack* stack, void* data);
static void* _pop(Stack* stack);
static int _isEmpty(Stack* stack);
static void _destroy(Stack* stack, int freeData);
static void* _peek(Stack* stack);
static int _size(Stack* stack);
static void _clear(Stack* stack, int);
static void _foreach(Stack* stack, void (*callback)(void*));

// Cria uma nova pilha (stack) e inicializa seus métodos através dos ponteiros de função.
Stack* newStack(void (*destroy_data)(void*)) {
	Stack* stack = malloc(sizeof(Stack));
	
	if (!stack) {
		DEBUG_PRINT("%s: falha ao alocar memoria.\n", __func__);
		return NULL;
	}

	stack->top = NULL;
	stack->count = 0;

	stack->destroy_data = destroy_data;
	stack->push = &_push;
	stack->pop = &_pop;
	stack->isEmpty = &_isEmpty;
	stack->destroy = &_destroy;
	stack->peek = &_peek;
	stack->size = &_size;
	stack->clear = &_clear;
	stack->foreach = &_foreach;

	return stack;
}

// Adiciona um elemento ao topo da lista, não faz cópia desse dado, apenas armazena o ponteiro do conteúdo.
static void _push(Stack* stack, void* data) {
	if (!stack) {
		DEBUG_PRINT("%s: ponteiro nulo para stack.\n", __func__);
		return;
	}

	Node* node = malloc(sizeof(Node));
	if (!node) {
		DEBUG_PRINT("%s: falha ao alocar memoria para node.\n", __func__);
		return;
	}

	node->data = data;
	node->next = stack->top;
	stack->top = node;
	stack->count++;

	DEBUG_PRINT("%s: no adicionado com sucesso.\n", __func__);
}

// Remove e retorna o elemento do topo da pilha.
static void* _pop(Stack* stack) {
	if (!stack) {
		DEBUG_PRINT("%s: ponteiro nulo para stack.\n", __func__);
		return NULL;
	}

	Node* temp = stack->top;
	if (!temp) {
		DEBUG_PRINT("%s: o topo esta vazio.\n", __func__);
		return NULL;
	}

	void* data = temp->data;
	stack->top = stack->top->next;
	stack->count--;

	free(temp);

	DEBUG_PRINT("%s: node removido do topo com sucesso.\n", __func__);
	return data;
}

// Checa se a pilha está vazia.
// Se tiver retorna 1, se não 0.
static int _isEmpty(Stack* stack) {
	if (!stack) {
		DEBUG_PRINT("%s: ponteiro nulo para stack.\n", __func__);
		return 1;
	}

	return (!stack->top) ? 1 : 0;
}

// Destrói a pilha liberando todos seus nós.
// Se a variavel 'freeData' for 1, libera também o conteúdo que os nós apontavam.
//
//			ATENÇÃO
//	Caso os dados apontados não tenham sido alocados
//	dinamicamente, por exemplo: variáveis locais.
//	Jamais utilize o 'freeData' igual a 1. Pois isso
//	vai causar comportamentos indefinido ao tentar
//		liberar a memória não alocada.
static void _destroy(Stack* stack, int freeData) {
	if (!stack) {
		DEBUG_PRINT("%s: ponteiro nulo para stack.\n", __func__);
		return;
	}

	while (!stack->isEmpty(stack)) {
		Node* temp = stack->top;
		stack->top = stack->top->next;

		if (temp->data && freeData && stack->destroy_data) {
			stack->destroy_data(temp->data);
		} else if (temp->data && freeData && !stack->destroy_data) {
			free(temp->data);
			temp->data = NULL;
		}
		
		free(temp);
		temp = NULL;
	}
	
	free(stack);
	stack = NULL;

	DEBUG_PRINT("%s: stack deletada com sucesso.\n", __func__);
}

// Retorna o conteúdo do topo da pilha.
static void* _peek(Stack* stack) {
	if (!stack) {
		DEBUG_PRINT("%s: ponteiro nulo para stack.\n", __func__);
		return NULL;
	}

	if (stack->isEmpty(stack)) {
		DEBUG_PRINT("%s: a stack esta vazia.\n", __func__);
		return NULL;
	}

	DEBUG_PRINT("%s: topo da stack acessado com sucesso.\n", __func__);
	return stack->top->data;
}

// Retorna a quantidade de elementos na stack.
static int _size(Stack* stack) {
	if (!stack) {
		DEBUG_PRINT("%s: ponteiro nulo para stack.\n", __func__);
		return 0;
	}

	return (stack) ? stack->count : 0;
}

// Limpa a stack por completo mas não faz desalocação.
static void _clear(Stack* stack, int freeData) {
	if (!stack) {
		DEBUG_PRINT("%s: ponteiro nulo para stack.\n", __func__);
		return;
	}

	if (stack->isEmpty(stack)) {
		DEBUG_PRINT("%s: a stack ja esta vazia.\n", __func__);
		return;
	}

	while (!stack->isEmpty(stack)) {
		Node* temp = stack->top;
		stack->top = temp->next;

		if (temp->data && freeData && stack->destroy_data) {
			stack->destroy_data(temp->data);
		} else if (temp->data && freeData) {
			free(temp->data);
		}

		free(temp);
	}

	stack->count = 0;
	DEBUG_PRINT("%s: stack limpa com sucesso.\n", __func__);
}

// Percorre todos os nós da pilha e chama um ponteiro de função.
static void _foreach(Stack* stack, void (*callback)(void* data)) {
	if (!stack) {
		DEBUG_PRINT("%s: ponteiro nulo para stack.\n", __func__);
		return;
	}

	if (stack->isEmpty(stack)) {
		DEBUG_PRINT("%s: a pilha esta vazia.\n", __func__);
		return;
	}

	if (!callback) {
		DEBUG_PRINT("%s: callback nulo.\n", __func__);
		return;
	}

	Node* current = stack->top;
	while (current) {
		callback(current->data);
		current = current->next;
	}

	DEBUG_PRINT("%s: loop concluido com sucesso.\n", __func__);
}
