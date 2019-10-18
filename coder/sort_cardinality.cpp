#include "sort_common.h"
#include<chrono>
#include<thread>


struct Student
{
    int college;//院
    int department;//系
    int number;//学号

    bool less_than_college(const Student& s) const
    {
        return college <= s.college ? true : false;
    }

    bool same_college(const Student& s) const
    {
        return college == s.college;
    }

    bool less_than_department(const Student& s) const
    {
        return department <= s.department ? true : false;;
    }

    bool same_department(const Student&s ) const
    {
        return department == s.department;
    }

    bool less_than_number(const Student& s) const
    {
        return number <= s.number ? true : false;;
    }
};

bool operator <= (const Student& l, const Student& r)
{
    if(l.college == r.college && l.department == r.department && l.number == r.number)
        return true;

    if(l.college < r.college)
        return true;
    
    if(l.college == r.college && l.department < r.department)
        return true;
        
    if(l.college == r.college && l.department == r.department && l.number < r.number)
        return true;

    return false;
}

std::ostream& operator << (std::ostream& os, const Student &s)
{
    //os << "{ c: " << s.college << " d: " << s.department << " n: " << s.number << " }";
    os << "{" << s.college << "," << s.department << "," << s.number << "}";
    return os;
}

typedef std::list<Student> list_student;


template<typename array_type>
void printf_array_student(array_type& ls)
{
    std::for_each(ls.begin(),ls.end(),[](const Student& i){
        std::cout << i << "; ";
    });
    
    std::cout << std::endl;
}

int quick_sort(
    list_student& ls,
    list_student::iterator left,
     list_student::iterator right, 
     std::function<bool(const Student&, const Student& )> less_than_function)
{
    int run_cnt = 0;

    //拷贝左右游标，来遍历
    list_student::iterator left_cp = left;
    list_student::iterator right_cp = right;

    //每次取第一个为key
    Student key = *left;//大于key到放右边，小于key到放左边
    while(left_cp != right_cp)
    {
        //std::cout << "------------- " << std::endl;  
        //printf_array_student(ls);

        run_cnt ++;
        //std::cout << "key " << key << " left " << *left_cp << " right: " << *right_cp << std::endl;

        //从右边找到第一个小于key的
        while((left_cp != right_cp) && (less_than_function(key, *right_cp))) //*right_cp > key
            right_cp --;
        
        //std::cout << "find right: " << *right_cp << std::endl;
        if(left_cp != right_cp)
            *left_cp = *right_cp;//把找到小于key的，放到左边

        //从左边开始，找到第一个大于key的
        while((left_cp != right_cp) && (less_than_function(*left_cp,key)))//*left_cp <= key
            left_cp++;

        //std::cout << "find left " << *left_cp << std::endl;
        if(left_cp != right_cp)
            *right_cp = *left_cp;//把找到小于key的，放到左边

        *left_cp = key;
    }

    //printf_array_student(ls);
    //std::cout << "========= " << std::endl;  
    //递归把左边和右边的，继续做快速排序
    if(left != left_cp)
        run_cnt += quick_sort(ls, left, --left_cp, less_than_function);
    if(right != right_cp)
        run_cnt += quick_sort(ls, ++right_cp, right, less_than_function);
    
    return run_cnt;
}


int main()
{
    std::cout << "cardinality sort -------------\n";

    std::list<Student> ls = {
        {1,1,100},
        {2,2,1},
        {3,3,300},
        {1,1,101},
        {1,2,99},
        {2,2,222},
        {2,1,222},
        {3,1,11}
    };

    auto left = ls.begin();
    auto right = ls.end();
    right--;
    //先按照院排序
    quick_sort(
        ls,
        left,
        right,
        [](const Student& l, const Student& r)
        {
            bool ret = l.less_than_college(r);
            //std::cout << "l: " <<l << (ret ? "<=" : ">") << r <<std::endl; 
            return ret;
        });
    printf_array_student(ls);

    //在相同 院 内，按照 系 排序
    left = ls.begin();
    for(auto index = left; index != ls.end(); index ++)
    {
        auto next = index;
        next++;

        if(next == ls.end() || !index->same_college(*next))
        {
            right = next;
            right --;
            
            quick_sort(
                ls,
                left,
                right,
                [](const Student& l, const Student& r)
                {
                    bool ret = l.less_than_department(r);
                    //std::cout << "l: " <<l << (ret ? "<=" : ">") << r <<std::endl; 
                    return ret;
                });

            left = next;
        }

    }
    
    printf_array_student(ls);

    //在相同 系 内，按照 学号 排序
    left = ls.begin();
    for(auto index = left; index != ls.end(); index ++)
    {
        auto next = index;
        next++;

        if(next == ls.end() || !index->same_department(*next))
        {
            right = next;
            right --;
            
            quick_sort(
                ls,
                left,
                right,
                [](const Student& l, const Student& r)
                {
                    bool ret = l.less_than_number(r);
                    //std::cout << "l: " <<l << (ret ? "<=" : ">") << r <<std::endl; 
                    return ret;
                });

            left = next;
        }
    }

    printf_array_student(ls);

    ls = {
        {1,1,100},
        {2,2,1},
        {3,3,300},
        {1,1,101},
        {1,2,99},
        {2,2,222},
        {2,1,222},
        {3,1,11}
    };

    //一次比较出Student的大小，一次排序解决
    left = ls.begin();
    right = ls.end();
    right--;
    //先按照院排序
    quick_sort(
        ls,
        left,
        right,
        [](const Student& l, const Student& r)
        {
            bool ret = l <= r;
            //std::cout << "l: " <<l << (ret ? "<=" : ">") << r <<std::endl; 
            return ret;
        });

    printf_array_student(ls);

    return 0;
}