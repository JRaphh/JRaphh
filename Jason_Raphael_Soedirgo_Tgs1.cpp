#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void enterHold(){
	printf("Press [ENTER] to continue...");
	getchar();
}

int mainMenu(){
	int choice;
	system("cls");

	printf("Menu:\n");
    printf("1. Add Book\n");
    printf("2. Remove Book\n");
    printf("3. View List\n");
    printf("4. Exit\n");
    
    do{
		printf("Your choice: ");
		scanf("%d", &choice);
		getchar();
	} while(choice < 1 || choice > 4);
    
	return choice;
}

void addBook(int *count, char bookList[][100]){
	char name[100];
	system("cls");
	printf("Insert your book's name: ");
	scanf("%s",name);
	getchar();
	
	if(*count != 0 && *count < 10000){
		for(int i = 0; i < *count; i++){
			if(strcmp(name, bookList[i]) == 0){
				puts("This title has already existed!");
				return;
			}
		}
	}
	
	strcpy(bookList[*count], name);
	(*count)++;
	
	char temp[100];
	for(int i = 0; i < (*count) - 1; i++){
		for(int j = i + 1; j < *count; j++){
			if(strcmp(bookList[i], bookList[j]) > 0){
				strcpy(temp, bookList[i]);
				strcpy(bookList[i], bookList[j]);
				strcpy(bookList[j], temp);
			}
		}
	}
}

void viewList(int *count, char bookList[][100]){
	system("cls");
	if(*count == 0){
		puts("No Book!");
		return;
	}
	
	for(int i = 1; i <= *count; i++){
		printf("%d. %s\n", i, bookList[i - 1]);
	}	
}

void removeBook(int *count, char bookList[][100]){
	char remove[100];
	system("cls");
	
	if(*count == 0){
		puts("There is no book in the list!");
		return;
	}
	
	printf("Insert book's name: ");
	scanf("%s", remove);
	getchar();
	
	if(strcmp(remove, bookList[(*count) - 1]) == 0){
		(*count)--;
		return;
	}
	
	for(int i = 0; i < (*count) - 1; i++){
		if(strcmp(remove, bookList[i]) == 0){
			for(int j = i; j < (*count); j++){
				strcpy(bookList[j], bookList[j+1]);
			}
			break;
		}
		
		if(i == (*count) - 2){
			puts("Book not found!");
		}
	}
	
	
	(*count)--;
}

void exitProgram(){
	system("cls");
	exit(0);
}

void proceedChoice(int *count, char bookList[][100], int choice){
	
	switch(choice){
		case 1:{
			addBook(count, bookList);
			enterHold();
			break;
		}
		case 2:{
			removeBook(count, bookList);
			enterHold();
			break;
		}
		case 3:{
			viewList(count, bookList);
			enterHold();
			break;
		}
		case 4:{
			exitProgram();
			break;
		}
	}
}


int main(){
	int count = 0, choice = 0;
	char bookList[10000][100];
	
	while(true){
		
		choice = mainMenu();
		
		proceedChoice(&count, bookList, choice);
	}
	
	return 0;
}
