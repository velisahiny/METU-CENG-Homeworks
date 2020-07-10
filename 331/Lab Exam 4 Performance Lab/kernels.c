/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/* 
 * Please fill in the following student struct 
 */
team_t team = {
    "2172179",              /* Student ID */

    "Veli Şahin Yıldırım",     /* full name */
    "velisahiny@gmail.com",  /* email address */

    "",                   /* leave blank */
    ""                    /* leave blank */
};


/***************
 * Sobel KERNEL
 ***************/

/******************************************************
 * Your different versions of the sobel functions  go here
 ******************************************************/
char mysobel_descr[] = "mysobel: ";
void mysobel(int dim,int *src,int *dst){
    int i,j,count,i_dim,ker,c,offset;
    int kernel[3][3] = {{-1, 0, 1}, 
                     {-2, 0, 2}, 
                     {-1, 0, 1}};
   for(i=0;i<dim;i++){
        i_dim=i*dim;
        for(j=0;j<dim;j++){
            dst[i_dim+j]=0;
           
        }
       
    }
    
    count=dim-2;
    for(ker=0;ker<3;ker++){
        c=0;
        for(i = ker; c < count ; c++){
            i_dim = i*dim;
            for(j = 0; j < dim-2; j++) {
                offset=(-ker+1)*dim;
                     dst[i_dim+offset+j+1]+=kernel[ker][0]*src[i_dim+j]
                                    +kernel[ker][1]*src[i_dim+j+1]
                                    +kernel[ker][2]*src[i_dim+j+2];
            }
            i++;
        }
    }
}
char newsobel_descr[] = "newsobel: ";
void newsobel(int dim,int *src,int *dst){
    int i,j,i_dim,var;

  
  for(j=0;j<dim;j++){
      dst[0+j]=0;
      dst[(dim-1)*dim+j]=0;
  }
     i_dim = 0;
        for(i = 0; i < dim ; i++){
            for(j = 0; j < dim-2; j++) {
              /*  
                if(i==0||i==dim-1||j==0){
                    dst[i_dim+j]=0;
                    if(j==dim-3 && j!=0){
                        dst[i_dim+j+1]=0;
                    }
                }
                if(j==dim-3){
                        dst[i_dim+j+2]=0;
                }
             */
                if(j==0){
                     dst[i_dim+j]=0;
                }
                if(j==dim-3){
                    dst[i_dim+j+2]=0;
                }
                var =src[i_dim+j+2]-src[i_dim+j];
                if(i>=0 && i<=dim-3){
                    dst[i_dim+dim+j+1]=var;
                }
                if(i>=1 && i<=dim-2){
                    dst[i_dim+j+1]+=var<<1;
                }
                if(i>=2 && i<=dim-1){
                    dst[i_dim-dim+j+1]+=var;
                }
            }
            i_dim+=dim;
            
        }
    }
char unrollsobel_descr[] = "unrollsobel: ";
void unrollsobel(int dim,int *src,int *dst){
    int i,j,i_dim,offset,var1,var2,var3,var4,var5,var6,var7,var8,var9,var10,var11,var12,var13,var14,var15,var16;

    i_dim = 0;
    for(i=0;i<dim;i++){
      for(j=0;j<dim;j++){
          dst[i_dim+j]=0;
        }
        i_dim+=dim;
    }
  
     i_dim = 0;
        for(i = 0; i < dim ; i++){
            for(j = 0; j < dim-2-15; j+=16) {
                offset=i_dim+j;
                
                var1 =src[offset+2]-src[offset];
                var2=src[offset+3]-src[offset+1];
                var3=src[offset+4]-src[offset+2];
                var4=src[offset+5]-src[offset+3];
                var5 =src[offset+6]-src[offset+4];
                var6=src[offset+7]-src[offset+5];
                var7=src[offset+8]-src[offset+6];
                var8=src[offset+9]-src[offset+7];
                var9 =src[offset+10]-src[offset+8];
                var10=src[offset+11]-src[offset+9];
                var11=src[offset+12]-src[offset+10];
                var12=src[offset+13]-src[offset+11];
                var13 =src[offset+14]-src[offset+12];
                var14=src[offset+15]-src[offset+13];
                var15=src[offset+16]-src[offset+14];
                var16=src[offset+17]-src[offset+15];
                if(i>=0 && i<=dim-3){
                    dst[offset+dim+1]=var1;
                    dst[offset+dim+2]=var2;
                    dst[offset+dim+3]=var3;
                    dst[offset+dim+4]=var4;
                    dst[offset+dim+5]=var5;
                    dst[offset+dim+6]=var6;
                    dst[offset+dim+7]=var7;
                    dst[offset+dim+8]=var8;
                    dst[offset+dim+9]=var9;
                    dst[offset+dim+10]=var10;
                    dst[offset+dim+11]=var11;
                    dst[offset+dim+12]=var12;
                    dst[offset+dim+13]=var13;
                    dst[offset+dim+14]=var14;
                    dst[offset+dim+15]=var15;
                    dst[offset+dim+16]=var16;
                }
                if(i>=1 && i<=dim-2){
                    dst[offset+1]+=var1<<1;
                    dst[offset+2]+=var2<<1;
                    dst[offset+3]+=var3<<1;
                    dst[offset+4]+=var4<<1;
                    dst[offset+5]+=var5<<1;
                    dst[offset+6]+=var6<<1;
                    dst[offset+7]+=var7<<1;
                    dst[offset+8]+=var8<<1;
                    dst[offset+9]+=var9<<1;
                    dst[offset+10]+=var10<<1;
                    dst[offset+11]+=var11<<1;
                    dst[offset+12]+=var12<<1;
                    dst[offset+13]+=var13<<1;
                    dst[offset+14]+=var14<<1;
                    dst[offset+15]+=var15<<1;
                    dst[offset+16]+=var16<<1;
                }
                if(i>=2 && i<=dim-1){
                    dst[offset-dim+1]+=var1;
                    dst[offset-dim+2]+=var2;
                    dst[offset-dim+3]+=var3;
                    dst[offset-dim+4]+=var4;
                    dst[offset-dim+5]+=var5;
                    dst[offset-dim+6]+=var6;
                    dst[offset-dim+7]+=var7;
                    dst[offset-dim+8]+=var8;
                    dst[offset-dim+9]+=var9;
                    dst[offset-dim+10]+=var10;
                    dst[offset-dim+11]+=var11;
                    dst[offset-dim+12]+=var12;
                    dst[offset-dim+13]+=var13;
                    dst[offset-dim+14]+=var14;
                    dst[offset-dim+15]+=var15;
                    dst[offset-dim+16]+=var16;
                }
            }
            for(; j < dim-2; j++) {
                var1 =src[i_dim+j+2]-src[i_dim+j];
                if(i>=0 && i<=dim-3){
                    dst[i_dim+dim+j+1]=var1;
                }
                if(i>=1 && i<=dim-2){
                    dst[i_dim+j+1]+=var1<<1;
                }
                if(i>=2 && i<=dim-1){
                    dst[i_dim-dim+j+1]+=var1;
                }
                }
            i_dim+=dim;
            
        }

      
    }
char sobel16_descr[] = "sobel16: ";
void sobel16(int dim,int *src,int *dst){
    int i,j,i_dim,offset,var1,var2,var3,var4,var5,var6,var7,var8,var9,var10,var11,var12,var13,var14,var15,var16;

    i_dim = 0;
    for(i=0;i<dim;i++){
      for(j=0;j<dim;j++){
          dst[i_dim+j]=0;
        }
        i_dim+=dim;
    }
  
     i_dim = 0;
        for(i = 0; i < dim ; i++){
            for(j = 0; j < dim-2-15; j+=16) {
                offset=i_dim+j;
                
                var1 =src[offset+2]-src[offset];
                var2=src[offset+3]-src[offset+1];
                var3=src[offset+4]-src[offset+2];
                var4=src[offset+5]-src[offset+3];
                var5 =src[offset+6]-src[offset+4];
                var6=src[offset+7]-src[offset+5];
                var7=src[offset+8]-src[offset+6];
                var8=src[offset+9]-src[offset+7];
                var9 =src[offset+10]-src[offset+8];
                var10=src[offset+11]-src[offset+9];
                var11=src[offset+12]-src[offset+10];
                var12=src[offset+13]-src[offset+11];
                var13 =src[offset+14]-src[offset+12];
                var14=src[offset+15]-src[offset+13];
                var15=src[offset+16]-src[offset+14];
                var16=src[offset+17]-src[offset+15];
                if(i>=0 && i<=dim-3){
                    dst[offset+dim+1]=var1;
                    dst[offset+dim+2]=var2;
                    dst[offset+dim+3]=var3;
                    dst[offset+dim+4]=var4;
                    dst[offset+dim+5]=var5;
                    dst[offset+dim+6]=var6;
                    dst[offset+dim+7]=var7;
                    dst[offset+dim+8]=var8;
                    dst[offset+dim+9]=var9;
                    dst[offset+dim+10]=var10;
                    dst[offset+dim+11]=var11;
                    dst[offset+dim+12]=var12;
                    dst[offset+dim+13]=var13;
                    dst[offset+dim+14]=var14;
                    dst[offset+dim+15]=var15;
                    dst[offset+dim+16]=var16;
                }
                if(i>=1 && i<=dim-2){
                    dst[offset+1]+=var1<<1;
                    dst[offset+2]+=var2<<1;
                    dst[offset+3]+=var3<<1;
                    dst[offset+4]+=var4<<1;
                    dst[offset+5]+=var5<<1;
                    dst[offset+6]+=var6<<1;
                    dst[offset+7]+=var7<<1;
                    dst[offset+8]+=var8<<1;
                    dst[offset+9]+=var9<<1;
                    dst[offset+10]+=var10<<1;
                    dst[offset+11]+=var11<<1;
                    dst[offset+12]+=var12<<1;
                    dst[offset+13]+=var13<<1;
                    dst[offset+14]+=var14<<1;
                    dst[offset+15]+=var15<<1;
                    dst[offset+16]+=var16<<1;
                }
                if(i>=2 && i<=dim-1){
                    dst[offset-dim+1]+=var1;
                    dst[offset-dim+2]+=var2;
                    dst[offset-dim+3]+=var3;
                    dst[offset-dim+4]+=var4;
                    dst[offset-dim+5]+=var5;
                    dst[offset-dim+6]+=var6;
                    dst[offset-dim+7]+=var7;
                    dst[offset-dim+8]+=var8;
                    dst[offset-dim+9]+=var9;
                    dst[offset-dim+10]+=var10;
                    dst[offset-dim+11]+=var11;
                    dst[offset-dim+12]+=var12;
                    dst[offset-dim+13]+=var13;
                    dst[offset-dim+14]+=var14;
                    dst[offset-dim+15]+=var15;
                    dst[offset-dim+16]+=var16;
                }
            }
                //last 14
                offset=i_dim+j;
                var1 =src[offset+2]-src[offset];
                var2=src[offset+3]-src[offset+1];
                var3=src[offset+4]-src[offset+2];
                var4=src[offset+5]-src[offset+3];
                var5 =src[offset+6]-src[offset+4];
                var6=src[offset+7]-src[offset+5];
                var7=src[offset+8]-src[offset+6];
                var8=src[offset+9]-src[offset+7];
                var9 =src[offset+10]-src[offset+8];
                var10=src[offset+11]-src[offset+9];
                var11=src[offset+12]-src[offset+10];
                var12=src[offset+13]-src[offset+11];
                var13 =src[offset+14]-src[offset+12];
                var14=src[offset+15]-src[offset+13];
                if(i>=0 && i<=dim-3){
                    dst[offset+dim+1]=var1;
                    dst[offset+dim+2]=var2;
                    dst[offset+dim+3]=var3;
                    dst[offset+dim+4]=var4;
                    dst[offset+dim+5]=var5;
                    dst[offset+dim+6]=var6;
                    dst[offset+dim+7]=var7;
                    dst[offset+dim+8]=var8;
                    dst[offset+dim+9]=var9;
                    dst[offset+dim+10]=var10;
                    dst[offset+dim+11]=var11;
                    dst[offset+dim+12]=var12;
                    dst[offset+dim+13]=var13;
                    dst[offset+dim+14]=var14;
                }
                if(i>=1 && i<=dim-2){
                    dst[offset+1]+=var1<<1;
                    dst[offset+2]+=var2<<1;
                    dst[offset+3]+=var3<<1;
                    dst[offset+4]+=var4<<1;
                    dst[offset+5]+=var5<<1;
                    dst[offset+6]+=var6<<1;
                    dst[offset+7]+=var7<<1;
                    dst[offset+8]+=var8<<1;
                    dst[offset+9]+=var9<<1;
                    dst[offset+10]+=var10<<1;
                    dst[offset+11]+=var11<<1;
                    dst[offset+12]+=var12<<1;
                    dst[offset+13]+=var13<<1;
                    dst[offset+14]+=var14<<1;
                }
                if(i>=2 && i<=dim-1){
                    dst[offset-dim+1]+=var1;
                    dst[offset-dim+2]+=var2;
                    dst[offset-dim+3]+=var3;
                    dst[offset-dim+4]+=var4;
                    dst[offset-dim+5]+=var5;
                    dst[offset-dim+6]+=var6;
                    dst[offset-dim+7]+=var7;
                    dst[offset-dim+8]+=var8;
                    dst[offset-dim+9]+=var9;
                    dst[offset-dim+10]+=var10;
                    dst[offset-dim+11]+=var11;
                    dst[offset-dim+12]+=var12;
                    dst[offset-dim+13]+=var13;
                    dst[offset-dim+14]+=var14;
                }
                i_dim+=dim;
            }
          
      
    }
char sobel32_descr[] = "sobel32: ";
void sobel32(int dim,int *src,int *dst){
    int i,j,i_dim,offset,var1,var2,var3,var4,var5,var6,var7,var8,var9,var10,var11,var12,var13,var14,var15,var16;
    int var17,var18,var19,var20,var21,var22,var23,var24,var25,var26,var27,var28,var29,var30,var31,var32;

    i_dim = 0;
    for(i=0;i<dim;i++){
      for(j=0;j<dim;j++){
          dst[i_dim+j]=0;
        }
        i_dim+=dim;
    }
  
     i_dim = 0;
        for(i = 0; i < dim ; i++){
            for(j = 0; j < dim-2-31; j+=32) {
                offset=i_dim+j;
                
                var1 =src[offset+2]-src[offset];
                var2=src[offset+3]-src[offset+1];
                var3=src[offset+4]-src[offset+2];
                var4=src[offset+5]-src[offset+3];
                var5 =src[offset+6]-src[offset+4];
                var6=src[offset+7]-src[offset+5];
                var7=src[offset+8]-src[offset+6];
                var8=src[offset+9]-src[offset+7];
                var9 =src[offset+10]-src[offset+8];
                var10=src[offset+11]-src[offset+9];
                var11=src[offset+12]-src[offset+10];
                var12=src[offset+13]-src[offset+11];
                var13 =src[offset+14]-src[offset+12];
                var14=src[offset+15]-src[offset+13];
                var15=src[offset+16]-src[offset+14];
                var16=src[offset+17]-src[offset+15];
                var17 =src[offset+18]-src[offset+16];
                var18=src[offset+19]-src[offset+17];
                var19=src[offset+20]-src[offset+18];
                var20=src[offset+21]-src[offset+19];
                var21 =src[offset+22]-src[offset+20];
                var22=src[offset+23]-src[offset+21];
                var23=src[offset+24]-src[offset+22];
                var24=src[offset+25]-src[offset+23];
                var25 =src[offset+26]-src[offset+24];
                var26=src[offset+27]-src[offset+25];
                var27=src[offset+28]-src[offset+26];
                var28=src[offset+29]-src[offset+27];
                var29 =src[offset+30]-src[offset+28];
                var30=src[offset+31]-src[offset+29];
                var31=src[offset+32]-src[offset+30];
                var32=src[offset+33]-src[offset+31];
                if(i>=0 && i<=dim-3){
                    dst[offset+dim+1]=var1;
                    dst[offset+dim+2]=var2;
                    dst[offset+dim+3]=var3;
                    dst[offset+dim+4]=var4;
                    dst[offset+dim+5]=var5;
                    dst[offset+dim+6]=var6;
                    dst[offset+dim+7]=var7;
                    dst[offset+dim+8]=var8;
                    dst[offset+dim+9]=var9;
                    dst[offset+dim+10]=var10;
                    dst[offset+dim+11]=var11;
                    dst[offset+dim+12]=var12;
                    dst[offset+dim+13]=var13;
                    dst[offset+dim+14]=var14;
                    dst[offset+dim+15]=var15;
                    dst[offset+dim+16]=var16;
                    dst[offset+dim+17]=var17;
                    dst[offset+dim+18]=var18;
                    dst[offset+dim+19]=var19;
                    dst[offset+dim+20]=var20;
                    dst[offset+dim+21]=var21;
                    dst[offset+dim+22]=var22;
                    dst[offset+dim+23]=var23;
                    dst[offset+dim+24]=var24;
                    dst[offset+dim+25]=var25;
                    dst[offset+dim+26]=var26;
                    dst[offset+dim+27]=var27;
                    dst[offset+dim+28]=var28;
                    dst[offset+dim+29]=var29;
                    dst[offset+dim+30]=var30;
                    dst[offset+dim+31]=var31;
                    dst[offset+dim+32]=var32;
                }
                if(i>=1 && i<=dim-2){
                    dst[offset+1]+=var1<<1;
                    dst[offset+2]+=var2<<1;
                    dst[offset+3]+=var3<<1;
                    dst[offset+4]+=var4<<1;
                    dst[offset+5]+=var5<<1;
                    dst[offset+6]+=var6<<1;
                    dst[offset+7]+=var7<<1;
                    dst[offset+8]+=var8<<1;
                    dst[offset+9]+=var9<<1;
                    dst[offset+10]+=var10<<1;
                    dst[offset+11]+=var11<<1;
                    dst[offset+12]+=var12<<1;
                    dst[offset+13]+=var13<<1;
                    dst[offset+14]+=var14<<1;
                    dst[offset+15]+=var15<<1;
                    dst[offset+16]+=var16<<1;
                    dst[offset+17]+=var17<<1;
                    dst[offset+18]+=var18<<1;
                    dst[offset+19]+=var19<<1;
                    dst[offset+20]+=var20<<1;
                    dst[offset+21]+=var21<<1;
                    dst[offset+22]+=var22<<1;
                    dst[offset+23]+=var23<<1;
                    dst[offset+24]+=var24<<1;
                    dst[offset+25]+=var25<<1;
                    dst[offset+26]+=var26<<1;
                    dst[offset+27]+=var27<<1;
                    dst[offset+28]+=var28<<1;
                    dst[offset+29]+=var29<<1;
                    dst[offset+30]+=var30<<1;
                    dst[offset+31]+=var31<<1;
                    dst[offset+32]+=var32<<1;
                }
                if(i>=2 && i<=dim-1){
                    dst[offset-dim+1]+=var1;
                    dst[offset-dim+2]+=var2;
                    dst[offset-dim+3]+=var3;
                    dst[offset-dim+4]+=var4;
                    dst[offset-dim+5]+=var5;
                    dst[offset-dim+6]+=var6;
                    dst[offset-dim+7]+=var7;
                    dst[offset-dim+8]+=var8;
                    dst[offset-dim+9]+=var9;
                    dst[offset-dim+10]+=var10;
                    dst[offset-dim+11]+=var11;
                    dst[offset-dim+12]+=var12;
                    dst[offset-dim+13]+=var13;
                    dst[offset-dim+14]+=var14;
                    dst[offset-dim+15]+=var15;
                    dst[offset-dim+16]+=var16;
                    dst[offset-dim+17]+=var17;
                    dst[offset-dim+18]+=var18;
                    dst[offset-dim+19]+=var19;
                    dst[offset-dim+20]+=var20;
                    dst[offset-dim+21]+=var21;
                    dst[offset-dim+22]+=var22;
                    dst[offset-dim+23]+=var23;
                    dst[offset-dim+24]+=var24;
                    dst[offset-dim+25]+=var25;
                    dst[offset-dim+26]+=var26;
                    dst[offset-dim+27]+=var27;
                    dst[offset-dim+28]+=var28;
                    dst[offset-dim+29]+=var29;
                    dst[offset-dim+30]+=var30;
                    dst[offset-dim+31]+=var31;
                    dst[offset-dim+32]+=var32;
                }
            }//last 30
                offset=i_dim+j;
                var1 =src[offset+2]-src[offset];
                var2=src[offset+3]-src[offset+1];
                var3=src[offset+4]-src[offset+2];
                var4=src[offset+5]-src[offset+3];
                var5 =src[offset+6]-src[offset+4];
                var6=src[offset+7]-src[offset+5];
                var7=src[offset+8]-src[offset+6];
                var8=src[offset+9]-src[offset+7];
                var9 =src[offset+10]-src[offset+8];
                var10=src[offset+11]-src[offset+9];
                var11=src[offset+12]-src[offset+10];
                var12=src[offset+13]-src[offset+11];
                var13 =src[offset+14]-src[offset+12];
                var14=src[offset+15]-src[offset+13];
                var15=src[offset+16]-src[offset+14];
                var16=src[offset+17]-src[offset+15];
                var17 =src[offset+18]-src[offset+16];
                var18=src[offset+19]-src[offset+17];
                var19=src[offset+20]-src[offset+18];
                var20=src[offset+21]-src[offset+19];
                var21 =src[offset+22]-src[offset+20];
                var22=src[offset+23]-src[offset+21];
                var23=src[offset+24]-src[offset+22];
                var24=src[offset+25]-src[offset+23];
                var25 =src[offset+26]-src[offset+24];
                var26=src[offset+27]-src[offset+25];
                var27=src[offset+28]-src[offset+26];
                var28=src[offset+29]-src[offset+27];
                var29 =src[offset+30]-src[offset+28];
                var30=src[offset+31]-src[offset+29];
                
                if(i>=0 && i<=dim-3){
                    dst[offset+dim+1]=var1;
                    dst[offset+dim+2]=var2;
                    dst[offset+dim+3]=var3;
                    dst[offset+dim+4]=var4;
                    dst[offset+dim+5]=var5;
                    dst[offset+dim+6]=var6;
                    dst[offset+dim+7]=var7;
                    dst[offset+dim+8]=var8;
                    dst[offset+dim+9]=var9;
                    dst[offset+dim+10]=var10;
                    dst[offset+dim+11]=var11;
                    dst[offset+dim+12]=var12;
                    dst[offset+dim+13]=var13;
                    dst[offset+dim+14]=var14;
                    dst[offset+dim+15]=var15;
                    dst[offset+dim+16]=var16;
                    dst[offset+dim+17]=var17;
                    dst[offset+dim+18]=var18;
                    dst[offset+dim+19]=var19;
                    dst[offset+dim+20]=var20;
                    dst[offset+dim+21]=var21;
                    dst[offset+dim+22]=var22;
                    dst[offset+dim+23]=var23;
                    dst[offset+dim+24]=var24;
                    dst[offset+dim+25]=var25;
                    dst[offset+dim+26]=var26;
                    dst[offset+dim+27]=var27;
                    dst[offset+dim+28]=var28;
                    dst[offset+dim+29]=var29;
                    dst[offset+dim+30]=var30;
                    
                }
                if(i>=1 && i<=dim-2){
                    dst[offset+1]+=var1<<1;
                    dst[offset+2]+=var2<<1;
                    dst[offset+3]+=var3<<1;
                    dst[offset+4]+=var4<<1;
                    dst[offset+5]+=var5<<1;
                    dst[offset+6]+=var6<<1;
                    dst[offset+7]+=var7<<1;
                    dst[offset+8]+=var8<<1;
                    dst[offset+9]+=var9<<1;
                    dst[offset+10]+=var10<<1;
                    dst[offset+11]+=var11<<1;
                    dst[offset+12]+=var12<<1;
                    dst[offset+13]+=var13<<1;
                    dst[offset+14]+=var14<<1;
                    dst[offset+15]+=var15<<1;
                    dst[offset+16]+=var16<<1;
                    dst[offset+17]+=var17<<1;
                    dst[offset+18]+=var18<<1;
                    dst[offset+19]+=var19<<1;
                    dst[offset+20]+=var20<<1;
                    dst[offset+21]+=var21<<1;
                    dst[offset+22]+=var22<<1;
                    dst[offset+23]+=var23<<1;
                    dst[offset+24]+=var24<<1;
                    dst[offset+25]+=var25<<1;
                    dst[offset+26]+=var26<<1;
                    dst[offset+27]+=var27<<1;
                    dst[offset+28]+=var28<<1;
                    dst[offset+29]+=var29<<1;
                    dst[offset+30]+=var30<<1;
                   
                }
                if(i>=2 && i<=dim-1){
                    dst[offset-dim+1]+=var1;
                    dst[offset-dim+2]+=var2;
                    dst[offset-dim+3]+=var3;
                    dst[offset-dim+4]+=var4;
                    dst[offset-dim+5]+=var5;
                    dst[offset-dim+6]+=var6;
                    dst[offset-dim+7]+=var7;
                    dst[offset-dim+8]+=var8;
                    dst[offset-dim+9]+=var9;
                    dst[offset-dim+10]+=var10;
                    dst[offset-dim+11]+=var11;
                    dst[offset-dim+12]+=var12;
                    dst[offset-dim+13]+=var13;
                    dst[offset-dim+14]+=var14;
                    dst[offset-dim+15]+=var15;
                    dst[offset-dim+16]+=var16;
                    dst[offset-dim+17]+=var17;
                    dst[offset-dim+18]+=var18;
                    dst[offset-dim+19]+=var19;
                    dst[offset-dim+20]+=var20;
                    dst[offset-dim+21]+=var21;
                    dst[offset-dim+22]+=var22;
                    dst[offset-dim+23]+=var23;
                    dst[offset-dim+24]+=var24;
                    dst[offset-dim+25]+=var25;
                    dst[offset-dim+26]+=var26;
                    dst[offset-dim+27]+=var27;
                    dst[offset-dim+28]+=var28;
                    dst[offset-dim+29]+=var29;
                    dst[offset-dim+30]+=var30;
                }
            i_dim+=dim;   
        }
      
    }      

/* 
 * naive_sobel - The naive baseline version of Sobel 
 */
char naive_sobel_descr[] = "sobel: Naive baseline implementation";
void naive_sobel(int dim,int *src, int *dst) {
    int i,j,k,l;
    int ker[3][3] = {{-1, 0, 1}, 
                     {-2, 0, 2}, 
                     {-1, 0, 1}};  

    for(i = 0; i < dim; i++)
        for(j = 0; j < dim; j++) {	
	   dst[j*dim+i]=0;
            if(!((i == 0) || (i == dim-1) || (j == 0) || (j == dim-1))){
            for(k = -1; k <= 1; k++)
                for(l = -1; l <= 1; l++) {
                 dst[j*dim+i]=dst[j*dim+i]+src[(j + l)*dim+(i + k)] * ker[(l+1)][(k+1)]; 
                }
		       

      }
      
}
}
/* 
 * sobel - Your current working version of sobel
 * IMPORTANT: This is the version you will be graded on
 */

char sobel_descr[] = "Dot product: Current working version";
void sobel(int dim,int *src,int *dst) 
{

       sobel32(dim,src,dst);

}

/*********************************************************************
 * register_sobel_functions - Register all of your different versions
 *     of the sobel functions  with the driver by calling the
 *     add_sobel_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_sobel_functions() {
    add_sobel_function(&naive_sobel, naive_sobel_descr);   
    add_sobel_function(&sobel, sobel_descr);    
    add_sobel_function(&mysobel,mysobel_descr); 
    add_sobel_function(&newsobel,newsobel_descr); 
    add_sobel_function(&unrollsobel,unrollsobel_descr);
    add_sobel_function(&sobel32,sobel32_descr);
    add_sobel_function(&sobel16,sobel16_descr);
    /* ... Register additional test functions here */
}




/***************
 * MIRROR KERNEL
 ***************/

/******************************************************
 * Your different versions of the mirror func  go here
 ******************************************************/

char mirror16_descr[] = "mirror16 ";
void mirror16(int dim,int *src,int *dst) {
    
 	int i,j,i_n;
    i_n=0;
    for(i = 0; i < dim; i++){
        for(j= 0; j <= dim-15; j+=16) {
            dst[i_n+j+15]=src[i_n+ dim-1-(j+15)];
            dst[i_n+j+14]=src[i_n+ dim-1-(j+14)];
            dst[i_n+j+13]=src[i_n+ dim-1-(j+13)];
            dst[i_n+j+12]=src[i_n+ dim-1-(j+12)];
            dst[i_n+j+11]=src[i_n+ dim-1-(j+11)];
            dst[i_n+j+10]=src[i_n+ dim-1-(j+10)];
            dst[i_n+j+9]=src[i_n+ dim-1-(j+9)];
            dst[i_n+j+8]=src[i_n+ dim-1-(j+8)];
            dst[i_n+j+7]=src[i_n+ dim-1-(j+7)];
            dst[i_n+j+6]=src[i_n+ dim-1-(j+6)];
            dst[i_n+j+5]=src[i_n+ dim-1-(j+5)];
            dst[i_n+j+4]=src[i_n+ dim-1-(j+4)];
            dst[i_n+j+3]=src[i_n+ dim-1-(j+3)];
            dst[i_n+j+2]=src[i_n+ dim-1-(j+2)];
            dst[i_n+j+1]=src[i_n+ dim-1-(j+1)];
            dst[i_n+j+0]=src[i_n+ dim-1-(j+0)];
        }
        i_n += dim;
    }
    
}

char mirror32_descr[] = "mirror32 ";
void mirror32(int dim,int *src,int *dst) {
    
 	int i,j,i_n;
    i_n=0;
    for(i = 0; i < dim; i++){
        for(j= 0; j <= dim-31; j+=32) {
            dst[i_n+j+31]=src[i_n+ dim-1-(j+31)];
            dst[i_n+j+30]=src[i_n+ dim-1-(j+30)];
            dst[i_n+j+29]=src[i_n+ dim-1-(j+29)];
            dst[i_n+j+28]=src[i_n+ dim-1-(j+28)];
            dst[i_n+j+27]=src[i_n+ dim-1-(j+27)];
            dst[i_n+j+26]=src[i_n+ dim-1-(j+26)];
            dst[i_n+j+25]=src[i_n+ dim-1-(j+25)];
            dst[i_n+j+24]=src[i_n+ dim-1-(j+24)];
            dst[i_n+j+23]=src[i_n+ dim-1-(j+23)];
            dst[i_n+j+22]=src[i_n+ dim-1-(j+22)];
            dst[i_n+j+21]=src[i_n+ dim-1-(j+21)];
            dst[i_n+j+20]=src[i_n+ dim-1-(j+20)];
            dst[i_n+j+19]=src[i_n+ dim-1-(j+19)];
            dst[i_n+j+18]=src[i_n+ dim-1-(j+18)];
            dst[i_n+j+17]=src[i_n+ dim-1-(j+17)];
            dst[i_n+j+16]=src[i_n+ dim-1-(j+16)];
            dst[i_n+j+15]=src[i_n+ dim-1-(j+15)];
            dst[i_n+j+14]=src[i_n+ dim-1-(j+14)];
            dst[i_n+j+13]=src[i_n+ dim-1-(j+13)];
            dst[i_n+j+12]=src[i_n+ dim-1-(j+12)];
            dst[i_n+j+11]=src[i_n+ dim-1-(j+11)];
            dst[i_n+j+10]=src[i_n+ dim-1-(j+10)];
            dst[i_n+j+9]=src[i_n+ dim-1-(j+9)];
            dst[i_n+j+8]=src[i_n+ dim-1-(j+8)];
            dst[i_n+j+7]=src[i_n+ dim-1-(j+7)];
            dst[i_n+j+6]=src[i_n+ dim-1-(j+6)];
            dst[i_n+j+5]=src[i_n+ dim-1-(j+5)];
            dst[i_n+j+4]=src[i_n+ dim-1-(j+4)];
            dst[i_n+j+3]=src[i_n+ dim-1-(j+3)];
            dst[i_n+j+2]=src[i_n+ dim-1-(j+2)];
            dst[i_n+j+1]=src[i_n+ dim-1-(j+1)];
            dst[i_n+j+0]=src[i_n+ dim-1-(j+0)];
        }
        i_n += dim;
    }
    
}

/* 
 * naive_mirror - The naive baseline version of mirror 
 */
char naive_mirror_descr[] = "Naive_mirror: Naive baseline implementation";
void naive_mirror(int dim,int *src,int *dst) {
    
 	 int i,j;

  for(j = 0; j < dim; j++)
        for(i = 0; i < dim; i++) {
            dst[RIDX(j,i,dim)]=src[RIDX(j,dim-1-i,dim)];

        }

}


/* 
 * mirror - Your current working version of mirror
 * IMPORTANT: This is the version you will be graded on
 */
char mirror_descr[] = "Mirror: Current working version";
void mirror(int dim,int *src,int *dst) 
{

        
 	mirror32(dim,src,dst);

}

/*********************************************************************
 * register_mirror_functions - Register all of your different versions
 *     of the mirror functions  with the driver by calling the
 *     add_mirror_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_mirror_functions() {
    add_mirror_function(&naive_mirror, naive_mirror_descr);   
    add_mirror_function(&mirror, mirror_descr); 
    add_mirror_function(&mirror16,mirror16_descr);  
    add_mirror_function(&mirror32,mirror32_descr);
 
    /* ... Register additional test functions here */
}

