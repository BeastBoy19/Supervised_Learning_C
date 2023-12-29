#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"include\EDA.h"
float* mean(char*** dataset,int row,int col){
    float* mean=(float*)malloc(col*sizeof(float));
    memset(mean,0,(col)*sizeof(float));
    for(int i=0;i<col;i++){
        float sum=0;
        for (int j = 0; j < row; j++)
            sum+=atof(dataset[j][i]);
        mean[i] = sum/row;
    }
    return mean;
}
float* varience(char*** dataset,int row,int col){
    float *var = (float *)malloc(col * sizeof(float));
    memset(var, 0, (col) * sizeof(float));
    float *u = mean(dataset, row,col);
    for (int i = 0; i < col; i++){
        float sum = 0;
        for (int j = 0; j < row; j++)
            sum += pow(atof(dataset[j][i])-u[i],2);
        var[i] = sum/(row-1);
    }
    return var;
}
float* fisherscore(char*** dataset1,char*** dataset2,int row1,int row2,int col){
    float* score=(float*)malloc(col*sizeof(float));
    memset(score,0,(col)*sizeof(float));
    float *mean1=mean(dataset1,row1,col);
    float *mean2=mean(dataset2,row2,col);
    float *var1=varience(dataset1,row1,col);
    float *var2=varience(dataset2,row2,col);
    for(int i=0;i<col;i++){
        score[i]=(float)pow((mean1[i]-mean2[i]),2)/(var1[i]+var2[i]);
    }
    return score;
}
float *sd(char*** dataset,int row,int col){
    float *sig = (float *)malloc(col * sizeof(float));
    float *var = varience(dataset, row, col);
    for(int i=0;i<col;i++){
        sig[i]=sqrt(var[i]);
    }
    return sig;
}
float **correlation(char*** dataset,int row,int col){
    float **corr=(float**)malloc(col*sizeof(float*));
    float *u=mean(dataset,row,col);
    float *sig = sd(dataset, row, col);
    for(int i=0;i<col;i++){
        corr[i] = (float *)malloc(col * sizeof(float));
        for(int z=0;z<col;z++){
            float sum=0;
            for (int j = 0; j < row; j++)
                sum += ((atof(dataset[j][i]) - u[i])*(atof(dataset[j][z]) - u[z]));
            corr[i][z] = ((sum)/(sig[i]*sig[z]))/(row-1);
        }
    }
    return corr;
}
float max(char*** dataset,int col){
    float mx=LONG_MIN;
    for(int i=0;i<records;i++)
        if(mx<atof(dataset[i][col]))
            mx=atof(dataset[i][col]);
    return mx;
}
float min(char*** dataset,int col){
    float mn=LONG_MAX;
    for(int i=0;i<records;i++)
        if(mn>atof(dataset[i][col]))
            mn=atof(dataset[i][col]);
    return mn;
}
int main(){
    get_file("C:/Users/bikas/Projects/Dataset/IRIS.csv","r");
    char ***df = get_dataset(fp);
    printf("THE DATASET:\n");
    display(df,5,features);
    headerseperator(df);
    printf("\nSHAPE OF DATASET:\n");
    shape;
    char **u = get_funiques(df,features-1);
    int ucount=count;
    printf("\nUNIQUE CLASSES:\n");
    for(int i=0;i<ucount;i++)
        printf("%s\n",u[i]);
    char ***setosa = get_subset(df, u[0], features - 1);
    int setosacount=count;
    char ***versicolor = get_subset(df, u[1], features - 1);
    int versicolorcount = count;
    char ***virginica = get_subset(df, u[2], features - 1);
    int virginicacount = count;
    printf("\nFISHER DISCRIMINATION RATIO BETWEEN SETOSA & VERSICOLOR:\n");
    float *score=fisherscore(setosa,versicolor,setosacount,versicolorcount,features-1);
    xdisplay(score, features - 1);
    printf("\nFISHER DISCRIMINATION RATIO BETWEEN SETOSA & VIRGINICA:\n");
    score = fisherscore(setosa, virginica, setosacount, virginicacount, features - 1);
    xdisplay(score, features - 1);
    printf("\nFISHER DISCRIMINATION RATIO BETWEEN VIRGINICA & VERSICOLOR:\n");
    score = fisherscore(virginica, versicolor, virginicacount, versicolorcount, features - 1);
    xdisplay(score,features - 1);
    printf("\n");
    labelencoding(df,features-1);
    float **corr=correlation(df,records,features);
    printf("\nPEARSON CORRELATION:\n");
    for(int i=0;i<features;i++){
        for(int j=0;j<features;j++)
            printf("%f\t",corr[i][j]);
        printf("\n");
    }
    printf("\n");

    plot("Size", "Sepal Length", df, 0, records, "plot1");
    plot("Size", "Sepal Width", df, 1, records,"plot2");
    plot("Size", "Petal Length", df, 2, records, "plot3");
    plot("Size", "Petal Width", df, 3, records, "plot4");

    printf("max: %f\n",max(df,0));
    printf("min: %f\n", min(df, 0));
    return 0;
}