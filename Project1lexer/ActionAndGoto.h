#pragma once
#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
#define ProductionMax 300//限制产生式数量上限
#define ProjectMax 300//LR1项目数量上限
struct VN_First_Follow {
    string VN;//非终结符
    set<string> FIRST; //First集合
    set<string> FOLLOW;//Follow集合
};
struct Production {
    string start;//非终结符
    vector<string> next; //First集合
    int num = 0;
};
struct Project {
    string start;//非终结符
    vector<string> next; //First集合
    int num;//标记LR1项目中·的位置
    vector<string> tail;
    //重载==运算符，用于判断两个LR1项目相等
    bool operator==(const Project& rhs) {
        return (start == rhs.start &&
            next == rhs.next &&
            num == rhs.num &&
            tail == rhs.tail
            );
    }
    //重载!=运算符，用于判断两个LR1项目只有tail不同
    bool operator!=(const Project& rhs) {
        return (start == rhs.start &&
            next == rhs.next &&
            num == rhs.num);
    }
    //重载>运算符，用于判断两个LR1项目只有tail不同
    bool operator>(const Project& rhs) {
        return (start == rhs.start &&
            next == rhs.next &&
            num == rhs.num &&
            tail.size() > rhs.tail.size());
    }
    //重载<运算符，用于判断两个LR1项目只有tail不同
    bool operator<(const Project& rhs) {
        return (start == rhs.start &&
            next == rhs.next &&
            num == rhs.num &&
            tail.size() < rhs.tail.size());
    }

    //重载+运算符，用于合并两个只有tail不同的LR1项目
    Project operator+(const Project& rhs) {
        Project p;
        set<string> new_tail;
        vector<string> nn_tail;
        p.start = rhs.start;
        p.num = rhs.num;
        p.next = rhs.next;
        vector<string>::iterator it;
        for (it = this->tail.begin(); it != this->tail.end(); it++)
        {
            new_tail.insert(*it);
        }
        vector<string>::const_iterator it1;
        for (it1 = rhs.tail.begin(); it1 != rhs.tail.end(); it1++)
        {
            new_tail.insert(*it1);
        }
        copy(new_tail.begin(), new_tail.end(), back_inserter(nn_tail));
        p.tail = nn_tail;
        return p;
    }
};

class LR1 {
public:
    int ProdCount = 0;//产生式实际数量
    int ProjCount = 0;//LR1项目实际数量
    set<string> VN;// 非终结符集合
    set<string> VT;//终结符集合
    map<string, int> loc;
    Production prod[ProductionMax];//产生式集合
    vector<Project> proj[ProjectMax]; //LR1项目集
    VN_First_Follow VN_first_follow[ProductionMax];//非终结符集的First和Follow集
    map<string, int> mark_Follow;//用于标记Follow防止死循环
    map<string, int> GOTO[ProductionMax];
    map<string, string> ACTION[ProductionMax];
    friend class SytaxAnalyzer;
    friend class LexicalToken;
public:
    void InputProduction(string infile);
    set<string> GetFirst(string a);
    set<string> GetFollow(string a);
    void GetFirstAndFollow();
    vector<Project> CLOSURE(Project I);
    void MergeProject(vector<Project>& T);
    void showI(vector<Project> I);
    void LR1Analyse();
    void PrintActionAndGoto();
};
