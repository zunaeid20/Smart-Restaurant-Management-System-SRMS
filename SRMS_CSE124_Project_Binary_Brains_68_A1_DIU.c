/* #################### SRMS CSE124 Project Binary Brains 68_A1 DIU #################### */

/* ----------------- Libraries (3) - Both ----------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ----------------- Structures (3) - Both ----------------- */

struct food // For the descriptions of the menu items; For the structure of the menu
{
    char id[20];
    char name[30];
    float price;
    int stockCount; // NEW ADDED CODE: For managing stock quantity
    struct food *next;
};

struct food *start = NULL;

struct orderItem // For the order of a particular table
{
    char foodID[20];
    int qty;
    struct orderItem *next;
};

struct orderNode // For the queue of the tables gave order
{
    int tableNo;
    struct orderItem *items;
    struct orderNode *next;
};

struct orderNode *pendingOrders = NULL;

/* ----------------- File Operations (2) - Both ----------------- */

void saveData() // For saving all the operational data permanently
{
    FILE *fp = fopen("menu.txt", "w");
    if(fp == NULL)
        return;

    struct food *i = start;
    while(i != NULL)
    {
        // UPDATED CODE: Added stockCount to save file
        fprintf(fp, "%s;%s;%.2f;%d\n", i->id, i->name, i->price, i->stockCount);
        i = i->next;
    }
    fclose(fp);
}

void loadData() // For loading all the previous operational data just after starting the program
{
    FILE *fp = fopen("menu.txt", "r");
    if(fp == NULL) return;

    char line[200];
    while(fgets(line, sizeof(line), fp))
    {
        char id[20], name[30];
        float price;
        int stock; // NEW ADDED CODE: Variable for reading stock

        // UPDATED CODE: Reading 4 items now including stock
        if(sscanf(line, "%19[^;];%29[^;];%f;%d", id, name, &price, &stock) == 4)
        {
            struct food *newnode = (struct food*)malloc(sizeof(struct food));
            strcpy(newnode->id, id);
            strcpy(newnode->name, name);
            newnode->price = price;
            newnode->stockCount = stock; // NEW ADDED CODE: Assigning stock
            newnode->next = NULL;

            if(start == NULL)
            {
                start = newnode;
            }
            else
            {
                struct food *t = start;
                while(t->next != NULL) t = t->next;
                t->next = newnode;
            }
        }
    }
    fclose(fp);
}

/* #################### SINGLY LINKED LIST OPERATIONS (10) #################### */

/* ----------------- Menu Print (1) - Both ----------------- */

void printLinkList() // For printing the menu
{
    printf("\n-------------------- Smart Restaurant Menu --------------------\n");
    struct food *i = start;
    if(i == NULL)
    {
        printf("\nNo items available.\n");
        printf("\n---------------------------------------------------------------\n");
        return;
    }
    while(i != NULL)
    {
        // UPDATED CODE: Added Logic to Show Stock or Stock Out
        if(i->stockCount > 0)
        {
            printf("\nID: %-10s | %-20s | Price: %.2f Tk | Stock: %d\n", i->id, i->name, i->price, i->stockCount);
        }
        else
        {
            printf("\nID: %-10s | %-20s | Price: %.2f Tk | *** STOCK OUT ***\n", i->id, i->name, i->price);
        }
        i = i->next;
    }
    printf("\n---------------------------------------------------------------\n");
}

/* ----------------- Insert Functions for Inserting Food Items in the Menu (3) - Manager ----------------- */

void InsertBeginFood() // For inserting in the beginning of the menu
{
    // UPDATED CODE: ID and Name validation loop
    struct food *newnode = (struct food*)malloc(sizeof(struct food));
    struct food *temp;
    int exists;

    // STEP 1: ID Validation Loop
    while(1)
    {
        printf("Enter Food ID: ");
        scanf("%19s", newnode->id);

        temp = start;
        exists = 0;

        // Check if ID exists
        while(temp != NULL)
        {
            if(strcmp(temp->id, newnode->id) == 0)
            {
                exists = 1;
                break;
            }
            temp = temp->next;
        }

        if(exists) printf("Error: This ID already exists! Please enter a unique ID.\n");

        else  break;
    }

    // STEP 2: Name Validation Loop
    while(1)
    {
        printf("Enter Food Name: ");
        scanf(" %[^\n]", newnode->name);

        temp = start;
        exists = 0;

        // Check if Name exists
        while(temp != NULL)
        {
            if(strcmp(temp->name, newnode->name) == 0)
            {
                exists = 1;
                break;
            }
            temp = temp->next;
        }

        if(exists)   printf("Error: This Name already exists! Please enter a unique Name.\n");

        else break;

    }
    //printf("Enter Food ID: ");
    //scanf("%19s", newnode->id);
    // printf("Enter Food Name: ");
    // scanf(" %[^\n]", newnode->name);
    printf("Enter Food Price: ");
    scanf("%f", &newnode->price);

    printf("Enter Stock Quantity: "); // NEW ADDED CODE
    scanf("%d", &newnode->stockCount); // NEW ADDED CODE

    newnode->next = start;
    start = newnode;

    printf("Item added at beginning.\n");
    saveData();
}

void InsertLastFood() // For inserting in the last of the menu
{
    // UPDATED CODE: ID and Name validation loop
    struct food *newnode = (struct food*)malloc(sizeof(struct food));
    struct food *temp;
    int exists;

    // STEP 1: ID Validation Loop
    while(1)
    {
        printf("Enter Food ID: ");
        scanf("%19s", newnode->id);

        temp = start;
        exists = 0;

        // Check if ID exists
        while(temp != NULL)
        {
            if(strcmp(temp->id, newnode->id) == 0)
            {
                exists = 1;
                break;
            }
            temp = temp->next;
        }

        if(exists) printf("Error: This ID already exists! Please enter a unique ID.\n");

        else  break;
    }

    // STEP 2: Name Validation Loop
    while(1)
    {
        printf("Enter Food Name: ");
        scanf(" %[^\n]", newnode->name);

        temp = start;
        exists = 0;

        // Check if Name exists
        while(temp != NULL)
        {
            if(strcmp(temp->name, newnode->name) == 0)
            {
                exists = 1;
                break;
            }
            temp = temp->next;
        }

        if(exists)   printf("Error: This Name already exists! Please enter a unique Name.\n");

        else break;

    }

    // printf("Enter Food ID: ");
    // scanf("%19s", newnode->id);
    // printf("Enter Food Name: ");
    // scanf(" %[^\n]", newnode->name);
    printf("Enter Food Price: ");
    scanf("%f", &newnode->price);

    printf("Enter Stock Quantity: "); // NEW ADDED CODE
    scanf("%d", &newnode->stockCount); // NEW ADDED CODE

    newnode->next = NULL;

    if(start == NULL) start = newnode;

    else
    {
        struct food *i = start;
        while(i->next != NULL) i = i->next;
        i->next = newnode;
    }

    printf("Item added at last.\n");
    saveData();
}

void InsertAnyFood() // For inserting in any position of the menu; For inserting after any item of the menu
{
    if(start == NULL)
    {
        printf("No items available in the menu.\n");
        return;
    }

    char x[20];
    printf("After which food ID you want to insert: ");
    scanf("%19s", x);

    struct food *i = start;
    while(i != NULL && strcmp(i->id, x) != 0) i = i->next;
    if(i == NULL)
    {
        printf("Given ID not found.\n");
        return;
    }

    // UPDATED CODE: ID and Name validation loop
    struct food *newnode = (struct food*)malloc(sizeof(struct food));
    struct food *temp;
    int exists;

    // STEP 1: ID Validation Loop
    while(1)
    {
        printf("Enter Food ID: ");
        scanf("%19s", newnode->id);

        temp = start;
        exists = 0;

        // Check if ID exists
        while(temp != NULL)
        {
            if(strcmp(temp->id, newnode->id) == 0)
            {
                exists = 1;
                break;
            }
            temp = temp->next;
        }

        if(exists) printf("Error: This ID already exists! Please enter a unique ID.\n");

        else  break;
    }

    // STEP 2: Name Validation Loop
    while(1)
    {
        printf("Enter Food Name: ");
        scanf(" %[^\n]", newnode->name);

        temp = start;
        exists = 0;

        // Check if Name exists
        while(temp != NULL)
        {
            if(strcmp(temp->name, newnode->name) == 0)
            {
                exists = 1;
                break;
            }
            temp = temp->next;
        }

        if(exists)   printf("Error: This Name already exists! Please enter a unique Name.\n");

        else break;

    }
    //printf("Enter Food ID: ");
    //scanf("%19s", newnode->id);
    // printf("Enter Food Name: ");
    // scanf(" %[^\n]", newnode->name);
    printf("Enter Food Price: ");
    scanf("%f", &newnode->price);

    printf("Enter Stock Quantity: "); // NEW ADDED CODE
    scanf("%d", &newnode->stockCount); // NEW ADDED CODE

    newnode->next = i->next;
    i->next = newnode;

    printf("Item added after ID %s.\n", x);
    saveData();
}

/* ----------------- Delete Functions for Deleting Food Items from the Menu (3) - Manager ----------------- */

void deleteBeginFood() // For deleting from the beginning of the menu
{
    if(start == NULL)
    {
        printf("No items available in the menu.\n");
        return;
    }

    struct food *temp = start;
    start = start->next;
    free(temp);

    printf("Item deleted from beginning.\n");
    saveData();
}

void deleteLastFood() // For deleting from the last of the menu
{
    if(start == NULL)
    {
        printf("No items available in the menu.\n");
        return;
    }

    if(start->next == NULL)
    {
        struct food *temp = start;
        start = NULL;
        free(temp);

        printf("Item deleted from last.\n");
        saveData();
        return;
    }

    struct food *i = start;
    while(i->next->next != NULL) i = i->next;
    struct food *temp = i->next;
    i->next=NULL;
    free(temp);

    printf("Item deleted from last.\n");
    saveData();
}

void deleteAnyFood() // For deleting from any position of the menu; For deleting by ID number
{
    if(start == NULL)
    {
        printf("No items available in the menu.\n");
        return;
    }

    char y[20];
    printf("Which food ID you want to delete: ");
    scanf("%19s", y);

    if(strcmp(start->id, y) == 0)
    {
        struct food *temp = start;
        start = start->next;
        free(temp);

        printf("Item deleted having ID %s.\n", y);
        saveData();
        return;
    }

    struct food *i = start;
    while(i->next != NULL && strcmp(i->next->id, y) != 0) i = i->next;
    if(i->next == NULL)
    {
        printf("Given ID not found.\n");
        return;
    }

    struct food *temp = i->next;
    i->next = i->next->next;
    free(temp);
    printf("Item deleted having ID %s.\n", y);
    saveData();
}

/* ----------------- Update, Search and Count Functions for Menu (3) - Manager ----------------- */

void updateNodeFood() // For updating any food item in the menu by the ID number
{
    char x[20];
    printf("Enter the food ID to update: ");
    scanf("%19s", x);

    struct food *i = start;
    while(i != NULL && strcmp(i->id, x) != 0)
        i = i->next;

    if(i == NULL)
    {
        printf("Food ID %s not found.\n", x);
        return;
    }
// ID and Name validation starting
    char temp_id[20];
    char temp_name[50];

    struct food *temp;
    int exists;

    int id_valid = 0;
    int name_valid = 0;

    while(1)
    {
        // ID checking
        if(id_valid == 0)
        {
            printf("Enter New Food ID: ");
            scanf("%19s", temp_id);

            temp = start;
            exists = 0;
            while(temp != NULL)
            {

                if(temp != i && strcmp(temp->id, temp_id) == 0)
                {
                    exists = 1;
                    break;
                }
                temp = temp->next;
            }

            if(exists)
            {
                printf("Error: This ID already exists in the menu! Please try again.\n");
                continue;
            }
            else
            {
                id_valid = 1;
            }
        }

        // STEP 2: Name Check
        if(name_valid == 0)
        {
            printf("Enter New Food Name: ");
            scanf(" %[^\n]", temp_name);

            temp = start;
            exists = 0;
            while(temp != NULL)
            {
                if(temp != i && strcmp(temp->name, temp_name) == 0)
                {
                    exists = 1;
                    break;
                }
                temp = temp->next;
            }

            if(exists)
            {
                printf("Error: This Name already exists in the list! Please try again.\n");
                continue;
            }
            else
            {
                name_valid = 1;
            }
        }

        // Finalize
        if(id_valid == 1 && name_valid == 1)
        {

            strcpy(i->id, temp_id);
            strcpy(i->name, temp_name);
            break;
        }
    }

    printf("Enter New Food Price: ");
    scanf("%f", &i->price);

    printf("Enter New Stock Quantity: "); // NEW ADDED CODE
    scanf("%d", &i->stockCount); // NEW ADDED CODE

    printf("Description of the food item is updated.\n");
    saveData();
}

void searchNodeFood() // For searching any food item in the menu by the ID number
{
    char key[20];
    printf("Enter the food ID to search: ");
    scanf("%19s", key);
    struct food *i = start;
    int pos = 1;
    while(i != NULL)
    {
        if(strcmp(i->id, key) == 0)
        {
            printf("Found at the position %d. Name: %s, Price: %.2f Tk, Stock: %d\n", // UPDATED CODE (Shown Stock)
                   pos, i->name, i->price, i->stockCount);
            return;
        }
        i = i->next;
        pos++;
    }
    printf("Food ID %s not found.\n", key);
}

void countNodeFood() // For counting the food items of the menu
{
    struct food *i = start;
    int count = 0;
    while(i != NULL)
    {
        count++;
        i = i->next;
    }
    printf("Total food items: %d\n", count);
}


/* #################### QUEUE AND NESTED NODE OPERATIONS (3) #################### */

/* ----------------- Confirming Placed Orders - Enqueue and Nested Node Creation (1) - Customer ----------------- */

void addPendingOrder(int table, char *foodID, int qty) // Confirming placed orders by providing the table number, food id and quantity
{
    struct orderNode *ptr = pendingOrders;
    while(ptr != NULL)
    {
        if(ptr->tableNo == table) break;
        ptr = ptr->next;
    }

    struct orderItem *newIt = (struct orderItem*)malloc(sizeof(struct orderItem));
    strcpy(newIt->foodID, foodID);
    newIt->qty = qty;
    newIt->next = NULL;

    if(ptr != NULL)
    {
        if(ptr->items == NULL)
        {
            ptr->items = newIt;
        }

        else
        {
            struct orderItem *it = ptr->items;
            while(it->next != NULL) it = it->next;
            it->next = newIt;
        }
    }

    else
    {
        struct orderNode *newOrd = (struct orderNode*)malloc(sizeof(struct orderNode));
        newOrd->tableNo = table;
        newOrd->items = newIt;
        newOrd->next = NULL;

        if(pendingOrders == NULL) pendingOrders = newOrd;

        else
        {
            struct orderNode *t = pendingOrders;
            while(t->next != NULL) t = t->next;
            t->next = newOrd;
        }
    }
}

/* ----------------- Viewing Pending Orders - Printing Queue with Nested Node (1) - Both ----------------- */

void viewAllPendingOrders() // For viewing pending orders
{
    printf("\n====== Pending Orders ======\n");

    if(pendingOrders == NULL)
    {
        printf("\nNo pending orders available.\n");
        return;
    }

    struct orderNode *p = pendingOrders;

    while(p != NULL)
    {
        printf("\nTable %d: \n", p->tableNo);

        struct orderItem *it = p->items;
        float tableTotal = 0; // Per table total

        while(it != NULL)
        {
            struct food *f = start;

            while(f != NULL && strcmp(f->id, it->foodID) != 0)
                f = f->next;

            if(f != NULL)
            {
                float itemTotal = f->price * it->qty;
                tableTotal += itemTotal;

                printf("  %s x %d (%.2f Tk)\n", f->name, it->qty, itemTotal);
            }
            else
                printf("  Unknown Food ID %s x %d\n", it->foodID, it->qty);

            it = it->next;
        }

        printf("--- Total Bill: %.2f Tk ---\n", tableTotal);

        p = p->next;
    }

    printf("\n============================\n");
}

/* ----------------- Serving Orders - Dequeue (1) - Manager ----------------- */

void serveNextOrder() // For serving pending orders
{
    if(pendingOrders == NULL)
    {
        printf("No pending orders available.\n");
        return;
    }

    struct orderNode *serve = pendingOrders;
    printf("\nServing Table %d: \n", serve->tableNo);
    struct orderItem *it = serve->items;

    while(it != NULL)
    {
        struct food *f = start;
        while(f != NULL && strcmp(f->id, it->foodID) != 0) f = f->next;
        if(f != NULL) printf("  %s x %d (%.2f Tk)\n", f->name, it->qty, f->price * it->qty);
        else printf("  Unknown Food ID %s x %d\n", it->foodID, it->qty);
        it = it->next;
    }

    pendingOrders = pendingOrders->next;

    it = serve->items;
    while(it != NULL)
    {
        struct orderItem *tmp = it;
        it = it->next;
        free(tmp);
    }
    free(serve);
    printf("Order served.\n");
}


/* #################### MODES (4) #################### */

/* ----------------- Customer Mode (2) - Customer ----------------- */

void orderFood(int table) // Placing orders by providing the table number, food id and quantity
{
    char id[25];
    int qty;
    char more = 'y';
    float total = 0.0f;

    while(more == 'y' || more == 'Y')
    {

        printf("Enter the food ID to order: ");
        scanf("%24s", id);
        printf("Enter the quantity: ");

        if(scanf("%d", &qty) != 1)
        {
            while(getchar()!='\n');
            printf("Invalid quantity!\n");
            continue;
        }

        if(qty <= 0)
        {
            printf("Quantity must be a positive number.\n");
            continue;
        }

        struct food *i = start;
        int found = 0;

        while(i != NULL)
        {
            if(strcmp(i->id, id) == 0)
            {
                // NEW ADDED CODE: Checking Stock Logic Started
                if(i->stockCount >= qty)
                {
                    i->stockCount = i->stockCount - qty; // Decreasing stock
                    saveData(); // Saving Updated Stock to file

                    total += i->price * qty;
                    printf("Added %d x %s (%.2f Tk)\n", qty, i->name, i->price * qty);
                    addPendingOrder(table, id, qty);
                }
                else if(i->stockCount == 0)
                {
                    printf("Sorry! This item is OUT OF STOCK.\n");
                }
                else
                {
                    printf("Insufficient Stock! Only %d items available.\n", i->stockCount);
                }
                // NEW ADDED CODE: Checking Stock Logic Ended

                found = 1;
                break;
            }
            i = i->next;
        }
        if(!found) printf("Given ID not found.\n");

        printf("Order more? (y/n): ");
        scanf(" %c", &more);
    }

    if(total > 0) // UPDATED CODE: Added this check
    {
        printf("\nTotal payable: %.2f Tk.\n", total);
        printf("Your order will be served shortly.\n");
    }
}

void customerMode() // ##### CUSTOMER INTERFACE #####
{
    int table;
    printf("Enter Your Table Number (1-50): ");
    scanf("%d", &table);

    if(table < 1 || table > 50)
    {
        printf("Invalid Table Number! (Choice From 1 to 50.)\n");
        //return;
        customerMode(); // Updated

    }
    else // Updated
    {
        printf("Table Number %d Selected.\n", table);

        int choice;
        while(1)
        {
            printf("\n========= CUSTOMER MODE =========\n");
            printf("1. Show The Restaurant Menu\n");
            printf("2. Select & Order Items\n");
            printf("3. View ALL Pending Orders\n");
            printf("4. Back To Main Menu\n");
            printf("\n");
            printf("Enter Your Choice (1-4): ");

            if(scanf("%d", &choice) != 1)
            {
                while(getchar()!='\n');
                printf("Invalid Choice!\n");
                continue;
            }

            switch(choice)
            {
            case 1:
                printLinkList();
                break;
            case 2:
                orderFood(table);
                break;
            case 3:
                viewAllPendingOrders();
                break;
            case 4:
                return;
            default:
                printf("Invalid Choice!\n");
                break;
            }
        }
    }
}

/* ----------------- Manager Mode (2) - Manager ----------------- */

int managerLogin()  // For passwording the manager mode
{
    char pass[50];
    printf("Enter The Password: ");
    scanf("%49s", pass);
    if((strcmp(pass, "222") == 0) || (strcmp(pass, "223") == 0) || (strcmp(pass, "042") == 0) || (strcmp(pass, "017") == 0) || (strcmp(pass, "457") == 0)) return 1;
    printf("Invalid Password. Try Again.\n");
    managerLogin(); // Updated 2 lines
    // return 0;
}

void managerMode()  // ##### MANAGER INTERFACE #####
{
    if(!managerLogin()) return;
    int ch;

    while(1)
    {
        printf("\n========= MANAGER MODE =========\n");
        printf("1. Show The Restaurant Menu\n");
        printf("2. Add Item (First)\n");
        printf("3. Add Item (Last)\n");
        printf("4. Add Item (Any-ID)\n");
        printf("5. Delete Item (First)\n");
        printf("6. Delete Item (Last)\n");
        printf("7. Delete Item (Any-ID)\n");
        printf("8. Update Item (By ID)\n");
        printf("9. Search Item (By ID)\n");
        printf("10. Count Items\n");
        printf("11. View All Pending Orders\n");
        printf("12. Serve Next Order\n");
        printf("13. Back To Main Menu\n");
        printf("\n");
        printf("Enter Your Choice (1-13): ");

        if(scanf("%d", &ch) != 1)
        {
            while(getchar()!='\n');
            printf("Invalid Choice!\n");
            continue;
        }

        switch(ch)
        {
        case 1:
            printLinkList();
            break;
        case 2:
            InsertBeginFood();
            break;
        case 3:
            InsertLastFood();
            break;
        case 4:
            InsertAnyFood();
            break;
        case 5:
            deleteBeginFood();
            break;
        case 6:
            deleteLastFood();
            break;
        case 7:
            deleteAnyFood();
            break;
        case 8:
            updateNodeFood();
            break;
        case 9:
            searchNodeFood();
            break;
        case 10:
            countNodeFood();
            break;
        case 11:
            viewAllPendingOrders();
            break;
        case 12:
            serveNextOrder();
            break;
        case 13:
            return;
        default:
            printf("Invalid Choice.\n");
            break;
        }
    }
}

/* ----------------- Main (1) ----------------- */

int main()
{
    loadData();
    int choice;
    while(1)
    {
        printf("##################################################\n");
        printf("--------------------------------------------------\n");
        printf("|       SMART RESTAURANT MANAGEMENT SYSTEM       |\n");
        printf("--------------------------------------------------\n");
        printf("##################################################\n");
        printf("\n1. MANAGER\n2. CUSTOMER\n3. EXIT\n\nEnter Choice (1-3): ");


        if(scanf("%d", &choice) != 1)
        {
            while(getchar()!='\n');
            continue;
        }

        switch(choice)
        {
        case 1:
            managerMode();
            break;
        case 2:
            customerMode();
            break;
        case 3:
            printf("-------Thank you for visiting our restaurant-------");
            exit(0);
        default:
            printf("Invalid Choice.\n");
            break;
        }
    }
    return 0;
}