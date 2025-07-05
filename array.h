#pragma once

#include "stack.h"

typedef struct Array {
	void** items;
	int capacity;
	int quantity;

	void 	(*destroy)(struct Array*, int);
	void	(*add)(struct Array*, void*);
	void	(*remove)(struct Array*, int, int);
	void	(*sort)(struct Array*);
	
	struct Stack*	(*toStack)(struct Array*);

	void	(*destroy_data)(void*);
	int	(*compare)(const void*, const void*);
} Array;

Array* newArray(void (*destroy_data)(void*), int (*compare)(const void*, const void*));
