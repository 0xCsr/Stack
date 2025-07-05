/*
 * array.c
 * Implementação de um array dinâmico genérico em C.
 *
 * Autor: @0xCsr
 * Data: 04/07/2025
 *
 * Este array suporta operações básicas, como:
 * 	- destroy: destrói o array, liberando a memória, com a opção tammbém de liberar os dados com freeData.
 * 	- add: adiciona um ponteiro de conteudo ao array e também já cuida da realocação de memória, se precisar.
 * 	- remove: remove um ponteiro de conteudo do array e também já cuida da realocão de memória, se precisar.
 * 	- sort: ordena o array usando qsort(), mas pode-se implementar um sort manual usando o ponteiro 'compare'.
 *
 *	- Atenção, caso migre um stack para array, atente-se que o 'destroy_data' da stack, vai ser atribuido também ao array. 
 * */

#include "array.h"
#include "debug.h"

#include <stdio.h>
#include <stdlib.h>

static void _destroy(Array* array, int freeData);
static void _add(Array* array, void* data);
static void _remove(Array* array, int position, int freeData);
static void _sort(Array* array);
static void _grow(Array* array);
static void _shrink(Array* array);
static Stack* _toStack(Array* array);

// Cria um novo array e inicializa seus métodos através dos ponteiros de função.
// Caso não queira adicionar um 'destroy_data' ou 'compare' baste preencher os campos com NULL.
Array* newArray(void (*destroy_data)(void*), int (*compare)(const void*, const void*)) {
	Array* array = malloc(sizeof(Array));
	if (!array) {
		DEBUG_PRINT("%s: falha ao alocar memoria para array.\n", __func__);
		return NULL;
	}
	
	array->capacity = 2;
	array->quantity = 0;
	array->destroy_data = destroy_data;
	array->compare = compare;

	array->items = malloc(array->capacity * sizeof(void*));
	if (!array->items) {
		DEBUG_PRINT("%s: falha ao alocar memoria para data.\n", __func__);
		free(array);
		return NULL;
	}

	array->destroy = &_destroy;
	array->add = &_add;
	array->remove = &_remove;
	array->sort = &_sort;
	array->toStack = &_toStack;

	return array;
}

// Destrói o array, liberando todos seus datas.
// Se a variavel 'freeData' for 1, libera também o conteúdo do array.
static void _destroy(Array* array, int freeData) {
	if (!array) {
		DEBUG_PRINT("%s: ponteiro nulo para array.\n", __func__);
		return;
	}

	for (size_t i = 0; i < (size_t)array->quantity; i++) {
		void* temp = array->items[i];
		
		if (temp && freeData && array->destroy_data) {
			array->destroy_data(array->items[i]);
		} else if (temp && freeData && !array->destroy_data) {
			free(temp);
		}	
	}

	free(array->items);
	free(array);
	DEBUG_PRINT("%s: array deletado com sucesso.\n", __func__);
}

// Adiciona no array o ponteiro passado para função.
static void _add(Array* array, void* data) {
	if (!array) {
		DEBUG_PRINT("%s: ponteiro nulo para array.\n", __func__);
		return;
	}

	if (!data) {
		DEBUG_PRINT("%s: ponteiro nulo para data.\n", __func__);
		return;
	}

	if (array->quantity >= array->capacity) {
		_grow(array);	
	}
	
	array->items[array->quantity++] = data;
	DEBUG_PRINT("%s: conteudo adicionado com sucesso.\n", __func__);
}

// Remove o conteudo do array dado a sua posição, e também pode-se passar o 'freeData' para liberar a memória do conteúdo.
static void _remove(Array* array, int position, int freeData) {
	if (!array) {
		DEBUG_PRINT("%s: ponteiro nulo para array.\n", __func__);
		return;
	}

	if (position < 0 || position >= array->quantity) {
		DEBUG_PRINT("%s: index invalido para acesso de conteudo no array.\n", __func__);
		return;
	}

	if (array->items[position]) {
		if (array->destroy_data && freeData) {
			array->destroy_data(array->items[position]);
		} else if (freeData) {
			free(array->items[position]);
		}
	}
	
	for (size_t i = position; i < (size_t)array->quantity - 1; i++) {
		array->items[i] = array->items[i + 1];
	}

	array->items[array->quantity - 1] = NULL;
	array->quantity--;

	if (array->capacity > 2 && array->quantity < array->capacity / 4) {
		_shrink(array);
	}
}

// Usar apenas se tiver alocado ponterios de valores no 'nodes->data', ex: (int*, float*, double*, long*);
static void _sort(Array* array) {
	if (!array) {
		DEBUG_PRINT("%s: ponteiro nulo para array.\n", __func__);
		return;
	}

	if (!array->compare) {
		DEBUG_PRINT("%s: funcao de comparacao nao definida.\n", __func__);
		return;
	}

	qsort(array->items, array->quantity, sizeof(void*), array->compare);	
	
}

// Cuida da realocação para aumentar o tamanho do array.
static void _grow(Array* array) {
	if (!array) {
		DEBUG_PRINT("%s: ponteiro nulo para array.\n", __func__);
		return;
	}


	int tempCapacity = array->capacity * 2;

	void** temp = realloc(array->items, tempCapacity * sizeof(void*));
	if (!temp) {
		DEBUG_PRINT("%s: falha ao realocar memoria para items.\n", __func__);
		return;
	}

	array->capacity = tempCapacity;
	array->items = temp;
}

// Cuida da realocação para diminuir o tamanho do array.
static void _shrink(Array* array) {
	if (!array) {
		DEBUG_PRINT("%s: ponteiro nulo para array.\n", __func__);
		return;
	}

	int tempCapacity = array->capacity / 2;

	void** temp = realloc(array->items, tempCapacity * sizeof(void*));
	if (!temp) {
		DEBUG_PRINT("%s: falha ao realocar memoria para items.\n", __func__);
		return;
	}

	array->capacity = tempCapacity;
	array->items = temp;
}

static Stack* _toStack(Array* array) {
	if (!array) {
		DEBUG_PRINT("%s: ponteiro nulo para array.\n", __func__);
		return NULL;
	}

	Stack* stack = newStack(array->destroy_data);
	if (!stack) {
		DEBUG_PRINT("%s: falha ao criar stack.\n", __func__);
		return NULL;
	}

	for (int i = array->quantity - 1; i >= 0; i--) {
		if (array->items[i] != NULL) {
			stack->push(stack, array->items[i]);
		}
	}

	DEBUG_PRINT("%s: stack criada com sucesso.\n", __func__);
	return stack;
}
