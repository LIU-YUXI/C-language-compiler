#include <list>
#include <string>
#include <regex>
#include <iostream>
using namespace std;
/*
 * ������789.123.456, �������789
 */
void get()
{


    std::regex ip_reg("^[a-zA-Z][a-zA-Z0-9]{0,}");
    std::smatch matchResult;



    string inputStr;
    std::getline(std::cin, inputStr);


    //����ƥ��
    if (std::regex_search(inputStr, matchResult, ip_reg))
    {
        cout << "Match: ";
        //��ӡ�ӱ��ʽ���
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