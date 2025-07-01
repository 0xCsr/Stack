#pragma once
#include <stdio.h>

// Alterne isso para 0 ou 1. Para ativar as logs de depuração.
#define DEBUG 0

#if DEBUG
	#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
	#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif
