#include "person.h"
#include "debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void _show(struct Person* p);
static void _destroy(struct Person* p);

Person* newPerson(const char* first_name, const char* last_name, const int age) {
	Person* p = malloc(sizeof(Person));
	if (!p) {
		DEBUG_PRINT("%s: falha ao alocar memoria.\n", __func__);
		return NULL;
	}

	p->first_name = malloc(strlen(first_name) + 1);
	if (!p->first_name) {
		DEBUG_PRINT("%s: falha ao alocar memoria para first name.\n", __func__);
		free(p);
		return NULL;
	}
	strcpy(p->first_name, first_name);

	p->last_name = malloc(strlen(last_name) + 1);
	if (!p->last_name) {
		DEBUG_PRINT("%s: falha ao alocar memoria para last name.\n", __func__);
		free(p->first_name);
		free(p);
		return NULL;
	}
	strcpy(p->last_name, last_name);

	if (age < 0 || age > 120) {
		DEBUG_PRINT("%s: coloque a idade correta.\n", __func__);
		free(p->last_name);
		free(p->first_name);
		free(p);
		return NULL;
	}
	p->age = age;

	p->show = &_show;
	p->destroy = &_destroy;

	return p;
}

static void _show(Person* p) {
	if (!p) {
		DEBUG_PRINT("%s: ponteiro nulo para pessoa.\n", __func__);
		return;
	}
	printf("_show: Person first name: %s\nPerson last name: %s\nPerson age: %d\n", p->first_name, p->last_name, p->age);
}

static void _destroy(Person* p) {
	if (!p) {
		DEBUG_PRINT("%s: ponteiro nulo para pessoa.\n", __func__);
		return;
	}

	if (p->last_name) {
		free(p->last_name);
		p->last_name = NULL;
	}

	if (p->first_name) {
		free(p->first_name);
		p->first_name = NULL;
	}

	free(p);
}
