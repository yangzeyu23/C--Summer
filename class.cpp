#include <iostream>
using namespace std;


//创建类
class Box
{
    public:
        double length;
        double breadth;
        double height;
};

//声明对象
class Box Box1, Box2, Box3[1001],  *pt = &Box1;


//访问类的成员
int Box_main()
{
    Box box1;
    box1.length = 5.0;
    box1.breadth = 3.0;

    Box *point = &box1;
    pt->height = 2.0;
}


//成员函数
class CASE 
{
    public:
        double length;
        double breadth;
        double height;

        double getArea();

        double getVolume()
        {
            return length * breadth * height;
        }
};

//内联函数
inline double CASE::getArea()
{
    return length * breadth;
}


/* ------------------------------------------------
构造函数
在每次创建类的新对象时执行，名称与类的名称完全相同，不会返回任何类型，包括void。构造函数可以用于为某些成员变量设置初始值。
-------------------------------------------------*/
class Student 
{
    private:
        char* _name;
        int _age;
        float _score;

    public:
        Student(char* name, int age, float score);
        //声明构造函数

        void show(); //声明普通成员函数
};

//定义构造函数
Student::Student(char* name, int age, float score)
{
    _name = name;
    _age = age;
    _score = score;
} 

//定义普通成员函数
void Student::show()
{
    cout << "Name: " << _name << endl;
    cout << "Age: " << _age << endl;
    cout << "Score: " << _score << endl;
}  

int Student_main()
{
    Student student("Alice", 20, 95.5f);//创建对象，调用构造函数并传参

    student.show();   //调用成员函数

    Student *p_stu =new Student("Bob", 22, 88.0f); 
    p_stu->show();   //通过指针调用成员函数

    return 0;
}



/*-------------------------------------------------
析构函数
在每次删除所创建的对象时执行。名称与类的名称相同，但前面有一个波浪符号(~)。析构函数不接受任何参数，也不返回任何值。它通常用于释放资源。
--------------------------------------------------*/
class Line
{
    public:
        void SetLength(double len);
        double GetLength(void);

        Line(); //构造函数
        ~Line(); //析构函数

    private:
        double length;
};

Line::Line(void)
{
    cout << "Line object created." << endl;
}

Line::~Line(void)
{
    cout << "Line object deleted." << endl;
}

void Line::SetLength(double len)
{
    length = len;
}

int Line_main()
{
    Line line; //创建对象，调用构造函数
    line.SetLength(5.0);
    cout << "Length of line : " << line.GetLength() << endl;

    return 0; 
    //当程序结束时，Line对象被销毁，析构函数被调用
}


/*-------------------------------------------------
拷贝构造函数
拷贝构造函数用于创建一个新对象，该对象是现有对象的副本。它接受一个同类型的对象作为参数，并将其成员变量复制到新对象中。
--------------------------------------------------*/



/*-------------------------------------------------
友元函数
友元函数是一个非成员函数，但可以访问类的私有和保护成员。它通常用于需要访问类内部数据但不属于类的操作。
--------------------------------------------------*/
class BoxFriend
{
    private:
        double width;

    public:
        friend void printWidth(BoxFriend box); //友元函数声明(注意不是任何类的成员函数)

        void setWidth(double wid)
        {
            width = wid;
        }
};

void printWidth(BoxFriend box)
{
    //可以访问Box的私有成员
    cout << "Width of box : " << box.width << endl;
} 

int BoxFriend_main()
{
    BoxFriend box;
    box.setWidth(10.0); //调用成员函数设置宽度

    printWidth(box);    //调用友元函数

    return 0;
}


/*-------------------------------------------------
this 指针
this 指针是所有成员函数的隐式参数，指向当前对象的地址。它在成员函数中使用，允许访问当前对象的成员变量和成员函数。友元函数不能使用 this 指针，因为它不是类的成员函数。
--------------------------------------------------*/
class BoxThis
{
    private:
        double length;
        double breadth;
        double height;

    public:
        BoxThis(double l, double b, double h)
        {
            length = l;
            breadth = b;
            height = h;
        }

        double volume()
        {
            return length * breadth * height;
        }

        int compare(BoxThis box)
        {
            return this->volume() > box.volume() ;
        }

};

int BoxThis_main()
{
    BoxThis box1(3.0, 4.0, 5.0);
    BoxThis box2(2.0, 6.0, 4.0);

    if (box1.compare(box2))
    {
        cout << "Box1 is larger than Box2." << endl;
    }
    else
    {
        cout << "Box2 is larger than or equal to Box1." << endl;
    }

    return 0;
}

//指向类指针：
int Boxcompare_main()
{
    BoxThis *box1 = new BoxThis(3.0, 4.0, 5.0);
    BoxThis *box2 = new BoxThis(2.0, 6.0, 4.0);

    BoxThis *ptrbox;   //declare a pointer to BoxThis
    
    ptrbox = box1;    //保存第一个对象的地址
    cout << "Box1 volume: " << box1->volume() << endl;

    ptrbox = box2;    //保存第二个对象的地址
    cout << "Box2 volume: " << box2->volume() << endl;

    return 0;
}


/*-------------------------------------------------
静态成员
静态成员属于类本身，而不是类的任何特定对象。它们在所有对象之间共享，并且可以通过类名直接访问。静态成员通常用于存储类的公共数据或计数器。
--------------------------------------------------*/
class BoxStatic
{
    private:
        double length;
        double breadth;
        double height;

    public:
        static int objectCount; //静态成员变量

        BoxStatic(double l, double b, double h)
        {
            length = l;
            breadth = b;
            height = h;
            objectCount++; //每次创建对象时增加计数
        }

        static int getObjectCount() //静态成员函数
        {
            return objectCount;
        }
};

int BoxStatic::objectCount = 0; //初始化静态成员变量

int BoxStatic_main()
{
    BoxStatic box1(3.0, 4.0, 5.0);
    BoxStatic box2(2.0, 6.0, 4.0);

    cout << "Total objects created: " << BoxStatic::getObjectCount() << endl;

    return 0;
}

//实际上，类的静态函数就是增加了类的访问权限的全局函数。
//静态函数可以继承和覆盖，但不能是虚函数。
//函数的实现使用 static 修饰，则只能在本cpp文件中使用，不会同其他cpp文件的同名函数冲突。不要在头文件中声明 static 的全局函数，不要在源文件中声明非 static 的全局函数。




/*-------------------------------------------------
继承
继承允许一个类（派生类）从另一个类（基类）继承属性和方法。派生类可以扩展或修改基类的功能。
--------------------------------------------------*/
// 基类
class Shape 
{
   public:
      void setWidth(int w)
      {
         width = w;
      }
      void setHeight(int h)
      {
         height = h;
      }
   protected:
      int width;
      int height;
};

class PaintCost 
{
   public:
      int getCost(int area)
      {
         return area * 70;
      }
};

// 多继承派生类
class Rectangle: public Shape, public PaintCost
{
   public:
      int getArea()
      { 
         return (width * height); 
      }
};

int Rectangle_main()
{
   Rectangle Rect;
   Rect.setWidth(5);
   Rect.setHeight(7);
   cout << "Total area: " << Rect.getArea() << endl;

   int area = Rect.getArea();
   cout << "Total paint cost: $" << Rect.getCost(area) << endl;

   return 0;
} 



/*-------------------------------------------------
动态内存
动态内存分配允许在运行时分配和释放内存。C++ 提供了 new 和 delete 操作符来管理动态内存。
--------------------------------------------------*/
class box
{
   public:
      box() { 
         cout << "调用构造函数！" <<endl; 
      }
      ~box() { 
         cout << "调用析构函数！" <<endl; 
      }
};

int box_main( )
{
   box * myBoxArray = new box[4];
   delete [] myBoxArray;   
   return 0;
}