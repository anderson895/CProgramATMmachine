#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define key 33

// DATA STRUCTURES

// CODE FOR ACCOUNTS

typedef struct Acc
{
    char accnum[6];
    char name[50];
    char month[10];
    char day[10];
    char year[10];
    char contact[20];
    char pin[7];
    double balance;
}acc;
acc a[100];
int aCount = 0;

void transaction(int n);
void withdraw(int n);

void fundTransfer(int n);
void balanceInq(int n);

void viewProfile(int n);
void deposit(int n);
void changePin(int n);

//  HANDLING FILE

//  ACCOUNT LOAD

void load()
{
    FILE *fp = fopen("ATM accounts.txt", "r");

    fscanf(fp, "%d\n", &aCount);
    for(int i=0; i<aCount; i++)
    {
        fscanf(fp, "%s\n", &a[i].accnum);
        fgets(a[i].name, 50, fp);
        a[i].name[strlen(a[i].name) - 1] = '\0';
        fgets(a[i].month, 10, fp);
        a[i].month[strlen(a[i].month) - 1] = '\0';
        fgets(a[i].day, 10, fp);
        a[i].day[strlen(a[i].day) - 1] = '\0';
        fgets(a[i].year, 10, fp);
        a[i].year[strlen(a[i].year) - 1] = '\0';
        fgets(a[i].contact, 20, fp);
        a[i].contact[strlen(a[i].contact) - 1] = '\0';
        fgets(a[i].pin, 7, fp);
        a[i].pin[strlen(a[i].pin)] = '\0';
        fscanf(fp, "%lf\n", &a[i].balance);
    }

    fclose(fp);
}

// Save Accounts

void save()
{
    FILE *fp = fopen("ATM accounts.txt", "w");

    fprintf(fp, "%d\n", aCount);
    for(int i=0; i<aCount; i++)
    {
        fprintf(fp, "%s\n", a[i].accnum);
        fprintf(fp, "%s\n", a[i].name);
        fprintf(fp, "%s\n", a[i].month);
        fprintf(fp, "%s\n", a[i].day);
        fprintf(fp, "%s\n", a[i].year);
        fprintf(fp, "%s\n", a[i].contact);
        fprintf(fp, "%s\n", a[i].pin);
        fprintf(fp, "%.2lf\n", a[i].balance);
    }

    fclose(fp);
}

// Insert Card

int card()
{
    FILE *fp = fopen("card.txt", "r");

    if(fp == NULL)
    {
        printf("\n\n\t\t\t>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        printf("\t\t\t      No card inserted. Please insert card...      \n");
        printf("\t\t\t>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
        system("pause");
        return 0;
    }

    printf("\n\n\t\t\t>>>>>>>>>>>>>>>>>>>>>><<<<\n");
    printf("\t\t\t     Validating card...     \n");
    printf("\t\t\t>>>>>>>>>>>>>>>>>>>>>><<<<<<<\n\n");
    system("pause");
    system("cls");
    printf("\n\n\t\t\t>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("\t\t\t|     Card inserted. You may now proceed...     |\n");
    printf("\t\t\t>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
    system("pause");
    system("cls");
    fclose(fp);

    return 1;
}

// ENCRYPTION AND DECRYPTION

// ENCRYPTION

void encrypt(char pin[])
{
    for(int i=0; i<strlen(pin); i++)
    {
        pin[i] = pin[i] + key;
    }
}

// DECRYPTION

void decrypt(char pin[])
{
    for(int i=0; i<strlen(pin); i++)
    {
        pin[i] = pin[i] - key;
    }
}

// MENU INTERFACES

// REGISTRATION / LOGIN PAGE

char menu()
{
    char option;

    printf("\n\n\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("\t\t\t                                                                 \n");
    printf("\t\t\t                     REGISTRATION / LOG-IN                       \n");
    printf("\t\t\t                                                                 \n");
    printf("\t\t\t          1. REGISTER                                            \n");
    printf("\t\t\t                                                                 \n");
    printf("\t\t\t          2. LOG-IN (Account Number + PIN Code)                  \n");
    printf("\t\t\t                                                                 \n");
    printf("\t\t\t          3. EXIT / SAVE DATA                                    \n");
    printf("\t\t\t                                                                 \n");
    printf("\t\t\t                                                                 \n");
    printf("\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("\n\t\t\tSELECT AN OPTION: ");
    scanf(" %c", &option);
    fflush(stdin);

    return option;
}

// REGISTRATION

void reg()
{
    int f, d, x = 0;
    char ch;
    char accnum[6];
    char name[50];
    char pin[7];
    double iniDeposit;

    printf("\n\n\t\t\t>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("\t\t\t                                                    \n");
    printf("\t\t\t                   REGISTRATION                     \n");
    printf("\t\t\t                                                    \n");
    printf("\t\t\t>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("\n\t\t\t[PLEASE ENTER THE AFFILIATED INFORMATION.]\n");
    do
    {
        f = 0;
        d = 1;
        printf("\n\t\t\tAccount Number: ");
        gets(accnum);
        for(int i=0; i<aCount; i++)
        {
            if(strcmp(accnum, a[i].accnum) == 0)
            {
                f = 1;
            }
        }
        for(int i=0; i<strlen(accnum); i++)
        {
            if(isalpha(accnum[i]))
            {
                d = 0;
            }
            if(isalpha(accnum[i]) == 0 && isdigit(accnum[i]) == 0)
            {
                d = 0;
            }
        }
        if(f == 1)
        {
            printf("\n\t\t\tError. Account Number Already Taken.\n");
            printf("\t\t\t---------------------------------------\n");
        }
        if(strlen(accnum) > 5)
        {
            printf("\n\t\t\tError. Account Number is Maximum 5 Digits.\n");
            printf("\t\t\t---------------------------------------\n");
        }
        if(d == 0)
        {
            printf("\n\t\t\tError. Input accepts digits only.\n");
            printf("\t\t\t---------------------------------------\n");
        }
    } while(f == 1 || strlen(accnum) > 5 || d == 0);
    strcpy(a[aCount].accnum, accnum);
    printf("\t\t\t---------------------------------------\n");

    do
    {
        f = 0;
        d = 0;
        printf("\n\t\t\tAccount Name: ");
        gets(name);
        for(int i=0; i<aCount; i++)
        {
            if(strcmp(name, a[i].name) == 0)
            {
                f = 1;
            }
        }
        if(f == 1)
        {
            printf("\n\t\t\tError. Account Name Already Taken.\n");
            printf("\t\t\t---------------------------------------\n");
        }
        for(int i=0; i<strlen(name); i++)
        {
            if(isdigit(name[i]))
            {
                d = 1;
            }
        }
        if(d == 1)
        {
            printf("\n\t\t\tError. No digits are allowed in the account name..\n");
            printf("\t\t\t-----------------------------------------\n");
        }
    } while(f == 1 || d == 1);
    strcpy(a[aCount].name, name);
    printf("\t\t\t---------------------------------------\n");

    printf("\n\t\t\t[BIRTHDAY]\n");
    printf("\t\t\tMonth: ");
    gets(a[aCount].month);
    printf("\t\t\tDay: ");
    gets(a[aCount].day);
    printf("\t\t\tYear: ");
    gets(a[aCount].year);                               //123
    printf("\t\t\t---------------------------------------\n");
    printf("\n\t\t\tContact Number: ");
    gets(a[aCount].contact);
    printf("\t\t\t----------------------------------------\n");

    do
    {
        printf("\n\t\t\tInitial Deposit: P");
        scanf("%lf", &iniDeposit);
        if(iniDeposit < 5000)
        {
            printf("\n\t\t\tError. Minimum Initial Deposit is 5000\n");
            printf("\t\t\t=======================================\n");
        }
    } while(iniDeposit < 5000);
    fflush(stdin);
    a[aCount].balance = iniDeposit;
    printf("\t\t\t=======================================\n");
    printf("\n\t\t\tINFORMATION REGISTERED SUCCESSFULLY\n\n");
    system("pause");
    system("cls");

    printf("\n\n\t\t\t[INPUT PIN CODE]\n");
    printf("\n\t\t\tPIN Code: ");
    while((ch = getch()) != 13 && x < 5)
    {
        if(x < 0)
        {
            x = 0;
        }
        if(ch == 8)
        {
            putch('\b');
            putch(' ');
            putch('\b');
            x--;
            continue;
        }
        if(isdigit(ch))
        {
            pin[x++] = ch;
            putch('*');
        }
    }
    if(x == 5)
    {
        pin[x++] = ch;
    }
    encrypt(pin);
    strcpy(a[aCount].pin, pin);
    printf("\n\t\t\t>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<\n");
    printf("\n\t\t\tREGISTRATION SUCCESSFUL. THANK YOU.\n");
    aCount++;
}

// LOGIN

void login()
{
    printf("\n\n\t\t\t>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("\t\t\t                                                     \n");
    printf("\t\t\t                      LOG-IN                         \n");
    printf("\t\t\t                                                     \n");
    printf("\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<\n");

    if(aCount == 0)
    {
        printf("\n\t\t\tNo accounts detected. Register an account first.\n\n");
        printf("\t\t\t=======================================\n");
        system("pause");
        system("cls");
        return;
    }

    int n, f = 0, v, x = 0;
    int tries = 1;
    char ch;
    char accnum[6];
    char pin[7];

    printf("\n\t\t\tEnter Account Number: ");
    gets(accnum);
    for(int i=0; i<aCount; i++)
    {
        if(strcmp(accnum, a[i].accnum) == 0)
        {
            n = i;
            f = 1;
        }
    }
    printf("\t\t\t=======================================\n");

    if(f == 0)
    {
        printf("\n\t\t\tInvalid Account Number.\n");
        printf("\t\t\t=======================================\n");
        printf("\n");
        system("pause");
        system("cls");
        return;
    }

    decrypt(a[n].pin);
   // printf("%s", a[n].pin);
    do
    {
        x = 0;
        printf("\n\t\t\tEnter PIN Code: ");
        while((ch = getch()) != 13 && x < 5)
        {
            if(x < 0)
            {
                x = 0;
            }
            if(ch == 8)
            {
                putch('\b');
                putch(' ');
                putch('\b');
                x--;
                continue;
            }
            if(isdigit(ch))
            {
                pin[x++] = ch;
                putch('*');
            }
        }
        if(x == 5)
        {
            pin[x++] = ch;
        }
        pin[x] = '\0';

        if(strcmp(pin, a[n].pin) == 0)
        {
            v = 1;
            break;
        }
        else
        {
            printf("\n\t\t\tInvalid PIN Code. Please Try Again.\n");
            printf("\t\t\t=======================================\n");
            tries++;
            v = 0;
        }
    } while(tries <= 4);
    encrypt(a[n].pin);

    if(v == 0)
    {
        printf("\n\t\t\tToo many attempts. Returning...\n\n");
        printf("\t\t\t=======================================\n");
        system("pause");
        system("cls");
        return;
    }

    printf("\n\t\t\tLOG-IN SUCESSFUL.\n\n");
    printf("\t\t\t=======================================\n");
    system("pause");
    system("cls");
    transaction(n);
}

// MAIN

int main()
{
    if(card() == 1)
    {

        load();
      //  viewProfile(0);
      // viewProfile(1);
     //  viewProfile(2);
        char m;

        do
        {

            m = menu();

            switch(m)
            {
            case '1':
                system("cls");
                reg();
                printf("\n");
                system("pause");
                system("cls");
                break;
            case '2':
                system("cls");
                login();
                break;
            case '3':
                printf("\n\t\t\tTHANK YOU FOR USING OUR BANK. HAVE A GREAT DAY.\n\n");
                system("pause");
                system("cls");
                printf("\n\t\t\tDATA SAVED to \"ATM accounts.txt\"\n");
                save();
                break;
            default:
                printf("\n\n\t\t\tInvalid Input.\n\n");
                printf("\t\t\t=======================================\n");
                system("pause");
                system("cls");
            }

        } while(m != '3');

    }

    return 0;
}

// TRANSACTION FUNCTIONS

// TRANSACTION MENU

void transaction(int n)
{
    char option;

    do
    {
        printf("\n\n\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        printf("\t\t\t                                                                 \n");
        printf("\t\t\t                          TRANSACTION                            \n");
        printf("\t\t\t                                                                 \n");
        printf("\t\t\t              1. BALANCE INQUIRY                                 \n");
        printf("\t\t\t              2. WITHDRAW                                        \n");
        printf("\t\t\t              3. DEPOSIT                                         \n");
        printf("\t\t\t              4. FUND TRANSFER                                   \n");
        printf("\t\t\t              5. CHANGE PIN CODE                                 \n");
        printf("\t\t\t              6. VIEW MY PROFILE                                 \n");
        printf("\t\t\t              7. CLOSE ACCOUNT / FINISH TRANSACTION              \n");
        printf("\t\t\t                                                                 \n");
        printf("\t\t\t                                                                 \n");
        printf("\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
        printf("\n\t\t\tSELECT AN OPTION: ");
        scanf(" %c", &option);
        fflush(stdin);

        switch(option)
        {
        case '1':
            system("cls");
            balanceInq(n);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case '2':
            system("cls");
            withdraw(n);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case '3':
            system("cls");
            deposit(n);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case '4':
            system("cls");
            fundTransfer(n);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case '5':
            system("cls");
            changePin(n);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case '6':
            system("cls");
            viewProfile(n);
            printf("\n");
            system("pause");
            system("cls");
            break;
        case '7':
            system("cls");
            break;
        default:
            printf("\n\t\t\tInvalid Input.\n");
            printf("\t\t\t=======================================\n");
        }
    } while(option != '7');
}

// BALANCE INQUIRY

void balanceInq(int n)
{
    printf("\n\n\t\t\t======================================================\n");
    printf("\t\t\t|                                                    |\n");
    printf("\t\t\t|                  BALANCE INQUIRY                   |\n");
    printf("\t\t\t|                                                    |\n");
    printf("\t\t\t======================================================\n");
    printf("\n\t\t\t|   YOUR BALANCE: P%.2lf\n", a[n].balance);
    printf("\t\t\t=======================================\n");
}

// WITHDRAW

void withdraw(int n)
{
    printf("\n\n\t\t\t======================================================\n");
    printf("\t\t\t|                                                    |\n");
    printf("\t\t\t|                      WITHDRAW                      |\n");
    printf("\t\t\t|                                                    |\n");
    printf("\t\t\t======================================================\n");

    double withdrawAmount;

    printf("\n\t\t\t|   YOUR BALANCE: P%.2lf\n", a[n].balance);
    printf("\t\t\t=======================================\n");
    if(a[n].balance <= 0)
    {
        printf("\n\t\t\tInsufficient Balance.\n");
        printf("\t\t\t=======================================\n");
        return;
    }
    do
    {
        printf("\n\t\t\t|   WITHDRAW AMOUNT: P");
        scanf("%lf", &withdrawAmount);
        fflush(stdin);
        if(withdrawAmount > a[n].balance)
        {
            printf("\n\t\t\tWithdraw Amount Exceeded Account Balance. Please Try Again.\n");
            printf("\t\t\t=======================================\n");
            continue;
        }
        else if(withdrawAmount < 500)
        {
            printf("\n\t\t\tWithdraw Amount has a Minimum of P500. Please Try Again.\n");
            printf("\t\t\t=======================================\n");
            continue;
        }
        else
        {
            printf("\n\t\t\tWithdraw Successful.\n");
            printf("\t\t\tP%.2lf\n\t\t\t-\n\t\t\tP%.2lf\n", a[n].balance, withdrawAmount);
            a[n].balance -= withdrawAmount;
            printf("\n\t\t\t|   YOUR BALANCE: P%.2lf\n", a[n].balance);
            printf("\t\t\t=======================================\n");
            break;
        }
    } while(1);
}

// DEPOSIT

void deposit(int n)
{
    printf("\n\n\t\t\t======================================================\n");
    printf("\t\t\t|                                                    |\n");
    printf("\t\t\t|                       DEPOSIT                      |\n");
    printf("\t\t\t|                                                    |\n");
    printf("\t\t\t======================================================\n");

    double depositAmount;

    printf("\n\t\t\t|   YOUR BALANCE: P%.2lf\n", a[n].balance);
    printf("\t\t\t=======================================\n");
    do
    {
        printf("\n\t\t\t|   DEPOSIT AMOUNT: P");
        scanf("%lf", &depositAmount);
        fflush(stdin);
        if(depositAmount < 5000)
        {
            printf("\n\t\t\tMinimum Deposit Amount is 5000. Please Try Again.\n");
            printf("\t\t\t=======================================\n");
            continue;
        }
        else
        {
            printf("\n\t\t\tDeposit Successful.\n");
            printf("\t\t\tP%.2lf\n\t\t\t+\n\t\t\tP%.2lf\n", a[n].balance, depositAmount);
            a[n].balance += depositAmount;
            printf("\n\t\t\t|   YOUR BALANCE: P%.2lf\n", a[n].balance);
            printf("\t\t\t=======================================\n");
            break;
        }
    } while(1);
}

// FUND TRANSFER

void fundTransfer(int n)
{
    printf("\n\n\t\t\t======================================================\n");
    printf("\t\t\t|                                                    |\n");
    printf("\t\t\t|                   FUND TRANSFER                    |\n");
    printf("\t\t\t|                                                    |\n");
    printf("\t\t\t======================================================\n");

    printf("\n\t\t\t|   YOUR BALANCE: P%.2lf\n", a[n].balance);
    printf("\t\t\t=======================================\n");

    if(aCount == 1)
    {
        printf("\n\t\t\tCannot Transfer Funds. There no other registered accounts.\n");
        printf("\t\t\t=======================================\n");
        return;
    }
    if(a[n].balance <= 0)
    {
        printf("\n\t\t\tInsufficient Balance.\n");
        printf("\t\t\t=======================================\n");
        return;
    }

    int nCounter = 0;
    int x, f = 0;
    char accnum[6];
    double transfer;

    printf("\n\t\t\t|   REGISTERED ACCOUNTS\n");
    for(int i=0; i<aCount; i++)
    {
        if(i == n)
        {
            continue;
        }
        printf("\t\t\t%s  ", a[i].accnum);
        nCounter++;
        if(nCounter % 2 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\t\t\t=======================================\n");

    printf("\n\t\t\t|   ACCOUNT NUMBER TO TRANSFER FUNDS: ");
    gets(accnum);
    for(int i=0; i<aCount; i++)
    {
        if(strcmp(accnum, a[i].accnum) == 0)
        {
            x = i;
            f = 1;
        }
    }

    if(f == 0)
    {
        printf("\n\t\t\tInvalid Account Number.\n");
        printf("\t\t\t=======================================\n");
        return;
    }

    do
    {
        printf("\n\t\t\t|   TRANSFER AMOUNT: P");
        scanf("%lf", &transfer);
        fflush(stdin);
        if(transfer > a[n].balance)
        {
            printf("\n\t\t\tTransfer Amount Exceeded Account Balance. Please Try Again.\n");
            printf("\t\t\t=======================================\n");
            continue;
        }
        else if(transfer < 5000)
        {
            printf("\n\t\t\tMinimum Transfer Amount is 5000. Please Try Again.\n");
            printf("\t\t\t=======================================\n");
            continue;
        }
        else
        {
            printf("\n\t\t\tTransfer Funds Successful.\n");
            printf("\t\t\tP%.2lf\n\t\t\t-\n\t\t\tP%.2lf\n", a[n].balance, transfer);
            a[n].balance -= transfer;
            printf("\n\t\t\t|   YOUR BALANCE: P%.2lf\n", a[n].balance);
            printf("\t\t\t=======================================\n");

            printf("\n\t\t\t[TRANSFERED]\n");
            printf("\n\t\t\tAccount %s\n", a[x].accnum);
            printf("\t\t\tP%.2lf\n\t\t\t+\n\t\t\tP%.2lf\n", a[x].balance, transfer);
            a[x].balance += transfer;
            printf("\n\t\t\t|   ACCOUNT %s BALANCE: P%.2lf\n", a[x].accnum, a[x].balance);
            printf("\t\t\t=======================================\n");
            break;
        }
    } while(1);
}

// CHANGE PIN

void changePin(int n)
{
    printf("\n\n\t\t\t======================================================\n");
    printf("\t\t\t|                                                    |\n");
    printf("\t\t\t|                     CHANGE PIN                     |\n");
    printf("\t\t\t|                                                    |\n");
    printf("\t\t\t======================================================\n");

    int d, x = 0;
    char ch;
    char newPin[7];

    printf("\n\t\t\t|   ENCRYPTED PIN: %s\n", a[n].pin);
    decrypt(a[n].pin);
    printf("\t\t\t|   DECRYPTED PIN: %s\n", a[n].pin);
    printf("\t\t\t=======================================\n");

    printf("\n\t\t\t|   Enter New PIN Code: ");
    while((ch = getch()) != 13 && x < 5)
    {
        if(x < 0)
        {
            x = 0;
        }
        if(ch == 8)
        {
            putch('\b');
            putch(' ');
            putch('\b');
            x--;
            continue;
        }
        if(isdigit(ch))
        {
            newPin[x++] = ch;
            putch('*');
        }
    }
    if(x == 5)
    {
        newPin[x++] = ch;
    }
    newPin[x] = '\0';
    printf("\n");
    encrypt(newPin);
    printf("\t\t\t|   ENCRYPTED NEW PIN CODE: %s\n", newPin);
    strcpy(a[n].pin, newPin);
    printf("\n\t\t\tPIN CODE CHANGED SUCCESSFULLY.\n");
    printf("\t\t\t=======================================\n");
}

// VIEW PROFILE

void viewProfile(int n)
{
    printf("\n\n\t\t\t======================================================\n");
    printf("\t\t\t|                                                    |\n");
    printf("\t\t\t|                    VIEW PROFILE                    |\n");
    printf("\t\t\t|                                                    |\n");
    printf("\t\t\t======================================================\n");

    printf("\n\t\t\t|   ACCOUNT NUMBER: %s\n", a[n].accnum);
    printf("\t\t\t=======================================\n");
    printf("\n\t\t\t|   ACCOUNT NAME: %s\n", a[n].name);
    printf("\t\t\t=======================================\n");
    printf("\n\t\t\t|   BIRTHDAY: %s %s, %s\n", a[n].month, a[n].day, a[n].year);
    printf("\t\t\t=======================================\n");
    printf("\n\t\t\t|   CONTACT NUMBER: %s\n", a[n].contact);
    printf("\t\t\t=======================================\n");
    printf("\n\t\t\t|   BALANCE: P%.2lf\n", a[n].balance);
    printf("\t\t\t=======================================\n");
    decrypt(a[n].pin);
    printf("\n\t\t\t|   PIN CODE (DECRYPTED): %s\n", a[n].pin);
    encrypt(a[n].pin);
    printf("\t\t\t=======================================\n");
}
