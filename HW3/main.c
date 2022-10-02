#include <stdio.h>
#include <math.h>
#include <stdbool.h>
void write_file (int number);
int sum (int n1, int n2, int flag);
int multi (int n1, int n2, int flag);
int isprime (int a);
void sort_file ();
void print_file ();
int count_numbers();
bool check_number(int number);
void print_to_temp(int number);
void create_tempfile();


int main(){

    FILE *fpf= fopen("results.txt","a");

    int flag,selection,sum_or_mult,n1,n2,a;

    while(1){
        printf("\nSelect operation:\n");
        printf("1. Calculate sum/multiplication between two numbers\n");
        printf("2. Calculate prime numbers\n");
        printf("3. Show number sequence in file\n");
        printf("4. Sort number sequence in file\n");
        printf("5. EXIT\n");
        printf("-----------------------------\n");
        printf("Select operation\n");
        scanf("%d",&selection);

        if(selection == 5){
            return 0;
        }


        switch(selection){
            case(1):
                printf("Please enter '0' for sum, '1' for multiplication\n");
                scanf("%d",&sum_or_mult);

                if(sum_or_mult != 1 && sum_or_mult != 0){
                printf("ERROR. Enter valid number!");
                    return 0;
                }
                if(sum_or_mult == 0){ //0 is sum
                    getchar();
                    printf("Please enter '0' to work on even numbers, '1' to work on odd numbers\n");
                    scanf("%d",&flag);
                    
                    if(flag != 1 && flag !=0 ){
                        printf("ERROR. Enter valid number!");
                        return 0;
                    }

                    printf("Please enter two different number:\n");
                    printf("Number 1: ");
                    scanf("%d",&n1);

                    printf("\nNumber 2: ");
                    scanf("%d",&n2);
                
                    write_file( sum(n1,n2,flag));
                }
                else{
                    getchar();
                    printf("Please enter '0' to work on even numbers, '1' to work on odd numbers.\n");
                    scanf("%d",&flag);
                    
                    if(flag != 1 && flag !=0 ){
                        printf("ERROR. Enter valid number!");
                        return 0;
                    }
                    printf("Please enter two different number:\n");
                    printf("Number 1: ");
                    scanf("%d",&n1);

                    printf("Number 2: ");
                    scanf("%d",&n2);
                
                    write_file( multi(n1,n2,flag));
                    printf("The result is written to the results.txt file");


                }
                break;
            case(2):
                getchar();   
                printf("Please enter an integer: ");
                scanf("%d",&a);

                for(int i=2; i < a; i++){
                    if(isprime(i) == 1){
                        printf("%d is a prime number.\n",i);  
                    }
                    else
                        printf("%d is not a prime number, it is dividible by %d\n",i,isprime(i));
                }
                break;
            case(3):
                print_file();
                break;
            case(4):
                sort_file();
                break;
        }
    }
    fclose(fpf);
}


int sum(int n1,int n2, int flag){
    //flag 0 even, 1 odd
    int sum=0;
    int big_num = n2;
    int small_num = n1;
    if(n2 < n1){
        big_num = n1;
        small_num = n2;
    }
    if(flag == 0){
        for(int i=small_num+1; i < big_num ; i++){
            if(i%2 == 0) 
                sum=sum+i;
        }
    }
    else
        for(int i=small_num+1; i < big_num ; i++){
            if(i%2 == 1) 
                sum=sum+i;
        }
    return sum;
}

int multi (int n1, int n2, int flag){
    int multi=1;
    int big_num = n2;
    int small_num = n1;
    if(n2 < n1){
        big_num = n1;
        small_num = n2;
    }
    if(flag == 0){
        for(int i=small_num+1; i < big_num ; i++){
            if(i%2 == 0) 
                multi = multi*i;
        }
    }
    else
        for(int i=small_num+1; i < big_num ; i++){
            if(i%2 == 1) 
                multi = multi*i;
        }
    return multi;

}

void write_file (int number){
    FILE *fpw;
    fpw = fopen("results.txt","a");
    fprintf(fpw,"%d ",number);
    fclose(fpw);
}

int isprime (int a){

    int flag=1;

    if(a==2){
        return 1;//prime
    }
    for(int x=2; x <= sqrt(a); x++){
        if( a%x == 0){
            flag = 0; //not prime
            break;
        }
        else flag = 1; //prime
    }

    if(flag == 0){//not prime
        for(int i=2; i<a; i++){
            if( a%i == 0){
                flag = i;
                break;
            }
        }
    }
    return flag;
}

void print_file (){
    int num;
    FILE *fpp;
    fpp = fopen("results.txt","r");
    
    while(fscanf(fpp, "%d", &num) == 1)
        printf("%d ", num);

    fclose(fpp);
}

int count_numbers() {
    FILE *fp = fopen("results.txt", "r");
    
    int dummy;

    int count = 0;

    while (fscanf(fp, "%d", &dummy) != EOF) {
        //printf("%d\n", dummy);
        ++count;
    }

    fclose(fp);

    return count;
}

bool check_number(int number) {
    FILE *fp = fopen("temp.txt", "r");

    int comp;

    while (fscanf(fp, "%d", &comp) != EOF) {
        if(number == comp) {
            fclose(fp);
            return true;
        }
    }

    return false;
}

void print_to_temp(int number) {
    FILE *fp = fopen("temp.txt", "a+");
    fprintf(fp, "%d ", number);
    fclose(fp);
}

void sort_file() {

    int number_count = count_numbers();
    
    FILE *fp = fopen("results.txt", "r");
    FILE *fp1 = fopen("temp.txt", "w"); //Create the temp.txt
    fclose (fp1);

    while (number_count > 0) {
    
        int temp = 0;

        int min1 = 0, min2 = 0, min3 = 0;

        int flag1 = 0, flag2 = 0, flag3 = 0;

        fseek(fp, SEEK_SET, 0);

        while(fscanf(fp, "%d", &min1) != EOF) {
            if(check_number(min1) == false) {
                flag1 = 1;
                --number_count;
                break;
            }
        }

        fseek(fp, SEEK_SET, 0);

        while(fscanf(fp, "%d", &temp) != EOF) {
            if(check_number(temp) == false) {
                if(min1 > temp)
                    min1 = temp;     
            }
        }

        if(flag1 == 1)
            print_to_temp(min1);

        fseek(fp, SEEK_SET, 0);

        while(fscanf(fp, "%d", &min2) != EOF) {
            if(check_number(min2) == false) {
                flag2 = 1;
                --number_count;
                break;
            }
        }

        fseek(fp, SEEK_SET, 0);

        while(fscanf(fp, "%d", &temp) != EOF) {
            if(check_number(temp) == false) {
                if(min2 > temp)
                    min2 = temp;
            }   
        }

        if(flag2 == 1)
            print_to_temp(min2);

        fseek(fp, SEEK_SET, 0);

        while(fscanf(fp, "%d", &min3) != EOF) {
            if(check_number(min3) == false) {
                flag3 = 1;
                --number_count;
                break;
            }
        }

        fseek(fp, SEEK_SET, 0);

        while(fscanf(fp, "%d", &temp) != EOF) {
            if(check_number(temp) == false) {
                if(min3 > temp)
                    min3 = temp;
            }
        }

        if(flag3 == 1)
            print_to_temp(min3);
    }

    int temp;

    //Write temp.txt content to result.txt
    fp = fopen("results.txt", "w");
    fp1 = fopen("temp.txt", "r");
    
    
    while(fscanf(fp1, "%d", &temp) != EOF) {
        fprintf(fp, "%d ", temp);
    }
    
    fclose(fp1);
    remove("temp.txt"); // remove temp.txt

    fclose(fp);
}