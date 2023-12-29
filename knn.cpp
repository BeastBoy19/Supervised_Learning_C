#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "include\EDA.h"
float distance(char **row1,char **row2,int col){
    float sum=0;
    for(int i=0;i<col;i++)
        sum += pow(atof(row2[i])-atof(row1[i]), 2);
    return sum;
}
void aswap(float *rec1,float *rec2){
    float temp = *rec1;
    *rec1 = *rec2;
    *rec2 = temp;
}
void sswap(char *rec1,char *rec2){
    char *temp=(char*)malloc(sizeof(char)*WMAX);
    strcpy(temp,rec1);
    strcpy(rec1,rec2);
    strcpy(rec2,temp);
}
void bubble_sort(float *array, char **carray) {  
  for (int i = 0; i < traincount-1; i++) {  
    for (int j = 0; j < traincount - i - 1; j++) {  
      if (array[j] > array[j + 1]) {  
        aswap(&array[j],&array[j+1]);
        sswap(carray[j],carray[j+1]);
      }  
    }  
  }  
}  
int findmax(int *maj,int n){
    int max=0;
    int index=0;
    for(int i=0;i<n;i++){
        if(max<maj[i]){
            max = maj[i];
            index=i;
        } 
    }
    return index;
}
char *major(char ***dataset,char **data,int key){
    char **u = get_funiques(dataset, features - 1);
    int ucount = count;
    int maj[ucount];
    memset(maj,0,sizeof(int)*ucount);
    for(int z=0;z<key;z++){
        for(int i=0;i<ucount;i++){
            if(!strcmp(u[i],data[z])){
                maj[i]++;
            }
        }
    }
    return u[findmax(maj,ucount)];
}
void knn(char ***dataset,int key){
    char **prediction=(char**)malloc(sizeof(char*)*testcount);
    float *compute=(float*)malloc(sizeof(float)*traincount);
    for(int i=0;i<testcount;i++){
        memset(compute,0,sizeof(float)*traincount);
        for(int j=0;j<traincount;j++)
            compute[j]=distance(trainX[j],testX[i],features-1);
        char **temp=copy(trainY,traincount);
        bubble_sort(compute, temp);
        prediction[i]=(char*)malloc(sizeof(char)*WMAX);
        strcpy(prediction[i],major(dataset,temp,key));
    } 
    evaluate(dataset,prediction);
}
int main(){
    get_file("C:/Users/bikas/Projects/Dataset/IRIS.csv","r");
    char ***df = get_dataset(fp);
    printf("THE DATASET:\n");
    display(df,5,features);
    headerseperator(df);
    printf("\nSHAPE OF DATASET:\n");
    shape;
    shuffle(df,2);
    printf("\nAFTER SHUFFLING:\n");
    display(df,5,features);
    train_test_split(df,0.6);
    printf("\nTraining size : %d\ttesting size : %d\n\n",traincount,testcount);
    knn(df,3);
    return 0;
}