//#include <hash_map>
#include <map>
#include <list>
#include <string>
#include <regex>
using namespace std;

class LexicalHashToken {
private:
    //hash_map<string, int> LexicalHashMap;
    map<string, int> LexicalHashMap;
public:
    /**
     * TODO 初始化词法记号表
     */
    LexicalHashToken();
    /**
     * TODO 获得词法记号表
     * @return 词法记号表LexicalTokenMap
     */
    map<string, int> getLexicalHashMap();

    /**
     * TODO 根据给定的词法单元，返回对应的词法记号
     * @param word 词法单元
     * @return 词法记号token
     */
    int getToken(string word);

    /**
     * TODO 判断一个标识符是否为关键字
     * @param word 标识符
     * @return boolean值
     */
    static bool isKeyWord(string word);
};


class ReadSources {
private:
    list<string> CodeList;  // 每一个节点为一行代码的链表

public:
    /**
     * TODO 读取给定的源代码文件，并将其每一行作为一个链表的一个节点
     * @param fileName 源代码文件路径
     * @throws IOException
     */
    ReadSources(string fileName);
    /**
     * TODO 获得源代码文件生成的链表
     * @return 源代码文件对应的链表
     */
    list<string> getCodeList();
};

class LexicalAnalysis {
    /**
     *
     * @param srcCode 一行代码
     */
public:
    void getWordMap(string srcCode);
    static string getCharType(string str);
    void printWordMap(string fileName);
};
