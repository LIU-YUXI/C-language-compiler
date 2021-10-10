#include <iostream>
#include <fstream>
#include "./LexicalAnalysis.h"
using namespace std;

/*LexicalToken类成员函数的实现*/


LexicalHashToken::LexicalHashToken() {
    //LexicalHashMap = new LinkedHashMap;
    LexicalHashMap.insert(pair<string, int>("#", 0));
    LexicalHashMap.insert(pair<string, int>("for", 1));
    LexicalHashMap.insert(pair<string, int>("if", 2));
    LexicalHashMap.insert(pair<string, int>("then", 3));
    LexicalHashMap.insert(pair<string, int>("else", 4));
    LexicalHashMap.insert(pair<string, int>("while", 5));
    LexicalHashMap.insert(pair<string, int>("do", 6));
    LexicalHashMap.insert(pair<string, int>("ID", 10));// 一般标识符
    LexicalHashMap.insert(pair<string, int>("NUM", 11));// 数字
    LexicalHashMap.insert(pair<string, int>("+", 13));
    LexicalHashMap.insert(pair<string, int>("-", 14));
    LexicalHashMap.insert(pair<string, int>("*", 15));
    LexicalHashMap.insert(pair<string, int>("/", 16));
    LexicalHashMap.insert(pair<string, int>(":", 17));
    LexicalHashMap.insert(pair<string, int>(":=", 18));
    LexicalHashMap.insert(pair<string, int>("<", 20));
    LexicalHashMap.insert(pair<string, int>("<>", 21));
    LexicalHashMap.insert(pair<string, int>("<=", 22));
    LexicalHashMap.insert(pair<string, int>(">", 23));
    LexicalHashMap.insert(pair<string, int>(">=", 24));
    LexicalHashMap.insert(pair<string, int>("=", 25));
    LexicalHashMap.insert(pair<string, int>(";", 26));
    LexicalHashMap.insert(pair<string, int>("(", 27));
    LexicalHashMap.insert(pair<string, int>(")", 28));
    LexicalHashMap.insert(pair<string, int>("//", 29));
    LexicalHashMap.insert(pair<string, int>("/*", 30));
    LexicalHashMap.insert(pair<string, int>("*/", 31));
    LexicalHashMap.insert(pair<string, int>("==", 32));
    LexicalHashMap.insert(pair<string, int>("!=", 33));
    LexicalHashMap.insert(pair<string, int>(",", 34));
    LexicalHashMap.insert(pair<string, int>("int", 35));
    LexicalHashMap.insert(pair<string, int>("void", 36));
    LexicalHashMap.insert(pair<string, int>("return", 37));
    LexicalHashMap.insert(pair<string, int>("{", 38));
    LexicalHashMap.insert(pair<string, int>("}", 39));
}
map<string, int> LexicalHashToken::getLexicalHashMap() {
    return LexicalHashMap;
}
int LexicalHashToken::getToken(string word) {
    if (word == "" | word.empty())
        return -1;
    if (!LexicalHashMap.count(word))
        return -1;
    return LexicalHashMap[word];
}
//静态成员不能在类中初始化,静态成员函数在类外实现时候无须加static关键字
bool LexicalHashToken::isKeyWord(string word) {
    if (word == "")//空指向如何表示？
        return false;
    string keyWord[] = { "int", "for", "if", "then", "else",
            "do", "while", "until", "input", "output","return","void" };
    for (string aWord : keyWord)
        if (word == aWord)
            return true;
    return false;
}


/*ReadSources成员函数的实现*/
ReadSources::ReadSources(string fileName) {
    //CodeList = new LinkedList<>();
    ifstream src(fileName);
    string line;
    //Scanner s = new Scanner(Paths.get(fileName));
    while (getline(src, line)) {
        CodeList.insert(CodeList.end(), line);
        //CodeList.add(src.getline());
    }
}

list<string> ReadSources::getCodeList() {
    return CodeList;
}