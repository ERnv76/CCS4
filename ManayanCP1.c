/* 
Name: Vern Andre A Manayan 
Problem: The purpose of this program is to create a book container that seperate fiction and non-fiction and stack them.
Date Started: July 11,2025
Date Finished: 
*/
#include<stdio.h>
#include<stdbool.h>
#inluce<string.h>
#include<stdlib.h>

#define SIZE 3

typedef struct Container{
	char title[50];
	char author[50];
	char classification[50];
}BOOK;

void menuDisplay(void);
void bookcontainer(container1[SIZE],cointainer2[SIZE],*top1,*top2);
int addBook();
void stackCreate();
void clearScreen();
 	
int main(void)
{
	BOOK container1[SIZE], cointainer2[SIZE];
	bool Create1=false, Create2= false;
	int top1, top2; 
	int choice; 
	do{
		choice=menuDisplay();		
		switch(choice){
			case 1:BookContainer(BOOK container1[SIZE],BOOK container2[SIZE],&top1,&top2,&Create1,&Create2);//add book 
			break;
			case 2:addBook(container1[SIZE],container2[SIZE],&top1,&top2);
			break;
			case 3:/*removeBook()*/;
			break;
			case 4:/*takeBook()*/;
			break;
			case 5:/*displayTop*/;
			break;
			case 6:/*exit()*/;
			break;
			default:("Please choose only the choices provided");
			break;
		}
	}while(choice!=6);
}	
	
	
	
void menuDisplay(void)
	{
	int num;
		printf("Menu");
		printf("1.Add container");
		printf("2.Add book");
		printf("3.Remove book");
		printf("4.Take book");
		printf("5.display top");
		printf("6.Exit");
		printf("Please! type your choice");	
		scanf("%d",&num);
	return num;
	}
	
void bookcontainer(container1[SIZE],cointainer2[SIZE],*top1,*top2,*Create1,*Create2){
	bool Create1=false, Create2=flase;
		int t1=*top1, t2=top2;	
		*Create1=stackCreate(Container1,&t1);
		*Create2=stackCreate(Container2,&t2);
}

void stackCreate(""){
	
}
int addBook(BOOK container1[SIZE],BOOK container[SIZE],*top1,*top2){
	bool Full=false;
	char title[50];
	char author[50];
	char Category[50];
	
	printf("Title of the book");
	gets(title);
	printf("Name of the Author");

}




bool isFull(int top)
	{
		if(top==SIZE-1)
			return true;
		else 
			return false;
	}	

bool isEmpty(int top)
	{
		if(top==SIZE-1)
			reutrn true;
		else
			return false;
	}

void clearScreen() 
{
    #ifdef _WIN32
    system("cls"); 
    #else
    system("clear"); // I was coding this on Linux and not on Windows, needed this to test on Linux.
    #endif
}
