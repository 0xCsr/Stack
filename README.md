# 📚 Pilha Dinâmica Genérica em C

Uma implementação de **pilha dinâmica genérica** em C, utilizando **ponteiros de função** para simular conceitos de **orientação a objetos**. Esta estrutura permite armazenar qualquer tipo de dado, desde que seja passado via ponteiro, garantindo flexibilidade e reusabilidade.

---

## 🚀 Funcionalidades

A pilha é manipulada por ponteiros de função, permitindo chamadas como `stack->push(...)`. As operações principais são:

- **`newStack(void (*destroy_data)(void*))`**
  Cria uma stack, atribui o ponteiro personalizado de destruição de conteúdo do ponteiro.
  Caso não queira utilizar, basta chamar a função usando `NULL`.

- **`push(stack, void* data)`**  
  Insere um novo elemento no topo da pilha. O dado é armazenado por referência (ponteiro).

- **`pop(stack)`**  
  Remove o elemento do topo da pilha e retorna o ponteiro para os dados. O nó correspondente é desalocado.

- **`peek(stack)`**  
  Retorna o ponteiro para o elemento do topo, sem removê-lo.

- **`isEmpty(stack)`**  
  Retorna `1` se a pilha estiver vazia, ou `0` caso contrário.

- **`size(stack)`**  
  Retorna o número de elementos atualmente armazenados na pilha.

- **`destroy(stack, int freeData)`**  
  Libera todos os nós e a estrutura da pilha.  
  - Se `freeData == 1`, a função `destroy_data` será usada para liberar cada conteúdo armazenado.  
  - Se `freeData == 0`, os ponteiros de dados não serão alterados, apenas os nós e a pilha serão desalocados.

- **`destroy_data(void* data)`**  
  Ponteiro de função opcional que pode ser definido pelo usuário para liberar corretamente os dados da pilha.  
  Deve ser atribuído quando a pilha armazena estruturas complexas que exigem desalocação personalizada.

- **`clear(stack, int freeData)`**
  Limpa todos os nós da pilha.
  - Se `freeData == 1`, a função `clear` será usada para liberar cada conteúdo armazeado através do ponteiro de função `destroy_data`.
  - Se `freeData == 0`, os ponteiros de dados não serão alterados, apenas os nós serão desalocados.

- **`foreach(stack, void (*callback)(void*))`**
  Percorre todos os elementos da pilha e faz uma chamada de função através de um ponteiro.

---

## 📦 Como compilar

Certifique-se de ter o `make` instalado. Para compilar o projeto:

```bash
make

