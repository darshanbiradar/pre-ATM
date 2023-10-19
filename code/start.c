#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
float Amount;
int card_line;
int acc_line;
int beni_count;
char temp_block[1024];
char temp_deduct[1024];
//card info storing in a structure
typedef struct {
    char card_no[17];
    char pin[5];
    char expiry_date[6];
    char acc_no[12];
    char card_blocked[5];
}card;
//if customer present storing in the account structure
typedef struct{
    char no[102];
    char name_holde[100];
    char DOB[100];
    float amount;
    char status[10];
}Account;

card user;
Account user_acc;
Account beni;

int isNumber(const char *str) {
    int i = 0;
    if (str[0] == '\0' || (str[0] == '-' && str[1] == '\0')) {
        return 0; 
    }
    while (str[i] != '\0') {
        if (!isdigit(str[i])) {
            return 0;
        }
        i++;
    }
    return 1; 
}

//Setting the amount to the atm at the time of INITILIZATION
void ATM_init(){
    Amount=100000;
    if(isalnum(Amount)){
        //return Amount;
    }
    // else{
    //     printf("Invalid Input\n");
    //     printf("Enter a Valid Amount :");
    //     scanf("%f",&Amount);
    // }
}

//Creating a generic file for opening the file in the read mode
//return type is FILE pointer
FILE* fileread(char *s){
    FILE *fp=fopen(s,"r");
    if(fp==NULL){
        printf("Error Opening the File\n");
    }
    else return fp;
}

//Function to check whether the entered Card number is persent in the bank file system if yes then storing it into the card structure
//return type boolean 
bool card_autho(){
    system("cls");
    char card_no[17];
    int i=0;
    printf("Enter the Card No:");
    scanf("%s",card_no);
    while (i<3){
         if (strlen(card_no) != 16){
        printf("Enter valid 16 digit Card No\n");
        _sleep(2000);
        return false;
    }
    FILE *fp = fileread("..\\Data_base\\card_data.txt");
    card_line=0;
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL){
        card_line++;
        sscanf(line, "%16s %4s %5s %11s %2s", user.card_no, user.pin, user.expiry_date, user.acc_no,user.card_blocked);
        if (strcmp(card_no, user.card_no) == 0){
            if(strcmp(user.card_blocked,"ok")==0)
                return true;
            else{
            printf("Card Blocked Please Contact The Branch Manager\n");
            fclose(fp);
            return false;
            }
        }
    }
    i++;
    printf("Card Number Invalid\n");
    _sleep(4000);
    fclose(fp);
    return false;
    }  
}

void rewrite(char *source,char *dest){
    FILE *fp_read=fopen(source,"r");
    FILE *fp_write=fopen(dest,"w");
    char line[1024];
    while(fgets(line,1024,fp_read)!=NULL){
        fputs(line,fp_write);
    }
    fclose(fp_read);
    fclose(fp_write);
}

void  block(){
    char concat[1024];
    int acc_width=12,name_width=18,dob_width=11,amt_width=10;
    sprintf(concat,"%s %s %s %s no\n",user.card_no,user.pin,user.expiry_date,user.acc_no);
    // printf("%s",concat);
    strcpy(temp_block,concat);
}

//Blocking of a card
void block_card(){
    FILE *fp_pre=fopen("..\\Data_base\\card_data.txt","r");
    FILE *fp_temp=fopen("..\\Data_base\\card_temp.txt","w");
    char pr_line[1024];
        bool keep_reading=true;
        int count=1;
        do{
            fgets(pr_line,1024,fp_pre);
            if(card_line==count){
                fputs(temp_block,fp_temp);
                block();
            }
            else{    
                fputs(pr_line,fp_temp);
                }
            count++;
            if(feof(fp_pre))
                keep_reading=false;
        }while(keep_reading);
        fclose(fp_pre);
        fclose(fp_temp);
        rewrite("..\\Data_base\\card_temp.txt","..\\Data_base\\card_data.txt");
}


//Checking fo authenication of the user with his PIN
bool pin_autho(){
    system("cls");
    int tries=0;
    char pin[5];
    while(tries<3){        // MAX of 3 tries
        printf("\nEnter your PIN: ");
        scanf("%s",pin);
        if(strcmp(user.pin,pin)==0){
            printf("Authentication Successfull\n");
            return true;
        }
        tries++;
    }
    printf("Card Blocked Please Contact The Branch Manager\n"); //if fails then card is blocked
    _sleep(1000);
    block_card();
    return false;
}



//opening the acc_info file and matching the account number and storing the details in the account structure
void acc_info_fetch(){
    FILE *fp=fileread("..\\Data_base\\acc_info.txt");
    char line[256];
    acc_line=0;
    while(fgets(line,sizeof(line),fp)!=NULL){
        acc_line++;
        sscanf(line,"%s | %[^|] | %s  | $%f |%s",user_acc.no,user_acc.name_holde,user_acc.DOB,&user_acc.amount,user_acc.status);
        if(strcmp(user.acc_no,user_acc.no)==0){
            if(strncmp(user_acc.status,"ok",2)==0)
                return;
            else{
                printf("Bad Account\n");
            }
        }
    }
    fclose(fp);
}

void with_stcat(){
    char concat[1024];
    int acc_width=11,name_width=18,dob_width=13,amt_width=9;
    sprintf(concat,"%-*s | %-*s| %-*s | $%-*.2f|%s\n",acc_width,user_acc.no,name_width,user_acc.name_holde,dob_width,user_acc.DOB,amt_width,user_acc.amount,user_acc.status);
    //printf("%s",concat);
    strcpy(temp_deduct,concat);
}
void with_write(){
        FILE *fp_acc=fopen("..\\Data_base\\acc_info.txt","r");
        FILE *fp_temp=fopen("..\\Data_base\\temp_acc.txt","w");
        char pr_line[1024];
        bool keep_reading=true;
        int count=1;
        do{
            fgets(pr_line,1024,fp_acc);
            if(acc_line==count){
                with_stcat();
                fputs(temp_deduct,fp_temp);
            }
            else
                fputs(pr_line,fp_temp);
             if(feof(fp_acc))
                keep_reading=false;
            count++;
            
        }while(keep_reading);
        fclose(fp_acc);
        fclose(fp_temp);
        rewrite("..\\Data_base\\temp_acc.txt","..\\Data_base\\acc_info.txt");
        
}

void Withdraw(){
    system("cls");
    int u_amt,i=0;
    // printf("Avaliable Balance: $%.2f\n",user_acc.amount);
    while(i<3){
        printf("Enter amount to withdraw (Max tries 3): ");
        scanf("%d",&u_amt);
        if (u_amt <= Amount && u_amt <= user_acc.amount) {
            break;
        }
        i++;
    }
    user_acc.amount=user_acc.amount-u_amt;
    Amount = Amount - u_amt;
    // char *new_data=stcat();
    with_write();
//     printf("Avaliable Balance: $%.2f\n",user_acc.amount);
//     printf("Avaliable balance in the ATM %.2f\n",Amount);
}
void transf_stcat(){
    char concat[1024];
    int acc_width=11,name_width=18,dob_width=14,amt_width=9;
    sprintf(concat,"%-*s | %-*s| %-*s | $%-*.2f|%s\n",acc_width,beni.no,name_width,beni.name_holde,dob_width,beni.DOB,amt_width,beni.amount,beni.status);
    //printf("%s",concat);
    strcpy(temp_deduct,concat);
}
void transf_write(){
        FILE *fp_acc=fileread("..\\Data_base\\acc_info.txt");
        FILE *fp_temp=fopen("..\\Data_base\\temp_acc.txt","w");
        char pr_line[1024];
        bool keep_reading=true;
        int count=1;
        do{
            fgets(pr_line,1024,fp_acc);
            if(beni_count==count){
                transf_stcat();
                fputs(temp_deduct,fp_temp);
            }
            else
                fputs(pr_line,fp_temp);
            count++;
            if(feof(fp_acc))
                keep_reading=false;
        }while(keep_reading);
        fclose(fp_acc);
        fclose(fp_temp);
        rewrite("..\\Data_base\\temp_acc.txt","..\\Data_base\\acc_info.txt");
}
void init_transfer(){
    float temp_amt;
    system("cls");
    printf("\t\tHolder of %s account no is %s\n",beni.no,beni.name_holde);
    printf("Enter the amount you wish to transfer: ");
    scanf("%f",&temp_amt);
    if(user_acc.amount >= temp_amt && temp_amt > 0 ){
        user_acc.amount=user_acc.amount-temp_amt;
        beni.amount=beni.amount+temp_amt;
        with_write();
        transf_write();
        printf("Transfer was successfull\n");
    }
    else if(user_acc.amount < temp_amt){
        printf("Insufficient Balanace\n");
    }
}

void transfer_funds(){
    // Account beni;
    char temp[13];
    int i=0;
    beni_count=0;
    while(i<2){
        printf("Enter the 11 digit Account number of the reciever (MAX tries 2):");
        scanf("%s",temp);
        FILE *fp=fileread("..\\Data_base\\acc_info.txt");
        char line[256];
        while(fgets(line,sizeof(line),fp)!=NULL){
            beni_count++;
            sscanf(line,"%s | %[^|] | %s | $%f |%s",beni.no,beni.name_holde,beni.DOB,&beni.amount,beni.status);
            printf("\n%s | %s | %s | $%f |%s",beni.no,beni.name_holde,beni.DOB,beni.amount,beni.status);
            if(strncmp(temp,beni.no,11)==0){
                if(strcmp(beni.status,"ok")==0){
                    init_transfer();
                    return;
                }
                else{
                    printf("Bad Account\n");
                }
            }
        }
        i++;
    }
}
void deposit(){
    float amt;
    system("cls");
    //10printf("Current Balance %.2f",user_acc.amount);
    printf("Enter the amount u want to deposit:");
    scanf("%f",&amt);
    user_acc.amount=user_acc.amount+amt;
    with_write();
}

void mini_statement(){

}

void bal_enq(){
    system("cls");
    printf("Current Balance is $%.2f\n",user_acc.amount);
    _sleep(5000);
    system("cls");
    printf("Thank you for using the service");
    _sleep(4000);
    system("cls");
}

void select_operation(){
    system("cls");
    int choice=-1;
    retry:
        printf("\t\t\t\tWELCOME %s\t\t\n",user_acc.name_holde);
        printf("_____________________________________________________________________________\n");
        printf("\t\t1.Withdrawal\t\t2.Transfer Funds\n\n\t\t3.Mini Statement\t4.Balance Enquiry\n\n\t\t\t    5.Depoist\n\n\t\t\tYour Choice: ");
        scanf("%d",&choice);
   
    switch(choice){
        case 1:Withdraw();
                bal_enq();
                break;
        case 2:transfer_funds();
                bal_enq();
                break;
        case 3:mini_statement();
                break;
        case 4:bal_enq();
                break;
        case 5:deposit();
                bal_enq();
        default:goto retry;
                break;
    }
}
void dump(){
}
int main() {
    char temp;
    start:
    _sleep(2000);
    ATM_init();
    system("cls");
    printf("\t\t\tWELCOME CUSTOMER\n");
    _sleep(1000);
    scanf("%c",&temp);
    bool card_sucess=card_autho();
    if(card_sucess){
        bool pin_success=pin_autho();
        if(pin_success){
        acc_info_fetch();
        select_operation();}
    }
    void dump();
    goto start;
    return 0;
}