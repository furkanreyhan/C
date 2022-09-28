#include <stdio.h>
int main(){
    int size;
    int k=0;
    printf("Enter size: ");
    scanf("%d",&size);
    

    for(int i=0; i<size; i++){
        for(int j=0; j<i+1; j++){
            k++;
            if(k%2==0)
                printf("0");
            else
                printf("1");
        }
        printf("\n");
    }
}
