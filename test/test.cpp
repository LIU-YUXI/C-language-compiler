#include <list>
#include <string>
#include <regex>
#include <iostream>
using namespace std;
/*
 * 输入是789.123.456, 输出的是789
 */
void get()
{


    std::regex ip_reg("^[a-zA-Z][a-zA-Z0-9]{0,}");
    std::smatch matchResult;



    string inputStr;
    std::getline(std::cin, inputStr);


    //正则匹配
    if (std::regex_search(inputStr, matchResult, ip_reg))
    {
        cout << "Match: ";
        //打印子表达式结果
        for (size_t i = 0; i < matchResult.size(); ++i)
        {
            cout << matchResult[i] << " ";
        }
    }
    else
    {
        cout << "Not Match!";
    }

}

int main()
{
    get();
}