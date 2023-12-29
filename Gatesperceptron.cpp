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
void propagation(float x[][columns],float *w,float *b,float a){
    int count=1;
    for(int i=0;i<records;i++){
        float o=0.0;
        printf("Forwardpropagation %d : ",i+1);
        for(int j=0;j<columns-1;j++){
            o+=conv(x[i][j],w[j],0);
            printf("%d  ",(int)x[i][j]);
        }
        o=step(o+*b);
        printf("%d \n",(int)o);
        if(o!=x[i][columns-1]){
            printf("Error! output : %d , target : %d\n",(int)o,(int)x[i][columns-1]);
            printf("\nBackpropagation %d : ",count++);
            backprop(x[i],w,o,x[i][2],b,a);
            i=-1;
        }      
    }
}
void plot(float x[][columns],const char *str){
    FILE *wp ,*gnuplot;
    wp=fopen("plot5.dat","w");
    gnuplot = popen("gnuplot -persist", "w");
    for(int i=0;i<records;i++){
        for(int j=0;j<columns;j++)
            fprintf(wp,"%d ",(int)x[i][j]);
        fprintf(wp,"\n");
    }
    fclose(wp);
    fprintf(gnuplot, "set title \"Data analysis %s\"\n"
                     "set palette define (0 0.5 0.5 0.5, 1 1 0 0)\n"
                     "plot \"plot5.dat\" using 1:2:3 with points pt 7 ps 3 palette notitle\n",
            str);
    fclose(gnuplot);
}
int main(){
    float weights[columns] = {0, 0};
    float bias = 1;
    float alpha = 0.5;
    float LOGIC[records][columns]={{0,0,0},{0,1,0},{1,0,0},{1,1,1}};
    plot(LOGIC,"AND GATE");
    propagation(LOGIC, weights, &bias, alpha);
    return 0;
}