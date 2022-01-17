#pragma once
#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
#define ProductionMax 300//���Ʋ���ʽ��������
#define ProjectMax 300//LR1��Ŀ��������
struct VN_First_Follow {
    string VN;//���ս��
    set<string> FIRST; //First����
    set<string> FOLLOW;//Follow����
};
struct Production {
    string start;//���ս��
    vector<string> next; //First����
    int num = 0;
};
struct Project {
    string start;//���ս��
    vector<string> next; //First����
    int num;//���LR1��Ŀ�С���λ��
    vector<string> tail;
    //����==������������ж�����LR1��Ŀ���
    bool operator==(const Project& rhs) {
        return (start == rhs.start &&
            next == rhs.next &&
            num == rhs.num &&
            tail == rhs.tail
            );
    }
    //����!=������������ж�����LR1��Ŀֻ��tail��ͬ
    bool operator!=(const Project& rhs) {
        return (start == rhs.start &&
            next == rhs.next &&
            num == rhs.num);
    }
    //����>������������ж�����LR1��Ŀֻ��tail��ͬ
    bool operator>(const Project& rhs) {
        return (start == rhs.start &&
            next == rhs.next &&
            num == rhs.num &&
            tail.size() > rhs.tail.size());
    }
    //����<������������ж�����LR1��Ŀֻ��tail��ͬ
    bool operator<(const Project& rhs) {
        return (start == rhs.start &&
            next == rhs.next &&
            num == rhs.num &&
            tail.size() < rhs.tail.size());
    }

    //����+����������ںϲ�����ֻ��tail��ͬ��LR1��Ŀ
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
    int ProdCount = 0;//����ʽʵ������
    int ProjCount = 0;//LR1��Ŀʵ������
    set<string> VN;// ���ս������
    set<string> VT;//�ս������
    map<string, int> loc;
    Production prod[ProductionMax];//����ʽ����
    vector<Project> proj[ProjectMax]; //LR1��Ŀ��
    VN_First_Follow VN_first_follow[ProductionMax];//���ս������First��Follow��
    map<string, int> mark_Follow;//���ڱ��Follow��ֹ��ѭ��
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
