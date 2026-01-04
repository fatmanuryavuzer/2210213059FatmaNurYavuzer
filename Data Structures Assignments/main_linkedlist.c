#include <stdio.h>
#include <stdlib.h>

/*
  HW3 - Singly Linked List (C)
  Ýçerik:
  - Liste oluþturma
  - Traversal (yazdýrma)
  - Ekleme: baþa, sona, araya (index)
  - Silme: baþtan, sondan, index'ten, deðere göre (ilk eþleþme)
  - Complexity notlarý (yorum satýrlarýnda)

  Not: index 0-based (0,1,2,...)
*/

typedef struct Node {
    int data;
    struct Node* next;
} Node;

/* ---------- Yardýmcý Fonksiyonlar ---------- */

/* O(1) */
Node* create_node(int x) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) {
        perror("malloc");
        exit(1);
    }
    n->data = x;
    n->next = NULL;
    return n;
}

/* Traversal / Print -> O(n) */
void print_list(const Node* head) {
    printf("[");
    while (head) {
        printf("%d", head->data);
        head = head->next;
        if (head) printf(" -> ");
    }
    printf("]\n");
}

/* Liste uzunluðu -> O(n) */
int length(const Node* head) {
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

/* ---------- Ekleme Ýþlemleri ---------- */

/* Baþa ekleme -> O(1) */
void insert_front(Node** head, int x) {
    Node* n = create_node(x);
    n->next = *head;
    *head = n;
}

/* Sona ekleme -> O(n) (tail tutulursa O(1) olur) */
void insert_back(Node** head, int x) {
    Node* n = create_node(x);

    if (*head == NULL) {
        *head = n;
        return;
    }

    Node* cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = n;
}

/*
  Ortaya ekleme (index'e):
  - index 0 ise baþa ekler
  - index >= len ise sona ekler
  Complexity: O(n) (düðümü bulmak için)
*/
void insert_at(Node** head, int index, int x) {
    if (index <= 0 || *head == NULL) {
        insert_front(head, x);
        return;
    }

    Node* cur = *head;
    int i = 0;

    /* cur, (index-1). düðüme ilerler */
    while (cur->next && i < index - 1) {
        cur = cur->next;
        i++;
    }

    Node* n = create_node(x);
    n->next = cur->next;
    cur->next = n;
}

/* ---------- Silme Ýþlemleri ---------- */

/* Baþtan silme -> O(1) */
int delete_front(Node** head) {
    if (*head == NULL) return 0;

    Node* tmp = *head;
    *head = (*head)->next;
    free(tmp);
    return 1;
}

/* Sondan silme -> O(n) */
int delete_back(Node** head) {
    if (*head == NULL) return 0;

    /* tek eleman */
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return 1;
    }

    Node* cur = *head;
    while (cur->next->next) cur = cur->next;

    free(cur->next);
    cur->next = NULL;
    return 1;
}

/*
  Index'ten silme (0-based)
  - index 0 -> baþtan siler
  Complexity: O(n)
*/
int delete_at(Node** head, int index) {
    if (*head == NULL || index < 0) return 0;

    if (index == 0) return delete_front(head);

    Node* cur = *head;
    int i = 0;

    while (cur->next && i < index - 1) {
        cur = cur->next;
        i++;
    }

    if (cur->next == NULL) return 0; /* index yok */

    Node* tmp = cur->next;
    cur->next = tmp->next;
    free(tmp);
    return 1;
}

/*
  Deðere göre silme (ilk eþleþen)
  Complexity: O(n)
*/
int delete_value(Node** head, int x) {
    if (*head == NULL) return 0;

    if ((*head)->data == x) {
        return delete_front(head);
    }

    Node* cur = *head;
    while (cur->next && cur->next->data != x) {
        cur = cur->next;
    }

    if (cur->next == NULL) return 0; /* bulunamadý */

    Node* tmp = cur->next;
    cur->next = tmp->next;
    free(tmp);
    return 1;
}

/* Tüm listeyi temizle -> O(n) */
void free_list(Node** head) {
    while (*head) {
        delete_front(head);
    }
}

/* ---------- Demo / Test ---------- */
int main(void) {
    Node* head = NULL;

    printf("=== Liste Olusturma (insert_back ile) ===\n");
    insert_back(&head, 10);
    insert_back(&head, 20);
    insert_back(&head, 30);
    print_list(head);
    printf("Length: %d\n\n", length(head));

    printf("=== Basa Ekleme (O(1)) ===\n");
    insert_front(&head, 5);
    print_list(head);

    printf("\n=== Sona Ekleme (O(n)) ===\n");
    insert_back(&head, 40);
    print_list(head);

    printf("\n=== Ortaya Ekleme (index=2) (O(n)) ===\n");
    insert_at(&head, 2, 15); /* [5,10,15,20,30,40] */
    print_list(head);

    printf("\n=== Silme: Bastan (O(1)) ===\n");
    delete_front(&head);
    print_list(head);

    printf("\n=== Silme: Sondan (O(n)) ===\n");
    delete_back(&head);
    print_list(head);

    printf("\n=== Silme: Index'ten (index=2) (O(n)) ===\n");
    delete_at(&head, 2);
    print_list(head);

    printf("\n=== Silme: Degere gore (x=20) (O(n)) ===\n");
    delete_value(&head, 20);
    print_list(head);

    printf("\n=== Traversal: Listeyi yazdirma zaten O(n) ===\n");

    printf("\n=== Free List ===\n");
    free_list(&head);
    print_list(head);

    return 0;
}

