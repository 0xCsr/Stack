# Pilha Dinâmica Genérica em C

Implementação de uma pilha dinâmica genérica com uso de ponteiros de função. Simulando conceitos de orientação a objetos em C.  

## Funcionalidades:

    stack->push(stack, (ponteiro para o conteudo)): Adiciona o ponteiro do conteudo no topo da stack.

    stack->pop(stack): Retorna um ponteiro para o conteudo do topo da pilha e desaloca o nó que guardava o conteúdo.
    
    stack->isEmpty(stack): Retorna 0 ou 1 para verificar se a pilha está vazia.
    
    stack->destroy(stack, (0 ou 1)): Destroi a pilha, caso o valor seja 0, não limpa os dados, apenas a pilha e os nós. Caso seja 1, limpa tudo através do ponteiro de função 'destroy_data'.
    
    stack->peek(stack): Retorna o último elemento do topo.
    
    stack->size(stack): Retorna a quantidade de elementos da pilha.
    
    stack->destroy_data(ponteiro de conteúdo): É utilizado dentro do 'destrutor' da pilha. Para utilizar, basta passar o ponteiro de função do destrutor da sua struct.

---

## Como compilar

Use o `make` para compilar o projeto:

```bash
make

