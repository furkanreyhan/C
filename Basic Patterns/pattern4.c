 #include <stdio.h>
 int main()
 {
    int size;
    int k=0;
    printf("Enter size: ");
    scanf("%d",&size);
    

    for(int i=0; i<size; i++){
        for(int j=0; j<i+1; j++){
            if(j%2==0)
                printf("%d",1);
            else
                printf("%d",0);

        }
        printf("\n");
    }
    return 0;
 }
 