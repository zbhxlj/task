int a;  // 外部变量定义

int Func(float b);  //函数声明

int Algorithm(float c, float b){  //函数定义
    
// 局部变量声明 以及赋值   
    int c;   // int
    c = 123;  

    long d;  //long
    d = 12L;

    float e;   //float
    e = 3.563;

    char str[9];  // 数组

    str = "asd";  // 字符串

    char ch;    //字符

    ch = 'c';  


// 运算符
    c = a * b / a + b - b;  //四则运算  和 赋值

    c = a == b;  // ==  和 = 
    a != b;  // !=
    a >= b;  // >=
    a <= b;  // <=
    a > b;  // >
    a < b;  // <       
    a && b;
    a || b;

    a = a ||  b && a < a > b < b <= a >= b != c + a - b * c / d ;


// 语句
    while(a > b) {
        a = b;
    } //while语句

    if(a > b) {
        b = c;
    }  // if语句

    if(a > b){
        b = c;
    }
    else {
        c = b;
    } // if else 语句

    for(a = 0; a < 8; a = a + 1){
        b = b + 1;
    }
        
    
    return 1; // return 语句

    break;  //break 语句

    continue;  //continue 语句


    if(a > b) {
        if(a > b){
            b = a;
        }
        else {
             a = b;
        }
    } // if 的嵌套
        

    while(a != 0) {
        while(b = c) {
            b = c;
        }
    } //while的嵌套
        
}
float x, y;