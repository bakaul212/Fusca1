
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct node
{
    char foodname[50];
    int quantity;
    float price;
    int data;
    int time;
    int served;
    char size;
    time_t timestamp;
    struct node *prev;
    struct node *next;
};

struct node *headc = NULL, *newnode, *tailc = NULL;
struct node *heada = NULL, *taila = NULL;
struct node *head_s;

void banner(int n)
{
    system("cls");
    printf("\n**************************************************************************\n");
    if (n == 0)
    {
        char *string = "\tWELCOME TO THE FOOD ORDERING SYSTEM IN YOUR DESIRE RESTAURANT";
        printf("%s\n", string);
    }
    else if (n == 1)
    {
        char *string = "\t\tPlace your order";
        printf("%s\n", string);
    }
    else if (n == 2)
    {
        char *string = "\t\tList of ordered items";
        printf("%s\n", string);
    }
    else if (n == 3)
    {
        char *string = "\t\tFinal Bill";
        printf("%s\n", string);
    }
    else if (n == 4)
    {
        char *string = "\t\tView total sales";
        printf("%s\n", string);
    }
    printf("**************************************************************************\n");
}

void goBack()
{
    getchar();
    printf("\t\t\tPress enter key to return to main menu...");
    getchar();
}

void menu()
{
    printf("\n\t1. Place your order\n");
    printf("\t2. View and delete your ordered items\n");
    printf("\t3. Display final bill\n");
    printf("\t4. View total sales\n");
    printf("\t5. Exit \n\n");
    printf("\t\t   Enter Your Choice --->");
}

struct node *addFood(struct node *head, int data, char foodname[25], float price, int time)
{
    newnode = (struct node *)malloc(sizeof(struct node));

    newnode->data = data;
    newnode->price = price;
    newnode->time = time;
    newnode->quantity = 0;
    newnode->served = 0;
    strcpy(newnode->foodname, foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;

    if (temp == NULL)
        heada = taila = newnode;
    else
    {
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newnode;
        newnode->prev = taila;
        taila = newnode;
    }

    return heada;
}

struct node *create(struct node *head, int data, int quantity, char size)
{
    newnode = (struct node *)malloc(sizeof(struct node));

    struct node *temp1 = heada;
    int flag = 0;
    time_t t;
    struct tm ttm;
    char sizeName[20];

    while (temp1 != NULL)
    {
        if (temp1->data == data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if (flag == 1)
    {

        newnode->data = data;
        if (size == 'f')
            newnode->price = quantity * 2 * (temp1->price);
        else
            newnode->price = quantity * (temp1->price);
        newnode->time = temp1->time;
        newnode->quantity = quantity;
        strcpy(newnode->foodname, temp1->foodname);
        newnode->served = temp1->served;
        newnode->size = size;
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;

        if (temp == NULL)
        {
            t = time(NULL);
            t += temp1->time * 60;
            newnode->timestamp = t;
            headc = tailc = newnode;
        }
        else
        {
            while (temp->next != NULL)
                temp = temp->next;
newnode->timestamp = temp->timestamp + (temp1->time * 60);
            temp->next = newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }
        ttm = *localtime(&newnode->timestamp);

        if (size == 'f')
            strcpy(sizeName, "family");
        else
            strcpy(sizeName, "single");
        printf("\t\t You have picked %d %s %s size and price %0.2f\n", newnode->quantity, newnode->foodname, sizeName, newnode->price);
        printf("\t\t Your order will be served in %02d:%02d\n", ttm.tm_hour, ttm.tm_min);
    }
    else
    {
        printf("\n\t\tThis item is not present in the menu!\n");
    }
    return headc;
}

void displayList(struct node *head)
{
    struct node *temp1 = head;
    time_t t;
    struct tm *ttm;
    char sizeName[20];
    t = time(NULL);

    if (temp1 == NULL)
    {
        printf("\n\t\tList is empty!!\n\n");
    }
    else
    {
        printf("\n");

        char *name = "Food Name";
        if (temp1->quantity == 0)
        {
            printf("   Product ID\t%22s\tPrice\n", name);
        }
        else
        {
            printf("   Product ID\t%22s\t Quantity\tPrice\tSize\tServed ETC\n", name);
        }
        while (temp1 != NULL)
        {
            if (temp1->quantity == 0)
                printf("   %d\t%30s\t%0.2f\n", temp1->data, temp1->foodname, temp1->price);
            else
            {
                if (temp1->size == 'f')
                    strcpy(sizeName, "Family");
                else
                    strcpy(sizeName, "Single");
                if (temp1->served == 0 && t < temp1->timestamp)
                {
                    ttm = localtime(&temp1->timestamp);
                    printf("   %d\t%30s\t\t%d\t%0.2f\t%s\t%02d:%02d\n", temp1->data, temp1->foodname, temp1->quantity, temp1->price, sizeName, ttm->tm_hour, ttm->tm_min);
                }
                else
                {
                    temp1->served = 1;
                    printf("   %d\t%30s\t\t%d\t%0.2f\t%s\tServed\n", temp1->data, temp1->foodname, temp1->quantity, temp1->price, sizeName);
                }
            }

            temp1 = temp1->next;
        }
        printf("\n");
    }
}

struct node *totalSales(int data, int quantity, time_t timestamp, char served, char size)
{
    newnode = (struct node *)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = heada;
    while (temp1->data != data)
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity * (temp1->price);
    newnode->quantity = quantity;
    newnode->time = temp1->time;
    newnode->timestamp = timestamp;
    newnode->served = served;
    newnode->size = size;
    strcpy(newnode->foodname, temp1->foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;

    if (temp == NULL)
        head_s = newnode;
    else
    {
        while (temp->next != NULL)
        {
            if (temp->data == data)
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        }

        if (flag == 1)
        {
            temp->quantity += newnode->quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next = newnode;
        }
    }

    return head_s;
}

void calculateToTSales()
{
    struct node *temp = headc;
    while (temp != NULL)
    {
        head_s = totalSales(temp->data, temp->quantity, temp->timestamp, temp->served, temp->size);
        temp = temp->next;
    }
}
struct node *delete (int data, struct node *head, struct node *tail)
{
    if (head == NULL)
    {
        printf("\n\tList is empty\n");
    }
    else
    {
        struct node *temp;
        if (data == head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if (data == tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while (data != temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}

int deleteFood()
{
    printf("\n\tEnter Product ID. of the food item which you want to be deleted or -1 for go back main menu: ");
    int num;
    scanf("%d", &num);
    if (num == -1)
        return -1;
    struct node *temp = headc;
    while (temp != NULL)
    {
        if (temp->data == num)
        {
            headc = delete (num, headc, tailc);
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

void displayDetail(struct node *head, int m)
{
    displayList(head);
    struct node *temp = head;
    float total_price = 0;
    int total_order = 0, waiting = 0, served = 0;
    while (temp != NULL)
    {
        total_order++;
        if (temp->served == 1)
            served++;
        else
            waiting++;
        total_price += temp->price;
        temp = temp->next;
    }

    if (m == 1)
    {
        printf("\tServing order: %d\n", waiting);
        printf("\tServed order: %d\n", served);
        printf("\tTotal order: %d\n", total_order);
        printf("\tTotal Earn: %0.02f\n", total_price);
    }
    else
        printf("\tTotal price: %0.02f\n", total_price);
}

struct node *deleteList(struct node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        struct node *temp = head;
        while (temp->next != 0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

void options()
{
    int flag = 0, j = 1;
    char ch;
    while (1)
    {
        banner(0);
        menu();

        int opt;
        scanf("%d", &opt);
if (opt == 5)
            break;
        switch (opt)
        {
        case 1:
            banner(1);
            displayList(heada);
            printf("\n\tEnter number corresponding to the item you want to order: ");
            int n;
            scanf("%d", &n);
            printf("\tEnter quantity: ");
            int quantity;
            scanf("%d", &quantity);
            getchar();
            char size;
            printf("\tEnter Size For \n");
            printf("\t Single = s\n");
            printf("\t Family = f (Price 2X)\n");
            printf("\t\t->");
            scanf("%c", &size);
            headc = create(headc, n, quantity, size);
            printf("\n\tThank you! Your order was successfully submitted!\n");
            goBack();
            break;
        case 2:
            banner(2);
            displayList(headc);
            int x;
            x = deleteFood();
            if (x == 1)
            {
                printf("\n\t### Updated list of your ordered food items ###\n");
                displayList(headc);
            }
            else if (x == 0)
                printf("\n\tFood item with given serial number doesn't exist!! Please try again.\n");
            break;
        case 3:
            banner(3);
            calculateToTSales();
            displayDetail(headc, 0);
            headc = deleteList(headc);
            printf("\n\tHave a nice day!\n");
            printf("\tThanks for your order.\n");
            goBack();
            break;
        case 4:
            banner(4);
            displayDetail(head_s, 1);
            goBack();
            break;
        default:
            printf("\n\tWrong Input !! PLease choose valid option\n");
            goBack();
            break;
        }
    }
}

int main()
{
    heada = addFood(heada, 1, "Phuchka", 50, 1);
    heada = addFood(heada, 2, "ChotPoti", 50, 5);
    heada = addFood(heada, 3, "Thai Soup", 200, 10);
    heada = addFood(heada, 4, "Chicken Biriyani", 150, 10);
    heada = addFood(heada, 5, "Fried Rice with vegetable", 350, 10);
    heada = addFood(heada, 6, "Chicken Chowmein", 120, 10);
    heada = addFood(heada, 7, "Kachchi Biryani", 120, 10);

    options();
}
