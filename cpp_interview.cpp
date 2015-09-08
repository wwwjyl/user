/*
 * c++ questions and answer.
 *
 *
 * */
#include <stdio.h>
#include <iostream>
using namespace std;


#include <arpa/inet.h>

#include <vector>


/* for question 5*/
void UpperCase( char str[] ) // 将str 中的小写字母转换成大写字母
{
    for( size_t i=0; i<sizeof(str)/sizeof(str[0]); ++i )
    {
        if( 'a'<=str[i] && str[i]<='z' )
        {
            str[i] -= ('a'-'A' );
        }
    }
}

/*for question 7*/
struct Test
{
    Test(int ) { }
    Test() { }
    void fun() { }
};

/*for question 11*/
struct CLS
{
    int m_i;
    CLS(int i): m_i( i ) {   }
    CLS()
    {
        CLS( 0 );
    }
};

/*for question 14*/
void* mymemcpy1(void* dst, const void* src, size_t count)
{
    char* pdst = (char *)dst;
    const char* psrc = (const char *)src;

    if (NULL == dst || NULL == src || count <= 0)
        return NULL;

    /*forward*/
    if (src > dst)
    {
        while(0 != count--)
            *pdst++ = *psrc++;
    }
    /*reverse*/
    else if (src < dst)
    {
        pdst = pdst + count;
        psrc = psrc + count;
        while(0 != count--)
            *pdst-- = *psrc--;
    }

    return dst;
}


/*for question 14 new idea*/
void* mymemcpy( void* dest, const void* src, size_t count ) 
{ 
    char* d = (char*)dest; 
    const char* s = (const char*)src; 
    //   int n = (count + 7) / 8; // count > 0 assumed 
    int n = count >> 3; 
    switch( count & 7 ) 
    { 
        do {   *d++ = *s++; 
            case 7: *d++ = *s++; 
            case 6: *d++ = *s++; 
            case 5: *d++ = *s++; 
            case 4: *d++ = *s++; 
            case 3: *d++ = *s++; 
            case 2: *d++ = *s++; 
            case 1: *d++ = *s++; 
            case 0: ;
        } while (--n > 0); 
    } 

    return dest; 
}



int main()
{
/*
 * 1.c++vector iterator编译器classnull1、int a=5，则 ++(a++)的值是（）
 * A、5      B、   6          C、7       D、逻辑错误
 * a++返回的是一个临时变量，这里是右值，不能再前面++了
 * */
    
    int y = 5;
    //++(y++); /*16:11: error: lvalue required as increment operand*/
    //++ ++y;  /*its ok*/




/*
 *2.下面的代码输出什么？
 *取地址运算符比+运算符的优先级要高 
 * 
 *&a+1不是首地址+1， 系统会认为加一个a数组的偏移， 是偏移了一个数组的大小（本例是5个int ）
 * */
    int  z[5] = {1, 2, 3, 4, 5};  
    int  *ptr = (int *)(&z+1);  
    printf("%d %d\n",*(z+1),*(ptr-1));

/*
 *3.以下三条输出语句分别输出什么？
 * 答：分别输出false,false,true。str1和str2都是字符数组，每个都有其自己的存储区，它们的值则是各存储区首地址，
 *    不等；str3和str4同上，只是按const语义，它们所指向的数据区不能修改。str5和str6并非数组而是字符指针，
 *       并不分配存储区，其后的“abc”以常量形式存于静态数据区，而它们自己仅是指向该区首地址的指针，所以相等。
 * */
    char str1[] = "abc";
    char str2[] = "abc";

    const char str3[] = "abc";
    const char str4[] = "abc";

    const char* str5 = "abc";
    const char* str6 = "abc";


    printf("%p -- %p\n", str1, str2);
    printf("%p -- %p\n", str3, str4);
    printf("%p -- %p\n", str5, str6);
    
    cout << boolalpha << ( str1==str2 ) << endl; 
    cout << boolalpha << ( str3==str4 ) << endl;
    cout << boolalpha << ( str5==str6 ) << endl;

/*
 *4.下面代码的输出是什么？
 *
 * 浮点数的 1.0f 在内存里是这样表示的： 
 * 0011 1111 1000 0000 00000000 00000000 
 * 这个32位二进制数被当作整数输出就是： 
 * 1065353216 
 * 而整数的 1 在内存里是这样表示的： 
 * 0000 0000 0000 0000 00000000 00000001 
 * 所以 (int)a != (int&)a 
 *
 * 浮点的0和整数的0 在内存里都是： 
 * 0000 0000 0000 0000 00000000 00000000 
 * 所以 (int)b == (int&)b 
 * */
    float a = 1.0f;
    cout<< (int)a <<endl;
    cout<< (int&)a <<endl;
    cout << boolalpha << ( (int)a==(int&)a ) << endl; 

    float b = 0.0f;
    cout<< (int)b <<endl;
    cout<< (int&)b <<endl;
    cout << boolalpha << ( (int)b==(int&)b ) << endl; 


/*
 *5.以下代码中的两个sizeof用法有问题吗？
 * sizeof 使用在字符串数组是 包含'\0'
 * */
    char str[] = "aBcDe";

    cout << "str字符长度为: " << sizeof(str)/sizeof(str[0]) << endl;

    UpperCase( str );
    cout << str << endl;

/*
 *6.以下代码有什么问题？ 
 * 
 *error: operands to ?: have different types ‘int’ and ‘const char*’
 * */
    //cout<< (true?1:"0") <<endl;

    cout<< (true?1:'0') <<endl; /*it's ok!*/
    /*表达式返回的类型为double型，%d输出肯定不对，仅仅输出了double型的阶码中的最后4字节，此处为0*/
    cout << sizeof((true?1:1.3)) << endl;
    printf("%d\n",(true?1:1.3)); 
    
    printf("%lf\n",(true?1:1.3)); 
    printf("%08x\n",htonl((true?1:1.3))); 


    
/*
 * 7.以下代码有什么问题？
 *
 * error: request for member ‘fun’ in ‘t’, which is of non-class type ‘Test()’
 *
 *类是结构体的扩展,在类中封装了对数据成员的操作,缺省的成员为私有的,而结构体为公有的,
 *这就是它们的区别,对构造函数的调用,如果没有参数,是不需要加上括号的,如果加了括号,就不
 *是定义一个对象了,而是声明了一个函数,返回该类型,所以上面的Test   b(),实际上是调用一个函数名为b,
 *返回类型为Test的函数,而不是创建了一个对象b,去掉括号后,就是调用的没有形参的构造函数。
 * */
    Test r(1);
    r.fun();
    Test t();
    //t.fun();


/*
 *8.非C++内建型别A和B, 在哪几种情况下B能隐式转化为A? (待测试) 
 * #http://blog.csdn.net/lingfengtengfei/article/details/12347001
 *第一种：classB: public A {…}
 第二种：classB:
 {
 Operator A();
 }
 第三种：class A
 {
 A （const B &）
 }
 第四种：A&operator ＝（const B & ）
 赋值操作，不是正宗的隐式类型转换，但可以勉强算一个。
 * */


/*9.以下代码能够编译通过吗，为什么？
 *  warning: unused variable ‘str33’ [-Wunused-variable]
 *  size2 是动态确定的
 * */    
    unsigned int const size1 = 2;
    char str11[ size1 ];
    unsigned int temp = 0;
    cin >> temp;
    unsigned int const size2 = temp;
    char str22[ size2 ];
    char str33[ size2 ] = { 0 };


/*
 * 10.以下反向遍历array数组的方法有什么错误？
 *
 *答：首先数组定义有误，应加上类型参数：vector<int> array。其次vector::size_type 被定义为
 unsigned int，即无符号数，这样做为循环变量的i 为0 时再减1 就会变成最大的整数，导致循环失去控
 制。
 * */
    #if 0
    vector array;

    array.push_back( 1 );
    array.push_back( 2 );
    array.push_back( 3 );
    for( vector::size_type i=array.size()-1; i>=0; --i )    // 反向遍历array数组
    {
        cout << array[i] << endl;
    }
    #endif


/*
 *11.以下代码中的输出语句输出吗，为什么？
 *
 * CLS obj；这里已经为obj分配了内存，然后调用默认构造函数，但是默认构造函数还未执行完，却调用了另一个构造函数，
 * 这样相当于产生了一个匿名的临时CLS对象，它调用CLS(int)构造函数，将这个匿名临时对象自己的数据成员m_i初始化为0；
 * 但是obj的数据成员并没有得到初始化。于是obj的m_i是未初始化的，因此其值也是不确定的
 *
 * */
    CLS obj;
    cout << obj.m_i << endl;

/*
 * 12.C++中的空类，默认产生哪些类成员函数？
 * ++ 空类默认产生的类成员函数:缺省构造函数,拷贝构造函数,析构函数,赋值运算符,取址运算符,取址运算符 const
 *
 * */
#if 0
    class class1
    {
        public:
            class1(){}//缺省构造函数

            class1(const class1&){}//拷贝构造函数

            ~class1(){}//析构函数

            class1&operator=(const class1&){}//赋值运算符

            class1*operator&(){}//取址运算符

            const class1*operator&()const{}//取址运算符 const
    };

    //空类class2会产生class1一样的成员函数

    class class2
    {
    };

    class2 obj1;//缺省构造函数

    class2 obj2;

    obj1=obj2;//赋值运算符

    &obj2;//取址运算符

    class2 obj3(obj1);//拷贝构造函数

    class2 const obj4;
    &obj4;//取址运算符 const

#endif

    


/*
 *13.以下代码有什么问题吗？
 *小心容器内容插入删除导致的迭代器失效, 
 *问题：少删除连续元素后在一个元素
 *
 * for( vector<int>::iterator itor=array.begin(); itor!=array.end(); )
    {
        if( 2 == *itor )
            itor=array.erase( itor );
        else
            ++itor;
    }
 * */
    typedef vector<int> IntArray;

    IntArray array13;
    array13.push_back( 1 );
    array13.push_back( 2 );
    array13.push_back( 2 );
    array13.push_back( 3 );

    cout << "test vector erase" << endl;
    // 删除array数组中所有的2
    for( IntArray::iterator itor=array13.begin(); itor!=array13.end(); ++itor )
    {
        if( 2 == *itor )
        {
            array13.erase( itor );
        }
        cout << *itor << endl;

    }


/*
 *14.写一个函数，完成内存之间的拷贝。[考虑问题是否全面]
 * 
 * 注意是否重叠
 * 注意参数正确否
 * 注意++操作的类型
 *
 * */

    return 0;
}


