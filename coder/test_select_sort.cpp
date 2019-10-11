#include "test_common.h"


template<typename array_type>
int select_sort(array_type& in, array_type& out)
{
    int run_cnt = 0;
    auto item_in = in.begin();
    out.insert(out.begin(), *item_in);
    
    for(++item_in ; item_in != in.end() ; item_in ++)
    {
        auto item_out = out.begin();
        for( ; item_out != out.end() ; item_out ++)
        {
            run_cnt ++;
            //头插，第一个小于自己的
            //尾插，可以从最后一个开始遍历
            if(*item_in < *item_out)
            {
                break;
            }
        }

        //if(item_out == out.end())
        //    std::cout << "insert: " << *item_in << " on last;" << std::endl;
        //else
        //    std::cout << "insert: " << *item_in << ", front:" << *item_out << std::endl;
            
        out.insert(item_out,*item_in);
    }

    return run_cnt;
}

template<typename array_type>
int select_sort(array_type& in)
{
    int run_cnt = 0;
    auto select_it = in.begin();
    
    //从第二个开始判断
    for(; select_it != in.end() ; select_it ++)
    {
        //每次都把当前循环的第一个作为初始的最小的位置
        auto least_index = select_it;
        for(auto index = select_it+1; index != in.end() ; index ++)
        {
            run_cnt ++;
            if(*index < *least_index)
            {
                //每次都记录当前的最小值
                least_index = index;
            }
        }
            
        //和循环的第一个交换
        int tmp = *least_index;
        *least_index = *select_it;
        *select_it = tmp;

        //printf_array_int(in);
    }

    return run_cnt;
}


int main()
{
    std::cout << "select_sort 1 -------------" << std::endl;
    vector_int in = vc_data;    
    vector_int out;
    std::cout << "run count:" << select_sort(in,out) << std::endl; 
    is_asc_array_int(out);
    //printf_array_int<list_int>(out);


    std::cout << "select_sort 2 -------------" << std::endl;
    vc_data = {1,21,4,6,5,31,22};
    std::cout << "run count:" << select_sort(vc_data) << std::endl;        
    is_asc_array_int(vc_data);
    //printf_array_int<vector_int>(vc_data);


    // std::cout << "merge_list -------------" << std::endl;
    // list_int r = {7,8,9,10};
    // ls.clear();
    // merge_list(out,r,ls);
    // std::cout << "merge " << std::endl;
    // printf_array_int<list_int>(ls);



    return 0;
}