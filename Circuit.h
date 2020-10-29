#include <stdio.h>
#include <stdbool.h>
#include "structure.h"
#define N 153
#define wait 1000
typedef struct List L;
/*----Car movement function----*/
car CorridorA(car ct,int MAT[42][153],parking PAR[54]);
car CorridorB1(car ct,int MAT[42][153],parking PAR[54]);
car CorridorB2(car ct,int MAT[42][153],parking PAR[54]);
car B1ToB2(car ct,int MAT[42][153]);
car CorridorC1(car ct,int MAT[42][153],parking PAR[54]);
car CorridorC2(car ct,int MAT[42][153],parking PAR[54]);
car C1ToC2(car ct,int MAT[42][153]);
car CorridorD(car ct,int MAT[42][153],parking PAR[54]);
car EnterToA(car ct,int MAT[42][153]);
car AToB(car ct,int MAT[42][153]);
car BToct(car ct,int MAT[42][153]);
car CToD(car ct,int MAT[42][153]);
car DToExit(car ct,int MAT[42][153]);
List* Exitanddelete(car ct,List*L);
car ExitandRetry(car ct,List*L);
car Circuit(car ct,int MAT[42][153],parking PAR[54],List *L);
bool checkcolision(car c,int MAT[42][153]);
/*----- Parking a car function -----*/
car parking_Left_A(car ct,int MAT[42][153],parking PAR[54]);
car parking_Right_A(car ct,int MAT[42][153],parking PAR[54]);
car parkingB1(car ct,int MAT[42][153],parking PAR[54]);
car parkingB2(car ct,int MAT[42][153],parking PAR[54]);
car parkingC1(car ct,int MAT[42][153],parking PAR[54]);
car parkingC2(car ct,int MAT[42][153],parking PAR[54]);
car parking_Left_D(car ct,int MAT[42][153],parking PAR[54]);
car parking_Right_D(car ct,int MAT[42][153],parking PAR[54]);

car Circuit(car ct,int MAT[42][153],parking PAR[54],List* L) //this function loops every action that a car car do ( moving and parking)
{
      ct= EnterToA(ct,MAT);
      ct= CorridorA(ct,MAT,PAR);
      ct= parking_Left_A( ct, MAT,PAR);
      ct= parking_Right_A( ct, MAT,PAR);
      ct= AToB(ct,MAT);
      ct= CorridorB1(ct,MAT,PAR);
      ct= parkingB1(ct,MAT,PAR);
      ct= B1ToB2(ct,MAT);
      ct= parkingB2(ct,MAT,PAR);
      ct= CorridorB2(ct,MAT,PAR);
      ct= BToct(ct,MAT);
      ct= parkingC1(ct,MAT,PAR);
      ct= CorridorC1(ct,MAT,PAR);
      ct= C1ToC2(ct,MAT);
      ct= parkingC2(ct,MAT,PAR);
      ct= CorridorC2(ct,MAT,PAR);
      ct= CToD(ct,MAT);
      ct= CorridorD(ct,MAT,PAR);
      ct= parking_Left_D(ct,MAT,PAR);
      ct= parking_Right_D(ct,MAT,PAR);
      ct= DToExit(ct,MAT);
      L= Exitanddelete(ct,L);
      ct= ExitandRetry(ct,L);
      return ct;
}
/*---the idea behind every parking guntion is the same , juste position change depend on the parking corridor --*/
car parking_Left_A(car ct,int MAT[42][153],parking PAR[54])
{
  // Selecting the parking slot ID
  int i=-1;
  if(ct.x==3){i=0;}
  if(ct.x==7){i=1;}
  if(ct.x==11){i=2;}
  if(ct.x==15){i=3;}
  if(ct.x==19){i=4;}
  if(ct.x==23){i=5;}
  if(ct.x==27){i=6;}
  if(ct.x==31){i=7;}
  if(ct.x==35){i=8;}
  if(ct.x==39){i=9;}
  if(i==-1){return ct;}
  else
  {
    if(PAR[i].timer==0)//entering the parking zone
    {
      if(ct.y<19&&ct.y>4)
      {
        PAR[i].boolean=1;
        for(int i =0;i<10;i++)
        {
          if(ct.x==3+i*4)
            {
              ct=turn(ct,"W");
              if(checkcolision(ct,MAT)){ct=turn(ct,"W");ct.v=1;ct=move(ct);}
              if(!checkcolision(ct,MAT)){ct.v=-1;ct=move(ct);ct.v=0;} 
              return ct;
            }
        }
      }
    }
    if (ct.y==4){ct.v=0;PAR[i].timer+=1;}// timer when parked
    if(PAR[i].timer>=wait) // Existing the parking slot
    {
      if(ct.y<19&&ct.y>3)
      {
          PAR[i].boolean =1;
          ct.v=1; ct=turn(ct,"E"); 
          if(checkcolision(ct,MAT)){ct.v=1;ct=turn(ct,"E"); ct=move(ct);}
          if(!checkcolision(ct,MAT)){ct=turn(ct,"E"); ct.v=-2;ct=move(ct);ct.v=0;return ct;}  
      }
        if(ct.y==19&&strcmp(ct.dir,"E")==0&&ct.x!=39)
        {
          ct=turn(ct,"S");
          if(checkcolision(ct,MAT))
          {
            ct=turn(ct,"S");ct.v=1;ct=move(ct);
            PAR[i].timer=0;PAR[i].boolean=0;
          }
            if(!checkcolision(ct,MAT)){ct.v=0;}
        }
        if(ct.y==19&&strcmp(ct.dir,"E")==0&&ct.x==39)
        {
          ct=turn(ct,"E");
          if(checkcolision(ct,MAT))
          {
            ct=turn(ct,"E");ct.v=1;
            ct=move(ct);ct=move(ct);
            PAR[i].timer=0;PAR[i].boolean=0;
          }
          if(!checkcolision(ct,MAT)){ct.v=0;}
        }
      return ct;
    }
  }
  return ct;
}
car parking_Right_A(car ct,int MAT[42][153],parking PAR[54])
{
  int i=-1;
  if(ct.x==11){i=10;}
  if(ct.x==15){i=11;}
  if(ct.x==19){i=12;}
  if(ct.x==23){i=13;}
  if(ct.x==27){i=14;}
  if(ct.x==31){i=15;}
  if(i==-1){return ct;}
  else
  {
    if(PAR[i].timer==0)
    {
      if(ct.y>19&&ct.y<30)
      {
        for(int i =0;i<6;i++)
        {
          if(ct.x==11+i*4)
            {
              ct=turn(ct,"E");
              if(checkcolision(ct,MAT)){ct=turn(ct,"E");ct.v=1;ct=move(ct);}
              if(!checkcolision(ct,MAT)){ct=turn(ct,"E");ct.v=-1;ct=move(ct);ct.v=0;} 
              return ct;
            }
        }
      }
    }
    if (ct.y==30&&i!=-1){ct.v=0;PAR[i].timer+=1;}
    if(PAR[i].timer==wait)
    {
      for (int j=0;j<6;j++)
      {
        if(ct.x==11+4*j)
        {
          if(ct.y>19&&ct.y<31)
          {
            ct.v=1; ct=turn(ct,"W"); 
            if(checkcolision(ct,MAT)){ct.v=1;ct=turn(ct,"W"); ct=move(ct);}
            if(!checkcolision(ct,MAT)){ct=turn(ct,"W");ct.v=-1;ct=move(ct);ct.v=0;}    
          }
        }
        if(ct.y==19&&strcmp(ct.dir,"W")==0&&ct.x!=39)
        {

          ct=turn(ct,"S");
          if(checkcolision(ct,MAT))
          {
            ct=turn(ct,"S");ct.v=1;ct=move(ct);
            PAR[i].timer=0;PAR[i].boolean=0;
          }
          if(!checkcolision(ct,MAT)){ct.v=0;}
        }
      }
      return ct;
    }
  }
  return ct;
}

/*---- The idea for moving around the parking is the same for every corridor function , only position change-----*/
car CorridorA(car ct,int MAT[42][153],parking PAR[54])
{
  if (ct.y==19)// check for the position and if the car is in this corridor
  {
    for (int i=0; i<10;i++)
    {
      if (ct.x==3 +4*i)// checking for every left lot in A
      {
        if(PAR[i].boolean==0&&ct.exiting==0)// Check if parking lot is available 
        {
          ct.exiting=1;
          ct.v=1;
          PAR[i].boolean=1;
          ct=turn(ct,"W");
          ct=move(ct);
          return ct;
        }
      }
    }
    for(int i = 0 ; i < 6; i++)
    {
      if (ct.x==11 +4*i)// checking for every right lot in A
      {
        if(PAR[i+10].boolean==0&&ct.exiting==0)// Check if parking lot is available 
        {
          ct.exiting=1;
          ct=turn(ct,"E");
          if(checkcolision(ct,MAT))
          {
            PAR[i+10].boolean=1;
            ct=turn(ct,"E");
            ct=move(ct);
            return ct;  
          }
        }
      }
    }
    if (ct.x==39&&ct.y==19){ct=turn(ct,"E");ct.v=1;ct=move(ct);return ct;}//Exiting this corridor
    if(ct.x>=3 && ct.x<39)// moving around this corridor
    { 
      if(checkcolision(ct,MAT)){ct.v=1;ct=turn(ct,"S");ct=move(ct);}
      return ct;
    }
  }
  return ct;
}
car parking_Left_D(car ct,int MAT[42][153],parking PAR[54])
{
  int i=-1;
  if(ct.x==11){i=38;}
  if(ct.x==15){i=39;}
  if(ct.x==19){i=40;}
  if(ct.x==23){i=41;}
  if(ct.x==27){i=42;}
  if(ct.x==31){i=43;}
  if(ct.x==35){i=44;}
  if(i==-1){return ct;}
  else
  {
    if(PAR[i].timer==0)
    {
      if(ct.y<136&&ct.y>118)
      {
        PAR[i].boolean=1;
        for(int i =0;i<6;i++)
        {
          if(ct.x==11+i*4)
            {
              ct=turn(ct,"W");
              if(checkcolision(ct,MAT)){ct=turn(ct,"W");ct.v=1;ct=move(ct);}
              if(!checkcolision(ct,MAT)){ct.v=-1;ct=move(ct);ct.v=0;} 
              return ct;
            }
        }
      }
    }
    if (ct.y==118){ct.v=0;PAR[i].timer+=1;}
    if(PAR[i].timer>=wait)
    {
      if(ct.y<136&&ct.y>117)
      {
          PAR[i].boolean =1;
          ct.v=1; ct=turn(ct,"E"); 
          if(checkcolision(ct,MAT)){ct.v=1;ct=turn(ct,"E"); ct=move(ct);}
          if(!checkcolision(ct,MAT)){ct=turn(ct,"E"); ct.v=-1;ct=move(ct);ct.v=0;return ct;}  
      }
        if(ct.y==136&&strcmp(ct.dir,"E")==0)
        {
          ct=turn(ct,"N");
          if(checkcolision(ct,MAT))
          {
            ct=turn(ct,"N");ct.v=1;ct=move(ct);
            PAR[i].timer=0;PAR[i].boolean=0;
          }
            if(!checkcolision(ct,MAT)){ct.v=0;}
        }
      return ct;
    }
  }
  return ct;
}
car parking_Right_D(car ct,int MAT[42][153],parking PAR[54])
{
  int i=-1;
  if(ct.x==3){i=44;}
  if(ct.x==7){i=45;}
  if(ct.x==11){i=46;}
  if(ct.x==15){i=47;}
  if(ct.x==19){i=48;}
  if(ct.x==23){i=49;}
  if(ct.x==27){i=50;}
  if(ct.x==31){i=51;}
  if(ct.x==35){i=52;}
  if(ct.x==39){i=53;}
  if(i==-1){return ct;}
  else
  {
    if(PAR[i].timer==0)
    {
      if(ct.y>136&&ct.y<146)
      {
        PAR[i].boolean=1;
        for(int i =0;i<10;i++)
        {
          if(ct.x==3+i*4)
          {
            ct=turn(ct,"E");
            if(checkcolision(ct,MAT)){ct=turn(ct,"E");ct.v=1;ct=move(ct);}
            if(!checkcolision(ct,MAT)){ct.v=-1;ct=move(ct);ct.v=0;} 
            return ct;
          }
        }
      }
    }
    if (ct.y==146){ct.v=0;PAR[i].timer+=1;}
    if(PAR[i].timer>=wait)
    {
      if(ct.y>136&&ct.y<149)
      {
          PAR[i].boolean =1;
          ct.v=1; ct=turn(ct,"W"); 
          if(checkcolision(ct,MAT)){ct.v=1;ct=turn(ct,"W"); ct=move(ct);}
          if(!checkcolision(ct,MAT)){ct=turn(ct,"W"); ct.v=-2;ct=move(ct);ct.v=0;return ct;}  
      }
        if(ct.y==136&&strcmp(ct.dir,"W")==0&&ct.x!=3)
        {
          ct.v=1;
          ct=turn(ct,"N");ct=move(ct);
          if(checkcolision(ct,MAT))
          {
            ct=turn(ct,"N");ct.v=1;ct=move(ct);
            PAR[i].timer=0;PAR[i].boolean=0;
          }
          if(!checkcolision(ct,MAT)){ct.v=0;}
        }
        if(ct.y==136&&strcmp(ct.dir,"W")==0&&ct.x==3)
        {
          ct=turn(ct,"W");
          if(checkcolision(ct,MAT))
          {
            ct=turn(ct,"W");ct.v=1;
            ct=move(ct);
            PAR[i].timer=0;PAR[i].boolean=0;
          }
          if(!checkcolision(ct,MAT)){ct.v=0;}
        }
      return ct;
    }
  }
  return ct;
}
car CorridorD(car ct,int MAT[42][153],parking PAR[54])
{
  if (ct.y==136)
  {
    for (int i=0; i<10;i++)
    {
      if (ct.x==3 +4*i)
      {
        if(PAR[i+44].boolean==0&&ct.exiting==0)
        {
          PAR[i+44].boolean=1;ct.exiting=1;
          ct=turn(ct,"E");
          ct=move(ct);
          return ct;
        }
      }
    }
    for(int i = 0 ; i < 6; i++)
    {
      if (ct.x==11 +4*i)
      {
        if(PAR[i+38].boolean==0&&ct.exiting==0)  
        {
          PAR[i+38].boolean=1;ct.exiting=1;
          ct=turn(ct,"W");
          ct=move(ct);
          return ct;  
        }
      }
    }
    if(ct.x>3 && ct.x<=39)
    {ct.v=1;
        if(checkcolision(ct,MAT))
        {
          ct=turn(ct,"N");
          ct=move(ct);
          return ct;
        }
    }if(ct.x==3&&ct.y==136){ct.v=1;ct=turn(ct,"W");ct=move(ct);}
  }
  return ct;
}
car parkingB1(car ct,int MAT[42][153],parking PAR[54])
{
  int i=-1;
  if(ct.x==11){i=16;}
  if(ct.x==15){i=17;}
  if(ct.x==19){i=18;}
  if(ct.x==23){i=19;}
  if(ct.x==27){i=20;}
  if(ct.x==31){i=21;}
  if(i==-1){return ct;}
  else
  {
    if(PAR[i].timer==0)
    {
      if(ct.y<49&&ct.y>41)
      {
        for(int i =0;i<6;i++)
        {
          if(ct.x==11+i*4)
            {
              ct=turn(ct,"W");
              if(checkcolision(ct,MAT)){ct=turn(ct,"W");ct.v=1;ct=move(ct);}
              if(!checkcolision(ct,MAT)){ct=turn(ct,"W");ct.v=-1;ct=move(ct);ct.v=0;} 
              return ct;
            }
        }
      }
    }
    if (ct.y==41&&i!=-1){ct.v=0;PAR[i].timer+=1;}
    if(PAR[i].timer>=wait)
    {
      for (int j=0;j<6;j++)
      {
        if(ct.x==11+4*j)
        {
          if(ct.y<49&&ct.y>39)
          {
            ct.v=1; ct=turn(ct,"E"); 
            if(checkcolision(ct,MAT)){ct.v=1;ct=turn(ct,"E"); ct=move(ct);}
            if(!checkcolision(ct,MAT)){ct=turn(ct,"E");ct.v=-1;ct=move(ct);ct.v=0;}
          }
        }
        if(ct.y==49&&strcmp(ct.dir,"E")==0&&ct.x!=11)
        {
          PAR[i].boolean=0;
          PAR[i].timer=0;
          ct=turn(ct,"N");
          ct=move(ct);
        }
        if(ct.y==49&&strcmp(ct.dir,"E")==0&&ct.x==11)
        {
          PAR[i].boolean=0;
          PAR[i].timer=0;
          ct=turn(ct,"E");
          ct=move(ct);
        }
      }
      return ct;
    }
  }
return ct;
}
car CorridorB1(car ct,int MAT[42][153],parking PAR[54])
{
  if (ct.y==49 && ct.x>=11)
  {
    for (int i=0; i<6;i++)
    {
      if (ct.x==11 +4*i)
      {
        if(PAR[i+16].boolean==0&&ct.exiting==0)  
        {
          PAR[i+16].boolean=1;ct.exiting=1;
          ct=turn(ct,"W");
          ct=move(ct);
          return ct;  
        }
      }
    }
    if(ct.x>11 && ct.x<39)
    {
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"N");
        ct=move(ct);
        return ct;
      }
    }
  }
  if(ct.x==11&&ct.y==49){ct=turn(ct,"E");ct=move(ct);} 
  return ct;
}
car parkingC2(car ct,int MAT[42][153],parking PAR[54])
{
  int i=-1;
  if(ct.x==11){i=32;}
  if(ct.x==15){i=33;}
  if(ct.x==19){i=34;}
  if(ct.x==23){i=35;}
  if(ct.x==27){i=36;}
  if(ct.x==31){i=37;}
  if(i==-1){return ct;}
  else
  {
    if(PAR[i].timer==0)
    {
      if(ct.y<106&&ct.y>100)
      {
        for(int i =0;i<6;i++)
        {
          if(ct.x==11+i*4)
            {
              ct=turn(ct,"E");
              if(checkcolision(ct,MAT)){ct=turn(ct,"E");ct.v=1;ct=move(ct);}
              if(!checkcolision(ct,MAT)){ct=turn(ct,"E");ct.v=-2;ct=move(ct);ct.v=0;} 
              return ct;
            }
        }
      }
    }
    if (ct.y==106&&i!=-1){ct.v=0;PAR[i].timer+=1;}
    if(PAR[i].timer>=wait)
    {
      for (int j=0;j<6;j++)
      {
        if(ct.x==11+4*j)
        {
          if(ct.y<=107&&ct.y>100)
          {
            ct.v=1; ct=turn(ct,"W"); 
            if(checkcolision(ct,MAT)){ct.v=1;ct=turn(ct,"W"); ct=move(ct);}
            if(!checkcolision(ct,MAT)){ct=turn(ct,"W");ct.v=-1;ct=move(ct);ct.v=0;}
          }
        }
      }
      if(ct.y==100 &&strcmp(ct.dir,"W")==0)
      {
        ct=turn(ct,"S");
        ct=move(ct);
        PAR[i].boolean=0;
        PAR[i].timer=0;
      }
      return ct;
    }
  }
return ct;
}
car CorridorC2(car ct,int MAT[42][153],parking PAR[54])
{
  if (ct.y==100)
  {

    for (int i=0; i<6;i++)
    {
      if (ct.x==11 +4*i)
      {
        if(PAR[i+32].boolean==0&&ct.exiting==0)  
        {
          PAR[i+32].boolean=1;ct.exiting=1;
          ct=turn(ct,"E");
          ct=move(ct);
          return ct;  
        }
      }
    }
    if(ct.x==31)
    {
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"S");
        ct=move(ct);
        return ct;
      }
    }
    if(ct.x>=11 && ct.x<31)
    {  
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"S");
        ct=move(ct);
        return ct;
      }
    }
  }
  return ct;
}
car parkingB2(car ct,int MAT[42][153],parking PAR[54])
{
  int i=-1;
  if(ct.x==15){i=22;}
  if(ct.x==19){i=23;}
  if(ct.x==23){i=24;}
  if(ct.x==27){i=25;}
  if(ct.x==31){i=26;}
  if(i==-1){return ct;}
  else
  {
    if(PAR[i].timer==0)
    {
      if(ct.y>62&&ct.y<67)
      {
        for(int i =0;i<5;i++)
        {
          if(ct.x==15+i*4)
            {
              ct=turn(ct,"E");
              if(checkcolision(ct,MAT)){ct=turn(ct,"E");ct.v=1;ct=move(ct);}
              if(!checkcolision(ct,MAT)){ct=turn(ct,"E");ct.v=-1;ct=move(ct);ct.v=0;} 
              return ct;
            }
        }
      }
    }
    if (ct.y==67&&i!=-1){ct.v=0;PAR[i].timer+=1;}
    if(PAR[i].timer>=wait)
    {
      for (int j=0;j<6;j++)
      {
        if(ct.x==11+4*j)
        {
          if(ct.y>62&&ct.y<70)
          {
            ct.v=1; ct=turn(ct,"W"); 
            if(checkcolision(ct,MAT)){ct.v=1;ct=turn(ct,"W"); ct=move(ct);}
            if(!checkcolision(ct,MAT)){ct=turn(ct,"W");ct.v=-1;ct=move(ct);ct.v=0;}
          }
        }
        if(ct.y==62&&strcmp(ct.dir,"W")==0)
        {
          PAR[i].boolean=0;
          PAR[i].timer=0;
          ct=turn(ct,"S");
          ct=move(ct);
        }
      }
      return ct;
    }
  }
return ct;
}
car CorridorB2(car ct,int MAT[42][153],parking PAR[54])
{
  if (ct.y==62)
  {
    for (int i=0; i<=4;i++)
    {
      if (ct.x==15 +4*i)
      {
        if(PAR[i+22].boolean==0&&ct.exiting==0)  
        {
          PAR[i+22].boolean=1;ct.exiting=1;
          ct=turn(ct,"E");
          ct=move(ct);
          return ct;  
        }
      }
    }
    if(ct.x>=14 && ct.x<31)
    {
        if(checkcolision(ct,MAT))
        {
          ct=turn(ct,"S");
          ct=move(ct);
          return ct;
        }
    }
  }
  return ct;
}
car parkingC1(car ct,int MAT[42][153],parking PAR[54])
{
  int i=-1;
  if(ct.x==15){i=27;}
  if(ct.x==19){i=28;}
  if(ct.x==23){i=29;}
  if(ct.x==27){i=30;}
  if(ct.x==31){i=31;}
  if(i==-1){return ct;}
  else
  {
    if(PAR[i].timer==0)
    {
      if(ct.y>80&&ct.y<88)
      {
        for(int i =0;i<5;i++)
        {
          if(ct.x==15+i*4)
            {
              ct=turn(ct,"W");
              if(checkcolision(ct,MAT)){ct=turn(ct,"W");ct.v=1;ct=move(ct);}
              if(!checkcolision(ct,MAT)){ct=turn(ct,"W");ct.v=-1;ct=move(ct);ct.v=0;} 
              return ct;
            }
        }
      }
    }
    if (ct.y==80&&i!=-1){ct.v=0;PAR[i].timer+=1;}
    if(PAR[i].timer>=wait)
    {
      for (int j=0;j<6;j++)
      {
        if(ct.x==15+4*j)
        {
          if(ct.y>79&&ct.y<88)
          {
            ct.v=1; ct=turn(ct,"E"); 
            if(checkcolision(ct,MAT)){ct.v=1;ct=turn(ct,"E"); ct=move(ct);}
            if(!checkcolision(ct,MAT)){ct=turn(ct,"E");ct.v=-1;ct=move(ct);ct.v=0;}
          }
        }
        if(ct.y==88&&strcmp(ct.dir,"E")==0)
        {
          PAR[i].boolean=0;ct.exiting=1;
          PAR[i].timer=0;
          ct=turn(ct,"N");
          ct=move(ct);
        }
      }
      return ct;
    }
  }
return ct;
}
car CorridorC1(car ct,int MAT[42][153],parking PAR[54])
{
  if (ct.y==88)
  {
    for (int i=0; i<=4;i++)
    {
      if (ct.x==15 +4*i)
      {
        if(PAR[i+27].boolean==0&&ct.exiting==0)  
        {
          PAR[i+27].boolean=1;ct.exiting=1;
          ct=turn(ct,"W");
          ct=move(ct);
          return ct;  
        }
      }
    }
    if(ct.x>14 && ct.x<=31)
    {
        if(checkcolision(ct,MAT))
        {
          ct=turn(ct,"N");
          ct=move(ct);
          return ct;
        }
    }
    if(ct.x==15&&ct.y==88){ct=turn(ct,"N");ct=move(ct);} 
  }
  return ct;
}
//Travel Between ctorridor
car EnterToA(car ct,int MAT[42][153])
{ 
  if (ct.x==5&& ct.y<=65)
  {
    if(ct.y<=65 && ct.y>58)
    {
        if(checkcolision(ct,MAT))
        {
          ct=turn(ct,"W");
          ct=move(ct);
          return ct;
        }
    }
  }
  if (ct.x==3&& ct.y<=65)
  {
    if(ct.y<=58 && ct.y>19)
    {
      if(ct.y==19)
      {
        if(checkcolision(ct,MAT)){ct.v=1;ct=turn(ct,"W");ct=move(ct);}
        if(!checkcolision(ct,MAT)){ct.v=0;}
      } 
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"W");
        ct=move(ct);
        return ct;
      }
      return ct;
    }
  }
  if (ct.y==58 )
  {
    if(ct.x<=5 && ct.x>3)
    {
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"N");
        ct=move(ct);
        return ct;
      }
    }
  }
  return ct;
}
car AToB(car ct,int MAT[42][153])
{
  if (ct.x==39)
  {
    if(ct.y>19 && ct.y<49)
    {
      ct.v=1;
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"E");
        ct=move(ct);
        return ct;
      }
    }
  }
  if (ct.y==49&& ct.x>31)
  {
    if(checkcolision(ct,MAT))
    {
      ct=turn(ct,"N");
      ct=move(ct);
      return ct;
    }
  }
  return ct;
}
car BToct(car ct,int MAT[42][153])
{
  if (ct.y==62)
  {
    if (ct.x>=30 && ct.x<36)
    {
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"S");
        ct=move(ct);
        return ct;
      }
    }
  }
  if (ct.x==36)
  {
    if (ct.y>=62 && ct.y<88)
    {
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"E");
        ct=move(ct);
        return ct;
      }
    }
  }
  if(ct.y==88)
  {
    if(ct.x<=36 && ct.x>31)
    {
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"N");
        ct=move(ct);
        return ct;
      }
    }
  }
  return ct;
}
car B1ToB2(car ct,int MAT[42][153])
{
  if (ct.x==11 )
      {
        if (ct.y>49  && ct.y<62)
        {
          if(checkcolision(ct,MAT))
          {
            ct=turn(ct,"E");
            ct=move(ct);
            return ct;
          }
        }
      }
  if (ct.y==62 && ct.x>=11)
  {
    if( ct.x>=11 && ct.x<15)
    {
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"S");
        ct=move(ct);
        return ct;
      }
    }
  }
  return ct;
}
car C1ToC2(car ct,int MAT[42][153])
{
  if (ct.y==88 )
  {
    if( ct.x>11 && ct.x<15)
    {
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"N");
        ct=move(ct);
        return ct;
      }
    }
  }
  if (ct.x==11)
  {
    if (ct.y>=88  && ct.y<100)
    {
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"E");
        ct=move(ct);
        return ct;
      }
    }
  }
  return ct;
}

car CToD(car ct,int MAT[42][153]) 
{
  if (ct.y==100)
  {
    if (ct.x>31 && ct.x<39)
    {

      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"S");
        ct=move(ct);
        return ct;
      }
    }
  }
  if (ct.x==39)
  {
    if (ct.y>=100 && ct.y<136)
    {
      ct=turn(ct,"E");
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"E");
        ct=move(ct);
        return ct;
      }
    }
  }
  return ct;
}
car DToExit(car ct,int MAT[42][153])
{ 
  if (ct.x==3&& ct.y>=65)
  {
    if(ct.y<136 && ct.y>91)
    {ct=turn(ct,"W");
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"W");
        ct=move(ct);
        return ct;
      }
    }
  }
  if (ct.y==91 )
  {
    if(ct.x<5 && ct.x>=3)
    {
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"S");
        ct=move(ct);
        return ct;
      }
    }
  }
  if (ct.x==5 && ct.y>=65)
  {
    if(ct.y<=91 && ct.y>84)
    {
      if(checkcolision(ct,MAT))
      {
        ct=turn(ct,"W");
        ct=move(ct);
        return ct;
      }
    }
  }
  return ct;
}

List* Exitanddelete(car ct,List*L)// Delete a car from the linked list if it has already found a parking lot 
{
  if (ct.x==5 &&ct.y==84&&ct.exiting==1)// when at the exit door
  {
    deletecar(L);
  }
  ct.x=5;ct.y=65;
  return L;  
}
car ExitandRetry(car ct,List*L)
{
  if (ct.x==5 &&ct.y==84&&ct.exiting==0)
  {
    ct.x=5;
    ct.y=65;
    ct.exiting=0;
  }
  return ct;  
}
///
void initmatrice(int MAT[42][153])// Initialise the matrice , which mean set to one every wall of the parking
{
  memset(MAT, 0, sizeof(MAT[0][0]) * 42 * 153);
  for(int i=0;i<N;i++)
  {
    //cadre
    MAT[0][i]=1 ;
    MAT[41][i]=0 ;
  }
  for(int i=0;i<42;i++)
  {
    MAT[i][0]=1;
    MAT[i][N-1]=1;
    MAT[i][2]=1;
  }
  //entry 
  for(int i=1;i<5;i++)
  {
    MAT[i][63]=1 ;
    MAT[i][88]=1 ;
  }
  for(int i=1;i<12;i++)
  {
    MAT[i][70]=1;
    MAT[i][81]=1;
  }
  for(int i=70;i<82;i++)
  {
    MAT[11][i]=1;
  }
  //parking mid
  for(int i=8;i<33;i++)
  {
    MAT[i][36]= 1 ;
    MAT[i][38]= 1 ;
    MAT[i][39]= 1 ;     
    
    MAT[i][112]=1 ;
    MAT[i][113]=1 ;
    MAT[i][114]=1 ;
    MAT[i][116]=1 ;
  }
  //parking cent
  for(int i=13;i<33;i++)
  {
    MAT[i][73]=1;
    MAT[i][75]=1;
    MAT[i][76]=1;
    MAT[i][78]=1;
  }
}
void poswriting(car c,int MAT[42][153])
{
  if(strcmp(c.mdl,"car1/")==0) // car model  1
  {
  if(strcmp(c.dir,"N")==0||strcmp(c.dir,"S")==0)
    {//North and South directions
      for(int i=0;i<3;i++)
      {
        MAT[c.x+i][c.y]=1;
        MAT[c.x+i][c.y+1]=1;
        MAT[c.x+i][c.y+2]=1;
      }
    }
   if(strcmp(c.dir,"E")==0||strcmp(c.dir,"W")==0)
     {//East and West directions
       for(int i=0;i<5;i++)
       {         
        MAT[c.x][c.y+i]=1;
        MAT[c.x+1][c.y+i]=1;
       }
     }
  }
  if(strcmp(c.mdl,"car3/")==0)
  {
  if(strcmp(c.dir,"N")==0||strcmp(c.dir,"S")==0)
    {//North and South directions
      for(int i=0;i<3;i++)
      {
        MAT[c.x+i][c.y]=1;
      }
    }
   if(strcmp(c.dir,"E")==0||strcmp(c.dir,"W")==0)
     {//East and West directions
       for(int i=0;i<3;i++)
       {         
        MAT[c.x][c.y+i]=1;
       }
     }
  }
  if(strcmp(c.mdl,"car2/")==0)
  {
      for(int i=0;i<2;i++)
      {
        MAT[c.x][c.y+i]=1;
        MAT[c.x+1][c.y+i]=1;
      }
  }
}

bool checkcolision(car c,int MAT[42][153])// check if a collision would happend , it depend on the car model
{
  if(strcmp(c.mdl,"car1/")==0) // car model  1
  {
    if(strcmp(c.dir,"N")==0)//car looking in North direction
    {
      if(MAT[c.x-1][c.y]==1||MAT[c.x-1][c.y+2]==1)
      {
        return false;
      }
    }
    if(strcmp(c.dir,"S")==0)//car looking in South direction
    {
      if(MAT[c.x+3][c.y]==1||MAT[c.x+3][c.y+2]==1)
      {
        return false;
      }
    }
    if(strcmp(c.dir,"W")==0)//car looking in West direction
    {
      if(MAT[c.x][c.y-1]==1||MAT[c.x+1][c.y-1]==1)
      {
        return false;
      }
    }
    if(strcmp(c.dir,"E")==0)//car looking in East direction
    {
      if(MAT[c.x][c.y+5]==1||MAT[c.x+1][c.y+5]==1)
      {
        return false;
      }
    }
    return true;
  }
  if(strcmp(c.mdl,"car3/")==0)//  // car model 3
  {
    if(strcmp(c.dir,"N")==0)
    {
      if(MAT[c.x-1][c.y]==1)
      {
        return false;
      }
    }
    if(strcmp(c.dir,"S")==0)
    {
      if(MAT[c.x+3][c.y]==1)
      {
        return false;
      }
    }
    if(strcmp(c.dir,"W")==0)
    {
      if(MAT[c.x][c.y-1]==1||MAT[c.x+1][c.y-1]==1)
      {
        return false;
      }
    }
    if(strcmp(c.dir,"E")==0)
    {
      if(MAT[c.x][c.y+3]==1||MAT[c.x+1][c.y+3]==1)
      {
        return false;
      }
    }
    return true;
  }
  if(strcmp(c.mdl,"car2/")==0) // car model 2
  {
    if(strcmp(c.dir,"N")==0)
    {
      if(MAT[c.x-1][c.y]==1||MAT[c.x-1][c.y+2]==1)
      {
        return false;
      }
    }
    if(strcmp(c.dir,"S")==0)
    {
      if(MAT[c.x+2][c.y]==1||MAT[c.x+2][c.y+2]==1)
      {
        return false;
      }
    }
    if(strcmp(c.dir,"W")==0)
    {
      if(MAT[c.x][c.y-1]==1||MAT[c.x+1][c.y-1]==1)
      {
        return false;
      }
    }
    if(strcmp(c.dir,"E")==0)
    {
      if(MAT[c.x][c.y+3]==1||MAT[c.x+1][c.y+3]==1)
      {
        return false;
      }
    }
    return true;
  }
return true;
}
