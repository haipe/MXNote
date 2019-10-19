#include "code_common.h"


int insert_sort(vector_int& in)
{
    //printf_array_int<vector_int>(in);
    int run_cnt = 0;
    int size = in.size();
    //第一个相当于有序队列的部分，从第二个开始算作无序部分
    for(int i = 1; i < size; i++)
    {
        int tmp = in[i];//保存一份当前位置的数据，用来记录需要插入的数据。
        //从i开始逐个比较合适位置，找到插入点
        int j = i;
        for(;j > 0; j--)
        {
            //std::cout << "[ " << j << " , " << j - 1 << " ] " << in[j] << " " << in[j-1] << std::endl;
            run_cnt ++;
            //如果比前面的小，则插入到前面的
            if(in[j] < in[j-1])
            {
                //std::cout << "swap [ " << j << " , " << j - 1 << " ] " << in[j] << " " << in[j-1] << std::endl;
                //in[i]已经保存，所以只要把前面的后移即可，最后找到位置之后在用保存的tmp覆盖即可
                in[j]=in[j-1];
                in[j-1] = tmp;
                continue;
            }

            //std::cout << "find insert position :"<< j << std::endl;
            break;
        }

        //找到前一个位置小于来当前比较的位置，即插入到这个之后
        in[j] = tmp;
        //printf_array_int<vector_int>(in);
    }

    return run_cnt;
}

int insert_sort_ex(vector_int& in, int space)//增加一个比较间隔参数
{ 
    //printf_array_int<vector_int>(in);
    int run_cnt = 0;
    int size = in.size();
    //第一个相当于有序队列的部分，从第二个开始算作无序部分
    for(int i = space; i < size; i+= space)
    {
        int tmp = in[i];//保存一份当前位置的数据，用来记录需要插入的数据。
        //从i开始逐个比较合适位置，找到插入点
        int j = i;
        for(;j > 0; j-= space)
        {
            //std::cout << "[ " << j << " , " << j - space << " ] " << in[j] << " " << in[j-space] << std::endl;
            run_cnt ++;
            //如果比前面的小，则插入到前面的
            if(in[j] < in[j-space])
            {
                //std::cout << "swap [ " << j << " , " << j - space << " ] " << in[j] << " " << in[j-space] << std::endl;
                //in[i]已经保存，所以只要把前面的后移即可，最后找到位置之后在用保存的tmp覆盖即可
                in[j]=in[j-space];
                in[j-space] = tmp;
                continue;
            }

            //std::cout << "find insert position :"<< j << std::endl;
            break;
        }

        //找到前一个位置小于来当前比较的位置，即插入到这个之后
        in[j] = tmp;
        //printf_array_int<vector_int>(in);
    }

    return run_cnt;
}

int shell_sort(vector_int& in)
{
    int run_cnt = 0;
    int space = in.size() / 2;
    for(int i = space ; i >= 1 ; i = i/2)
    {
        run_cnt += insert_sort_ex(in,i);
    }

    return run_cnt;
}


int main()
{
    std::cout << "insert_sort -------------" << std::endl;
    vc_data = {1,21,4,6,5,31,22};

    std::cout << "run count:" << insert_sort(vc_data) << std::endl; //count:218 973
    //std::cout << "run count:" << insert_sort_ex(vc_data,1) << std::endl; //count:218 973
    //std::cout << "run count:" << shell_sort(vc_data) << std::endl; //count:169 762
    //printf_array_int<vector_int>(vc_data);   
    is_asc_array_int(vc_data);

    return 0;
}