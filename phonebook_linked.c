#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char firstName[10];
    char lastName[10];
    char num[10];
    struct Node *next;
    struct Node *prev;

} Node;

void traversal(Node *head)
{
    Node *p = head;
    int i = 1;
    if (p == NULL)
    {
        printf("\nNothing to show, phonebook is empty");
    }
    else
    {
        while (p != NULL)
        {
            printf("\n[%d]| Name: %s %s | Number: %s |", i, p->firstName, p->lastName, p->num);
            p = p->next;
            i++;
        }
    }
}

// Node *getnode()
// {
//     return ((Node *)malloc(sizeof(Node)));
// }

Node *getDetails(Node *ptr)
{

    printf("\nEnter first name:");
    scanf("%s", &ptr->firstName);
    printf("\nEnter last name:");
    scanf("%s", &ptr->lastName);
    printf("\nEnter number:");
    scanf("%s", &ptr->num);

    return ptr;
}

Node *insert(Node *head)
{

    Node *ptr = (Node *)malloc(sizeof(Node));

    return getDetails(ptr);
}

Node *new (Node *head)
{
    if (head == NULL)
    {
        return insert(head);
    }

    else
    {
        Node *p = head;
        Node *ptr = (Node *)malloc(sizeof(Node));
        while (p->next != NULL)
            p = p->next;

        ptr = getDetails(ptr);

        p->next = ptr;
        ptr->prev = p;
        ptr->next = NULL;
        return head;
    }
}

int search(Node *ptr, char *str)
{
    if ((strcmp(ptr->firstName, str) == 0) || (strcmp(ptr->lastName, str) == 0) || (strcmp(ptr->num, str) == 0))
        return 1;

    return 0;
}

int searchFunc(Node *head, char *str)
{
    Node *ptr = head;
    int i = 1;
    int flag = 0;
    while (ptr != NULL)
    {
        if (search(ptr, str))
        {
            printf("\n| [%d] | Name: %s %s | Number: %s |", i, ptr->firstName, ptr->lastName, ptr->num);
            i++;
            flag++;
        }
        ptr = ptr->next;
    }

    if (ptr == NULL && flag == 0)
        printf("\nCouldn't search for %s", str);
}

void updateFunc(Node *head, char *str)
{
    Node *ptr = head;
    if (ptr == NULL)
        return;
    int opt;
    while (!search(ptr, str))
        ptr = ptr->next;

    printf("\nYou are about to modify following contact:");
    printf("\nName: %s %s | Number: %s", ptr->firstName, ptr->lastName, ptr->num);
    printf("\nWant to continue (1/0):");
    scanf("%d", &opt);

    if (opt == 0)
        return;

    else
    {
        int option;
        printf("\nWhat do you want to update");
        printf("\n1.First Name\n2.Last Name\n3.Number");
        printf("\nEnter:");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            printf("\nEnter First Name:");
            scanf("%s", &ptr->firstName);
            break;

        case 2:
            printf("\nEnter Last Name:");
            scanf("%s", &ptr->lastName);
            break;
        case 3:
            printf("\nEnter Number:");
            scanf("%d", &ptr->num);
        case 4:
            printf("[+] Quitting");
            break;

        default:
            printf("\nEnter a valid option");
        }
    }
}

int deleteOptions(Node *ptr)
{
    int opt;
    printf("\nYou are about to delete following contact");
    printf("\nName: %s %s | Number: %s", ptr->firstName, ptr->lastName, ptr->num);
    printf("\nYou wish to continue(1 for YES | 0 for NO):");
    scanf("%d", &opt);
    if (opt == 0 || opt == 1)
        return opt;
    else
    {
        printf("\nEnter a valid option");
        deleteOptions(ptr);
    }
}

Node *delete (Node *head, char *str)
{
    Node *p = head, *q = head->next;
    if (search(head, str))
    {
        if (deleteOptions(head))
        {
            Node *tmp;
            tmp = head->next;
            free(head);
            return tmp;
        }
    }

    else
    {
        int flag = 0;
        while (q != NULL)
        {
            if (search(q, str))
            {
                if (deleteOptions(q))
                {
                    Node *tmp;
                    tmp = q->next;
                    p->next = tmp;
                    if (tmp != NULL)
                        tmp->prev = p;
                    free(q);
                    flag++;
                    return head;
                }
                else
                {
                    p = p->next;
                    q = q->next;
                }
            }

            else
            {
                p = p->next;
                q = q->next;
            }
        }

        if (flag == 0)
        {
            printf("\nCouldn't delete");
            return head;
        }
    }
}

Node *deleteAll(Node *ptr)
{
    int opt;
    printf("\nThis will delete all contacts, are you sure (1/0):");
    scanf("%d", &opt);
    if (opt)
    {
        if (ptr->next == NULL && ptr->prev == NULL)
        {
            free(ptr);
            return NULL;
        }
        else
        {
            Node *p, *q;
            while (ptr->next != NULL)
            {
                if (q->next == NULL)
                {
                    p->next = NULL;
                    free(q);
                    p = ptr;
                    q = ptr->next;
                }
                p = p->next;
                q = q->next;
            }
            free(ptr);
            return NULL;
        }
    }
    else
        return ptr;
}

int main()
{
    // fflush(stdin);
    Node *head = (Node *)malloc(sizeof(Node));
    head = NULL;
    char str[10];
    int option;
    do
    {
        printf("\n========================================");
        printf("\n\tWELCOME TO PHONEBOOK");
        printf("\n========================================");
        printf("\n\t[1] Display all contacts\n\t[2] Add New Contact\n\t[3] Search Contact\n\t[4] Update a contact\n\t[5] Delete a Contact\n\t[6] Delete all contacts");
        printf("\n----------------------------------------");
        printf("\n\t\t[7] Exit");
        printf("\n========================================");
        printf("\nEnter your option: ");
        scanf("%d", &option);

        if (option == 1)
        {
            traversal(head);
            printf("\n");
            system("pause");
            system("cls");
        }

        else if (option == 2)
        {
            head = new (head);
            system("cls");
        }

        else if (option == 3)
        {

            printf("\nEnter (First Name / Last Name / Number) to search: ");
            scanf("%s", &str);

            searchFunc(head, str);
            printf("\n");
            system("pause");
            system("cls");
        }
        else if (option == 4)
        {
            printf("\nEnter (First Name / Last Name / Number) to update:");
            scanf("%s", &str);
            updateFunc(head, str);
            system("cls");
        }
        else if (option == 5)
        {
            printf("\nEnter (First Name / Last Name / Number) to delete: ");
            scanf("%s", &str);
            head = delete (head, str);
            system("cls");
        }

        else if (option == 6)
        {
            head = deleteAll(head);
        }

        else if (option == 7)
        {
            printf("\n[-]Quitting programme");
            system("cls");
        }

        else
        {
            printf("\nEnter a valid option");
            sleep(2);
            system("cls");
        }
    } while (option != 7);

    return 0;
}
