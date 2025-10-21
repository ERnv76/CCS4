/*
Name: Vern Andre A. Manayan
Summary of the problem:create BST to store information about blood bag (blood bag number, bloodtype, and composition).
Date Created:september 22, 2025
Date Finished: september 26, 2025

*/

#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include <conio.h>

#define SIZE 10
#define MAX 50

typedef struct node*ptr;
struct node{
	int IdNum;
	char type[SIZE];
	char Composition[MAX];
	ptr left;
	ptr right;
}BLOOD;

int Inputs(void);
bool CreateTree(ptr*);//to initial the root into NULL
bool InsertValue(ptr*);// to insert the needed information to the tree
bool Blood(char []);//to ask the bloodtype and its rhesus factor
bool typechecker(char []);// to check if the bloodtype inputted is valid
bool rhesusCheck(char []);// to check if the Rhesus symbol inputted is valid
ptr push(ptr, ptr, bool*);// to push the new element to the tree
bool found(ptr*);//the function that ask to look for the target  element
ptr search(ptr, int, ptr*);//to loop and look for the target element
void value(ptr*);//a function that call the functions for minimum value and the maximum value
ptr least(ptr, ptr*);//to search for the minimum 
ptr highest(ptr, ptr*); //to search for the maximum
void display(ptr,ptr);// to display values
bool duplicate(int, ptr);// to check if there is a duplication of blood bag numbers before storing it
bool deletion(ptr*);// a function for deletion
bool confirmation(int*);//to confirm if to really delete the target vale
bool performDeletion(ptr*, ptr, ptr, int);// it perform and identify which method on how to delete.
void displayTree(ptr*);//to displat the values of the tree 
void inorderTraversal (ptr *);//the sequence of how the diplay of the value of the tree 
bool exitProgram();
void continueProg();
void clearScreen();
void line(void);


void main()
{
	ptr root;
	int choice;
	bool create=false;
	bool proof=false;
	do{
	choice=Inputs();
	switch(choice){
		case 1://create a tree
			create=CreateTree(&root);
			if(create==false){
				printf("there is no tree created");
				continueProg();
			}
			else
				printf("successfully created a tree");
				continueProg();
		break;
		case 2:
			if(create==false){
				printf("there is no tree created");
				continueProg();
			}
			else{
				proof=InsertValue(&root);
				if(proof==true){
					printf("Successfully added a Blood bag");
					continueProg();
				}
				else{
					printf("Unsuccessful in adding a Blood bag");		
					continueProg();
				}
			}
				
		break;
		case 3://search for value
			if(create==false){
				printf("there is no tree created");
				continueProg();
			}
			else{
				proof=found(&root);
				if(proof==true){
					printf("successfully found the blood bag");
					continueProg();
				}
				else{
					printf("Unsuccessfully in finding the Blood bag");
					continueProg();
				}
			}
		break;
		case 4://delete value
			if(create==false){
				printf("there is no tree created");
				continueProg();
			}
			else{
				proof=deletion(&root);
				if(proof==true){
					printf("successfully deleted the blood bag");
					continueProg();
				}
				else{
					printf("Unsuccessfully in deleting the Blood bag");
					continueProg();
				}
			}
		break;
		case 5://find the minimum and maximum values
			if(create==false){
				printf("there is no tree created");
				continueProg();
			}
			else{
				value(&root);
				continueProg();
			}
		break;
		case 6://display tree
			if(create==false){
				printf("there is no tree created");
				continueProg();
			}
			else{
				displayTree(&root);
				continueProg();
			}
		break;
		case 7:exitProgram();
		break;
		default:printf("Please choose only from the choices! ");
				continueProg();
		break;
	}	 
	}while(choice!=7);

}

int Inputs(void)
{
    int num;
    printf("\n--- MENU ---\n");
    printf("1. Create tree\n");
    printf("2. Insert value\n");
    printf("3. search value\n");
    printf("4. delete value\n");
    printf("5. find the minimum and maximum values\n");
    printf("6. dispaly tree\n");
    printf("7. Exit\n");
    printf("Enter your choice      :");
    scanf("%d", &num);
    return num;
}

bool CreateTree(ptr *root)
{
	bool create=false;
	*root=NULL;
	if(*root==NULL)
	create=true;
	return create;	
}

bool InsertValue(ptr *root)
{
	ptr element=(ptr)malloc(sizeof(BLOOD));
	bool check=false;
	bool dual=false;
	int id;
	char BloodType[SIZE];
	int choice;
	char Composition[MAX];
	
	printf("Blood bag ID Number    :");
		scanf("%d", &id);
	if(id < 1000 || id > 9999){	
		printf("Error!!! Invalid Bag ID number\n");
		return false; 																										
	}
	dual=duplicate(id, *root);
	if (dual==true){
		printf("Duplicate Blood bag ID number\n");
		return false;	
	}	
	check=Blood(BloodType); 
	if(check==false){
		return false;
	}
	printf(" 1.)Whole blood\n 2.)Packed RBC\n 3.)Platelet\n 4.)Plasma\n");
	printf("Blood composition	:");
	scanf("%d",&choice);
	switch(choice){
	case 1:strcpy(Composition,"Whole blood");
		break;
	case 2:strcpy(Composition,"Packed RBC");
		break;
	case 3:strcpy(Composition,"Platelet");
		break;
	case 4:strcpy(Composition,"Plasma");
		break;
	default:printf("Please choose only the choices provided.\n");
			return false;
		break;		
	}
			
    element->IdNum=id;
    strcpy(element->type, BloodType);
    strcpy(element->Composition, Composition);
    element->left =NULL;
	element->right=NULL;
    *root = push(*root, element, &dual);

		if(*root!=NULL)
			return true;
		else 
			return false;
}

bool duplicate(int id, ptr root)
{
    while (root != NULL) {
        if (id == root->IdNum) {
            return true;
        } else if (id < root->IdNum) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return false;
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

ptr push(ptr root, ptr element, bool *dual)
{
	if(root==NULL)
		return element;
    if (element->IdNum < root->IdNum) {
        root->left = push(root->left,element,dual);
    } else{
        root->right = push(root->right,element,dual);
    } 
    return root;
}

bool found(ptr *root)
{
	int id;
	ptr element; 
	ptr parent=NULL;
	ptr current=*root;
	ptr sibling=NULL;
	
	if (*root == NULL) {
        printf("Error: The tree is empty, nothing to delete.\n");
        return false;
    }
	printf("Blood Bag Number       : ");
	scanf("%d", &id);
	element= search(*root, id, &parent);
	if(element==NULL)
		return false;
	printf("Blood Bag Number       : %d\n",element->IdNum);
	printf("Blood Type 	       : %s\n",element->type);
	printf("Composition  	       : %s\n",element->Composition);
	if(element->IdNum==current->IdNum)
		printf("The Blood bag is at the root\n");
	else{
		if (parent != NULL) {
        	printf("Parent Bag Number      : %d\n", parent->IdNum);
        	
		if (parent->left == element && parent->right != NULL) {
            sibling = parent->right;
        } else if (parent->right == element && parent->left != NULL) {
            sibling = parent->left;
        }
        if (sibling != NULL) {
            printf("Sibling Bag Number     : %d\n", sibling->IdNum);
        } else {
        	printf("Sibling Bag Number     :NONE\n");
        	}
    	}
	}
	return true;
}

ptr search(ptr root, int id, ptr *parent)
{
    while (root != NULL) {
        if (id == root->IdNum) {
            return root;
        } else if (id < root->IdNum) {
            *parent = root;
            root = root->left;
        } else {
            *parent = root;
            root = root->right;
        }
    }
    return NULL;
}
void value(ptr *root)
{
	ptr mini, max;
	ptr miniroot=NULL;
	ptr maxroot=NULL;
	
	if (*root == NULL) {
        printf("Error: The tree is empty, nothing to delete.\n");
        return false;
    }
	mini=least(*root, &miniroot);
	max=highest(*root,&maxroot);
	printf("The minimun value\n");
	line();
	display(mini,miniroot);
	printf("The Maximum value\n");
	line();
	display(max, maxroot);	
}

ptr least(ptr leaf, ptr *parent)
{
   	while (leaf->left != NULL) {
   		*parent=leaf;
        leaf = leaf->left;
    }
    return leaf;
}

ptr highest(ptr leaf,ptr *parent) 
{
    while (leaf->right != NULL) {
    	*parent=leaf;
        leaf = leaf->right;
    }
    return leaf;
}

void display(ptr show, ptr parent)
{	
	printf("Blood bag number    : %d\n", show->IdNum);
	printf("Blood type          : %s\n", show->type);
	printf("Composition         : %s\n", show->Composition);
	line();
	printf("Parent Node:\n");
	if (parent != NULL){
	    printf("Blood bag number    : %d\n", parent->IdNum);
		printf("Blood type          : %s\n", parent->type);
		printf("Composition         : %s\n", parent->Composition);
	}
    else
		printf("Parent of the Node  :none\n");
	line();	
}

bool deletion(ptr *root)
{
	int Id;
	bool confirm=false;
	bool success=false;
	ptr parent=NULL;
	ptr element=NULL;

	if (*root == NULL) {
        printf("Error: The tree is empty, nothing to delete.\n");
        return false;
    }
	printf("Blood bag number to be deleted     :");
	scanf("%d",&Id);
	
	element=search(*root, Id, &parent);
	if(element==NULL){
		printf("Error: Blood Bag Number %d not found!\n", Id);
		return false;
	}
	confirm =confirmation(&Id);
	if(confirm==false)
		return false;
	success=performDeletion(root, element, parent, Id);
	if(success==true)
	return true;
}
bool confirmation(int *Id){
	char confirm;
	printf("Blood Bag %d found. Confirm deletion? (y/n): ", *Id);
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf("Deletion cancelled.\n");
        return false;
    }
    else 
    	return true;
     clearScreen();	
}

bool performDeletion(ptr *root, ptr element, ptr parent, int Id) {
    ptr child=NULL;        
    ptr succParent=NULL;   
    ptr succ=NULL; 
	// --- Case 1: Node is a leaf ---
	if (element->left == NULL && element->right == NULL) {
		printf("Blood bag number    : %d || ", element->IdNum);
        printf("Blood type          : %s || ", element->type);
        printf("Composition         : %s\n", element->Composition);
        
		if (parent == NULL) { // deleting the root
            free(element);
            *root = NULL;
        } else if (parent->left == element) {
            parent->left = NULL;
            free(element);
        } else {
            parent->right = NULL;
            free(element);
        }
        printf("Deleted %d (leaf node).\n", Id);

    }

    // --- Case 2: Node has one child ---
    else if (element->left == NULL || element->right == NULL) {
    	printf("Blood bag number    : %d || ", element->IdNum);
        printf("Blood type          : %s || ", element->type);
        printf("Composition         : %s\n", element->Composition);
        
		child = (element->left != NULL) ? element->left : element->right;
        if (parent == NULL) { // deleting root
            *root = child;
        } else if (parent->left == element) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        free(element);
        printf("Deleted %d (had one child).\n", Id);
        
    }

    // --- Case 3: Node has two children ---
    else {
    	printf("Blood bag number    : %d || ", element->IdNum);
        printf("Blood type          : %s || ", element->type);
        printf("Composition         : %s\n", element->Composition);
        // Find inorder successor
        succParent = element;
        succ = element->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        // Copy successor's data
        element->IdNum = succ->IdNum;
        strcpy(element->type, succ->type);
        strcpy(element->Composition, succ->Composition);


        // Adjust links
        if (succParent->left == succ)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        free(succ);
        printf("Deleted %d (had two children, replaced with inorder successor).\n", Id);
        printf("Blood bag number    : %d || ", element->IdNum);
        printf("Blood type          : %s || ", element->type);
        printf("Composition         : %s\n", element->Composition);
    }
    return true;
}


void displayTree(ptr *root)
{
ptr locRoot = *root;
	
	if (*root == NULL) {
        printf("Error: The tree is empty, nothing to delete.\n");
        return false;
    }

    printf("Contents of the tree:\n");
    if (locRoot->left == NULL && locRoot->right == NULL)
    {
        // single node tree
        printf("Blood bag number    : %d || ", locRoot->IdNum);
        printf("Blood type          : %s || ", locRoot->type);
        printf("Composition         : %s\n", locRoot->Composition);
    }
    else
    {
        // inorder traversal
        inorderTraversal(&locRoot);
    }
    printf("successfully display Tree");
    return;
}

void inorderTraversal (ptr *root)
{
	ptr p = *root;

    // traverse the left subtree
    if (p->left != NULL)
        inorderTraversal(&p->left);

    // visit the root
    printf("Blood bag number    : %d ||  ", p->IdNum);
    printf("Blood type          : %s ||  ", p->type);
    printf("Composition         : %s\n", p->Composition);

    // traverse the right subtree
    if (p->right != NULL)
        inorderTraversal(&p->right);	
}

bool exitProgram() 
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