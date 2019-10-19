#include "code_common.h"

//n的阶乘
int get_factorial(int n)
{
    if(n <=1)
    {
        return 1;
    }
    
    return get_factorial(n-1) * n; //尾递归
}

//尾递归可以用循环的方式实现
int get_factorial2(int n)
{
    if(n <=1)
    {
        return 0;
    }
    
    int ret = 1;
    for(int i = 2;i <= n; i++)
    {
        ret *= i;
    }
    
    return ret;
}

//回文串判断，忽略大小写
int palindrome_check(const std::string& str, int left, int right)
{
    int index = -1;
    if(left >= right)
    {
        return -1;
    }
    char left_char = ::tolower(str.at(left));
    char right_char = ::tolower(str.at(right));
    if(left_char != right_char)
        return left;

    return palindrome_check(str,++left,--right);
}

int palindrome_check2(const std::string& str)
{
    if(str.length() <= 1)
        return -1;

    int left = 0, right = str.length()-1;
    for( ; left < right; left++, right--)
    {
        char left_char = ::tolower(str.at(left));
        char right_char = ::tolower(str.at(right));
        
        //std::cout << "left " << left_char << " right " << right_char << std::endl;
        if(left_char != right_char)
            return left;
    }

    return -1;
}



int main()
{
    std::cout << "get_factorial(5) = " << get_factorial(5) << std::endl;
    std::cout << "get_factorial2(5)= " << get_factorial2(5) << std::endl;

    std::string str = "zxcvbnmnbvcxz";
    std::cout   << str
                << " is " 
                //<< (palindrome_check(str,0,str.length()-1) == -1 ? "a" : "not" )
                << (palindrome_check2(str) == -1 ? "a" : "not" )
                << " palindrome string" 
                << std::endl;

    return 0;
}