#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct person
{
    char name[20];
    char country_code[4];
    long int mble_no;
    char gender[8];
    char mail[50];
};

typedef struct person person;

void start();
void menu();
void add_contact();
void record_list();
void search_contact();
void remove_contact();
void update_contact();
void take_input(person *p);


int main()
{
    start();
    return 0;
}

void start()
{
    int choice;
    while(1)
    {
        menu();
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                record_list();
                getchar();
                getchar();
                break;
            case 2:
                add_contact();
                getchar();
                getchar();
                break;
            case 3:
                search_contact();
                getchar();
                getchar();
                break;
            case 4:
                remove_contact();
                getchar();
                getchar();
                break;
            case 5:
                update_contact();
                getchar();
                getchar();
                break;

            default :
                system("clear");
                printf("Thanks for using phonebook : )\n");
                getchar();
                getchar();
                exit(1);
        }
    }
}

void menu()
{
    system("clear");
    printf("\t\t\n");
    printf("\t\t*                  WELCOME TO PHONEBOOK                   *\n");
    printf("\t\t--------------------------------------------------------------\n\n");
    printf("\t\t\t1) list record\n\n");
    printf("\t\t\t2) Add contact\n\n");
    printf("\t\t\t3) Search contact\n\n");
    printf("\t\t\t4) delete contact\n\n");
    printf("\t\t\t5) Update contact\n\n");
    printf("\t\t\t7) exit Phonebook\n\n\n");

    printf("\t\t\t\tEnter your Choice : ");
}


void add_contact()
{
    system("clear");
    FILE *fp;
    fp = fopen("phonebook_db", "ab+");
    if (fp == NULL)
    {
        printf("Error!\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        person p;
        take_input(&p);
        fwrite(&p, sizeof(p), 1, fp);
        fflush(stdin);
        fclose(fp);
        system("clear");
        printf("Record added Successfully\n");
        printf("Press any key to continue ....\n");

    }
}

void take_input(person *p)
{
    system("clear");
    getchar();
    printf("Enter name : ");
    scanf("%[^\n]s",p->name);

    printf("Enter country code : ");
    scanf("%s",p->country_code); 
    
    printf("Enter mobile no : ");
    scanf("%ld",&p->mble_no); 

    printf("Enter gender : ");
    scanf("%s",p->gender); 
    
    printf("Enter email : ");
    scanf("%s",p->mail); 
}

void record_list()
{
    system("clear");
    FILE *fp;
    fp = fopen("phonebook_db", "rb");
    if (fp == NULL)
    {
        printf("Error !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        person p;
        printf("\n\t\t\t\t\n");
        printf("\t\t\t\t*                  ALL RECORDS LISTED IN PHONEBOOK                 *\n");
        printf("\t\t\t\t----------------------------------------------------------------------\n\n\n");
        printf("  NAME\t\t\t\t   COUNTRY CODE\t\t    PHONE NO\t\t    GENDER\t\t             EMAIL\n");
        printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            int i;
            int len1 = 40 - strlen(p.name);
            int len2 = 19 - strlen(p.country_code);
            int len3 = 15;
            int len4 = 21 - strlen(p.gender);
            printf("%s",p.name);
            for(i=0;i<len1;i++) printf(" ");

            printf("%s",p.country_code);
            for(i=0;i<len2;i++) printf(" ");

            printf("%ld",p.mble_no);
            for(i=0;i<len3;i++) printf(" ");

            printf("%s",p.gender);
            for(i=0;i<len4;i++) printf(" ");

            printf("%s",p.mail);
            printf("\n");
            fflush(stdin);
        }
        fflush(stdin);
        fclose(fp);
        printf("\n\nPress any key to continue....\n");
        
    }
}

void search_contact()
{
    system("clear");
    long int phone;
    printf("Enter Phone number of the person you want to search : ");
    scanf("%ld",&phone);

    FILE *fp;
    fp = fopen("phonebook_db", "rb");
    if (fp == NULL)
    {
        printf("Error !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        int flag = 0;
        person p;
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(p.mble_no == phone)
            {
                printf("  NAME\t\t\t\t   COUNTRY CODE\t\t    PHONE NO\t\t    GENDER\t\t             EMAIL\n");
                printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
                int i;
                int len1 = 40 - strlen(p.name);
                int len2 = 19 - strlen(p.country_code);
                int len3 = 15;
                int len4 = 21 - strlen(p.gender);
                printf("%s",p.name);
                for(i=0;i<len1;i++) printf(" ");

                printf("%s",p.country_code);
                for(i=0;i<len2;i++) printf(" ");

                printf("%ld",p.mble_no);
                for(i=0;i<len3;i++) printf(" ");

                printf("%s",p.gender);
                for(i=0;i<len4;i++) printf(" ");

                printf("%s",p.mail);
                printf("\n");

                flag = 1;
                break;
            }
            else continue;
            
        }
        if(flag == 0) 
        {
            system("clear");
            printf("Person is not in the Phonebook\n");
        }
        fflush(stdin);
        fclose(fp);
        printf("\n\nPress any key to continue....\n");
    }

}

void remove_contact()
{
    system("clear");
    long int phone;
    printf("Enter Phone number of the person you want to remove from phonebook : ");
    scanf("%ld",&phone);

    FILE *fp,*temp;
    fp = fopen("phonebook_db", "rb");
    temp = fopen("temp","wb+");
    if (fp == NULL)
    {
        printf("Error !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        person p;
        int flag = 0;
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(p.mble_no == phone)
            {
                system("clear");
                printf("Person removed successfully\n");
                flag = 1;
            }
            else fwrite(&p,sizeof(p),1,temp);
            fflush(stdin);
        }
        if(flag == 0)
        {
            system("clear");
            printf("No record found for %d number\n",phone);
        }
        fclose(fp);
        fclose(temp);
        remove("phonebook_db");
        rename("temp","phonebook_db");
        fflush(stdin);
        printf("Press any key to continue....\n");
        
    }

}

void update_contact()
{

    system("clear");
    long int phone;
    printf("Enter Phone number of the person you want to update details : ");
    scanf("%ld",&phone);

    FILE *fp,*temp;
    fp = fopen("phonebook_db", "rb");
    temp = fopen("temp","wb+");
    if (fp == NULL)
    {
        printf("Error in file opening, Plz try again !\n");
        printf("Press any key to continue....\n");
        return;
    }
    else
    {
        int flag = 0;
        person p;
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(p.mble_no == phone) 
            {   
                take_input(&p);
                fwrite(&p, sizeof(p), 1, temp);
                system("clear");
                printf("Data updated successfully\n");
                flag = 1;
            }
            else fwrite(&p,sizeof(p),1,temp);
            fflush(stdin);
        }
        if(flag == 0)
        {
            system("clear");
            printf("No record found for %d number\n",phone);
        }
        fclose(fp);
        fclose(temp);
        remove("phonebook_db");
        rename("temp","phonebook_db");
        fflush(stdin);
        printf("Press any key to continue....\n");
    }
}
