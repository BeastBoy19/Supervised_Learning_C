#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "include\EDA.h"
int value(int *set,int n){
    for(int i=0;i<n;i++)
        if(set[i]>0)
            return set[i];
    return -1;
}
void naive(char ***dataset,const char **test){
    int *j=(int*)malloc(sizeof(int)*features);
    char ***unichar=(char***)malloc(sizeof(char**)*features);
    for(int i=0;i<features;i++){
        char **u = get_funiques(dataset, i);
        unichar[i] = (char **)malloc(sizeof(char *) * count);
        j[i] = count;
        for(int z=0;z<j[i];z++){
            unichar[i][z] = (char *)malloc(sizeof(char) * WMAX);
            strcpy(unichar[i][z], u[z]);
        }
    }
    int ***uni=(int***)malloc(sizeof(int**)*j[features-1]);
    for(int o=0;o<j[features-1];o++){
        char ***featuresuni=get_subset(dataset, unichar[features-1][o], features - 1);
        int temp=count;
        uni[o] = (int **)malloc(sizeof(int *) * features);
        for (int i = 0; i < features; i++){
            uni[o][i]=(int*)malloc(sizeof(int)*j[i]);
            for(int z=0;z<j[i];z++){
                uni[o][i][z] = uniquecount(featuresuni, temp, i, unichar[i][z]);
            }
        }
    }
    double max=0;
    int id=-1;
    for(int i=0;i<j[features-1];i++){
        double val=0;
        int prob=value(uni[i][features-1],j[features-1]);
        for(int z=0;z<features-1;z++){
            val=(double)prob/records;
            for(int p=0;p<j[z];p++){
                if(!strcmp(unichar[z][p],test[z]))
                    val=val*((double)uni[i][z][p]/prob);
            }
        }
        if(max<val){
            max=val;
            id=i;
        }
    }
    printf("%s",unichar[features-1][id]);
}
int main(){
    get_file("C:/Users/bikas/Projects/Dataset/IRIS.csv","r");
    char ***df = get_dataset(fp);
    printf("THE DATASET:\n");
    display(df,5,features);
    headerseperator(df);
    printf("\nSHAPE OF DATASET:\n");
    shape;
    shuffle(df, 2);
    display(df, 5, features);
    const char *test[4]={"6.5","3","5.8","2.2"};
    printf("\nPREDICTION : \n");
    naive(df,test);
    return 0;
}