# 📚 Pilha Dinâmica Genérica em C

Uma implementação de **pilha dinâmica genérica** em C, utilizando **ponteiros de função** para simular conceitos de **orientação a objetos**. Esta estrutura permite armazenar qualquer tipo de dado, desde que seja passado via ponteiro, garantindo flexibilidade e reusabilidade.

---

## 🚀 Funcionalidades

A estrutura de pilha é manipulada por meio de ponteiros de função, permitindo chamadas no estilo `stack->push(...)`. As principais operações disponíveis são:

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

- **`destroy(stack, int free_data)`**  
  Libera todos os nós e a estrutura da pilha.  
  - Se `free_data == 1`, a função `destroy_data` será usada para liberar cada conteúdo armazenado.  
  - Se `free_data == 0`, os ponteiros de dados não serão alterados, apenas os nós e a pilha serão desalocados.

- **`destroy_data(void* data)`**  
  Ponteiro de função opcional que pode ser definido pelo usuário para liberar corretamente os dados da pilha.  
  Deve ser atribuído quando a pilha armazena estruturas complexas que exigem desalocação personalizada.

---

## 📦 Como compilar

Certifique-se de ter o `make` instalado. Para compilar o projeto:

```bash
make

