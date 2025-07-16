#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct Book {
    int id;
    char title[MAX_LENGTH];
    char author[MAX_LENGTH];
    char category[50];
    float price;
} Book;

typedef struct NodeSLL {
    Book book;
    struct NodeSLL *next;
} NodeSLL;

typedef struct NodeDLL {
    Book book;
    struct NodeDLL *next;
    struct NodeDLL *prev;
} NodeDLL;

void showMenu() {
    printf("----- BOOK  MANAGER -----\n");
    printf("1. Them sach\n");
    printf("2. Hien thi danh sach tat ca quyen sach\n");
    printf("3. Xoa sach\n");
    printf("4. Cap nhat thong tin mot quyen sach\n");
    printf("5. Danh dau sach da doc xong\n");
    printf("6. Sap xep danh sach theo gia tang dan\n");
    printf("7. Tim kiem sach theo tieu de\n");
    printf("8. Thoat chuong trinh\n");
}

NodeSLL *addNode(Book book) {
    NodeSLL *newNode = (NodeSLL *) malloc(sizeof(NodeSLL));
    newNode->book = book;
    newNode->next = NULL;
    return newNode;
}

NodeDLL *addNodeDLL(Book book) {
    NodeDLL *newNode = (NodeDLL *) malloc(sizeof(NodeDLL));
    newNode->book = book;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

NodeSLL *addBook(NodeSLL *head) {
    Book book;
    printf("Nhap id: ");
    scanf("%d", &book.id);
    getchar();

    printf("Nhap ten sach: ");
    fgets(book.title, MAX_LENGTH, stdin);
    book.title[strcspn(book.title, "\n")] = 0;

    printf("Nhap ten tac gia: ");
    fgets(book.author, MAX_LENGTH, stdin);
    book.author[strcspn(book.author, "\n")] = 0;

    printf("Nhap the loai: ");
    fgets(book.category, 50, stdin);
    book.category[strcspn(book.category, "\n")] = 0;

    printf("Nhap gia sach: ");
    scanf("%f", &book.price);

    NodeSLL *newNode = addNode(book);
    newNode->next = head;
    return newNode;
}

void printBook(NodeSLL *head) {
    NodeSLL *temp = head;
    while (temp != NULL) {
        printf("Id: %d | Title: %s | Author: %s | Category: %s | Price: %.3f \n", temp->book.id, temp->book.title,
               temp->book.author, temp->book.category, temp->book.price);
        temp = temp->next;
    }
}

NodeSLL *deleteBook(NodeSLL *head) {
    int idDelete;
    printf("Nhap id de xoa: ");
    scanf("%d", &idDelete);
    NodeSLL *temp = head;
    NodeSLL *prev = NULL;

    while (temp && temp->book.id != idDelete) {
        prev = temp;
        temp = prev->next;
    }

    if (!temp) {
        printf("Khong tim thay quyen sach!\n");
        return temp;
    }

    if (!prev) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Xoa quyen sach thanh cong!\n");
    return head;
}

void updateBook(NodeSLL *head) {
    int idUpdate;
    printf("Nhap id can cap nhat: ");
    scanf("%d", &idUpdate);

    NodeSLL *temp = head;
    while (temp && temp->book.id != idUpdate) {
        temp = temp->next;
    }

    if (!temp) {
        printf("Quyen sach khong ton tai");
        return;
    }
    getchar();

    printf("Nhap ten quyen sach moi: ");
    fgets(temp->book.title, MAX_LENGTH, stdin);
    temp->book.title[strcspn(temp->book.title, "\n")] = 0;

    printf("Nhap ten tac gia moi: ");
    fgets(temp->book.author, MAX_LENGTH, stdin);
    temp->book.author[strcspn(temp->book.author, "\n")] = 0;

    printf("Nhap the loai moi: ");
    fgets(temp->book.category, 50, stdin);
    temp->book.category[strcspn(temp->book.category, "\n")] = 0;

    printf("Nhap gia sach moi: ");
    scanf("%f", &temp->book.price);

    printf("Cap nhat quyen sach thanh cong!");
    printf("\n");
}

NodeDLL *markBook(NodeSLL **head, NodeDLL *dHead) {
    int id;
    printf("Nhap id sach da doc xong: ");
    scanf("%d", &id);

    NodeSLL *temp = *head, *prev = NULL;

    while (temp && temp->book.id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("Khong tim thay sach!\n");
        return dHead;
    }

    if (!prev) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    NodeDLL *newNode = addNodeDLL(temp->book);
    newNode->next = dHead;
    if (dHead) dHead->prev = newNode;
    dHead = newNode;

    free(temp);
    printf("Danh dau sach da doc xong!\n");
    return dHead;
}


void arrangeBook(NodeSLL *head) {
    if (head == NULL) return;

    int swapped;
    NodeSLL *left;
    NodeSLL *right = NULL;

    do {
        swapped = 0;
        left = head;

        while (left->next != right) {
            if (left->book.price > left->next->book.price) {
                Book temp = left->book;
                left->book = left->next->book;
                left->next->book = temp;
                swapped = 1;
            }
            left = left->next;
        }
        right = left;
        printBook(head);
    } while (swapped);
}

void searchBook(NodeSLL *head) {
    char title[MAX_LENGTH];
    getchar();

    printf("Nhap tieu de sach can tim: ");
    fgets(title, MAX_LENGTH, stdin);
    title[strcspn(title, "\n")] = 0;

    NodeSLL *temp = head;
    int found = 0;
    while (temp) {
        if (strcspn(temp->book.title, title)) {
            printf("Ket qua thay: \n");
            printf("Id: %d | Title: %s | Author: %s | Category: %s | Price: %.2f\n",
                   temp->book.id, temp->book.title, temp->book.author,
                   temp->book.category, temp->book.price);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Khong tim thay sach!\n");
    }
}

void freeBook(NodeSLL *head, NodeDLL *dHead) {
    NodeSLL *temp = head;
    while (temp != NULL) {
        NodeSLL *curentNode = temp;
        temp = temp->next;
        free(curentNode);
    }

    NodeDLL *dTemp = dHead;
    while (dTemp != NULL) {
        NodeDLL *curentDNode = dTemp;
        dTemp = dTemp->next;
        free(curentDNode);
    }
}

int main() {
    int choice;
    NodeSLL *head = NULL;
    NodeDLL *dHead = NULL;

    do {
        showMenu();
        printf("Moi ban nhap lua chon cua ban:");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Danh sach quan ly sach: \n");
                head = addBook(head);
                break;
            case 2:
                printBook(head);
                break;
            case 3:
                head = deleteBook(head);
                break;
            case 4:
                updateBook(head);
                break;
            case 5:
                head = markBook(head, dHead);
                break;
            case 6:
                printf("Danh sach quan ly sach da duoc sap xep: \n");
                arrangeBook(head);
                break;
            case 7:
                searchBook(head);
                break;
            case 8:
                printf("Thoat chuong trinh");
                break;
            default:
                break;
        }
    } while (choice != 8);

    freeBook(head, dHead);

    return 0;
}
