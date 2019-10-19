#include "code_common.h"


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


//合并有序队列
template<typename array_type>
int merge_sort_array_int(
    typename array_type::iterator left_it, int left_cnt, 
    typename array_type::iterator right_it, int right_cnt, 
    array_type& out, typename array_type::iterator insert_it)
{
    //printf_array_int<array_type>(left_it, left_cnt);
    //printf_array_int<array_type>(right_it, right_cnt);

    int run_cnt = 0;
    
    int left_loop = 0;
    int right_loop = 0;
    //从头开始合并，直到其中一个遍历完，则另一个直接从遍历位置 插入到队尾
    while(left_loop != left_cnt && right_loop != right_cnt)
    {
        run_cnt ++;

        //std::cout << "left " << *left_it << " right "  << *right_it << std::endl; 
        if(*left_it < *right_it)//如果左边小于右边，则把左边到插入合并队列
        {
            *insert_it = *left_it;//返回插入后到位置
            left_loop ++;   //遍历递增
            left_it++;
        }
        else    //把右边的插入到合并队列
        {
            *insert_it = *right_it;//返回插入后到位置
            right_it++;
            right_loop++;
        }

        insert_it ++;
        //printf_array_int(out);
    }

    if(left_loop == left_cnt)   //如果左边到遍历完，则把右边剩余到直接插入到队尾
    {
        run_cnt ++;

        while (right_loop != right_cnt)
        {
            *insert_it = *right_it;
            insert_it ++;
            right_it++;
            right_loop++;
        }
    }
    else if(right_loop == right_cnt)    //如果右边到遍历完，则把左边到剩余队列，直接插入到队尾
    {
        run_cnt ++;

        while(left_loop != left_cnt)
        {
            *insert_it = *left_it;
            insert_it ++;
            left_loop ++;
            left_it++;
        }
    }

    return run_cnt;
}

//归并排序
int merge_sort(vector_int& vc)
{
    //适合在可以O(1) 时间访问到队列到数据结构中归并排序，否则还需要额外到时间来定位，分组
    int run_cnt = 0;

    int cnt = vc.size();
    vector_int vc_tmp(cnt, 0);//构造一个同样大小到队列，缓存

    //循环分组归并，按照2到倍数扩大分组，直到只剩两组进行归并
    int space = 2;
    while(1)
    {
        int perfect_merge_index = cnt - (cnt % space);
        std::cout << " space " << space << ", perfect index " << perfect_merge_index << std::endl;
        int st = space /2;
        int i = 0;
        //正常合并，可以完美分组的
        for(;i < perfect_merge_index ; i += space)
        {
            int left = i;
            int right = left + st;
            //std::cout << " i " << i << " left " << left << " right "  << right << std::endl; 
            //合并
            vector_int::iterator left_it = vc.begin() + left;
            vector_int::iterator right_it = vc.begin() + right;

            //std::cout << "left " << *left_it << " right "  << *right_it << std::endl; 
            vector_int::iterator insert_it = vc_tmp.begin() + left;
            run_cnt += merge_sort_array_int(left_it,st,right_it,st,vc_tmp,insert_it);
        }

        //剩下最后一个不能完美分组的合并
        if(i < cnt)
        {
            //最后一次合并
            int left = i;
            int left_loop = st;
            int right = left + st;
            int right_loop = st;
            if(right > cnt) //右边超出范围，则只有一个左边合并
            {
                right = cnt -1;
                right_loop = 0;
            }
            else    //右边不完整
            {
                right = left + st;
                right_loop = cnt - right;
            }
            
            //std::cout << " not perfect " << std::endl; 
            //std::cout << " i " << i << " left " << left << " loop " << left_loop << " right "  << right << " loop " << right_loop << std::endl; 
            //合并
            vector_int::iterator left_it = vc.begin() + left;
            vector_int::iterator right_it = vc.begin() + right;

            //std::cout << "left " << *left_it << " right "  << *right_it << std::endl; 
            vector_int::iterator insert_it = vc_tmp.begin() + left;
            run_cnt += merge_sort_array_int(left_it,left_loop,right_it,right_loop,vc_tmp,insert_it);
        }

        vc = vc_tmp;
        //printf_array_int(vc);

        if(space >= cnt)
            break;

        space = space*2;
    }

    return run_cnt;
}


int main()
{
    int run_cnt = 0;
    vector_int vc = {19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
    vc = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    std::cout << "select_sort 1 -------------" << std::endl;
    vector_int in = vc;    
    vector_int out;
    std::cout << "run count:" << select_sort(in,out) << std::endl; 
    is_asc_array_int(out);
    //printf_array_int<list_int>(out);


    std::cout << "select_sort 2 -------------" << std::endl;
    //vc = {1,21,4,6,5,31,22};
    std::cout << "run count:" << select_sort(vc) << std::endl;        
    is_asc_array_int(vc);
    //printf_array_int<vector_int>(vc);

 
    std::cout << "merge_sort 1 -------------" << std::endl;
    vector_int ls1 = {1,4,6,8,13,18,19,22};//
    vector_int ls2 = {2,7,9};//
    out.clear();
    out.resize(ls1.size() + ls2.size());
    run_cnt = merge_sort_array_int(ls1.begin(), ls1.size(), ls2.begin(), ls2.size(), out, out.begin());
    std::cout << "run count:" << run_cnt << std::endl;
    //printf_array_int(out);     
    is_asc_array_int(out);
    
    std::cout << "merge_sort 2 -------------" << std::endl;
    //vc_data = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    //vc_data = {19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
    run_cnt = merge_sort(vc_data);
    std::cout << "run count:" << run_cnt << std::endl;
    //printf_array_int(out);     
    is_asc_array_int(out);




    return 0;
}