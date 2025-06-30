#pragma once

typedef struct Node {
	void* data;
	struct Node* next;
} Node;

typedef struct Stack {
	struct Node* top;

	// Aqui estão os ponteiros de função.
	// Caso queira adicionar novas funções a pilha,
	// basta seguir esse modelo e implementar a sua lógica.
	// Lembre-se de alterar o método 'construtor' (newStack())
	// da pilha para receber os novos ponteiros de função.
	void	(*push)(struct Stack*, void*);
	void*	(*pop)(struct Stack*);
	int	(*isEmpty)(struct Stack*);
	void	(*destroy)(struct Stack*, int);
	void*	(*peek)(struct Stack*);
} Stack;

Stack* newStack();
