#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
#define MIN_LENGTH 5
#define MAX_LENGTH 50

typedef struct HashTable {
    char* table[TABLE_SIZE];
} HashTable;

int hash(char* str) {
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        sum += (int)str[i];
    }
    return sum % TABLE_SIZE;
}

void addString(HashTable* ht, char* str) {
    if (strlen(str) < MIN_LENGTH || strlen(str) > MAX_LENGTH) {
        printf("Error: String length must be between %d and %d characters.\n", MIN_LENGTH, MAX_LENGTH);
        return;
    }

    int index = hash(str);
    while (ht->table[index] != NULL) {
        if (strcmp(ht->table[index], str) == 0) {
            printf("String already exists in the hash table.\n");
            return;
        }
        index = (index + 1) % TABLE_SIZE;
    }
    ht->table[index] = strdup(str);
    printf("String added: %s\n", str);
}

void searchString(HashTable* ht, char* str) {
    int index = hash(str);
    while (ht->table[index] != NULL) {
        if (strcmp(ht->table[index], str) == 0) {
            printf("String found: %s\n", str);
            return;
        }
        index = (index + 1) % TABLE_SIZE; // Linear probing
    }
    printf("String not found: %s\n", str);
}

void removeString(HashTable* ht, char* str) {
    int index = hash(str);
    while (ht->table[index] != NULL) {
        if (strcmp(ht->table[index], str) == 0) {
            free(ht->table[index]); // Free allocated memory
            ht->table[index] = NULL; // Mark as deleted
            printf("String removed: %s\n", str);
            return;
        }
        index = (index + 1) % TABLE_SIZE; // Linear probing
    }
    printf("String not found: %s\n", str);
}

void viewTable(HashTable* ht) {
    printf("Hash Table Contents:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->table[i] != NULL) {
            printf("Index %d: %s\n", i, ht->table[i]);
        }
    }
}

int main() {
    HashTable ht = { { NULL } }; 
    int choice;
    char str[MAX_LENGTH + 1]; 

    do {
        printf("\nMenu:\n");
        printf("1. Add string\n");
        printf("2. Search string\n");
        printf("3. Remove string\n");
        printf("4. View hash table\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter string to add: ");
                fgets(str, sizeof(str), stdin);
                str[strcspn(str, "\n")] = 0; 
                addString(&ht, str);
                break;
            case 2:
                printf("Enter string to search: ");
                fgets(str, sizeof(str), stdin);
                str[strcspn(str, "\n")] = 0; 
                searchString(&ht, str);
                break;
            case 3:
                printf("Enter string to remove: ");
                fgets(str, sizeof(str), stdin);
                str[strcspn(str, "\n")] = 0; 
                removeString(&ht, str);
                break;
            case 4:
                viewTable(&ht);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    for (int i = 0; i < TABLE_SIZE; i++) {
            if (ht.table[i] != NULL) {
                free(ht.table[i]); 
        }
    }

    return 0;
}
