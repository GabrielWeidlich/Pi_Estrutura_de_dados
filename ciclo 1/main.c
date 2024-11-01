#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Product {
    char name[50];
    float price;
    int quantity;
} Product;

typedef struct Node {
    Product product;
    struct Node* next;
} Node;

Product createProduct(char* name, float price, int quantity) {
    Product p;
    strcpy(p.name, name);
    p.price = price;
    p.quantity = quantity;
    return p;
}

Node* addProduct(Node* list, Product product) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error!\n");
        return list;
    }
    newNode->product = product;
    newNode->next = list;
    return newNode;
}

Node* removeProduct(Node* list, char* name) {
    Node* current = list;
    Node* previous = NULL;

    while (current != NULL && strcmp(current->product.name, name) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Product %s not found.\n", name);
        return list;
    }

    if (previous == NULL) {
        list = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Product %s removed.\n", name);
    return list;
}

void printProducts(Node* list) {
    Node* current = list;
    printf("Product List:\n");
    while (current != NULL) {
        printf("Name: %s | Price: %.2f | Quantity: %d\n", 
                current->product.name, current->product.price, current->product.quantity);
        current = current->next;
    }
}

void freeList(Node* list) {
    Node* current = list;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Node* list = NULL;

    Product p1 = createProduct("Product 1", 10.5, 5);
    Product p2 = createProduct("Product 2", 20.0, 3);
    Product p3 = createProduct("Product 3", 15.75, 10);

    list = addProduct(list, p1);
    list = addProduct(list, p2);
    list = addProduct(list, p3);

    printProducts(list);

    list = removeProduct(list, "Product 2");

    printProducts(list);

    freeList(list);

    return 0;
}
