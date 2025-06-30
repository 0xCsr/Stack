#pragma once

typedef struct Person {
	char* first_name;
	char* last_name;
	int age;

	void	(*show)(struct Person*);
	void	(*destroy)(struct Person*);
} Person;

Person* newPerson(const char*, const char*, const int);
void destroyPersonWrapper(Person* p); // <- Método da struct para ponteiro de função genérico do 'destroy_data' da pilha.
