#include <stdio.h>

int main(){
    FILE *fp = fopen("coefficient.txt","w");
    FILE *fp1 = fopen("graph.txt","w");

    int selection,flag;
    int a,b,c;
    int a1,b1,c1;
    do{

        printf("Select an operation...\n");
        printf("0 -> Enter the coefficents.\n");
        printf("1 -> Draw the graph.\n");
        printf("2 -> Print the graph into a txt file\n");
        printf("3 -> Exit\n\n");
        printf("Choice: ");

        scanf("%d",&selection);

        switch(selection){
            case(0):
                printf("Please enter the coefficient for the following equation: x=a*(y*y) + b*y + c \n");
                
                printf("a: ");
                scanf("%d",&a);
                getchar();
                fprintf(fp,"%d\n",a);
                
                printf("b: ");
                scanf("%d",&b);
                getchar();
                fprintf(fp,"%d\n",b);
                
                printf("c: ");
                scanf("%d",&c);
                getchar();
                fprintf(fp,"%d\n",c);

                fclose(fp);

                printf("coefficients.txt file has been created.");
                break;
            case(1):
                fp = fopen("coefficient.txt","r");
                printf("Coefficients has been read from txt.file\n");
                fscanf(fp,"%d %d %d",&a1,&b1,&c1);


                for(int i=-56; i < 0; i++){
                printf(" ");        
                }
                printf("^\n");

                for(int y=16; y > -16 ; y-- ){

                    for(int x= -56; x <= 56 ; x++ ){
                        
                        if(x == (a1*y*y) + (b1*y) + c1){
                            
                            printf("\b\033[0;33m#\033[0m");
                        }
                        //\033[1;31m kırmızı // \033[0;33m sarı // \033[0;34m mavi //\033[0;36m cyan \033[0m 
                        else if( x == 0){
                                if(y == 15)
                                    printf("\b\b\b\033[0;36m15\033[0m ");
                                else if(y == 10)
                                    printf("\b\b\b\033[0;36m10\033[0m ");
                                else if(y == 5)
                                    printf("\b\b\033[0;36m5\033[0m ");
                                else if(y == -1)
                                    printf("\b\b\033[0;36m0\033[0m ");
                                else if(y == -5)
                                    printf("\b\b\b\033[0;36m-5\033[0m ");
                                else if(y == -10)
                                    printf("\b\b\b\b\033[0;36m-10\033[0m ");
                                else if(y == -15)
                                    printf("\b\b\b\b\033[0;36m-15\033[0m ");
                            printf("|");
                        }
                        else if(x==-56 && y ==0){
                            printf("<");
                        }

                        else if ( y == 0){
                            

                            printf("-");

                            if(x==56){
                                printf(">");
                            }

                        }

                        else if(y==-1){

                            if(x==-50)
                                printf("\033[0;34m-50\033[0m        ");
                            else if(x==-40)
                                printf("\033[0;34m-40\033[0m        ");
                            else if(x==-30)
                                printf("\033[0;34m-30\033[0m        ");
                            else if(x==-20)
                                printf("\033[0;34m-20\033[0m        ");
                            else if(x==-10)
                                printf("\033[0;34m-10\033[0m        ");
                            else if(x==10)
                                printf("         \033[0;34m10\033[0m         ");
                            else if(x==20)
                                printf("\033[0;34m20\033[0m         ");
                            else if(x==30)
                                printf("\033[0;34m30\033[0m         ");
                            else if(x==40)
                                printf("\033[0;34m40\033[0m         ");
                            else if(x==50)
                                printf("\033[0;34m50\033[0m         ");
                        }

                        else
                            printf(" ");

                    }
                printf("\n");
                }
                fclose(fp);
                break;
            case(2):

                for(int i=-56; i < 0; i++){
                fprintf(fp1," ");        
                }
                fprintf(fp1,"^\n");

                for(int y=16; y > -16 ; y-- ){

                    for(int x= -56; x <= 56 ; x++ ){
                        
                        if(x == (a1*y*y) + (b1*y) + c1){
                            fprintf(fp1,"#");
                        }

                        else if( x == 0){
                            fprintf(fp1,"|");
                        }
                        else if(x==-56 && y ==0){
                            fprintf(fp1,"<");
                        }

                        else if ( y == 0){
                            
                            fprintf(fp1,"-");

                            if(x==56){
                                fprintf(fp1,">");
                            }
                        }

                        else
                            fprintf(fp1," ");

                    }
                fprintf(fp1,"\n");
                }
                fclose(fp1);
                break;
            default:
                if((selection!=0 || selection!= 1 || selection!= 2) && selection!=3 )
                    printf("***Invalid selection***\n");
                break;
        }

    }while(selection != 3);

    return 0;
    

}