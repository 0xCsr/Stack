#pragma once

typedef struct Person {
	char* first_name;
	char* last_name;
	int age;

	void	(*show)(struct Person*);
	void	(*destroy)(struct Person*);
} Person;

Person* newPerson(const char*, const char*, const int);

void destroyPersonWrapper(void*);
void showPersonWrapper(void*);
