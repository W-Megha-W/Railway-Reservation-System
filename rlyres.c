#include<stdio.h>
#include<ctype.h>
#include"conio2.h"
#include"rlyres.h"

int enterchoice()
{
    int i;
    textcolor(YELLOW);
    gotoxy(48,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=0;i<120;i++)
    {
        printf("-");
    }
    printf("\nSelect an option\n");
    printf("1- View Trains\n2- Book Ticket\n3- View Ticket\n4- Search Ticket No\n5- View All Bookings\n6- View Train Bookings\n7- Cancel Ticket\n8- Cancel Train\n9- Quit\n");
    printf("\nEnter choice:");
    int ch;
    scanf("%d",&ch);
    return ch;
}

void add_trains()
{
    FILE *fp;
    fp=fopen("d:\\myproject\\alltrains.dat","rb");
    if(fp==NULL)
    {
        Train alltrains[4]={
        {"123","BPL","GWA",2100,1500},
        {"546","BPL","DEL",3500,2240},
        {"345","HBJ","AGR",1560,1135},
        {"896","HBJ","MUM",4500,3360}};
        fp=fopen("d:\\myproject\\alltrains.dat","wb");
        fwrite(alltrains,4*sizeof(Train),1,fp);
     //   printf("File Saved Successfully!");
        fclose(fp);
    }
    else
    {
     //   printf("File already present\n");
        fclose(fp);
    }
}

void view_trains()
{
    clrscr();
    FILE *fp;
    fp=fopen("d:\\myproject\\alltrains.dat","rb");
    Train tr;
    int i;
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
    for(i=0;i<120;i++)
    {
        printf("-");
    }
   printf("\n\n");
     while(fread(&tr,sizeof(tr),1,fp)==1)
     {
         printf("%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
         printf("\n");
     }
     fclose(fp);
     getch();
}

int check_train_no(char *trainno)
{
    FILE *fp;
    fp=fopen("d:\\myproject\\alltrains.dat","rb");
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        if(strcmp(tr.train_no,trainno)==0)
        {
          fclose(fp);
          return 1;                                                                           //If the match occurs then return 1 other wise read the next record.

        }
    }
    fclose(fp);
    return 0;                                                                                //If all records are read and the train number is not found then return 0(i.e.,return 0,if train no not found).
}

Passenger *get_passenger_details()
{
    gotoxy(100,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter your name :");
    static Passenger psn;                                                                     //declared static because to retain it even after the function completes its execution.
    fflush(stdin);                                                                                    //to clean the buffer
    fgets(psn.p_name,20,stdin);                                                               //The C library function char *fgets(char *str, int n, FILE *stream) reads a line from the specified stream and stores it into the string pointed to by str. It stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first.
    char *pos;
    pos=strchr(psn.p_name,'\n');                                                             //strchr() points to (here) '\n' in the given string i.e., psn.p_name
    *pos='\0';
    if(strcmp(psn.p_name,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,30);
        printf("Reservation Cancelled!");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    printf("Enter gender(M/F) :");
    int valid;
    do
    {
     valid=1;
     fflush(stdin);
     scanf("%c",&psn.gender);
     if(psn.gender=='0')
     {
         textcolor(LIGHTRED);
         gotoxy(1,30);
         printf("Reservation Cancelled!\t\t\t\t");
         getch();
         textcolor(YELLOW);
         return NULL;
     }
     if(psn.gender!='M' && psn.gender!='F')
     {
         textcolor(LIGHTRED);
         gotoxy(1,30);
         printf("Error! Gender should be M or F (in uppercase)");
         valid=0;
         getch();
         gotoxy(20,2);
         printf(" \t\t\t");
         gotoxy(20,2);
         textcolor(YELLOW);
     }
 }while(valid==0);
 gotoxy(1,30);
 printf("\t\t\t\t\t\t\t");
 gotoxy(1,3);
 printf("Enter train no. :");
 do
 {
     valid=1;
     fflush(stdin);
     fgets(psn.train_no,10,stdin);
     pos=strchr(psn.train_no,'\n');                                //strchr() points to (here) '\n' in the given string i.e., psn.p_name
     *pos='\0';
     if(strcmp(psn.train_no,"0")==0)
     {
         textcolor(LIGHTRED);
         gotoxy(1,30);
         printf("Reservation Cancelled!\t\t\t");
         getch();
         textcolor(YELLOW);
         return NULL;
     }
     //printf("%d",check_train_no(&psn.train_no));
     if(check_train_no(&psn.train_no)==0)
     {
         textcolor(LIGHTRED);
         gotoxy(1,30);
         printf("Error! Invalid Train No");
         valid=0;
         getch();
         gotoxy(18,3);
         printf("\t\t\t\t\t");
         gotoxy(18,3);
         textcolor(YELLOW);
     }
   }while(valid==0);
   gotoxy(1,30);
   printf("\t\t\t\t\t\t\t");
   gotoxy(1,4);
   printf("Enter travelling class(First AC-F,Second AC-S) :");
   do
   {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if(psn.p_class=='0')
        {
           gotoxy(1,30);
           textcolor(LIGHTRED);
           printf("Reservation Cancelled!\t\t\t\t\t\t");
           getch();
           textcolor(YELLOW);
           return NULL;
        }
        if(psn.p_class!='F' && psn.p_class!='S')
        {
           textcolor(LIGHTRED);
           gotoxy(1,30);
           printf("Error! Travelling class should be F or S (in uppercase)");
           valid=0;
           getch();
           gotoxy(49,4);
           printf("\t\t");
           gotoxy(49,4);
           textcolor(YELLOW);
        }
   }while(valid==0);
   gotoxy(1,30);
   printf("\t\t\t\t\t\t\t");
   gotoxy(1,5);
   printf("Enter address :");
   fflush(stdin);
   fgets(psn.address,10,stdin);
   pos=strchr(psn.address,'\n');
   pos='\0';
   if(strcmp(psn.address,"0")==0)
   {
        gotoxy(1,30);
        textcolor(LIGHTRED);
        printf("Reservation Cancelled!\t\t\t");
        getch();
        textcolor(YELLOW);
        return NULL;
    }
    printf("Enter age :");
    do
    {
        valid=1;
        scanf("%d",&psn.age);
        if(psn.age==0)
        {
            gotoxy(1,30);
            textcolor(LIGHTRED);
            printf("Reservation Cancelled!\t\t\t");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if(psn.age<0)
        {
            gotoxy(1,30);
            textcolor(LIGHTRED);
            printf("Error! Age should be positive");
            getch();
            valid=0;
            gotoxy(12,6);
            printf(" \b");
        }
    }while(valid==0);
    gotoxy(1,30);
    printf("\t\t\t\t\t\t\t");
    gotoxy(1,7);
    printf("Enter mobile number :");
    do
    {
        valid=1;
        fflush(stdin);
        fgets(psn.mob_no,11,stdin);
        pos=strchr(psn.mob_no,'\n');
        if(pos!=NULL)
            pos='\0';
        if(strcmp(psn.mob_no,"0")==0)
        {
           gotoxy(1,30);
            textcolor(LIGHTRED);
            printf("Reservation Cancelled!\t\t\t");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if(check_mob_no(psn.mob_no)==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,30);
            printf("Error!Invalid Mobile No");
            getch();
            valid=0;
            gotoxy(22,7);
            printf("\t\t\t\t");
            gotoxy(22,7);
            textcolor(YELLOW);
        }
    }while(valid==0);
    return &psn;
}

int check_mob_no(char *p_mob)
{
    if(strlen(p_mob)!=10)
        return 0;

    while(*p_mob!='\0')
    {
        if(isdigit(*p_mob)==0)
            return 0;
        p_mob++;
    }
    return 1;
}


int get_booked_ticket_count(char *train_no,char tc)
{
    FILE *fp;
    fp=fopen("d:\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    int count=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if((strcmp(pr.train_no,train_no)==0)&& pr.p_class=='tc')
         count++;
    }
    fclose(fp);
    return count;
}

int last_ticket_no()
{
    FILE *fp;
    Passenger pr;
    fp=fopen("d:\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    fseek(fp,-1*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;
}

int book_ticket(Passenger P)
{
    FILE *fp;
    int count=1;
    int ticket_count=get_booked_ticket_count(P.train_no,P.p_class);
    if(ticket_count==30)
    {
        textcolor(LIGHTRED);
       printf("All seats full in train no %s in %c class!",P.train_no,P.p_class);
       return -1;
    }
    else
    {
        count=count+last_ticket_no();
    }
    P.ticketno=count;
    fp=fopen("d:\\myproject\\allbookings.dat","ab");
    if(fp==NULL)
    {
        printf("Sorry! file cannot be opened.");
        return -1;
    }
    fwrite(&P,sizeof(P),1,fp);
    fclose(fp);
    return P.ticketno;
}

int accept_ticket_no()
{
    printf("Enter ticket no :");
    int valid;
    int ticket_no;
    do
    {
     valid=1;
     scanf("%d",&ticket_no);
     if(ticket_no==0)
     {
         textcolor(LIGHTRED);
         gotoxy(1,30);
         printf("Cancelling Input\t\t");
         getch();
         textcolor(YELLOW);
         return 0;
     }
     if(ticket_no<0)
        {
            gotoxy(1,30);
            textcolor(LIGHTRED);
            printf("Error! Ticket number should be positive");
            getch();
            valid=0;
            gotoxy(17,1);
            textcolor(YELLOW);
            printf(" \t");
        }
     }while(valid==0);
   return ticket_no;
}

void view_ticket(int ticket_no)
{
    FILE *fp;
    fp=fopen("d:\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
    {
      printf("No bookings done yet!");
      return -1;
    }
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
       if(pr.ticketno==ticket_no)
       {
        printf("\nName : %s \nGender : %c \nTrain no.  %s \nClass : %c \nAddress : %sAge : %d \nMob no.  %s \nTicket no.  %d",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticketno);
        printf("\n\n");
        getch();
        found=1;
        break;
       }
    }
    if(found==0)
    {
        textcolor(LIGHTRED);
        printf("\nNo details of ticket no. %d found!",ticket_no);
    }
    fclose(fp);
}
int cancel_ticket(int ticket_no)
{
    FILE *fp1,*fp2;
    fp1=fopen("d:\\myproject\\allbookings.dat","rb");
    fp2=fopen("d:\\myproject\\temp.dat","wb+");
    if(fp1==NULL)
    {
        printf("No bookings done yet!");
        return -1;
    }
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
       if(pr.ticketno!=ticket_no)
       {
           fwrite(&pr,sizeof(pr),1,fp2);
       }
       else
       {
           found=1;
       }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("d:\\myproject\\temp.dat");
    }
    else
    {
        remove("d:\\myproject\\allbookings.dat");
        rename("d:\\myproject\\temp.dat","d:\\myproject\\allbookings.dat");
    }
    return found;
}

char * accept_train_no()
{
    static char train_no[10];
    printf("Enter train no. :");
    int valid=1;
  do
  {

     fflush(stdin);
     scanf("%s",train_no);
     if(strcmp(train_no,"0")==0)
     {
         textcolor(LIGHTRED);
         gotoxy(1,30);
         printf("Cancelling Input.....");
         getch();
         textcolor(YELLOW);
         return NULL;
     }
     //printf("%d",check_train_no(&psn.train_no));
     if(check_train_no(&train_no)==0)
     {
         textcolor(LIGHTRED);
         gotoxy(1,30);
         printf("Error! Invalid Train No");
         valid=0;
         getch();
         gotoxy(18,1);
         printf("\t\t\t\t\t");
         gotoxy(18,1);
         textcolor(YELLOW);
     }
   }while(valid==0);
   clrscr();
   return train_no;
}

int cancel_train(char * ptrainno)
{
    FILE *fp1,*fp2;
    fp1=fopen("d:\\myproject\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        printf("No bookings done yet!");
        return -1;
    }
    fp2=fopen("d:\\myproject\\temp.dat","wb+");
    if(fp1==NULL)
    {
        printf("Error in cancelling ticket!");
        return -1;
    }
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(strcmp(pr.train_no,ptrainno)!=0)
        {
            fwrite(fp1,sizeof(pr),1,fp2);
        }
        else
            found=1;
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("d:\\myproject\\temp.dat");
    }
    else
    {
        remove("d:\\myproject\\allbookings.dat");
        rename("d:\\myproject\\temp.dat","d:\\myproject\\allbookings.dat");
    }
    return found;
}

void view_all_bookings()
{
    FILE *fp;
    fp=fopen("d:\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        printf("No bookings done yet!");
        return -1;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        printf("%s %c %s %d %s %c %d %s ",pr.p_name,pr.gender,pr.address,pr.age,pr.train_no,pr.p_class,pr.ticketno,pr.mob_no);
        printf("\n");
    }
    fclose(fp);
}

void view_bookings(char * trainno)
{
    FILE *fp;
    fp=fopen("d:\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        printf("No bookings done yet!");
        return -1;
    }
    Passenger pr;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,trainno)==0)
        {
            printf("%s %c %s %d %s %c %d %s ",pr.p_name,pr.gender,pr.address,pr.age,pr.train_no,pr.p_class,pr.ticketno,pr.mob_no);
            printf("\n");
        }
    }
    fclose(fp);
}

char* accept_mob_no()
{
    static char mob_no[10];
    int valid;
    char *pos;
    printf("Enter mobile number :");
    do
    {
        valid=1;
        fflush(stdin);
        fgets(mob_no,11,stdin);
        pos=strchr(mob_no,'\n');
        if(pos!=NULL)
            pos='\0';
        if(strcmp(mob_no,"0")==0)
        {
           gotoxy(1,30);
            textcolor(LIGHTRED);
            printf("Reservation Cancelled!\t\t\t");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        if(check_mob_no(mob_no)==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,30);
            printf("Error!Invalid Mobile No");
            getch();
            valid=0;
            gotoxy(22,1);
            printf("\t\t\t\t");
            gotoxy(22,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    return mob_no;
}

int * get_ticket_no(char * mno)
{
    FILE *fp;
    fp=fopen("d:\\myproject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        printf("No bookings done yet!");
        return -1;
    }

    Passenger pr;
    static int tnos[10];
    int i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,mno)==0)
        {
            tnos[i]=pr.ticketno;
            i++;
        }
    }
    tnos[i]=-1;
    return tnos;
}
