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

// Cria uma nova pilha (stack) e inicializa seus métodos através dos ponteiros de função.
Stack* newStack() {
	Stack* stack = malloc(sizeof(Stack));
	
	if (!stack) {
		DEBUG_PRINT("%s: falha ao alocar memoria.\n", __func__);
		return NULL;
	}

	stack->top = NULL;
	stack->push = &_push;
	stack->pop = &_pop;
	stack->isEmpty = &_isEmpty;
	stack->destroy = &_destroy;
	stack->peek = &_peek;

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
//					ATENÇÃO
//			Caso os dados apontados não tenham sido alocados
//			dinamicamente, por exemplo: variáveis locais.
//			Jamais utilize o 'freeData' igual a 1. Pois isso
//			vai causar comportamentos indefinido ao tentar
//				liberar a memória não alocada.
static void _destroy(Stack* stack, int freeData) {
	if (!stack) {
		DEBUG_PRINT("%s: ponteiro nulo para stack.\n", __func__);
		return;
	}

	while (stack->top) {
		Node* temp = stack->top;
		stack->top = stack->top->next;

		if (temp->data && freeData) {
			free(temp->data);
		}
		
		free(temp);
	}
	
	free(stack);
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
