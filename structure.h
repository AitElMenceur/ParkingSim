#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <locale.h>
#include <time.h>

#define lngline 300
/*----Car Structure -------*/
typedef struct car car;
 struct car
{
  char dir[1];// North="N"...
  int x,y,v; // position and velocity
  char mdl[10];// Car model (Ex: "car1/")
  char color[10]; // Color 
  int exiting;// Exiting the Parking 
  car *next;//Pointer to the next car
};
/*----Parking lot structure------*/
typedef struct {
  ///position
  int x;
  int y;
  //State
  int boolean;
  int booleanBis;
  //Timer
  int timer;
}parking;
/*---Begening of the linked list----*/
typedef struct 
{
  car *first;
}List;
car* createarraycar(int nbcar);
void delay(int number_of_seconds) ;
void reset();
void gotoxy(int x,int y);
char *retrievetxt(car c,char color[]);
void dispcar(car c);
void background() ;
car move(car c);
car turn(car c, char direction[1]);
parking changestate(parking par);

char *retrievetxt(car c,char color[10]) // Retrieve Txt file data,
{ 
  /*Building relative path of the .txt file*/
  printf("%s",color);
  char * Buffer="";
  char s[lngline]= "";
  FILE* fichier = NULL;
  char location[] = "./obj/";
  strcat(location, c.mdl);
  strcat(location, c.dir);
  strcat(location,".txt"); 
  char str[]="";
  fichier = fopen(location, "r");
  /*Retreving*/
  while (fgets(str,lngline, fichier) != NULL)// Check en of a line
    {
      strcat(s,str);
    }
  fclose(fichier);
  Buffer = (char*)malloc(strlen(s) + 1);
  return Buffer;
}

void background() // Display the Parking 
{ 
  gotoxy(0,0);
  printf("\033[0;34m");
  char s[lngline]= "";
  FILE* fichier = NULL;
  char location[] = "./obj/Parking.txt";
  fichier = fopen(location, "r");
  while (fgets(s,lngline, fichier) != NULL)
    {
      printf("%s",s);
    }
  printf("\n");
  fclose(fichier);
}
void menutitle() //a menu, we didn't use it here in the end as the project require a random choice of mode(full,fluid) 
{
  gotoxy(0,0);
  printf("\033[0;34m");
  char s[lngline]= "";
  FILE* fichier = NULL;
  char location[] = "./obj/Parkingmenu.txt";
  fichier = fopen(location, "r");
  while (fgets(s,lngline, fichier) != NULL)
    {
      printf("%s",s);
    }
  printf("\n");
  fclose(fichier);
gotoxy(40,0);
}

void reset()// clear output screen
{ 
  printf("\033[H\033[J");
}

void gotoxy(int x, int y)// Move cursor to (x,y) coordinates
{ 
  printf("\033[%d;%dH",x,y);
}

void dispcar(car c)
{
  printf("%s",c.color);
  char *p= retrievetxt(c,c.color);
  if(strcmp(c.mdl,"car1/")==0)//Model 1
  {
    if(strcmp(c.dir,"N")==0||strcmp(c.dir,"S")==0)
      {//North and South directions
        gotoxy(c.x,c.y);
        printf("%.9s",p);
        gotoxy(c.x+1,c.y);
        printf("%.9s",&p[9]);
        gotoxy(c.x+2,c.y);
        printf("%.9s",&p[18]);
        printf("\n");
        
      }
    if(strcmp(c.dir,"E")==0||strcmp(c.dir,"W")==0)
    {//East and West directions
      gotoxy(c.x,c.y);
      printf("%.15s",p);
      gotoxy(c.x+1,c.y);
      printf("%.15s",&p[15]);
      printf("\n");
    }
  }
  if(strcmp(c.mdl,"car3/")==0)//Model 3
  {
    if(strcmp(c.dir,"N")==0||strcmp(c.dir,"S")==0)
      {//North and South directions
        gotoxy(c.x,c.y);
        printf("%.3s",p);
        gotoxy(c.x+1,c.y);
        printf("%.1s",&p[3]);
        gotoxy(c.x+2,c.y);
        printf("%.3s",&p[4]);
        printf("\n");
        
      }
    if(strcmp(c.dir,"E")==0||strcmp(c.dir,"W")==0)
    {//East and West directions
      gotoxy(c.x,c.y);
      printf("%.7s",p);
      printf("\n");
    }
  }
  if(strcmp(c.mdl,"car2/")==0)//Model 2
  {
    if(strcmp(c.dir,"N")==0||strcmp(c.dir,"S")==0)
      {//North and South directions
        gotoxy(c.x,c.y);
        printf("%.9s",p);
        gotoxy(c.x+1,c.y);
        printf("%.9s",&p[9]);
        printf("\n");      
      }
    if(strcmp(c.dir,"E")==0||strcmp(c.dir,"W")==0)
    {//East and West directions
      gotoxy(c.x,c.y);
      printf("%.9s",p);
      gotoxy(c.x+1,c.y);
      printf("%.9s",&p[9]);
      printf("\n");
    }
  }
   printf("\033[0;30m");
   gotoxy(41,170);
}
void disppark(parking par[54])
{
   printf("\033[0;30m");
   gotoxy(41,170);
   for (int j=0;j<54;j++) 
   {
     int x = par[j].x;
     int y = par[j].y;
     if(par[j].booleanBis)
     {
       y+=6;//Left Parking slot
     }
     else
     {
       y-=3;// Right parking slot
     }
     if(par[j].boolean==1)
     {
       printf("\033[1;31m");//Slot is occupied
     }
     if(par[j].boolean==0)
     {
       printf("\033[1;32m");//Slot is free
     }
     gotoxy(x-1,y);
     printf("█");
     gotoxy(x,y);
     printf("█");
     gotoxy(x+1,y);
     printf("█");
   }
  printf("\033[0;30m");
  gotoxy(41,170);
}
car turn(car ct, char direction[1])
{
  strcpy(ct.dir,direction);
  return ct;
}

car move(car ct)// moving a car
{
  if (strcmp (ct.dir, "N")==0)// To North
  {
      ct.x-=ct.v;
      return ct;
  }
  else if (strcmp (ct.dir,"S")==0)// To South
  {
    ct.x+=ct.v;
    return ct;
  }
  else if (strcmp (ct.dir, "E")==0)// To East
  {
    ct.y+=ct.v;
    return ct;
  }
  else if (strcmp (ct.dir,"W")==0 )// To West
  {
    ct.y-=ct.v;
    return ct;
  }
 return ct; 
}

parking* initparking() // initialise every parking lot structure in an array
{
  parking* Parking=(parking*)malloc(sizeof(parking)*54);
  for(int i = 0 ; i < 10; i++)
  {
    Parking[i].y = 5;
    Parking[i].x = 3+4*i;
    Parking[i].booleanBis = 0;
  }
  for(int i = 0 ; i < 6; i++)
  {
    Parking[10+i].y =30;
    Parking[10+i].x = 11+4*i;
    Parking[10+i].booleanBis = 1;
  }
  for(int i = 0 ; i < 6; i++)
  {
    Parking[16+i].y =42;
    Parking[16+i].x = 11+4*i;
    Parking[16+i].booleanBis = 0;
  }
  for(int i = 0 ; i < 5; i++)
  {
    Parking[22+i].y =68;
    Parking[22+i].x = 15+4*i;
    Parking[22+i].booleanBis = 1;
  }
  for(int i = 0 ; i < 5; i++)
  {
    Parking[27+i].y =80;
    Parking[27+i].x = 15+4*i;
    Parking[27+i].booleanBis = 0;
  }
  for(int i = 0 ; i < 6; i++)
  {
    Parking[32+i].y =106;
    Parking[32+i].x = 11+4*i;
    Parking[32+i].booleanBis = 1;
  }
  for(int i = 0 ; i < 6; i++)
  {
    Parking[38+i].y =118;
    Parking[38+i].x = 11+4*i;
    Parking[38+i].booleanBis = 0;
  }
  for(int i = 0 ; i < 10; i++)
  {
    Parking[44+i].y = 147;
    Parking[44+i].x = 3+4*i;
    Parking[44+i].booleanBis = 1;
  }
  for(int i =0; i < 54; i++)
  {
    Parking[i].boolean = 0;
    Parking[i].timer=0;
  }
  return Parking;
}

void delay(int number_of_seconds)// Time delay 
{
  usleep(number_of_seconds*1000);
}

car createcar(car ct)// Create car with a random model and color.
{
  ct.x=5;  
  ct.y=65;
  ct.v=1;
  strcpy(ct.dir,"N");
  int choice;
  choice=rand()%3;// Random model
  switch(choice)
  {
    case 0:
      strcpy(ct.mdl,"car1/");
      break;
    case 1:
      strcpy(ct.mdl,"car2/");
      break;
    case 2:
      strcpy(ct.mdl,"car3/");
      break;
  }
  int x= 1+rand()%5;// Random Color
  char result[50];
  sprintf(result,"\033[0;3%d", x);
  strcat(result,"m");
  strcpy(ct.color,result);
  ct.next=NULL;
  ct.exiting=0;
  return ct;
}
/* ---Linked list manipulation----*/
List *initialisation()
{
    List *list = (List*)malloc(sizeof(List));
    car *element = (car*)malloc(sizeof(car));
    if (list == NULL || element == NULL)
    {
      exit(EXIT_FAILURE); 
    }
    *element=createcar(*element);// First car 
    element->next = NULL;
    list->first = element;// append the car to the List head 
    return list;
}
void insertion(List *list)
{
  car *newcar;//New element  
  newcar = (car*)malloc(sizeof(car));
  if (list == NULL || newcar == NULL)
  {
    exit(EXIT_FAILURE);
  }
  *newcar=createcar(*newcar);// create car 
  /* insert car at the end */
  car *current=list->first;//get first node adress
  while (true)
  {
    if(current->next==NULL)
    {
      current->next=newcar;// append the element to the end
      break;
    }    
    current = current->next;  // loop until reaching the end of the linked list
  }
}
void deletecar(List* list)
{
  car* e,*prec=NULL;
  e=list->first;// get the head 
  while(e!=NULL)
  {
    if(e->x==5&&e->y==84)// Position condition
    {
      if(prec==NULL)// if first element of the list
      {
        list->first=e->next;
      }
      else
      {
        prec->next=e->next;// break the list and link the n-1 car with the n+1 car 
      }
    }
    else//looping
    {
      prec=e;
    }
    e=e->next;
  }
}

