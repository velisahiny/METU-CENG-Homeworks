#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
void print(char a[],int length){
         int i;
         for (i=0;i<length; i++){
            printf("%c",a[i]);
        }
        printf("\n");
    }
void printfl(float a[],int length){
         int i;
         for (i=0;i<length; i++){
            printf("%f ",a[i]);
        }
        printf("\n");
    }
void printint(int a[],int length){
       int i;
         for (i=0;i<length; i++){
            printf("%d ",a[i]);
        }
        printf("\n");
    }
double evaluate(char postfix[] , int length, double values[]){

  int i,j=0,onda;
  char a;
  double depo[200],sayi=0;

 for(i=0;i<length;i++){

    sayi=0;
    if (postfix[i]>47 && postfix[i]<58){ /* 0-9*/
      while (postfix[i]!='f' && postfix[i]!='i'){
      sayi = (sayi)*10 + (postfix[i]-48);
      i++;
      if (postfix[i]=='.'){
        onda =1;
        i++;
        while(postfix[i]!='f'){
          sayi = sayi +(double)(postfix[i]-48)/pow(10,onda);
          onda++;
          i++;
              }
      }
      }

        depo[j]=sayi;
        j++;
        /*i++;*/
    }
    else if(postfix[i]>64 && postfix[i] < 91){ /* A-Z*/
        depo[j]=values[postfix[i]-65];
        j++;
        continue;
    }
    else if(postfix[i]=='*' || postfix[i]=='-' || postfix[i]=='+' || postfix[i]=='/' || postfix[i]=='^')
    {
      a=postfix[i];
      switch (a) {
        case '*':
          sayi=depo[j-1]*depo[j-2];
          depo[j-2]=sayi;
          j--;
          break;
        case '+':
          sayi=depo[j-1]+depo[j-2];
          depo[j-2]=sayi;
          j--;
          break;
        case '-':
          sayi=depo[j-2]-depo[j-1];
          depo[j-2]=sayi;
          j--;
          break;
        case '/':
          sayi=depo[j-2]/depo[j-1];
          depo[j-2]=sayi;
          j--;
          break;
        case '^':
          sayi=pow(depo[j-2],depo[j-1]);
          depo[j-2]=sayi;
          j--;
          break;
      }
      continue;

    }
    else if(postfix[i]=='q' || postfix[i]=='s' || postfix[i]=='l' || postfix[i]=='k' || postfix[i]=='~'){/* sin =s cos =k ln =l sqrt = q*/
      a=postfix[i];
      switch (a) {
        case 'q':
          sayi = pow(depo[j-1],0.5);
          depo[j-1]= sayi;
          break;
        case 's':
          sayi = sin(depo[j-1]);
          depo[j-1]=sayi;
          break;
        case 'l':
          sayi = log(depo[j-1]);
          depo[j-1]= sayi;
          break;
        case 'k':
          sayi=cos(depo[j-1]);
          depo[j-1]= sayi;
          break;
        case '~':
          sayi = -depo[j-1];
          depo[j-1] = sayi;
          break;
      }
      continue;
    }
  }
return depo[j-1];
}
int main(){
  double ustsinir,ust,altsinir,alt,minmax,rvalue,r,values[26],deger,min=LONG_MAX,max=LONG_MIN;
  /*char test[]={'A','B','2','i','^','+','q','5','i','C','+','l','+'};*/
  int y,a=0,i=0,j=0,k=0,t,d,s=0,q=0,l=0,m,harfsayisi=0,girdisayisi,h,z,harfindex, *output,index,o;
  float ara1,ara2,ihtimal,girdiler[26][200];
  long int denemesayisi,x;
  char f,formula[201],que[200],stack[200],formula2[201],c,harf,harfler[26];
  while (f != '\n'){
    f = getchar();
    if (f>64&&f<91){
      for(d=0;d<l;d++){
        if (f == harfler[d]){
          break;
        }
        }
      if (d==l){
        harfler[l]= f;
        harfsayisi++;
        l++;

      }
    }

    if  (f !=' ' && f!='\n'){
      formula[i]=f;
      i++;
}
}
/*Inputs */
scanf("%d %ld",&girdisayisi,&denemesayisi);
for(h=0;h < harfsayisi;h++){
    scanf(" %c %f %f",&harf,&ara1,&ara2);
    girdiler[harf-65][0]=ara1,girdiler[harf-65][1]=ara2;
    for(a=0;a<girdisayisi;a++){
    scanf(" %f",&ihtimal);
    girdiler[harf-65][a+2]=ihtimal;
}
}
output = (int*) calloc(girdisayisi,sizeof(int));

for(j=0;j<i;j++){
  if(formula[j]=='s'){
      char a;
      a=formula[j+1];
      if (a=='q'){
        formula2[k]='q';
        j+=3;
        }
      else if (a=='i'){
        formula2[k]='s';
        j+=2;
    }
  }
  else if (formula[j]=='c') {
      formula2[k]='k';
      j+=2;
    }
  else if(formula[j]=='l'){
      formula2[k]='l';
      j++;
    }
  else{
    formula2[k]=formula[j];
  }
  k++;
  }
/*  print(formula2,k);*/
for(t=0;t<=k;t++){
  if(t==k){
    for(m=0;m<s;m++){
      que[q]=stack[s-m-1];

      q++;
    }
    break;
  }
  c=formula2[t];
  if ((c>47 && c<58) || c == '.' || (c>64 && c<91)){ /* 0-9 . A-Z*/
    int w;
    w=t;
    if ((c>47 && c<58) || c == '.' ){
      while (formula2[w]>47 && formula2[w]<58){
          w++;
        }
        if (formula2[w]=='.'){
          w++;
          while ((formula2[t]>47 && formula2[t]<58) || formula2[t]=='.'){
            que[q]=formula2[t];
            t++;
            q++;
          }
          que[q]='f';
          t--;
          q++;
        }
        else {
          while (formula2[t]>47 && formula2[t]<58 ){
            que[q]=formula2[t];
            t++;
            q++;
          }
          que[q]='i';
          q++;
          t--;
              }
}
else{
  que[q]=c;
  q++;
}
    continue;
  }
  else if(c=='q'|| c=='s' || c=='k' || c=='l'||c == '~'){
  stack[s]=c;
  s++;
  continue;
}
  else if(c == '*'|| c == '+' || c == '-' || c == '/' || c == '^'){
  while (stack[s-1]=='*'||stack[s-1]=='+'||stack[s-1]=='-'||stack[s-1]=='/'||stack[s-1]=='^'||stack[s-1]=='s'||stack[s-1]=='q'||stack[s-1]=='k'||stack[s-1]=='l'||stack[s-1]=='~'){
    if( (c == '+' || c == '-' )&& (stack[s-1]=='+'||stack[s-1]=='-'||stack[s-1]=='*'||stack[s-1]=='/'||stack[s-1]=='^')){
      que[q]=stack[s-1];
      s--;
      q++;
      continue;
    }
    else if((c == '*' || c == '/')&& (stack[s-1]=='*'||stack[s-1]=='/'||stack[s-1]=='^')){
      que[q]=stack[s-1];
      s--;
      q++;
      continue;
    }
    break;
    }
    stack[s]=c;
    s++;
    continue;
  }
  else if(c=='('){
    stack[s]=c;
    s++;
    continue;
  }
  else if(c ==')'){

      while(stack[s-1]!='('){
        que[q]=stack[s-1];
        s--;
        q++;
      }
      s--;

      if (stack[s-1]=='s'||stack[s-1]=='q'||stack[s-1]=='k'||stack[s-1]=='l'||stack[s-1]=='~'){
        que[q]=stack[s-1];
        s--;
        q++;
      }
      continue;
    }

}

/*printfl(girdiler[1],girdisayisi+2);*/
/*flev = evaluate(que,q,variables);
printf("%f",flev);*/
for(z=0;z<h;z++){ /*harfler kadar dönsün*/
  for(y=0;y<girdisayisi;y++){
    girdiler[harfler[z]-65][y+3]+= girdiler[harfler[z]-65][y+2];
  }
}
srand(time(NULL));

for(x=0;x<denemesayisi;x++){

  for(z=0;z<h;z++){
    i=2;
    harfindex = harfler[z]-65;
    altsinir=0;
    ustsinir =girdiler[harfindex][girdisayisi+1];
    r =((double)rand()/(double)RAND_MAX)* ustsinir + altsinir; /* aralık icin random*/
    while (r>girdiler[harfindex][i]){
      i++;
    }

    ust =(i-1)*(girdiler[harfindex][1]-girdiler[harfindex][0])/girdisayisi+girdiler[harfindex][0];


    alt= ust - (girdiler[harfindex][1]-girdiler[harfindex][0])/girdisayisi;
    rvalue=((double)rand()/(double)RAND_MAX)*(ust-alt) + alt; /* deger icin random*/
    values[harfindex]=rvalue;

  }
  minmax = evaluate(que,q,values);
  if (minmax > max){
    max = minmax;
  }
 if (minmax <min) {
    min = minmax;
  }
}
for(x=0;x<denemesayisi;x++){

  for(z=0;z<h;z++){
    i=2;
    harfindex = harfler[z]-65;
    altsinir=0;
    ustsinir =girdiler[harfindex][girdisayisi+1];
    r =((double)rand()/(double)RAND_MAX)* ustsinir + altsinir;
    while (r>girdiler[harfindex][i]){
      i++;
    }

    ust =(i-1)*(girdiler[harfindex][1]-girdiler[harfindex][0])/girdisayisi+girdiler[harfindex][0];


    alt= ust - (girdiler[harfindex][1]-girdiler[harfindex][0])/girdisayisi;
    rvalue=((double)rand()/(double)RAND_MAX)*(ust-alt) + alt;
    values[harfindex]=rvalue;
  }
  index =0;
  deger = evaluate(que,q,values);
  while(deger>(max-min)/girdisayisi*(index+1)+min){
    index++;
  }

  output[index]++;
  }
/*printf("\noutput :");
printint(output,girdisayisi);*/
printf("%f",min );
printf(" %f",max );
/*printf("output/deneme:  ")*/
for(o=0;o<girdisayisi;o++){
  printf(" %f",(double)output[o]/denemesayisi);
}


/*printf("%ld",denemesayisi);*/
return 0;
}
