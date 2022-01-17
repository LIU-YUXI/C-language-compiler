//#include <hash_map>
#include <map>
#include <list>
#include <string>
#include <regex>
using namespace std;
class Token {
private:
    int type;
    string content;
    string typestr;
public:
    int father;
    int pos; // 在语法树中的位置
    bool is_vn;
    int row; // 在源文件的第几行
    int getType() {
        return this->type;
    }
    string getTypestr() {
        return this->typestr;
    }
    string getContent() {
        return this->content;
    }
    Token() {
        type = -1;
        content = "";
        father = -1;
        pos = -1;
        is_vn = false;
        row=0;
    }
    Token(int type, string content) {
        this->type = type;
        this->content = content;
        this->typestr = content;
        this->row=0;
        father = -1;
        pos = -1;
        is_vn = false;
    }
    Token(int type, string content,int row) {
        this->type = type;
        this->content = content;
        this->typestr = content;
        this->row=row;
        father = -1;
        pos = -1;
        is_vn = false;
    }
    Token(int type, string content, string typestr,int row) {
        this->type = type;
        this->content = content;
        this->typestr = typestr;
        this->row=row;
        father = -1;
        pos = -1;
        is_vn=false;
    }
    Token(int type, string content,bool is_vn) {
        this->type = type;
        this->content = content;
        this->typestr = content;
        father = -1;
        pos = -1;
        this->is_vn = is_vn;
    }
};

class LexicalHashToken {
private:
    map<string, int> LexicalHashMap;
public:
    /**
     * TODO 初始化词法记号表
     */
    LexicalHashToken(map<string, int> loc);
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
     */
    ReadSources(string fileName);
    /**
     * TODO 获得源代码文件生成的链表
     * @return 源代码文件对应的链表
     */
    list<string> getCodeList();
};

class LexicalAnalysis {
    vector<Token>TokenList; // vector储存源程序中所有token
    map<string, int> loc;
public:
    LexicalAnalysis(map<string, int> loc){
        this->loc=loc; // 终结符在action表上的位置（即token的序号
    };
    stringstream getWordMap(string srcCode);
    static string getCharType(string str);
    string printWordMap(string fileName);
    void buildTokenVector(string fileName);
    // void buildToken(string srcCode);
    vector<Token> getTokenList();
};
