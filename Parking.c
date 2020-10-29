#include "Circuit.h"

int main()
{
  srand(time(NULL));
  int choice,freq,nbcar;
  while(1)
  {
    reset();
    choice=(rand()%2);
    switch(choice)
    {
      case 0:
        reset();
        nbcar=(rand() % (60 - 30 + 1)) + 30; 
        freq=(rand() % (50 - 20 + 1)) + 20; 
        break;
      case 1:
        nbcar=(rand() % (100 - 54 + 1)) + 54; 
        freq=(rand() % (30 - 10 + 1)) + 10; 
        break;
    }
    reset();
    //Creating linked-list and matrix
    parking*PAR;
    PAR=initparking();
    List *L;
    L=initialisation();
    reset();
    int mat1[42][153]={0};
    int mat2[42][153]={0};
    initmatrice(mat1);
    int p=0;
    //Main loop
    while(1)
    {
      int i=0;
      while(i!=freq)
      {
        initmatrice(mat2);
        background();
        disppark(PAR);
        car *current=L->first;
        while (current != NULL) 
        {
          *current=Circuit(*current,mat1,PAR,L);
          poswriting(*current,mat2);
          dispcar(*current);
          current = current->next;
        }
        disppark(PAR); 
        delay(80);
        memcpy(mat1,mat2,42*153*sizeof(int));
        reset(); 
        i++;
      }
      i=0;
      //creating a car
      if (p<=nbcar)
      {
        insertion(L);
        p++;
      }
      //Exiting the simulation
      if(L->first==NULL){return 0;}
    }
  }
}

