j8u/*

NAME:Vern Andre A. Manayan
PROBLEM: The puurpose if this program is to create a book container that separates the 
fiction and the non-fiction book to their respective category in Singly linked list.
DATE STARTED:07/28/2025
DATE FINISHED:07/31/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

#define MAX 50

typedef struct book* booknd;

struct book {
    char title[MAX];
    char author[MAX];
    char classification[MAX];
    booknd next;
} BOOK;

// Function Prototypes
int menuDisplay(void);// displaying the menu and responsible for asking the user for input based on the menu
void bookContainer(booknd *top1, booknd *top2, bool *Create1, bool *Create2);//to make sure the there are 2 stacks created 
bool createStack(booknd *top);//to make sure the there are 2 stacks created 
void addBook(booknd *top1, booknd *top2);//  for the adding of books this also where it classify which stack to book goes 
void push(booknd *top, booknd element);// to place or to push inputted information to the containers
bool isEmpty(booknd top);  // to check if the containers are empty
void continueProg(void);// to pause the program and clear the sceen
void clearScreen(void);//to clear the screen
booknd peek(booknd top);//to get the last the data inputted and to return false if the container is empty 
booknd pop(booknd *top);// to pop the book
void removeBook(booknd *top1, booknd *top2);//to ask what book will be remove  
void topBooks(booknd top1, booknd top2);//this will show the last book that was place in fictiona and non-fiction
bool exitProgram(void);//to check if the user really wants to exit the program.

static booknd isEmptyTop = NULL;

int main(void) {
    booknd top1=NULL, top2=NULL;//comtaniers
    bool Create1 = false, Create2 = false;// for checking if the containers are created
    bool end = false;// for checking if the user wants to exit.
    int choice;// to get what is returned

    do {
        choice = menuDisplay();
        switch (choice) {
            case 1:
                bookContainer(&top1, &top2, &Create1, &Create2);
                if (Create1==false&&Create2==false) {
                    printf("Successfully created both containers.");
                }
                continueProg();
                break;
            case 2:
                if (Create1==false&&Create2==false) {
                    printf("!!!No Container has been initialized!!!");
                } else {
                    addBook(&top1, &top2);
                }
                continueProg();
                break;
            case 3:
                if (Create1==false&&Create2==false) {
                    printf("!!!No Container has been initialized!!!");
                } else {
                    removeBook(&top1, &top2);
                }
                continueProg();
                break;
            case 4:
                if (Create1==false&&Create2==false) {
                    printf("!!!No Container has been initialized!!!");
                } else {
                    topBooks(top1, top2);
                }
                continueProg();
                break;
            case 5:
                end = exitProgram();
                if (end) {
                    printf("Thank you for using this program.\n");
                }
                continueProg();
                break;
            default:
                printf("Please choose only the choices provided.\n");
                continueProg();
        }
    } while (end==false);

    return 0;
}

int menuDisplay(void) {
    int num;// to store the inputted choice
    printf("\n--- MENU ---\n");
    printf("1. Create Book Containers\n");
    printf("2. Add Book\n");
    printf("3. Remove Book\n");
    printf("4. Display Top Book Info\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &num);
    getchar();
    return num;
}

void bookContainer(booknd *top1, booknd *top2, bool *Create1, bool *Create2) {
    *Create1 = createStack(top1);
    *Create2 = createStack(top2);
}

bool createStack(booknd *top) {
    booknd t = *top;
    t = NULL;
    *top = t;
    return true;
}

void addBook(booknd *top1, booknd *top2) {
    char title[MAX], author[MAX], classification[MAX];
    booknd newBook = (booknd)malloc(sizeof(BOOK));
    if (!newBook) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter the title of the book: ");
    gets(title);
    printf("Enter the name of the author: ");
    gets(author);
    printf("Enter the classification (Fiction/Non-Fiction): ");
    gets(classification);
    strlwr(classification);

    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    strcpy(newBook->classification, classification);
    newBook->next = NULL;

    if (strcmp(classification, "fiction") == 0) {
        push(top1, newBook);
        printf("Added '%s' by %s to Fiction.\n", title, author);
    } else if (strcmp(classification, "non-fiction") == 0) {
        push(top2, newBook);
        printf("Added '%s' by %s to Non-Fiction.\n", title, author);
    } else {
        printf("!!! Invalid classification. Must be 'Fiction' or 'Non-Fiction'.\n");
    }
}

bool isEmpty(booknd top) {
    if (top == NULL)
        return true;
    else
        return false;
}

void push(booknd *top, booknd element) {
    booknd t = *top;
    element->next = t;
    t = element;
    *top = t;
}

booknd pop(booknd *top) {
    booknd element;
    booknd t = *top;
    element = t;
    t = element->next;
    element->next = NULL;
    *top = t;
    return element;
}

booknd peek(booknd top) {
	booknd element;
	element=top;
    return element;
}


void removeBook(booknd *top1, booknd *top2) {
    char title[MAX], classification[MAX];
    booknd  targetTop, tempStack = NULL, popped;
    bool found = false;
	bool isEmptyTop =false;
	bool tempcon = false;
	
    printf("Enter the title of the book to remove: ");
    gets(title);
    printf("Enter the classification (Fiction / Non-Fiction): ");
    gets(classification);
    strlwr(classification);

    if (strcmp(classification, "fiction") == 0) {
        targetTop = *top1;
    } else if (strcmp(classification, "non-fiction") == 0) {
        targetTop = *top2;
    } else {
        printf("Invalid classification.\n");
        return;
    }

    isEmptyTop = isEmpty(targetTop); // simulate isEmpty()
    if (isEmptyTop==true) {
        printf("The %s container is empty.\n", classification);
        return;
    }

    while (isEmptyTop==false) {
        popped = pop(&targetTop);
        if (strcmpi(popped->title, title) == 0) {
            printf("Book '%s' removed from %s container.\n", popped->title, classification);
            free(popped);
            found = true;
            break;
        } else {
            push(&tempStack, popped);
        }
    }
		tempcon=isEmpty(tempStack);
    while (tempcon== false) {
        popped = pop(&tempStack);
        push(&targetTop, popped);
    }

    if (!found) {
        printf("Book '%s' not found in %s container.\n", title, classification);
    }
}

void topBooks(booknd top1, booknd top2) {
    booknd fictionTop = peek(top1);
    booknd nonFictionTop = peek(top2);
	bool noFiction=false;
	bool noNonfic=false;
	
	noFiction=isEmpty(fictionTop);
    printf("\nTop Book in Fiction:\n");
    if (noFiction==false) {
        printf("Title : %s\n", fictionTop->title);
        printf("Author: %s\n", fictionTop->author);
    } else {
        printf("Fiction container is empty.\n");
    }
	noNonfic=isEmpty(nonFictionTop);
    printf("\nTop Book in Non-Fiction:\n");
    if (noNonfic==false) {
        printf("Title : %s\n", nonFictionTop->title);
        printf("Author: %s\n", nonFictionTop->author);
    } else {
        printf("Non-Fiction container is empty.\n");
    }
}

bool exitProgram() {
    char choice;
    printf("Do you want to terminate the program (Yes - Y / No - N): ");
    scanf(" %c", &choice);
    getchar();
    if (choice == 'y' || choice == 'Y')
    	return true;
    else if(choice=='n'|| choice=='N')
    	return false;
	else{
		printf("invalid input");
	 continueProg();
	 return false;
	}
}

void continueProg() {
    printf("\nPress Enter to continue...");
    getch();
    clearScreen();
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
