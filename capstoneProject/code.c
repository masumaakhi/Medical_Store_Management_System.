#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include <conio.h>

//When you use 'ISEMPTY' in your code, the preprocessor replaces it with the defined text before the compiler processes the code. This effectively means that wherever you write ISEMPTY, it will be as if you wrote printf("\nEMPTY LIST:");./
#define ISEMPTY printf("\nEMPTY LIST:");

//Defined the maximum number of medicines, customers and admins, and the maximum length of a username or password.
#define MAX_MEDICINES 100
#define MAX_CUSTOMERS 100
#define MAX_ADMINS 10
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Structure to represent a medicine, User and Admin
//The typedef keyword is used to create an alias for a data type, making it easier to reference complex types with simpler names.
// This is a common practice in C programming to make code more readable and concise.
typedef struct {
    int id;
    char name[100];
    float price;
    int quantity;
	char email[50];
	char password[MAX_PASSWORD_LENGTH];
	char username[MAX_USERNAME_LENGTH];
	char phone[50];
} Medicine, User, Admin;

struct Admin {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};



// Structure for customer
typedef struct {
    char username[50];
    char password[50];
    char email[50];
    char name[50];
    char address[100];
    char phone[15];
    Medicine cart[50];
    int num_items;
} Customer;

// Medicines array and Customer array with MAX_MEDICINES and MAX_CUSTOMERS elements respectively
Medicine medicines[MAX_MEDICINES];
Customer customers[MAX_CUSTOMERS];
Admin admins[MAX_ADMINS];
int num_medicines = 0;
int num_customers = 0;
int num_admins = 0;
int customer_index = 0;


//
struct node
{
    int id;
    char name[20];
    int price;
    int qty;
    struct node *next;
};

struct node2
{
    int id;
    int qty;
    struct node2 *next2;
};

// Struct for cart
typedef struct CartNode {
    int id;
    int qty;
    struct CartNode* next2;
} CartNode;

//  creating type aliases snode for struct node and snode2 for struct node2.
typedef struct node snode;
typedef struct node2 snode2;

// Using the pointer to the struct node and struct node2 to create a new node and a new node2 respectively.
snode *newnode, *ptr, *prev,*temp;
snode *first = NULL, *last = NULL;
snode2 *newnode2, *ptr2, *prev2,*temp2;
snode2 *first2 = NULL, *last2 = NULL;
Customer *current_customer = NULL;
CartNode* first3 = NULL;
CartNode* last3 = NULL;
CartNode* newnode3;
CartNode* ptr3;
CartNode* temp3;
CartNode* prev3;


snode* create_node(int id, char *name, int price, int qty);
snode2* create_node2(int id, int qty);
CartNode* create_node3(int id, int qty);


// Function prototypes for the admin panel and the customer panel
void adminPanel();
void displayMenu();
bool adminSignIn();
void addMedicine();
void updateMedicine();
void deleteMedicine();
void displayInventory();
void customerPanel();
void customerSignUp();
bool customerSignIn();
void customerSignOut();
void searchMedicine();
void generateBill();

void addToCart();
void viewCart();
void modifyCart();
void checkout();
void checkStock(int id, int qty);
void updateCart(int id, int qty);

void deleteCart(int id);
void clearCart();
int posProduct(int id);
int posCart(int id);
void invoice();
void viewProfile();
void displayUpdatedMedicine();
void clearCustomerData();
void displayCheckout();
void placeOrder();
void order();
void loadMedicinesFromFile();




// Main function in this Program
int main() {
    system("color 0b");

    // Load medicines from file
    loadMedicinesFromFile();
    int choice;
      // Display menu and loop until user chooses to exit
    do {
        printf("\n===== Medical Store Management System =====\n");
        printf("1. Admin Panel\n");
        printf("2. Customer Panel\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
         // Process user's choice

        switch(choice) {
            case 1:
                // Call admin panel function
                adminPanel();
                break;
            case 2:
                // Call customer panel function
                customerPanel();
                break;
            case 3:
                // Exit the program
                printf("Exiting program. Goodbye!\n");
                exit(0);
                break;
            default:
                  // Inform user of invalid choice
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 4);// Repeat until user chooses to exit

    return 0;
}

// Function to load medicines from file
void loadMedicinesFromFile() {
    FILE* file = fopen("medicines.txt", "r");//creation file read mode
    if (file == NULL) {
        printf("Could not open medicines file. Starting with an empty inventory.\n");
        return;
    }

    int id, price, qty;
    char name[20];// array to store product name (max 20 characters)
    // Loop until end of file is reached
    while (fscanf(file, "%d %s %d %d", &id, name, &price, &qty) != EOF) {
 // Create a new node with the data read from file
        newnode = create_node(id, name, price, qty);
           // If this is the first node, set it as the first and last node
        if (first == NULL) {
            first = last = newnode;
             // Otherwise, add the new node to the end of the list
        } else {
            last->next = newnode;// link the new node to the previous last node
            last = newnode;// update the last node pointer
        }
    }

    fclose(file);//closing the file
}


// Admin Panel
void adminPanel() {
    system("color 0d");
   if(adminSignIn()) {

        system("cls");


        int choice;
          do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMedicine();
                break;
            case 2:
                updateMedicine();
                break;
            case 3:
                deleteMedicine();
                break;
            case 4:
                // displayInventory(medicines, count);
                displayInventory();
                break;
            case 5:
                searchMedicine();
                break;
            case 6:
                // main();
                // break;
                return;
            case 7:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
      } while (choice != 7);// Repeat until user chooses to exit
   }


    }





// Function to display the menu
void displayMenu() {

    printf("\n===== Admin Panel =====\n");

    printf("1. Add Medicine\n");
    printf("2. Update Medicine\n");
    printf("3. Delete Medicine\n");
    printf("4. Display Inventory\n");
    printf("5. Search Medicine\n");
    printf("6. Main Panel\n");
    printf("7. Exit\n");
}




// authenticate the admin
int authenticate(struct Admin *user) {
    // You can replace these with actual usernames and passwords
    char valid_username[] = "admin";
    char valid_password[] = "rms";

    // Compare provided username and password with valid ones
    if (strcmp(user->username, valid_username) == 0 && strcmp(user->password, valid_password) == 0) {
        return 1; // Authentication successful
    } else {
        return 0; // Authentication failed
    }
}

// AdminSignIn function

bool adminSignIn() {
    struct Admin user;

    printf("Enter username: ");
    scanf("%s", user.username);

    printf("Enter password: ");
    scanf("%s", user.password);
    // Attempt to authenticate the user

    if (authenticate(&user)) {
            // If authentication is successful, print a welcome message
        printf("Authentication successful! Welcome, %s.\n", user.username);
        return true;
    } else {
        // If authentication fails, print an error message
        printf("Authentication failed. Invalid username or password.\n");
        return false;
    }


}







// Function to add a new medicine
snode* create_node(int id, char *name, int price, int qty)
{
     // Allocate memory for the new node
    newnode=(snode*)malloc(sizeof(snode));
    if(newnode==NULL)
    {
        printf("\nSorry, no Products Available.");
        return 0;
    }
    else
    {
        // If memory allocation was successful, initialize the node's fields
        newnode->id=id;// set the product ID
        strcpy(newnode->name,name);// copy the product name into the node
        newnode->price=price; // set the product price
        newnode->qty=qty;// set the product quantity
        newnode->next=NULL;// set the next pointer to NULL (since it's a new node)
        return newnode;   // Return the newly created node
    }
}

// Function to create a new node in the second linked list
snode2* create_node2(int id, int qty)
{
    newnode2=(snode2*)malloc(sizeof(snode2));
    if(newnode2==NULL)
    {
        printf("\nSorry, no Products Available.");
        return 0;
    }
    else
    {
        newnode2->id=id;
        newnode2->qty=qty;
        newnode2->next2=NULL;  // Set the next pointer to NULL, since this is a new node
        return newnode2; // Return the newly created node
    }
}


// Function to AddMedicine
void addMedicine()
{

    system("cls");
    int id, price, qty,cnt=0,i;
    printf("\n=========================================================\n");
    printf("\t\t ADD MEDICINES!!\n");
    printf("=========================================================\n\n");
    char name[20],ch;
    FILE* file;
    printf("\nEnter the ID of the product: ");
    scanf("%d", &id);
    for (ptr = first;ptr != NULL;ptr = ptr->next)
    {
        if (ptr->id==id)
        {
            printf("Product ID already in use.");
            getch();
            return adminPanel();
        }

    }
    printf("\nEnter the name of the product: ");
    scanf("%s", name);
    printf("\nEnter the price of the product: ");
    scanf("%d", &price);
    printf("\nEnter the quantity of the product: ");
    scanf("%d", &qty);

    // Create a new node with the medicine details
    newnode = create_node(id, name, price, qty);
    // Determine the position where the new node should be inserted
   int pos = posProduct(id);

   // If the position is 0, it means the list is empty or the new node should be inserted at the beginnin
    if (pos == 0) {
        if (first == last && first == NULL) {
  // If the list is empty, set the first and last nodes to the new node
            first = last = newnode;
            first->next = NULL;
            last->next = NULL;
        } else {
             // If the list is not empty, insert the new node at the beginning
            temp = first;
            first = newnode;
            first->next = temp;
        }
    } else {
        // Traverse the list to find the correct position for the new node
        ptr = first;
        while (ptr != NULL) {
            ptr = ptr->next;
            cnt++;
        }
        if (pos == 1) { // If the position is 1, insert the new node at the beginning
            if (first == last && first == NULL) {
                first = last = newnode;
                first->next = NULL;
                last->next = NULL;
            } else {
                temp = first;
                first = newnode;
                first->next = temp;
            }
        } else if (pos > 1 && pos <= cnt) {
             // Insert the new node at the correct position
            ptr = first;
            for (i = 1; i < pos; i++) {
                prev = ptr;
                ptr = ptr->next;
            }
            prev->next = newnode;
            newnode->next = ptr;
        } else {
            printf("Product Not Found!!");
        }
    }
    // Open the file in append mode and write the new product details
    file = fopen("medicines.txt", "a");
    if (file == NULL) {
        printf("Error opening file!");
        return;
    }
    fprintf(file, "%d %s %d %d\n", id, name, price, qty);
    fclose(file); //closing the file

    printf("\nProduct Added Successfully!!");
    printf("\nDo you want to add another product[Y/N]? ");
    scanf("%s", &ch);
    if (ch == 'Y' || ch == 'y') {
        // system("cls");
        return addMedicine();
    }
    if (ch == 'N' || ch == 'n') {
        return;
    }

    getch();
}

// Function to DisplayUpdateMedicine
 void displayUpdatedMedicine(){
    int ch;
            printf("\n1. Update I'D.");
            printf("\n2. Update Name.");
            printf("\n3. Update Price.");
            printf("\n4. Update Quantity.");
            printf("\n5. Exit.");
            printf("\nEnter your choice: ");
            scanf("%d", &ch);
            switch(ch){
                case 1:
                    printf("Enter new I'D: ");
                    scanf(" %d", &ptr->id);
                    printf("Medicine updated successfully.\n");
                    return displayUpdatedMedicine();
                case 2:
                    printf("Enter new name: ");
                    scanf("%s", ptr->name);
                    printf("Medicine updated successfully.\n");
                    return displayUpdatedMedicine();

                case 3:
                    printf("Enter new price: ");
                    scanf("%d", &ptr->price);
                    printf("Medicine updated successfully.\n");
                    return displayUpdatedMedicine();

                case 4:
                    printf("Enter new quantity: ");
                    scanf("%d", &ptr->qty);
                    printf("Medicine updated successfully.\n");
                    return displayUpdatedMedicine();

                case 5:
                    return;

                default:
                    printf("Invalid choice!");
                    return;

            }while(ch != 5);

 }


// Function to update an existing medicine
void updateMedicine(){
    int id;

    displayInventory();

    printf("\nEnter ID of the medicine to update: ");
    scanf("%d", &id);

    for (ptr = first; ptr != NULL; ptr = ptr->next) {
        if(ptr->id == id){
            displayUpdatedMedicine();


            // Update the file with the new details
            // (This part would ideally involve reading all data, updating it, and writing it back)
            FILE* file = fopen("medicines.txt", "w");
            if (file == NULL) {
                printf("Error opening file for updating!");
                return;
            }
            // Traverse the linked list and extract the data from each node
            for (snode* tempPtr = first; tempPtr != NULL; tempPtr = tempPtr->next) {
                fprintf(file, "%d %s %d %d\n", tempPtr->id, tempPtr->name, tempPtr->price, tempPtr->qty);
            }
            fclose(file);

            return;
        }
    }
    printf("Medicine with ID %d not found.\n", id);
}



// Function to delete a medicine
void deleteMedicine()
{
    int id, cnt = 0, i,pos;

    displayInventory();  // Display the current inventory

    if (first == NULL)
    {
        ISEMPTY;
        printf("\nNo Products to delete\n");
    }
    else
    {
        printf("\nEnter the id of value to be deleted:");
        scanf(" %d", &id);
        // Find the position of the medicine with the given ID
        pos=posProduct(id);
        ptr = first;

        // If the medicine to delete is the first node in the list
        if (pos == 1)
        {


// Update the first node to point to the next node
            first = ptr->next;
            printf("\nElement deleted");
        }
        else
        {
             // Traverse the list to find the node to delete
            while (ptr != NULL)
            {
                ptr = ptr->next;
                cnt = cnt + 1;
            }
              // Check if the medicine was found in the list
            if (pos > 0 && pos <= cnt)
            {
                // Traverse the list again to find the node to delete
                ptr = first;
                for (i = 1;i < pos;i++)
                {
                    prev = ptr;
                    ptr = ptr->next;
                }
                prev->next = ptr->next;
            }
            else
            {
                printf("\nProduct Not Found!!");
                getch();
                return adminPanel();
            }
              // Free the memory allocated for the deleted node
            free(ptr);
            printf("\nElement deleted");
        }
    }
}


// The posProduct function is designed to find the position of a product with a given id in a linked
int posProduct(int id)
{
    int pos = 0;

        // Check if the inventory is empty
    if (first == NULL)
    {
        return pos;
    }
    else
    {
         // Traverse the linked list to find the product with the given ID
        for (ptr = first;ptr != NULL;ptr = ptr->next)
        {
              // Increment the position counter
            pos = pos + 1;
            // Check if the current node's ID matches the given ID
            if (ptr->id == id)
            {
                return pos;
            }
        }

    }

    return 0;

}

// Function to display the inventory
void displayInventory()
{
    system("cls");

    if (first == NULL)
    {
        ISEMPTY;
        printf("No Products Available. \n");
        getch();
        return adminPanel();
    }
    else
    {
        printf("\n=========================================================\n");
        printf("\t\t Product Details\n");
        printf("=========================================================\n\n");
        printf("ID\t Name\t Qty.\t Price(Rs.)\n\n");
        for (ptr = first;ptr != NULL;ptr = ptr->next)
        {
            printf("%d\t", ptr->id);
            printf("%s\t", ptr->name);
            printf("%d\t", ptr->qty);
            printf("%d\t", ptr->price);
            printf("\n");
        }
        printf("=========================================================\n");
    }
    getch();
}



// Function to Search the Medicines

void searchMedicine() {
    int id;
    printf("\nEnter ID of the medicine to search: ");
    scanf("%d", &id);
    printf("\n===================================\n");

    for (ptr = first;ptr != NULL;ptr = ptr->next) {
        if (ptr->id == id) {
            printf("Medicine found:\n");
            printf("ID\t Name\t Qty.\t Price(Rs.)\n\n");
            printf("%d\t%s\t%d\t%d\n", ptr->id, ptr->name, ptr->qty, ptr->price);
            return;
        }


    }
    printf("Medicine is not found.\n");

    getch();


}





// Customer Sign-in Function
bool customerSignIn() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("\nEnter customer username: ");
    scanf("%s", username);
    printf("\nEnter customer password: ");
    scanf("%s", password);

    FILE *file = fopen("customers.txt", "r");//creats file in read mode
    if (file == NULL) {
        printf("Error opening file.\n");
        return false;
    }

    char file_username[MAX_USERNAME_LENGTH];
    char file_password[MAX_PASSWORD_LENGTH];
    char file_email[50];
    char file_phone[50];
    
    // Read from the file until the end of the file is reached
    while (fscanf(file, "%s %s %s %s", file_username, file_password, file_email, file_phone) != EOF) {
            // Check if the username and password from the file match the input username and password
        if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0) {
            printf("\nCustomer Sign-in successful.\n");
            current_customer = (Customer *)malloc(sizeof(Customer));
            strcpy(current_customer->username, file_username);
            strcpy(current_customer->password, file_password);
            strcpy(current_customer->email, file_email);
            strcpy(current_customer->phone, file_phone);
            printf("\n*Welcome, %s!\n", current_customer->username);
            fclose(file);
            return true;
        }
    }

    fclose(file);
    printf("Invalid username or password...\n");
    return false;
}

void customerSignUp() {
    if (num_customers == MAX_CUSTOMERS) {
        printf("Cannot add more customers. Maximum limit reached.\n");
        return;
    }

    Customer new_customer;
    printf("\nEnter customer username: ");
    scanf("%s", new_customer.username);
    printf("\nEnter customer email: ");
    scanf("%s", new_customer.email);
    printf("\nEnter customer password: ");
    scanf("%s", new_customer.password);
    printf("\nEnter customer phone: ");
    scanf("%s", new_customer.phone);

    FILE *file = fopen("customers.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s %s %s %s\n", new_customer.username, new_customer.password, new_customer.email, new_customer.phone);
    fclose(file);

    printf("\nCustomer registered successfully.\n");
}

void viewProfile() {
    if (current_customer == NULL) {
        printf("Please sign in first.\n");
        return;
    }

    printf("\n===========================================\n");
    printf("\t\tCustomer Details : \n");
    printf("===========================================\n\n");
    printf("Username: %s\n", current_customer->username);
    printf("Email Address: %s\n", current_customer->email);
    printf("Password: %s\n", current_customer->password);
    printf("Phone Number: %s\n", current_customer->phone);
}

void customerSignOut() {
    if (current_customer != NULL) { // Check if a customer is currently signed in (i.e., current_customer is not NULL)
        printf("\nCustomer %s signed out successfully.\n", current_customer->username);
        free(current_customer);
        current_customer = NULL; // Set the current customer pointer to NULL to indicate no customer is signed in
    } else {
        printf("\nNo customer is currently signed in.\n");
    }
}

void customerPanel() {
    system("color 06");

    if (customerSignIn()) {
        int choice;
    do {
        printf("\n===== Customer Panel =====\n");

        printf("1. ViewProfile\n");
        printf("2. Add to Cart\n");
        printf("3. View Cart\n");
        printf("4. Payment\n");
        printf("5. SignOut\n");
        printf("6. Main Panel\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                viewProfile();
                break;
            case 2:
                addToCart();
                break;
            case 3:
                // Display cart contents
                printf("===== Cart =====\n");
                viewCart();
                break;
            case 4:
                generateBill();
                break;
            case 5:
                customerSignOut();
                return;
            case 6:
                // main();
                // break;
                return;
            case 7:
                printf("Exiting Customer Panel.\n");
                exit(1);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        } while(choice != 7);
    } else {
        printf("\nPlease sign up first.\n");
        customerSignUp();
        customerPanel();
    }
}




// Function to find the position of a cart item with a given ID
int posCart(int id)
{
    int pos = 0;

    if (first2 == NULL)
    {
        return pos;
    }
    else
    {
         // Iterate through the cart items
        for (ptr2 = first2;ptr2 != NULL;ptr2 = ptr2->next2)
        {
            pos = pos + 1;
            if (ptr2->id == id)
            {
                return pos;
            }
        }

    }
    return 0;

}




// Function to add a product to the cart
void addToCart()
{
    int id, qty,pos,cnt=0,i;
    char ch;
    FILE* file;
    system("cls");
    displayInventory();
    printf("\n Enter the ID of the product you wish to add to cart: ");
    scanf("%d",&id);
    
     // Search for the product in the inventory
    for (ptr = first;ptr != NULL;ptr = ptr->next)
    {
        // Check if the current product's ID matches the entered ID
        if (ptr->id == id)
        {
            printf("\n Enter the quantity[1-10]: ");
            scanf("%d",&qty);
            if (qty<=10) {
                // Check if the product is in stock
                checkStock(id, qty);
            
             // Create a new node for the cart with the product ID and quantity
                newnode2 = create_node2(id, qty);
                
                     // Find the position of the product in the cart
                pos=posCart(id);
                if(pos==0)
                {
                         // Check if the cart is empty
                    if (first2 == last2 && first2 == NULL)
                    {
                        // Initialize the cart with the new node
                        first2 = last2 = newnode2;
                        first2->next2 = NULL;
                        last2->next2 = NULL;
                    }
                    else
                    {
                              // Insert the new node at the beginning of the cart
                        temp2 = first2;
                        first2 = newnode2;
                        first2->next2 = temp2;
                    }
                }
                else
                {
                    ptr2 = first2;
                    while (ptr2 != NULL)
                    {
                        ptr2 = ptr2->next2;
                        cnt++;
                    }
                    
                     // If the product is at position 1, insert it at the beginning
                    if (pos == 1)
                    {
                        if (first2 == last2 && first2 == NULL)
                        {
                            first2 = last2 = newnode2;
                            first2->next2 = NULL;
                            last2->next2 = NULL;
                        }
                        else
                        {
                            temp2 = first2;
                            first2 = newnode2;
                            first2->next2 = temp2;
                        }
                    }
                    else if (pos>1 && pos<=cnt)
                    {
                        ptr2 = first2;
                        for (i = 1;i < pos;i++)
                        {
                            prev2 = ptr2;
                            ptr2 = ptr2->next2;
                        }
                        prev2->next2 = newnode2;
                        newnode2->next2 = ptr2;
                    }
                    else
                    {
                        printf("Product Not Found!!");
                    }
                }
                printf("\nProduct Added Successfully!!");
            }
            else
            {
                printf("\n Quantity can't exceed 10.");

                getch();
                return;
            }


              // Open the file in append mode and write the product details to the cart file
                file = fopen("cart.txt", "a");
                if (file == NULL) {
                    printf("Error opening file!");
                    return;
                }
                fprintf(file, "%d %d\n", id, qty);
                fclose(file);
            printf("\nDo you want to add another product[Y/N]? ");
            scanf("%s",&ch);
            if (ch == 'Y'||ch == 'y')
            {
                system("cls");
                return addToCart();
            }
            if (ch == 'N'||ch == 'n')
            {
                return;
            }
        }

    }


   // printf("\nProduct Not Found!!");
    getch();
    return;

}


// Function to check if a product is in stock
void checkStock(int id, int qty)
{
    if (first == NULL)
    {
          // If the inventory is empty, display an error message
        ISEMPTY;
    }
    else
        
    {
        
        // Iterate through the inventory to find the product with the given ID
        for (ptr = first;ptr != NULL;ptr = ptr->next)
        {
            
            // Check if the current product's ID matches the given ID
            if (ptr->id == id)
            {
                // Check if the available quantity is less than the requested quantity
                if (ptr->qty<qty)
                {
                    printf("Not enough products available.");
                    getch();
                    return;
                }
            }
        }

    }
}

// Function to view the products in the cart

void viewCart()
{
    system("cls");

    if (first == NULL)
    {
        ISEMPTY;
        printf("No Products Available in Cart. \n");
        getch();
        return customerPanel();
    }
    else
    {
        printf("\n=========================================================\n");
        printf("\t\t PRODUCTS IN CART:\n");
        printf("\n=========================================================\n");
        printf("ID\t Name\t Qty.\t Price(Rs.)\n\n");
        for (ptr2 = first2;ptr2 != NULL;ptr2 = ptr2->next2)
        {
            printf("%d\t", ptr2->id);
            for (ptr = first;ptr != NULL;ptr = ptr->next)
            {
                if (ptr->id==ptr2->id)
                {
                    printf("%s\t", ptr->name);
                    printf("%d\t", ptr2->qty);
                    printf("%d\t", ptr->price);
                }

            }
            printf("\n");
        }
        printf("=========================================================\n");
    }
    getch();
}



// Function to generate the bill and prompt the user for payment method
void generateBill()
{
    int ch;
    
    // Clear the screen and set the text color to blue
    system("cls");
    system("color 0B");
    printf("========Generate Payment Method========");
    printf("\n1. Modify your cart.");
    printf("\n2. Proceed to Checkout.");
    printf("\n0. Back");
    printf("\nPlease enter your Choice: ");
    scanf("%d", &ch);
    
     // Switch statement to handle the user's choice
    switch (ch)
    {
        case 1: {
            modifyCart();
            break;
        }
        case 2: {
            checkout();
            break;
        }
        case 0:
        {
            return;
        }
        default: {
            printf("Valid choice not entered!");
            getch();
            return generateBill();
        }
    }
}

// Function to modify the cart
void modifyCart()
{
    int id,qty,ch;
    
    // Clear the screen
    system("cls");
    viewCart();
    printf("\nEnter the ID of the Product you wish to Modify: ");
    scanf("%d",&id);
    
    // Iterate through the cart to find the product with the matching ID
    for (ptr2 = first2;ptr2 != NULL;ptr2 = ptr2->next2) {
        if (ptr2->id == id)
        {
            printf("\n1. Delete Product.");
            printf("\n2. Modify the quantity.");
            printf("\n0. Back.");
            printf("\nPlease enter your Choice: ");
            scanf("%d", &ch);
            switch (ch) {
                case 1: {
                    deleteCart(id);
                    getch();
                    return generateBill();
                }
                case 2: {
                    printf("\nEnter the new quantity[1-10]: ");
                    scanf("%d", &qty);
                    if (qty <= 10) {
                        updateCart(id, qty);
                        getch();
                        return generateBill();
                    } else {
                        printf("Quantity can't exceed 10.");
                        getch();
                        return modifyCart();
                    }
                }
                case 0: {
                    return;
                }
                default: {
                    printf("Valid choice not entered!");
                    getch();
                    return generateBill();
                }
            }

        }

    }
    printf("\n Product Not Found!!");
    getch();
    return generateBill();

}

// Function to delete a product from the cart
void deleteCart(int id)
{
    int pos,cnt=0,i;
    if (first2 == NULL)
    {
        // Display an error message if the cart is empty
        ISEMPTY;
        printf("\nNo Products to delete\n");
    }
    else
    {
        
        // Find the position of the product in the cart
        pos = posCart(id);
        ptr2 = first2;
        
        // Check if the product is at the first position
        if (pos == 1)
        {
            first2 = ptr2->next2;
            printf("\nProduct deleted from Cart.");
        }
        else
        {
             // Count the number of nodes in the cart
            while (ptr2 != NULL)
            {
                ptr2 = ptr2->next2;
                cnt = cnt + 1;
            }
            
            // Check if the product position is valid
            if (pos > 0 && pos <= cnt)
            {
                ptr2 = first2;
                // Traverse the cart to find the node before the product
                for (i = 1; i < pos; i++)
                {
                    prev2 = ptr2;
                    ptr2 = ptr2->next2;
                }
                prev2->next2 = ptr2->next2;
            }
            else
            {
                printf("\nProduct Not Found!!");
                getch();
                return generateBill();
            }
            free(ptr);
            printf("\nProduct deleted");
        }
    }
}
 //function to update any product in the cart
void updateCart(int id, int qty)
{
    if (first2 == NULL)
    {
        ISEMPTY;
    }
    else
    {
        for (ptr2 = first2; ptr2 != NULL; ptr2 = ptr2->next2)
        {
            if (ptr2->id == id)
            {
                ptr2->qty = qty;
                return generateBill();

            }
        }
    }
}



// Function to process the order
void order(){
    viewCart();

    printf("\nMedicines order successfully!!");
    printf("\nThank you for Shopping!!");

}

// Function to place an order
void placeOrder(){
    viewCart();
    char ch;
    printf("\n Are show your invoice[Y/N]?");
    scanf("%s",&ch);
    // Check if the user wants to view their invoice
    if (ch == 'Y'||ch == 'y')
    {
       return invoice();

    }
    if (ch == 'N'||ch == 'n')
    {
        return order();

    }


        getch();



}

// Function to display the checkout options
void displayCheckout(){
    int choise;
        printf("\n1. Place Order.");
        printf("\n2. Clear Checkout.");
        printf("\n3. Back.");
        printf("\nPlease enter your Choice: ");
        scanf("%d", &choise);
        
          // Use a switch statement to handle the user's choice
        switch (choise) {
            case 1: {
                placeOrder();
                break;
            }
            case 2: {
                clearCart();
                break;
            }
            case 3: {
                return;
            }
            default: {
                printf("Valid choice not entered!");
                getch();
                return displayCheckout();
            }
        }
}

// Function to handle the checkout process
void checkout()
{
    int total=0;

    viewCart();
    for (ptr2 = first2;ptr2 != NULL;ptr2 = ptr2->next2)
    {
        for (ptr = first;ptr != NULL;ptr = ptr->next)
        {
            if (ptr->id==ptr2->id)
            {
                   // Calculate the total cost for this item
                total+=(ptr2->qty)*(ptr->price);
            }
        }
        printf("\n");
    }
    printf("\n===================>> Total Bill Amount [Rs:  %d   ]\n\n",total);
    displayCheckout();

    getch();

}

//function for clearing the cart
void clearCart()
{
    for (ptr2 = first2;ptr2 != NULL;ptr2 = ptr2->next2)
    {
        deleteCart(ptr2->id);
    }
}


// Function to generate an invoice
void invoice() {
    system("cls");
    int total = 0;
    FILE *file;
    file = fopen("invoice.txt", "w"); // Open the file in write mode

    if (first == NULL) {
        fprintf(file, "No Products Available in Cart.\n");
        printf("No Products Available in Cart. \n");
        
        // Wait for the user to press a key
        getch();
        fclose(file); // Close the file before returning
        return customerPanel();
    } else {
        fprintf(file, "\n=========================================================\n");
        fprintf(file, "\t\t Provide Invoice\n");
        fprintf(file, "=========================================================\n");
        fprintf(file, "ID\t Name\t Qty.\t Price(Rs.)\tTotal\n\n");

        printf("\n=========================================================\n");
        printf("\t\t Provide Invoice\n");
        printf("=========================================================\n");
        printf("ID\t Name\t Qty.\t Price(Rs.)\t Total\n\n");

        for (ptr2 = first2; ptr2 != NULL; ptr2 = ptr2->next2) {
            fprintf(file, "%d\t", ptr2->id);
            printf("%d\t", ptr2->id);

            for (ptr = first; ptr != NULL; ptr = ptr->next) {
                if (ptr->id == ptr2->id) {
                    total += (ptr2->qty) * (ptr->price);
                    fprintf(file, "%s\t %d\t %d\t\t %d\n", ptr->name, ptr2->qty, ptr->price, ptr->price * ptr2->qty);
                    printf("%s\t %d\t %d\t\t %d\n", ptr->name, ptr2->qty, ptr->price, ptr->price * ptr2->qty);
                }
            }
            fprintf(file, "\n");
            printf("\n");
        }
        fprintf(file, "=========================================================\n\n");
        printf("=========================================================");
    }

    fprintf(file, "\n====================================================\n");
    fprintf(file, "Total Bill Amount: [Rs:  %d   ]\n\n", total);
    fprintf(file, "====================================================\n");
    fprintf(file, "\nThank you for Shopping\n");
    fprintf(file, "Visit Again\n");

    printf("\n====================================================\n");
    printf("Total Bill Amount: [Rs:  %d   ]\n\n", total);
    printf("====================================================\n");
    printf("\nThank you for Shopping\n");
    printf("Visit Again\n");

    fclose(file); // Close the file after writing
     getch();
}