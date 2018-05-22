#include <iostream>
#include <math.h>
#include <string.h>
#define PI 3.1415926

using namespace std;


double abc(double number)
{
    return number>0?number:(number*(-1));

}


class Shape
{
public:
    Shape(){};
    virtual double calArea(){};
    virtual double calPerimeter(){};
    virtual void show(){};
protected:
    double area;
    double perimeter;
};

class Rect:public Shape
{
public:
    Rect(double x1,double y1, double x2, double y2);
    double calArea(){area = abc((x_1-x_2)*abc(y_1-y_2));return area;};
    double calPerimeter(){perimeter = 2 * (abc(x_1-x_2)+abc(y_1-y_2));return perimeter;};
    void show(){cout<<area<<' '<<perimeter<<endl;}
protected:
    double x_1;
    double y_1;
    double x_2;
    double y_2;
};

Rect::Rect(double x1,double y1, double x2, double y2)
{
    x_1 = x1;
    y_1 = y1;
    x_2 = x2;
    y_2 = y2;
}

class Circle:public Shape
{
public:
    Circle(double xx,double yy, double rr):x(xx),y(yy),r(rr){};
    double calArea(){area = PI * r * r;return area;};
    double calPermimeter(){perimeter = 2.0 * PI * r;return perimeter;};
    void show(){cout<<area<<' '<<perimeter<<endl;}
protected:
    double x;
    double y;
    double r;
};

class Triangle:public Shape
{
public:
    Triangle(double x1, double y1, double x2,double y2,double x3,double y3):
        x_1(x1),y_1(y1),x_2(x2),y_2(y2),x_3(x3),y_3(y3){};
    double calArea();
    double calPerimeter();
    void show(){cout<<area<<' '<<perimeter<<endl;}
protected:
    double x_1;
    double y_1;
    double x_2;
    double y_2;
    double x_3;
    double y_3;
};

double Triangle::calArea()
{
    double a = sqrt((x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2));
    double b = sqrt((x_1-x_3)*(x_1-x_3)+(y_1-y_3)*(y_1-y_3));
    double c = sqrt((x_2-x_3)*(x_2-x_3)+(y_2-y_3)*(y_2-y_3));
    double p = (a + b + c) / 2.0;
    area = sqrt(p*(p-a)*(p-b)*(p-c));
    return area;
}

double Triangle::calPerimeter()
{
    perimeter =    sqrt((x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2))
                + sqrt((x_1-x_3)*(x_1-x_3)+(y_1-y_3)*(y_1-y_3))
                + sqrt((x_2-x_3)*(x_2-x_3)+(y_2-y_3)*(y_2-y_3));
    return perimeter;
}


int main()
{
    int number;
    char type[10];
    cin>>number;
    for(int i=0; i<number; i++)
    {
       cin>>type;
       if(strcmp(type,"Rect")==0)
       {
          double x1,y1,x2,y2;
          cin>>x1>>y1>>x2>>y2;
          Rect rect(x1,y1,x2,y2);
          rect.calArea();
          rect.calPerimeter();
          rect.show();
       }
       else if(strcmp(type,"Circle")==0)
       {
          double x,y,r;
          cin>>x>>y>>r;
          Circle circle(x,y,r);
          circle.calArea();
          circle.calPerimeter();
          circle.show();
       }
       else if(strcmp(type,"Triangle")==0)
       {
          double x1,y1,x2,y2,x3,y3;
          cin>>x1>>y1>>x2>>y2>>x3>>y3;
          Triangle triangle(x1,y1,x2,y2,x3,y3);
          triangle.calArea();
          triangle.calPerimeter();
          triangle.show();
       }
    }
    return 0;
}
