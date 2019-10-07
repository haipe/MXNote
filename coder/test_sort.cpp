#include <iostream>
#include <list>

typedef std::list<int> list_int;

void printf_list_int(list_int& ls)
{
    std::for_each(ls.begin(),ls.end(),[](int i){
        std::cout << i << "; ";
    });
    
    std::cout << std::endl;
}

void merge_list(list_int& left, list_int& right, list_int& out)
{
    auto left_it = left.begin();
    auto right_it = right.begin();

    while(left_it != left.end() && right_it != right.end())
    {
        if(*left_it <= *right_it)
        {
            out.push_back(*left_it);
            left_it++;
        }
        else
        {
            out.push_back(*right_it);
            right_it++;
        }
    }

    if(left_it == left.end() && right_it == right.end())
        return;

    if(left_it == left.end())
        out.insert(out.end(),right_it,right.end());
    else
        out.insert(out.end(), left_it, left.end());
}

void select_sort(list_int& in, list_int& out)
{
    auto item_in = in.begin();
    out.push_front(*item_in);
    
    for(++item_in ; item_in != in.end() ; item_in ++)
    {
        auto item_out = out.begin();
        for( ; item_out != out.end() ; item_out ++)
        {
            //头插，第一个小于自己的
            //尾插，可以从最后一个开始遍历
            if(*item_in < *item_out)
            {
                break;
            }
        }

        if(item_out == out.end())
            std::cout << "insert: " << *item_in << " on last;" << std::endl;
        else
            std::cout << "insert: " << *item_in << ", front:" << *item_out << std::endl;
            
        out.insert(item_out,*item_in);

        printf_list_int(out);
    }
}


int main()
{
    list_int ls = {1,21,4,6,5,31,22};
    list_int out;
    select_sort(ls,out);

    //std::cout << "size :" << out.size() << std::endl;

    printf_list_int(out);

    list_int r = {7,8,9,10};

    ls.clear();
    merge_list(out,r,ls);
    std::cout << "merge " << std::endl;
    printf_list_int(ls);

    return 0;
}