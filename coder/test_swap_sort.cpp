#include "test_common.h"

//冒泡排序
template<typename array_type>
int bubble_sort(array_type& ls)
{
    int run_cnt = 0;

    auto ls_it = ls.begin();
    auto buble_index = ls.end();//记录可以冒泡到的位置，此位置之后的队列为有序的
    //把大的冒到后面，可冒泡到位置前移
    for(; ls_it != buble_index; buble_index--)
    {
        auto ls_it_this = ls_it;
        auto ls_it_next = ls_it_this;
        ls_it_next++;
        //俩俩比较，大的交换。从而得到最后的一个为最大值
        for(; ls_it_next != buble_index; ls_it_this++, ls_it_next++)
        {
            if(*ls_it_this > *ls_it_next)//前面的比后面的大，则交换
            {
                //std::cout << *ls_it_this << " bubble behind " << *ls_it_next  << std::endl;
                int tmp = *ls_it_this;
                *ls_it_this = *ls_it_next;
                *ls_it_next = tmp;
            }

            run_cnt++;
        }
        
        //printf_array_int(ls);
    }

    return run_cnt;
}

template<typename array_type>
int quick_sort(array_type& ls,typename array_type::iterator left, typename array_type::iterator right)
{
    int run_cnt = 0;

    //拷贝左右游标，来遍历
    typename array_type::iterator left_cp = left;
    typename array_type::iterator right_cp = right;

    //每次取第一个为key
    int key = *left;//大于key到放右边，小于key到放左边
    while(left_cp != right_cp)
    {
        //std::cout << "------------- " << std::endl;  
        //printf_array_int(ls);

        run_cnt ++;
        //std::cout << "key " << key << " left " << *left_cp << " right: " << *right_cp << std::endl;

        //从右边找到第一个小于key的
        while((left_cp != right_cp) && (*right_cp > key))
            right_cp --;
        
        //std::cout << "find right: " << *right_cp << std::endl;
        if(left_cp != right_cp)
            *left_cp = *right_cp;//把找到小于key的，放到左边

        //从左边开始，找到第一个大于key的
        while((left_cp != right_cp) && (*left_cp <= key))
            left_cp++;

        //std::cout << "find left " << *left_cp << std::endl;
        if(left_cp != right_cp)
            *right_cp = *left_cp;//把找到小于key的，放到左边

        *left_cp = key;
    }

    //递归把左边和右边的，继续做快速排序
    if(left != left_cp)
        run_cnt += quick_sort(ls, left, --left_cp);
    if(right != right_cp)
        run_cnt += quick_sort(ls, ++right_cp,right);
    
    return run_cnt;
}

int main()
{
    int run_cnt = 0;
    std::cout << "swap sort ---------" << std::endl;
    list_int ls = {2,4,1,6,8,7,9,3,5,0};
    run_cnt = bubble_sort(ls);
    std::cout << "run count :" << run_cnt << std::endl;
    //printf_array_int(ls);
    is_asc_array_int(ls);

    ls = ls_data;//
    auto left = vc_data.begin();
    auto right = vc_data.end();
    right --;
    run_cnt = quick_sort(vc_data, left, right);
    std::cout << "run count :" << run_cnt << std::endl;
    //printf_array_int(ls);
    is_asc_array_int(ls);

    return 0;
}