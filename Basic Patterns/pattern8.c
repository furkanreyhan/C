#include <stdio.h>
int main(){
    int n; //height
    printf("Enter height: ");
    scanf("%d",&n);

    for(int y=0; y < n+1 ; y++ ){
        for(int x=0; x < (2*n)-1; x++){
            if(x > n-1-y && x < n+y-1){
                printf("*");
            }
            else   
                printf(" ");
        }
        printf("\n");
    }
}