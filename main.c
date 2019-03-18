#include <stdio.h>
#include <stdlib.h>
#include"conio2.h"
#include"rlyres.h"

int main()
{
   Passenger *ptr;

   int choice,result;
   int ticket_no;
   char *p_train_no;
   char *pmob_no;
   int *pticket_no;
   add_trains();
   while(1)
   {

       clrscr();
       choice=enterchoice();
       if(choice==9)
       {
           exit(0);
       }
       switch(choice)
       {
       case 1:
          clrscr();
          view_trains();
          break;
       case 2:
           clrscr();
           ptr=get_passenger_details();
           if(ptr==NULL)
            printf("Booking Cancelled!");
           else
           {
               ticket_no=book_ticket(*ptr);
               if(ticket_no== -1)
               {
                 textcolor(LIGHTRED);
                 printf("Booking Failed!");
               }
               else
               {
                   clrscr();
                   textcolor(LIGHTGREEN);
                   printf("Ticket successfully booked\nYour ticket number is %d",ticket_no);
               }
              textcolor(WHITE);
              printf("\nPress any key to go back to the main screen");
              getch();
              clrscr();
           }
          break;
       case 3:
          clrscr();
          ticket_no=accept_ticket_no();
          if(ticket_no!=0)
              view_ticket(ticket_no);
          textcolor(WHITE);
          printf("Press any key to go back to the main screen");
          clrscr();
          break;
       case 4:
          clrscr();
          pmob_no=accept_mob_no();
          int i=0;
          if(pmob_no!=NULL)
          {
            pticket_no=get_ticket_no(pmob_no);
            printf("Ticket nos. for booking of %s : \n",pmob_no);
            while(pticket_no[i]!=-1)
            {
                printf("%d\n",pticket_no[i]);
                i++;
            }
          }
          else
          {
              textcolor(LIGHTRED);
              printf("Sorry! No tickets booked against the mobile number %s ",pmob_no);
          }
          getch();
          clrscr();
          break;
       case 5:
           clrscr();
           view_all_bookings();
           getch();
           clrscr();
          break;
       case 6:
           clrscr();
           p_train_no=accept_train_no();
           view_bookings(p_train_no);
           getch();
          break;
       case 7:
          clrscr();
          ticket_no=accept_ticket_no();
          if(ticket_no!=0)
          {
              result=cancel_ticket(ticket_no);
              if(result==0)
              {
                  textcolor(LIGHTRED);
                  printf("Sorry! No tickets booked against the ticket number %d ",ticket_no);
              }
              else
              {
                  textcolor(GREEN);
                  printf("Ticket no %d successfully cancelled",ticket_no);
              }
              textcolor(WHITE);
              printf("\n\nPress any key to go back to the main screen");
          }
          getch();
          clrscr();
          break;
       case 8:
          clrscr();
          p_train_no=accept_train_no();
          if(p_train_no!=NULL)
          {
              result=cancel_train(p_train_no);
              if(result==0)
              {
                  textcolor(LIGHTRED);
                  printf("Sorry! No tickets booked in the train number %s ",p_train_no);
              }
              else
              {
                  textcolor(GREEN);
                  printf("Train no %s successfully cancelled.",p_train_no);
              }
              textcolor(WHITE);
              printf("\n\nPress any key to go back to the main screen");
          }
          getch();
          clrscr();
          break;
       default:
          textcolor(LIGHTRED);
          printf("Wrong Choice!Try again\n");
          getch();
          clrscr();
       }
   }
    return 0;
}
