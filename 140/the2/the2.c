#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the2.h"
double pow_(int number, int power){
  int sum=1;
  while(power){
    sum=sum*number;
    power--;
  }
  return sum;
}
node *init(int branch){
  node *head=malloc(sizeof(node));
  node *dummy=malloc(sizeof(node));
  head->key=1000*branch;
  head->down=dummy;
  dummy->down=NULL;
  dummy->next=NULL;
  dummy->key=0;

  return head;
}

void clear(node *list){
  node *alt,*sag,*temp;
  alt = list;
  sag=list;
  while(alt){
    sag=alt->next;
    while(sag){
      temp=sag;
      sag=sag->next;
      temp->next=NULL;
      temp->down=NULL;
      free(temp);
    }
    temp=alt;
    alt=alt->down;
    temp->next=NULL;
    temp->down=NULL;
    free(temp);
  }
}

int is_empty(node *list){
  if(list->down->next){
    return 0;
  }
  else{
    return 1;
  }
}
int num_levels(node *list){
  int i;
  node *alt;
  alt=list;
  for(i=0;alt!=NULL;i++){
    alt=alt->down;
  }
  return i-1;
}
int num_nodes(node *list){
  int i=0;
  node *alt, *sag;
  alt=list;
  while(alt->down){
      alt=alt->down;
  }
  sag=alt->next;
  while(sag){
    i++;
    sag=sag->next;
  }
  return i;
}


node* insert(node *list, int key, char *value){
  node *alt, *sag,*yedek,*retemp=NULL,*temp=NULL,*ilk=NULL,*onceki ,*newalt,*enalt, *newnode=NULL;
  int flag=1,N,B,insertion,i=0 ,levels,j;
  alt = list;
  while (alt){
    sag=alt->next;
    while(sag){
      if (sag->key ==key){
        flag=0;
        while(sag){
            i=0;
            for(j=0;j<5;j++) {(sag->value)[j]=0;}
            j=0;
            while(value[j]){
              (sag->value)[j] = value[j];
              j++;
            }
            retemp=sag;
            sag=sag->down;
            }
          return retemp;
          }
      sag=sag->next;
    }
    alt=alt->down;
  }

  if (flag){
    N=list->key%1000;
    B= list->key/1000;
    for(i=0;!((N+1)% (int)pow_(B,i)) ; i++);
    insertion=i-1;
    levels=num_levels(list);
    if(insertion>=levels){
      yedek=list->down;
      for(i=0;i<=insertion-levels;i++){
        newalt= malloc(sizeof(node));
        newnode = malloc(sizeof(node));
        newnode->next=NULL;
        newnode->down=NULL;
        newalt->next=NULL;
        newalt->down=NULL;
        newalt->down=list->down;
        list->down = newalt;
        newnode->key =key;
        for(j=0;j<5;j++) {(newnode->value)[j]=0;}
        j=0;
        while(value[j]){
          (newnode->value)[j]=value[j];
          j++;
        }
        newalt->next = newnode;
        newnode->down=temp;
        temp=newnode;
        if(i==0){
          ilk = temp;
        }
      }
    while(yedek){
      sag=yedek->next;
      onceki=yedek;
        while(sag && ((sag->key) < key)){
          onceki=sag;
          sag=sag->next;
        }
        if(!sag){
          newnode = malloc(sizeof(node));
          newnode->down=NULL;
          newnode->next=NULL;
          newnode->key=key;
          for(j=0;j<5;j++) {(newnode->value)[j]=0;}
          j=0;
          while(value[j]){
            (newnode->value)[j]=value[j];
            j++;
          }
          onceki->next=newnode;
          newnode->next=NULL;
          if(ilk)ilk->down=newnode;
          ilk=newnode;
          newnode->down=NULL;
        }
        else{
        newnode = malloc(sizeof(node));
        newnode->next=NULL;
        newnode->key=key;
        for(j=0;j<5;j++) {(newnode->value)[j]=0;}
        j=0;
        while(value[j]){
          (newnode->value)[j]=value[j];
          j++;
        }
        newnode->next=sag;
        onceki->next=newnode;
        if(ilk)ilk->down =newnode;
        ilk=newnode;
        newnode->down=NULL;
        }
      yedek=yedek->down;
    }
  }
    else{
      alt=list;
      for(i=0;i<(levels-insertion);i++){
          alt=alt->down;
      }
      while(alt){
        sag=alt->next;
        onceki=alt;
        while(sag && ((sag->key)<key)){
          onceki=sag;
          sag=sag->next;
        }
        if(!sag){
            newnode= malloc(sizeof(node));
            newnode->down=NULL;
            newnode->key=key;
            for(j=0;j<5;j++) {(newnode->value)[j]=0;}
            j=0;
           while(value[j]){
              (newnode->value)[j]=value[j];
              j++;
            }
            onceki->next=newnode;
            newnode->next=NULL;

            if(ilk)ilk->down=newnode;

            ilk=newnode;

        }

        else{

            newnode=malloc(sizeof(node));
            newnode->next=NULL;
            newnode->key=key;
            for(j=0;j<5;j++) {(newnode->value)[j]=0;}
            j=0;
            while(value[j]){
              (newnode->value)[j]=value[j];
              j++;
            }
            onceki->next=newnode;
            newnode->next=sag;
            if(ilk)ilk->down=newnode;
            ilk=newnode;
            newnode->down=NULL;
        }


        alt=alt->down;
      }
    }
  }

  if(flag){
    list->key +=1;
  }
  enalt=list->down;
  levels=num_levels(list);
  while(enalt){
    enalt->key=-(levels-1);
    levels--;
    enalt=enalt->down;
  }

  return ilk;
}
int delete(node *list,int key){
  node *alt,*sag ,*temp;
  int flag=0;
  alt=list;
  while(alt){
    sag=alt->next;
    temp=alt;
    while(sag){
      if (sag->key==key){
        temp->next=sag->next;
        sag->down=NULL;
        sag->next=NULL;
        free(sag);
        flag=1;
        break;
      }
      else{
        temp=sag;
        sag=sag->next;
      }
    }
    alt=alt->down;
  }
  alt=list->down;
  while(alt->down){
    temp=alt->down;
    if(!(alt->next)){
      free(alt);
      alt=temp;
      list->down=alt;
    }
    else{
      break;
    }
  }
    list->key -=flag;
  return flag;
}

void print(node *list){
  int i,level,count=0;
  node *alt,*enalt,*sag1,*sag2;
  level=num_levels(list);
  printf("%3d      ",list->key%1000);
  for(i=0;i<level;i++){
    printf(" %d",i);
  }
  printf("\n");
  printf("         ");
  for(i=0;i<level+1;i++){
    if(i==level){
      printf(" -\n");
    }
    else{
      printf(" +");
    }
  }
  enalt=list;
  alt=list;
  while(enalt->down){
    enalt=enalt->down;
  }
  sag1=enalt->next;
  while(sag1){
    printf("%3d:",sag1->key);
    printf("%5s",sag1->value);
    alt=list;
    count=0;
    while(alt){
      sag2=alt->next;
      while(sag2){
        if (sag2->key==sag1->key){
          count++;
          sag2=sag2->down;
          while(sag2){
            sag2=sag2->down;
            count++;
          }
          break;
        }
        if((sag2->key)> (sag1->key) ){
          break;
        }
        sag2=sag2->next;
      }
      if(count){
        break;
      }
      alt=alt->down;
    }
    for(i=0;i<count;i++){
    printf(" +");
  }
  printf("\n");
  sag1=sag1->next;
  }
}

void print_level(node *list,int level){
node *up,*alt,*sagalt,*sagup;
  alt=list;
  up=alt;
  while(!(alt->key==(-level))){
    up=alt;
    alt=alt->down;
  }
  sagalt=alt;
  sagup=up->next;
  if(up!=list){


  while(sagup){
    while(sagalt->key!=sagup->key){
      printf("             ");
      sagalt=sagalt->next;
    }
    printf("%3d:%5s -> ",sagup->key,sagup->value);
    sagup=sagup->next;
    sagalt=sagalt->next;
  }
  printf("\n");

  sagalt=alt;
  sagup=up->next;
  while(sagup){
    while(sagalt->key != sagup->key){
      printf("             ");
      sagalt=sagalt->next;
    }
    printf("   |         ");
    sagup=sagup->next;
    sagalt=sagalt->next;
  }
  printf("\n");
}
  sagalt=alt;
  while(sagalt){
    printf("%3d:%5s -> ",sagalt->key,sagalt->value);
    sagalt=sagalt->next;
  }
  printf("\n");

}


node *find(node *list,int key){
  node *alt,*sag;
  alt=list;
  while(alt){
    sag=alt;
    while(sag){
      if(sag->key == key){
        return sag;
      }
      else if ((sag->key<key) && ( (sag->next == NULL) || (sag->next->key > key) ) ){
        alt=sag;
        break;
      }
      sag=sag->next;
    }
    alt=alt->down;
  }

  return NULL;
}

void path(node *list,int key){
  node *alt,*sag;
  printf("%d v ",list->key);
  alt=list->down;
  while(alt){
    sag=alt;
    while(sag){
      if(sag->key == key){
        printf("%3d:%5s\n",sag->key,sag->value);
        return;
      }
      else if ((sag->key<key) && ( (sag->next == NULL) || ((sag->next->key) > key) ) ){
        alt=sag;
        break;
      }
      printf("%3d > ",sag->key);
      sag=sag->next;
    }
    printf("%3d v ",alt->key);
    alt=alt->down;
  }

}
