#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct buku {
    char isbn[100];
    char title[100];
    char author[100];
    int year;
};

struct node {
    struct buku data;
    struct node *prev, *next;
};

struct node *head = NULL;

void addBook() {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    printf("Tambah Buku Baru\n");
    printf("Masukan ISBN: ");
    scanf("%19s", newNode->data.isbn);
    getchar();
    printf("Masukan Judul: ");
    fgets(newNode->data.title, 50, stdin);
    newNode->data.title[strcspn(newNode->data.title, "\n")] = 0;
    printf("Masukan Pembuat: ");
    fgets(newNode->data.author, 100, stdin);
    newNode->data.author[strcspn(newNode->data.author, "\n")] = 0;
    printf("Masukan Tahun Rilis: ");
    scanf("%d", &newNode->data.year);
    getchar();
    newNode->prev = newNode->next = NULL;

    if (!head || strcmp(newNode->data.title, head->data.title) < 0) {
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
    } else {
        struct node *temp = head;
        while (temp->next && strcmp(temp->next->data.title, newNode->data.title) < 0)
            temp = temp->next;
        newNode->next = temp->next;
        if (temp->next) temp->next->prev = newNode;
        newNode->prev = temp;
        temp->next = newNode;
    }
    printf("Buku Telah Ditambahkan!\n");
    getchar();
    system("cls");
}

void viewBooks() {
    struct node *temp = head;
    if (!temp) {
        printf("=== List Buku ===\nTidak Ada Buku.\n");
        getchar();
        system("cls");
        return;
    }
    printf("\n=== List Buku ===\n");
    while (temp) {
        printf("ISBN           : %s\n", temp->data.isbn);
        printf("Judul          : %s\n", temp->data.title);
        printf("Pembuat        : %s\n", temp->data.author);
        printf("Tahun Rilis    : %d\n", temp->data.year);
        temp = temp->next;
    }
    getchar();
    system("cls");
}

void removeBook() {
    if (!head) {
        printf("Tidak Ada Buku Untuk Dihapus.\n");
        getchar();
        system("cls");
        return;
    }
    char title[50];
    printf("\n=== Hapus Buku ===\nMasukan Judul Buku Yang Ingin Dihapus: ");
    fgets(title, 50, stdin);
    title[strcspn(title, "\n")] = 0;

    struct node *temp = head;
    while (temp) {
        if (strcasecmp(temp->data.title, title) == 0) {
            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            if (temp == head) head = temp->next;
            free(temp);
            printf("Buku Telah Dihapus!\n");
            getchar();
            system("cls");
            return;
        }
        temp = temp->next;
    }
    printf("Buku Tidak Ditemukan!\n");
    getchar();
    system("cls");
}

void bookChoice(int choice){
	do {
        printf("Menu:\n");
        printf("1. Tambah Buku\n");
        printf("2. List Buku\n");
        printf("3. Hapus Buku\n");
        printf("4. Keluar\n");
        printf("Masukan Pilihan: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: removeBook(); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Pilihan Invalid. Pilih Antara 1 Sampai 4.\n");
            getchar();
            system("cls");
        }
    } while (choice != 4);
}
int main() {
    int choice;
    
    bookChoice(choice);
    
    return 0;
}
