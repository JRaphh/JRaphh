#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie {
    struct Trie *next[26];
    char desc[201];
    int isEnd;
};

struct Trie *createNode() {
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    for(int i = 0; i < 26; i++) {
        node->next[i] = NULL;
    }
    node->desc[0] = '\0';
    node->isEnd = 0;
    return node;
}

void insert(struct Trie *root, char word[], char description[]) {
    int len = strlen(word);
    int idx;
    struct Trie *curr = root;

    for(int i = 0; i < len; i++) {
        idx = word[i] - 'a';
        if(curr->next[idx] == NULL) {
            curr->next[idx] = createNode();
        }
        curr = curr->next[idx];
    }

    curr->isEnd = 1;
    strcpy(curr->desc, description);
}

struct Trie *search(struct Trie *root, char word[]) {
    int len = strlen(word);
    int idx;
    struct Trie *curr = root;

    for(int i = 0; i < len; i++) {
        idx = word[i] - 'a';
        if(curr->next[idx] == NULL) return NULL;
        curr = curr->next[idx];
    }

    if(curr->isEnd == 1) return curr;
    return NULL;
}

void printWords(struct Trie *root, char temp[], int level, int *count) {
    if(root->isEnd == 1) {
        temp[level] = '\0';
        (*count)++;
        printf("%d. %s\n", *count, temp);
    }

    for(int i = 0; i < 26; i++) {
        if(root->next[i]) {
            temp[level] = i + 'a';
            printWords(root->next[i], temp, level + 1, count);
        }
    }
}

void viewAll(struct Trie *root) {
    int count = 0;
    char temp[101];
    printWords(root, temp, 0, &count);
    if(count == 0) {
        printf("There is no slang word yet in the dictionary.\n");
    }
    printf("Press enter to continue...");
    getchar();
    getchar();
}

void prefixSearch(struct Trie *root, char prefix[]) {
    int idx;
    struct Trie *curr = root;
    for(int i = 0; i < strlen(prefix); i++) {
        idx = prefix[i] - 'a';
        if(curr->next[idx] == NULL) {
            printf("There is no prefix \"%s\" in the dictionary.\n", prefix);
            printf("Press enter to continue...");
            getchar(); getchar();
            return;
        }
        curr = curr->next[idx];
    }

    int count = 0;
    char temp[101];	
    strcpy(temp, prefix);
    int len = strlen(prefix);
    printWords(curr, temp, len, &count);
    if(count == 0) {
        printf("There is no prefix \"%s\" in the dictionary.\n", prefix);
    }
    printf("Press enter to continue...");
    getchar(); getchar();
}

void releaseWord(struct Trie *root) {
    char word[101];
    char desc[201];
    int valid = 0;
    int spaceCount = 0;

    do {
        system("cls");
        printf("Input a new slang word [Must be more than 1 character and contain no space]: ");
        scanf("%s", word);
        valid = 1;
        if(strlen(word) <= 1) valid = 0;
        for(int i = 0; i < strlen(word); i++) {
            if(word[i] == ' ') valid = 0;
        }
    } while(!valid);

    struct Trie *found = search(root, word);

    do {
        printf("Input a new slang word description [Must be more than 2 words]: ");
        scanf(" %[^\n]", desc);
        spaceCount = 0;
        for(int i = 0; i < strlen(desc); i++) {
            if(desc[i] == ' ' && desc[i+1] != '\0') spaceCount++;
        }
    } while(spaceCount < 1);

    insert(root, word, desc);

    if(found) {
        printf("Successfully updated a slang word.\n");
    } else {
        printf("Successfully released new slang word.\n");
    }
    printf("Press enter to continue...");
    getchar(); getchar();
}

void searchWord(struct Trie *root) {
    char word[101];
    int valid = 0;
    do {
        system("cls");
        printf("Input a slang word to be searched [Must be more than 1 character and contain no space]: ");
        scanf("%s", word);
        valid = 1;
        if(strlen(word) <= 1) valid = 0;
        for(int i = 0; i < strlen(word); i++) {
            if(word[i] == ' ') valid = 0;
        }
    } while(!valid);

    struct Trie *result = search(root, word);
    if(result == NULL) {
        printf("There is no word \"%s\" in the dictionary.\n", word);
    } else {
        printf("Slang word  : %s\n", word);
        printf("Description : %s\n", result->desc);
    }
    printf("Press enter to continue...");
    getchar(); getchar();
}

void menu(struct Trie *root) {
    int opt;
    do {
        system("cls");
        printf("         BOOGLE\n");
        printf("1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix word\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");
        printf("Option: ");
        scanf("%d", &opt);

        if(opt == 1) {
            releaseWord(root);
        } else if(opt == 2) {
            searchWord(root);
        } else if(opt == 3) {
            char prefix[101];
            do {
                printf("Input a prefix to be searched: ");
                scanf("%s", prefix);
            } while(strlen(prefix) < 2);
            prefixSearch(root, prefix);
        } else if(opt == 4) {
            printf("List of all slang words in the dictionary:\n");
            viewAll(root);
        }
    } while(opt != 5);

    printf("Thank you... Have a nice day :)\n");
}

int main() {
    struct Trie *root = createNode();
    menu(root);
    return 0;
}

