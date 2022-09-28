#include <stdio.h>
int main(){

    int n;
    printf("Enter line: ");
    scanf("%d",&n);

    for(int y=0; y<n ;y++){
        for(int x=0; x<n; x++){
            if(y==0 || x==0 || y==n-1 || x==n-1){
                printf("*");
            }
            else
                printf(" ");

        }
        printf("\n");
    }    
}