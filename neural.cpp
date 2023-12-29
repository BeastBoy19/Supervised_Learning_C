#include <stdio.h>
#include <string.h>
#include <math.h>
#define threshold 1
#define step(x) (x>=threshold?1:0)
#define conv(x,w,b) (x*w+b)
const int records=4;
const int columns=3;

void backprop(float x[columns],float *w,float o,float t,float *b,float a){
    for(int i=0;i<columns-1;i++){
        w[i]=w[i]+a*(t-o)*x[i];
        printf("weight %d : %f   ",i+1, w[i]);
    }  
    *b=*b+a*(t-o);
    printf("bias : %f\n", *b);
}
void propagation(float x[][columns],float ***w,float *b,float a,int *l,int t){
    int count=1;
    float *n[t-1];
    for(int q=0;q<records;q++){
        float o=0.0;
        printf("Forwardpropagation %d : ",q+1);
        for(int i=0;i<t-1;i++){
            n[i]=(float*)malloc(sizeof(float)*l[i+1]);
            for(int j=0;j<l[i];j++){
                for(int z=0;z<l[i+1];z++){
                    n[i][j]+=conv(x[q][j],w[i][j][z],b[i]);
                    printf("%d  ",(int)x[i][j]);
                }  
            }
        }
        o=step(o+*b);
        printf("%d \n",(int)o);
        // if(o!=x[i][columns-1]){
        //     printf("Error! output : %d , target : %d\n",(int)o,(int)x[i][columns-1]);
        //     printf("\nBackpropagation %d : ",count++);
        //     backprop(x[i],w,o,x[i][2],b,a);
        //     i=-1;
        // }      
    }
}
int main(){
    int hidden_layers=1;
    int total_layers=hidden_layers+2;
    int layers[total_layers]={2,2,1};
    float ***weights=(float***)malloc(sizeof(float**)*total_layers-1);
    for(int i=0;i<total_layers-1;i++){
        weights[i]=(float**)malloc(sizeof(float*)*layers[i]);
        for(int j=0;j<layers[i];j++){
            weights[i][j]=(float*)malloc(sizeof(float)*layers[j]);
            for(int z=0;z<layers[i+1];z++)
                weights[i][j][z]=0;
        }
    }
    float bias[total_layers]={0,1,1};
    float alpha = 0.5;
    float LOGIC[records][columns]={{0,0,0},{0,1,1},{1,0,1},{1,1,0}};
    propagation(LOGIC, weights, bias, alpha, layers,total_layers);
    return 0;
}