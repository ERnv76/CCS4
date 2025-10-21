#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#define SIZE 10
#define MAX 50
#define FILESIZE 20
#define HASH_DIV 53
#define LINEBUF 128
typedef struct node {
    int IdNum;
    char type[SIZE];
    char Composition[MAX];
    int synchain;
} NODE;

int Inputs(void);
bool CreateSkeleton(FILE *, NODE);
bool AddRecord(FILE *, NODE);
bool Blood(char []);
bool typechecker(char []);// to check if the bloodtype inputted is valid
bool rhesusCheck(char []);// to check if the Rhesus symbol inputted is valid

void exitProgram(void);
void continueProg(void); 
void clearScreen(void);
void line(void);

int main(void) 
{
    int choice = 0;
	bool create = false;
	bool proof = false; 
	bool exit = false; 
	NODE blood;
	FILE *fp;
       do {
        choice = Inputs();
        switch (choice) {
            case 1: // Create skeleton
                create = CreateSkeleton(&fp,blood);
                if (create == false) {
                    printf("Error creating the skeleton file.\n");
                    continueProg();
                } else {
                    printf("Successfully created the skeleton file.\n");
                    continueProg();
                }
                break;

            case 2: // Add record
                if (create == false) {
                    printf("There is no skeleton file created yet.\n");
                    continueProg();
                } else {
                    proof = AddRecord(&fp,blood);
                    if (proof == true) {
                        printf("Successfully added a blood bag record.\n");
                        continueProg();
                    } else {
                        printf("Unsuccessful in adding a blood bag record.\n");
                        continueProg();
                    }
                }
                break;

            case 3: // Edit record
                if (create == false) {
                    printf("There is no skeleton file created yet.\n");
                    continueProg();
                } else {
                    //proof = EditRecord();
                    if (proof == true) {
                        printf("Successfully edited the blood bag record.\n");
                        continueProg();
                    } else {
                        printf("Unsuccessful in editing the blood bag record.\n");
                        continueProg();
                    }
                }
                break;

            case 4: // Delete record
                if (create == false) {
                    printf("There is no skeleton file created yet.\n");
                    continueProg();
                } else {
                    //proof = DeleteRecord();
                    if (proof == true) {
                        printf("Successfully deleted the blood bag record.\n");
                        continueProg();
                    } else {
                        printf("Unsuccessful in deleting the blood bag record.\n");
                        continueProg();
                    }
                }
                break;

            case 5: // Search record
                if (create == false) {
                    printf("There is no skeleton file created yet.\n");
                    continueProg();
                } else {
                    //proof = SearchRecord();
                    if (proof == true) {
                        printf("Successfully found the blood bag record.\n");
                        continueProg();
                    } else {
                        printf("Unsuccessful in finding the blood bag record.\n");
                        continueProg();
                    }
                }
                break;

            case 6: // Display records
                if (create == false) {
                    printf("There is no skeleton file created yet.\n");
                    continueProg();
                } else {
                    //DisplayRecords();
                    continueProg();
                }
                break;

            case 7: // Exit
                exitProgram();
                if (exit == true)
                {
                	printf("Exiting Program!");
					continueProg();				
				}
				else{
					("Returning to menu");					
				} 
                break;

            default:
                printf("Please choose only from the choices!\n");
                continueProg();
                break;
        }
    } while (exit == false);

    return 0;
}

int Inputs(void)
{
    int num;
    printf("\n--- MENU ---\n");
    printf("1. Create blood table\n");
    printf("2. Insert value\n");
    printf("3. Search value\n");
    printf("4. Delete value\n");
    printf("5. Find min/max\n");
    printf("6. Display table\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &num);
    return num;
}

bool CreateSkeleton(FILE *fp, NODE blood)
 {
    int i;

    fp = fopen("bloodbank.dat", "wb");   // ?? changed here
    if (fp == NULL) 
        printf("Error opening file.\n");
	
	else{
    	for (i = 0; i < FILESIZE; i++) {
        	blood.IdNum = 0;
        	strcpy(blood.type, "");
        	strcpy(blood.Composition, "");
        	blood.synchain = -1;

	        fseek(fp, i * sizeof(NODE), SEEK_SET);
    	    fwrite(&blood, sizeof(NODE), 1, fp);
    	}
	}
    fclose(fp);
    return true;
}

bool AddRecord(FILE *fp, NODE blood)
{
    NODE temp;
    int id, hashValue, pos, newPos;
    char BloodType[SIZE];
    int choice;
    char Composition[MAX];
    bool check = false;
    bool foundEmpty = false;


    // Input Blood Bag ID
    printf("Blood bag ID Number    : ");
    scanf("%d", &id);
    if (id < 1000 || id > 9999) {
        printf("Error!!! Invalid Bag ID number.\n");
        fclose(fp);
        return false;
    }

    // Hashing (Division Remainder Method)
    hashValue = id % 53;
    // Compute file position
    pos = hashValue * sizeof(NODE);
    // Move file pointer and read record at hash position
    fseek(fp, pos, SEEK_SET);
    fread(&temp, sizeof(NODE), 1, fp);
    // Check for collision or empty slot
    if (temp.IdNum != 0) {
        printf("?? Collision detected at relative address %d.\n", hashValue);
        printf("Transferring record to another location...\n");
        // Linear probing to find next empty slot
        int i;
        for (i = (hashValue + 1) % FILESIZE; i != hashValue; i = (i + 1) % FILESIZE) {
            fseek(fp, i * sizeof(NODE), SEEK_SET);
            fread(&temp, sizeof(NODE), 1, fp);
            if (temp.IdNum == 0) {
                foundEmpty = true;
                newPos = i;
                break;
            }
        }
        if (!foundEmpty) {
            printf("Error: The file is full. Cannot insert new record.\n");
            fclose(fp);
            return false;
        }
        // Update synonym chain of original record
        fseek(fp, hashValue * sizeof(NODE), SEEK_SET);
        fread(&temp, sizeof(NODE), 1, fp);
        temp.synchain = newPos;
        fseek(fp, hashValue * sizeof(NODE), SEEK_SET);
        fwrite(&temp, sizeof(NODE), 1, fp);
        pos = newPos * sizeof(NODE);
    }
    // Input Blood Type (same as in your BST)
    check = Blood(BloodType);
    if (check == false) {
        fclose(fp);
        return false;
    }
    // Select Composition
    printf(" 1.)Whole blood\n 2.)Packed RBC\n 3.)Platelet\n 4.)Plasma\n");
    printf("Blood composition	: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1: strcpy(Composition, "Whole blood"); 
		break;
        case 2: strcpy(Composition, "Packed RBC"); 
		break;
        case 3: strcpy(Composition, "Platelet"); 
		break;
        case 4: strcpy(Composition, "Plasma"); 
		break;
        default:
            printf("Please choose only from the choices provided.\n");
            fclose(fp);
            return false;
    }
    // Fill record structure
    blood.IdNum = id;
    strcpy(blood.type, BloodType);
    strcpy(blood.Composition, Composition);
    blood.synchain = -1;
    // Write to computed address
    fseek(fp, pos, SEEK_SET);
    fwrite(&blood, sizeof(NODE), 1, fp);
    fclose(fp);
    printf("? Successfully stored the record in the relative file.\n");
    return true;
}
bool Blood(char BloodType[SIZE])
{
	bool match=false;
	bool factor=false;
	char type[SIZE], Rhesus[3];
	printf("Blood type (A,B,AB,O)  :");
		scanf(" %s", type);
	strupr(type);
	match = typechecker(type);
	if(match==false){
		printf("Invalid bloodtype inputted\n");
		return false;
	}
	printf("Rhesus factor(+/-)     :");
	scanf(" %2s", Rhesus);
	factor=rhesusCheck(Rhesus);
	if(factor==false){
		printf("The bloodtype inputted is invalid\n");
		return false;
	}
	strcat(type, Rhesus);
	strcpy(BloodType, type);	
	return true;
}
bool typechecker(char type[])
{
	if(strcmp(type, "A") == 0 || strcmp(type, "a") == 0 || strcmp(type, "B") == 0 || strcmp(type, "b") == 0 ||strcmp(type, "AB") == 0 || strcmp(type, "ab") == 0 ||strcmp(type, "O") == 0 || strcmp(type, "o") == 0)
    	return true;	
	else 
		return false; 
}
    
bool rhesusCheck(char Rhesus[])
{
	if(strcmp(Rhesus, "+") == 0 || strcmp(Rhesus, "-") == 0)
		return true;
	else 
		return false;
}

void exitProgram() 
{
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

void continueProg() 
{
    printf("\nPress Enter to continue...");
    getch();
    clearScreen();
}

void clearScreen() 
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void line(void)
{
	printf("_________________________\n");
}