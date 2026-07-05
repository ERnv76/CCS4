/* 
Name: Vern Andre A Manayan 
Problem: The purpose of this program is to create a book container that seperate fiction and non-fiction books inputted while using Queues.
Date Started: August 8,2025
Date Finished: August 15, 2025
*/
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include <conio.h>

#define QUEUESIZE 3
#define MAX 50
typedef struct Container{
	char title[50];
	char author[50];
	char classification[50];
}BOOK;

int menuDisplay(void);// display the menu and accept input of the user.(return a integer for the selected option by the user).
void BookContainer(BOOK container1[QUEUESIZE],BOOK cointainer2[QUEUESIZE],int *hd1,int *tl1,int *hd2,int *tl2,bool *Create1,bool *Create2);// this function is for the creation of the book containers/ queues.(no value retruned)
bool CreateQueue(BOOK container[QUEUESIZE], int *head, int *tail);// this function is responsible fo the creation contaioner and initailization of the placement of the head and tail for both containers.(return a bool true for error trapping) 
void addBook(BOOK container1[QUEUESIZE],BOOK container2[QUEUESIZE],int *hd1,int *tl1,int *hd2,int *tl2);//this is where the program ask for the classification where the book would be place. (returned no value)
void removeBook(BOOK container1[QUEUESIZE],BOOK container2[QUEUESIZE],int *hd1,int *tl1,int *hd2,int *tl2);//this is where the program ask what book is to be remove.(no value returned)
void lower(char bookTitle[], char title[]);// this function I create for error trapping for key sensitive input. (no value returned)
bool FullQueue(BOOK container[QUEUESIZE], int head,int tail);//this for checking if the the container being targeted is full.(returns a bool)
int Enqueue(BOOK container[QUEUESIZE],int tail,BOOK newbook);// this function is responsible for pushing the books inputted to the container. this also helps initialize for the location for the tail(returns the new value of the tail) 
bool EmptyQueue(int head, int tail);// to check if the container being targetted is empty(returns bool).
BOOK Dequeue(BOOK Container[QUEUESIZE],int *targethead);//to pulls out the inputs form the targetted container(it returns the element where the head is pointed)
bool exitProgram(void);//it exits the program(returns bool for error trapping);
void continueProg(void);//it pauses the program.
void clearScreen(void);//clears the screen.

int main(void){
	BOOK container1[QUEUESIZE], container2[QUEUESIZE];
	bool Create1=false, Create2= false;
	bool end;
	int hd1,tl1;// fiction 
	int hd2,tl2; // non-fiction 
	int choice; 
	do{
		choice = menuDisplay();		
		switch(choice){
			case 1:BookContainer(container1,container2,&hd1,&tl1,&hd2,&tl2,&Create1,&Create2);//add book 
					if(Create1==true&&Create2==true){
					printf("Successfully create a Container.");
					continueProg();
				}
			break;
			case 2:if(Create1==false&&Create2==false){
					printf("!!!No Container have been initialized!!!");
					continueProg();
					}else{	
					addBook(container1,container2,&hd1,&tl1,&hd2,&tl2);
					continueProg();
					}
			break;
			case 3:if(Create1==false&&Create2==false){
					printf("!!!No Container have been initialized!!!");
					continueProg();
					}else{
						removeBook(container1,container2,&hd1,&tl1,&hd2,&tl2);
					 continueProg();
					}	
			break;
			case 4:end = exitProgram();
					if(end==true){
						printf("thank you for using this program");
						continueProg();
					}
			break;
			default:("Please choose only the choices provided");
			break;
		}
	}while(end==false);
	return 0;
}	
	
int menuDisplay(void)
{
	int num;
    printf("\n--- MENU ---\n");
    printf("1. Create Book Containers\n");
    printf("2. Add Book\n");
    printf("3. Remove Book\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &num);
    getchar();
	return num;
}
	
void BookContainer(BOOK container1[QUEUESIZE],BOOK container2[QUEUESIZE],int *hd1,int *tl1,int *hd2,int *tl2,bool *Create1,bool *Create2)
{	
	int h1=*hd1, t1=*tl1;
	int h2=*hd2, t2=*tl2;
		*Create1=CreateQueue(container1,&h1,&t1);
		*Create2=CreateQueue(container2,&h2,&t2);
	*hd1=h1;
	*tl1=t1;
	*hd2=h2;
	*tl2=t2;
}

bool CreateQueue(BOOK container[QUEUESIZE], int *head,int *tail)
{
	int h=*head, t=*tail, i;
	for (int i = 0; i < QUEUESIZE; i++) {
        strcpy(container[i].title, "");
        strcpy(container[i].author, "");
        strcpy(container[i].classification, "");
    }
    t=-1;
    h=0;
    *tail=t;
    *head=h;
    return true;
}

void addBook(BOOK container1[QUEUESIZE],BOOK container2[QUEUESIZE],int *hd1,int *tl1,int *hd2,int *tl2)
{
	char title[MAX],author[MAX],classification[MAX],tempclass[MAX];
	bool Full=false;
	int h1=*hd1,t1=*tl1;//fcition 
	int h2=*hd2,t2=*tl2;//non-fiction
	BOOK newBook;
	printf("The title of the book            :");
		gets(title);
	printf("The name of the author           :");
		gets(author);
	printf("The classification of the book\n(Fiction/Non-fiction)            :");
		gets(classification);	
    strcpy(newBook.title, title);
    strcpy(newBook.author, author);
    strcpy(newBook.classification, classification);
    strcpy(tempclass,classification);
	strlwr(tempclass);		
	if (strcmp(tempclass,"fiction")==0){
		Full=FullQueue(container1, h1,t1);
		if(Full==true){
			printf("!!!Book container is full!!!\n");
        	printf("Cannot add book to the stack.\n");
			}else{
				t1=Enqueue(container1,t1,newBook);
				printf("You have added %s by %s to %s",title,author,classification);
				*hd1=h1;
				*tl1=t1;
			}
	}
	else if(strcmp(tempclass,"non-fiction")==0){
		Full=FullQueue(container2,h2,t2);;
		if(Full==true){
			printf("!!!Book container is full!!!\n");
        	printf("Cannot add book to the stack.\n");
    	    }else{
        		t2=Enqueue(container2, t2,newBook);
				printf("You have added %s by %s to %s",title, author,classification);
				*hd2=h2;
				*tl2=t2;
			}	
	}
	else{
		printf("!!! Invalid classification. Must be 'Fiction' or 'Non-Fiction'.\n");
	}
	
}

void removeBook(BOOK container1[QUEUESIZE],BOOK container2[QUEUESIZE],int *hd1,int *tl1,int *hd2,int *tl2)
{
	char title[MAX],author[MAX],classification[MAX],tempttitle[MAX],tempclass[MAX],titleLower[MAX];
	BOOK Temporary[QUEUESIZE];
	BOOK *targetContainer;
    BOOK popped;
    bool found=false;
    bool tempcon=false;
    bool itsEmpty;
    int h1=*hd1,t1=*tl1;//fcition 
	int h2=*hd2,t2=*tl2;//non-fiction
	int targethead, targettail;
	int temphead=0, temptail=-1;
	
	printf("Enter the title of the book to remove: ");
    gets(title);
    printf("Enter the classification (Fiction / Non-Fiction): ");
    gets(classification);
    strcpy(tempclass,classification);
    strlwr(tempclass);
    
	if (strcmp(tempclass, "fiction") == 0){
        targetContainer = container1;
        targethead = h1;
        targettail = t1;
		} else if (strcmp(tempclass, "non-fiction") == 0) {
       		targetContainer = container2;
       		targethead = h2;
        	targettail = t2;
    		} else {
        		printf("Invalid classification. Must be 'Fiction' or 'Non-Fiction'.\n");
        		return;
    }
    
    itsEmpty = EmptyQueue(targethead,targettail);
    
	if (itsEmpty == true){
        printf("The %s container is already empty.\n", classification);
        return;
	}
	else{
		while(itsEmpty == false)
		{
			popped = Dequeue(targetContainer,&targethead);
			strcpy(titleLower, title);
			strcpy(tempttitle, popped.title);
			lower(tempttitle,titleLower);
				if(strcmp(tempttitle, titleLower) == 0)
				{	
					printf("\nBook removed from %s container:\n", classification);
            		printf("Title : %s\n", popped.title);
        			printf("Author: %s\n", popped.author);
            		found = true;	
            		itsEmpty = EmptyQueue(targethead,targettail);
            		break;		
				}
					else
					{
						temptail = Enqueue(Temporary,temptail,popped);
					}
			itsEmpty = EmptyQueue(targethead,targettail);					
		}		
		tempcon = EmptyQueue(temphead,temptail);
		while(tempcon == false)
		{
			popped = Dequeue(Temporary,&temphead);
			targettail=Enqueue(targetContainer,targettail,popped);	
			tempcon = EmptyQueue(temphead, temptail);
		} 	
		
    	if (found == false) 
		{	
        	printf("\nBook titled '%s' not found in the %s container.\n", title, classification);
    	}
	}
	
	if (strcmp(classification, "fiction") == 0) {
        *hd1 = targethead;
        *tl1 = targettail;
    } 
    else if (strcmp(classification, "non-fiction") == 0) {
        *hd2 = targethead;
        *tl2 = targettail;
    }
}

void lower(char bookTitle[], char title[])
{
	strlwr(bookTitle);
	strlwr(title);	
	
}

bool FullQueue(BOOK container[QUEUESIZE], int head,int tail)
{
	if((head == 0&&tail == QUEUESIZE-1)||(tail == head - 1&&strcmp(container[tail].title,"") != 0))
		return true;
	else 
		return false;
} 

int Enqueue(BOOK container[QUEUESIZE],int tail,BOOK newbook)
{
	if(tail==QUEUESIZE-1)
		tail=0;
	else
		tail++;
		container[tail]=newbook;
	return tail;
}

bool EmptyQueue(int head, int tail)
{

	if (tail == -1 || (head == 0 && tail == QUEUESIZE - 1) || (tail + 1 == head))
		return true;
	else
		return false;	
}

BOOK Dequeue(BOOK container[QUEUESIZE],int *targethead)
{
	BOOK element; 
	int head= *targethead;
	if(head=QUEUESIZE-1)
		head=0;
	else
		head++;
	element	= container[head];			
	*targethead = head;
	return element;
}

bool exitProgram(void)
{
    char choice;
    printf("Do you want to terminate the program (Yes - Y/ NO - N): ");
    scanf(" %c", &choice);  // add a space before %c to skip newline characters

    if(choice == 'y' || choice == 'Y')
        return true;
    else 
        return false;
}

void continueProg(void)
{
	printf("\n Please press enter to continue");
	getch();
	clearScreen();
}

void clearScreen(void) 
{
    #ifdef _WIN32
    system("cls"); 
    #else
    system("clear"); // I was coding this on Linux and not on Windows, needed this to test on Linux.
    #endif
}
