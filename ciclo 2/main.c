#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto {
    char nome[50];
    float preco;
    int quantidade;
} Produto;

typedef struct Nodo {
    Produto produto;
    struct Nodo* proximo;
    struct Nodo* anterior;
} Nodo;

Produto criarProduto(char* nome, float preco, int quantidade) {
    Produto p;
    strcpy(p.nome, nome);
    p.preco = preco;
    p.quantidade = quantidade;
    return p;
}

Nodo* adicionarProduto(Nodo* lista, Produto produto) {
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (novoNodo == NULL) {
        printf("Erro de alocação de memória!\n");
        return lista;
    }
    novoNodo->produto = produto;
    novoNodo->proximo = lista;
    novoNodo->anterior = NULL;
    if (lista != NULL) {
        lista->anterior = novoNodo;
    }
    return novoNodo;
}

Nodo* removerProduto(Nodo* lista, char* nome) {
    Nodo* atual = lista;

    while (atual != NULL && strcmp(atual->produto.nome, nome) != 0) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Produto %s não encontrado.\n", nome);
        return lista;
    }

    if (atual->anterior != NULL) {
        atual->anterior->proximo = atual->proximo;
    } else {
        lista = atual->proximo;
    }

    if (atual->proximo != NULL) {
        atual->proximo->anterior = atual->anterior;
    }

    free(atual);
    printf("Produto %s removido.\n", nome);
    return lista;
}

void imprimirProdutos(Nodo* lista) {
    Nodo* atual = lista;
    printf("Lista de Produtos:\n");
    while (atual != NULL) {
        printf("Nome: %s | Preço: %.2f | Quantidade: %d\n", 
               atual->produto.nome, atual->produto.preco, atual->produto.quantidade);
        atual = atual->proximo;
    }
}

void liberarLista(Nodo* lista) {
    Nodo* atual = lista;
    while (atual != NULL) {
        Nodo* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}

int main() {
    Nodo* lista = NULL;

    Produto produtos[] = {
        criarProduto("Produto 1", 10.5, 5),
        criarProduto("Produto 2", 20.0, 3),
        criarProduto("Produto 3", 15.75, 10),
        criarProduto("Produto 4", 5.25, 8),
        criarProduto("Produto 5", 12.0, 12),
        criarProduto("Produto 6", 7.5, 7),
        criarProduto("Produto 7", 11.3, 2),
        criarProduto("Produto 8", 22.1, 15),
        criarProduto("Produto 9", 8.0, 6),
        criarProduto("Produto 10", 3.3, 20),
        criarProduto("Produto 11", 9.5, 9),
        criarProduto("Produto 12", 13.5, 4),
        criarProduto("Produto 13", 18.0, 14),
        criarProduto("Produto 14", 16.75, 5),
        criarProduto("Produto 15", 4.5, 16),
        criarProduto("Produto 16", 10.75, 2),
        criarProduto("Produto 17", 6.5, 12),
        criarProduto("Produto 18", 14.0, 8),
        criarProduto("Produto 19", 19.0, 10),
        criarProduto("Produto 20", 5.8, 13)
    };

    for (int i = 0; i < 20; i++) {
        lista = adicionarProduto(lista, produtos[i]);
    }

    printf("Lista após adicionar produtos:\n");
    imprimirProdutos(lista);

    lista = removerProduto(lista, "Produto 2");
    lista = removerProduto(lista, "Produto 5");
    lista = removerProduto(lista, "Produto 10");
    lista = removerProduto(lista, "Produto 15");
    lista = removerProduto(lista, "Produto 18");

    printf("\nLista após remoção de produtos específicos:\n");
    imprimirProdutos(lista);

    lista = removerProduto(lista, "Produto 25");

    printf("\nLista final de produtos:\n");
    imprimirProdutos(lista);

    liberarLista(lista);

    return 0;
}