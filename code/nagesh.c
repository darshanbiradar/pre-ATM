#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
char temp_deduct[1024];
struct BankAccount {
    long long accountNumber;
    char accountHolderName[50];
    char birthdate[12];  // Format: YYYY-MM-DD
    double balance;
    char status[3];  // Default status is "ok"
};

long long generateRandomAccountNumber() {
    // Seed the random number generator
    srand(time(NULL));

    // Generate a random account number between 10000000000 and 99999999999
    return (rand() % (99999999999LL - 10000000000LL + 1)) + 10000000000LL;
}
void transf_stcat(struct BankAccount *account){
    
}

void appendAccountToFile(const char *filename, struct BankAccount account) {
    // Open the file in append mode
    FILE *file = fopen(filename, "a");

    if (file == NULL) {
        perror("Error opening file for appending");
        return;
    }
    char concat[1024];
    int acc_width = 11, name_width = 17, dob_width = 10, amt_width = 8;
    char accountNumberStr[acc_width];
    char balanceStr[amt_width + 3];  // Including space for "$" and ".2"
    
    // Convert numerical values to strings
    sprintf(accountNumberStr, "%lld", account.accountNumber);
    sprintf(balanceStr, "$%.2f", account.balance);
    sprintf(concat, "%-*s | %-*s | %-*s | $%*.2f | %s\n", acc_width, accountNumberStr, name_width, account.accountHolderName, dob_width, account.birthdate, amt_width, balanceStr, account.status);
    fputs(concat,file);

    // Close the file
    fclose(file);
}


void depositMoney(const char *filename, long long accountNumber, double amount) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        perror("Error opening file for updating");
        return;
    }

    struct BankAccount account;
    int found = 0;

    while (fscanf(file, "%lld | %[^|] | %[^|] | $%lf | %s\n",
                  &account.accountNumber, account.accountHolderName, account.birthdate, &account.balance, account.status) != EOF) {
        if (account.accountNumber == accountNumber) {
            account.balance += amount;
            found = 1;
            fseek(file, -1 * (long)sizeof(account), SEEK_CUR);
            fprintf(file, "%lld | %s | %s | $%.2lf | %s\n",
                    account.accountNumber, account.accountHolderName, account.birthdate, account.balance, account.status);
            break;
        }
    }

    if (found) {
        printf("Balance updated successfully!\n");
    }
    fclose(file);
}



void displayAccountInfo(const char *filename, long long accountNumber,double balance) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    struct BankAccount account;
    int found = 0;

    while (fscanf(file, "%lld | %[^|] | %[^|] | $%lf | %s\n",
                  &account.accountNumber, account.accountHolderName, account.birthdate, &account.balance, account.status) != EOF) {
        if (account.accountNumber == accountNumber) {
            printf("Account Information:\n");
            printf("Account Number: %lld\n", account.accountNumber);
            printf("Account Holder Name: %s\n", account.accountHolderName);
            printf("Birthdate: %s\n", account.birthdate);
            printf("Balance: $%.2lf\n", balance);
            printf("Status: %s\n", account.status);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(file);
}

int main() {
    const char *filename = "..\\Data_base\\acc_info.txt";

    struct BankAccount newAccount;
    double depositAmount;
    // Generate a random account number
    newAccount.accountNumber = generateRandomAccountNumber();
    long accnum = newAccount.accountNumber;
    printf("\tWelcome To Shri Dharmasthala Manjunatheshwara Bank\n");
    printf("==================================================\n");
    printf("\tOPEN AN ACCOUNT\n");
    printf("==================================================\n");
    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", newAccount.accountHolderName);

    printf("Enter Birthdate (YYYY-MM-DD): ");
    scanf("%s", newAccount.birthdate);

    // Set the initial balance to 0
    newAccount.balance = 0.0;

    // Set the default status to "ok"
    strcpy(newAccount.status, "ok");

    // Append the new account to the file
    appendAccountToFile(filename, newAccount);

    printf("Account created successfully!\n");
    printf("Your Account Number is: %lld\n", newAccount.accountNumber);
    printf("\tACCOUNT CREDENTIALS\n");
    printf("==================================================\n");
    printf("Enter Account Number: ");
    scanf("%lld",&accnum);
    // Prompt the user for deposit
    char depositChoice;
    printf("Do you wish to Deposit Money into your Account? (y/n): ");
    scanf(" %c", &depositChoice);

    if (depositChoice == 'y' || depositChoice == 'Y') {

        printf("Enter the amount to deposit: ");
        scanf("%lf", &depositAmount);

        // Deposit money and update the balance
        depositMoney(filename, accnum, depositAmount);
    }

    // Display the account information
    displayAccountInfo(filename, newAccount.accountNumber,depositAmount+newAccount.balance);

    printf("Thank you for using our services!\n");

    return 0;
}