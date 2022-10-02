#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14

enum Shapes{Triangle=1, Quadrilateral, Circle, Pyramid, Cylinder};
enum Calculators{Area=1, Perimeter, Volume};

void buff(){
    int a;
    do{
        a = getchar();
    }while(a!= '\n' && a!= EOF);
}

int select_shape(){
    int s=0;
    int shape_selection;
    do{
        printf("Select a shape to calculate:\n"
            "-----------------------\n"
            "1.Triangle\n"
            "2.Quadrilateral\n"
            "3.Circle\n"
            "4.Pyramid\n"
            "5.Cylinder\n"
            "0.Exit\n"
            "-----------------------:\n"
            "Input:");

        s = scanf("%d",&shape_selection);
        
        buff();

        if(shape_selection==0){
            exit(0);
        }

        if(s==0){
            printf("\n\n***Invalid Input***\n\n");
            continue;
        }

        switch(shape_selection){
            case (Triangle):
                return Triangle;
                break;
            case (Quadrilateral):
                return Quadrilateral;
                break;
            case (Circle):
                return Circle;
                break;
            case (Pyramid):
                return Pyramid;
                break;
            case (Cylinder):
                return Cylinder;
                break;
            default:
                if(shape_selection != 0) printf("\n\n***Invalid Input!***\n\n");
                break;
        }

    }while(shape_selection != 0);

    return 0;
}


int select_calc(){
    int s;
    int selection;
    int calc_selection;
    do{
        printf("Select calculator:\n"
            "-----------------------\n"
            "1.Area\n"
            "2.Perimeter\n"
            "3.Volume\n"
            "0.Exit\n"
            "-----------------------:\n"
            "Input:");

        s = scanf("%d",&calc_selection);
        buff();

        if(calc_selection==0){
            exit(0);
        }

        if(s==0){
            printf("\n\n***Invalid Input***\n\n");
            continue;
        }

        switch(calc_selection){
            case (Area):
                return Area;
                break;
            case (Perimeter):
                return Perimeter;
                break;
            case (Volume):
                return Volume;
                break;
            default:
                if(calc_selection != 0) printf("\n\n***Invalid Input!***\n\n");
                break;
        }

    }while(calc_selection!=0);    

}

int calc_triangle(int calc){
    int a,b,c,s,perimeter;
    double area;
    
    if(calc == Volume){
        printf("\nYou can not calculate the volume of Triangle. Please try again\n");
        return 1;
    }
    
    
    if( !scanf("%d",&a)){
        buff();
        printf("\nERROR! Plase enter valid entry.\n");
        return -1; 
    }

    if( !scanf("%d",&b)){
        buff();
        printf("\nERROR! Plase enter valid entry.\n");
        return -1; 
    } 

    if( !scanf("%d",&c)){
        buff();
        printf("\nERROR! Plase enter valid entry.\n");
        return -1; 
    }

    if(a <= 0 || b <= 0 || c <= 0){
        printf("\nERROR! Plase enter valid entry.\n");
        return -1;
    }

    if(a+b<=c || a+c<=b || b+c<=a){
        printf("\nERROR! Please enter valid Triangle!\n");
        return -1;
    }


    switch(calc){
        case (Area):
            s = (a+b+c)/2;
            area = sqrt(s*(s-a)*(s-b)*(s-c));
            printf("\nArea of Triangle=%.2lf\n",area);
            break;
        case (Perimeter):
            perimeter = a+b+c;
            printf("\nPerimeter of Triangle=%d",perimeter);
            break;
    }
    return 1;
}

int calc_quadriliteral(int calc){
    int a,b,c,d,s,perimeter;
    double area;



    if(calc == Volume){
        printf("\nYou can not calculate the volume of Quadriliteral. Please try again\n");
        return 1;
    }

    if( !scanf("%d",&a)){
        buff();
        printf("\nERROR! Plase enter valid entry.\n");
        return -1; 
    }

    if( !scanf("%d",&b)){
        buff();
        printf("\nERROR! Plase enter valid entry.\n");
        return -1; 
    } 

    if( !scanf("%d",&c)){
        buff();
        printf("\nERROR! Plase enter valid entry.\n");
        return -1; 
    }

    if( !scanf("%d",&d)){
        buff();
        printf("\nERROR! Plase enter valid entry.\n");
        return -1; 
    }

    if(a <= 0 || b <= 0 || c <= 0 || d<=0 ){
        printf("\nERROR! Plase enter valid entry.\n");
        return -1;
    }

    switch(calc){
        case (Area):
            s = (a+b+c+d)/2;
            area = sqrt((s-a)*(s-b)*(s-c)*(s-d));
            printf("\nArea of Quadrilatreal=%.2lf\n",area);
            break;
        case (Perimeter):
            perimeter = a+b+c+d;
            printf("\nPerimeter of Quadrilateral=%d\n",perimeter);
            break;
    }

    return 1;
}

int calc_circle(int calc){
    int r;
    double circumference,area;

    if(calc == Volume){
        printf("\nYou can not calculate the volume of Circle. Please try again\n");
        return 1;
    }



    if( !scanf("%d",&r)){
        buff();
        printf("\nERROR! Plase enter valid entry.\n");
        return -1;
    }

    if(r<=0){
        printf("\nERROR! Plase enter valid entry.\n");
        return -1;
    }

    switch(calc){
        case (Area):
            area = PI * r * r;
            printf("Area of Circle : %.2lf\n",area);
            break;
        case (Perimeter):
            circumference = 2 * PI * r;
            printf("Circumference of cirlce : %.2lf\n",circumference);
            break;
    }
    return 1;
}
int calc_pyramid(int calc){
    int a,h,l;
    double B,L,surface_area;
    double volume;

    switch(calc){
        case(Area):
            printf("Please enter the base side and slant height of a Pyramid : \n ");

            if(!scanf("%d",&a)){
                buff();
                printf("\nERROR! Plase enter valid entry.\n");
                return -1;
            }

            if(!scanf("%d",&l)){
                buff();
                printf("\nERROR! Plase enter valid entry.\n");
                return -1;
            }

            if(a <= 0 || l <= 0){
                printf("\nERROR! Plase enter valid entry.\n");
                return -1;
            }


            B = a*a;

            L = 2*a*l;

            surface_area = B + L;

            printf("Base Surface Area of PYRAMID : %.2lf\n\n",B);
            printf("Lateral Surface Area of PYRAMID : %.2lf\n\n",L);
            printf("Surface area of PYRAMID : %.2lf\n\n",surface_area);

            break;
        case(Perimeter):
            break;
        case(Volume):
            printf("Please enter the base side and height of a Pyramid : \n ");

            if(!scanf("%d",&a)){
                buff();
                printf("\nERROR! Plase enter valid entry.\n");
                return -1;
            }
            if(!scanf("%d",&h)){
                buff();
                printf("\nERROR! Plase enter valid entry.\n");
                return -1;
            }

            if(a <= 0 || h <= 0){
                printf("\nERROR! Plase enter valid entry.\n");
                return -1;
            }

            volume = (1.0/3.0)*a*a*h;
            printf("Volume of a Pyramid : %.2lf\n",volume);
            break;
    }
    return 1;
}
int calc_cylinder(int calc){
    int r,h;
    double volume,base_surface,lateral_surface,surface;
    double base_surface_perimeter;



    if(!scanf("%d",&r)){
        buff();
        printf("\nERROR! Plase enter valid entry.\n");
        return -1;
    }

    if(!scanf("%d",&h)){
        buff();
        printf("\nERROR! Plase enter valid entry.\n");
        return -1;
    }

    if(r<=0 || h<=0){
        printf("\nERROR! Plase enter valid entry.\n");
        return -1;
    }

    switch(calc){
        case (Area):
            base_surface = PI * r * r;
            lateral_surface = 2 * PI * r * h;
            surface = 2 * PI * r * (r+h);
            printf("Base Surface Area of CYLINDER : %.2lf\n\n", base_surface);
            printf("Lateral Surface Area of CYLINDER : %.2lf\n\n", lateral_surface);
            printf("Surface Area of CYLINDER : %.2lf\n\n", surface);
            break;
        case (Perimeter):
            base_surface_perimeter = 2 * PI * r;
            printf("Base Surface Perimeter of CYLINDER : %.2lf\n\n",base_surface_perimeter);
            break;
        case (Volume):
            volume = PI * r * r * h;
            printf("Volume of a CYLINDER : %.2lf", volume);
            break;
    }

    return 1;
}

int calculate(int (*shapetype)(),int (*calctype)()){
    int type,calc,a=1;
    type = shapetype();
    calc = calctype();

    switch(type){
        case (Triangle):
            printf("Please enter three sides of Triangle:\n");
            do{
                a = calc_triangle(calc);
            } while(a == -1);
            break;
        case (Quadrilateral):
            printf("Please enter four sides of Quadrilitreal\n:");
            do{
                a = calc_quadriliteral(calc);
            } while(a == -1);
            break;
        case (Circle):
            printf("Please enter the radius of Circle:\n");
            do{
                a = calc_circle(calc);
            } while(a == -1);
            break;
        case (Pyramid):
            do{
                a = calc_pyramid(calc);
            } while(a == -1);
            break;
        case (Cylinder):
            printf("Please enter radius and height of Cylinder : \n");
            do{
                a = calc_cylinder(calc);
            } while(a == -1);
            break;
    }
    
    return 1;
    //type = shapetype();
    //calc = calctype();

}

int main(){
    do{

    }while(calculate(select_shape, select_calc));
    
    
    return 0;
}