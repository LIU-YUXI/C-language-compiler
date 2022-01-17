#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include <stack>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstring>
#include <map>
#include "SyntaxAnalyzer.h"
using namespace std;

// ����+�������
template <typename Project>
vector<Project>& operator +(vector<Project>& v1, vector<Project>& v2)
{
    v1.insert(v1.end(), v2.begin(), v2.end());
    return v1;
}

bool cmp_vector(vector<Project>& v1, vector<Project>& v2)
{
    if (v1.size() != v2.size()) return false;
    for (int i = 0; i < v2.size(); i++)
    {
        Project t;
        t = v2[i];
        vector<Project>::iterator result = find(v1.begin(), v1.end(), t); //����3
        if (result == v1.end()) //û�ҵ�
            return false;
    }
    return true;
}
/*
 *������ս����First��Follow��
 */
set<string> LR1::GetFirst(string a) { //��First���� 
    set<string> T;
    for (int i = 0; i < ProdCount; i++) {
        if (prod[i].start == a) {  // a->.. 
            for (int j = 0; j < prod[i].next.size(); j++) {
                if (VT.find(prod[i].next[j]) != VT.end()) { //���ս����ͷ 
                    T.insert(prod[i].next[j]);
                    //    T.erase("*");
                    break;

                }
                else {
                    if (prod[i].next[j] == prod[i].start)
                        break;
                    set<string> U = GetFirst(prod[i].next[j]);
                    T.insert(U.begin(), U.end());
                    if (U.find("null") != U.end()) { //U�к���*,�������¸���first
                        if (j != prod[i].next.size() - 1)
                            T.erase("null");
                    }
                    else
                        break;
                }
            }
        }
    }
    return T;
}

set<string> LR1::GetFollow(string a) {
    set<string> T;
    mark_Follow[a]++;
    if (mark_Follow[a] >= 2)
        return T;
    set<string> temp;
    if (a == prod[0].start) {
        T.insert("#");
    }
    for (int i = 0; i < ProdCount; i++) {
        for (int j = 0; j < prod[i].next.size(); j++) {
            if (VT.find(prod[i].next[j]) == VT.end() && a == prod[i].next[j]) { //�Ƿ��ս������FOLLOW���� 
                if (j == prod[i].next.size() - 1 && a != prod[i].start) {//S->...a 
                    set<string> tt = GetFollow(prod[i].start);
                    T.insert(tt.begin(), tt.end());
                }
                for (int k = j + 1; k < prod[i].next.size(); k++) {
                    if (VT.find(prod[i].next[k]) != VT.end()) {//����һ�����ս��  S->..av.. 
                        T.insert(prod[i].next[k]);
                        break;
                    }
                    else {
                        temp = GetFirst(prod[i].next[k]);
                        if (temp.find("null") != temp.end()) {//��null S->..a B.. 
                            T.insert(temp.begin(), temp.end());
                            T.erase("null");
                            if (k == prod[i].next.size() - 1) { //S->..a B
                                set<string> tt = GetFollow(prod[i].start);
                                T.insert(tt.begin(), tt.end());
                                break;
                            }
                        }
                        else {
                            T.insert(temp.begin(), temp.end());
                            break;
                        }
                    }
                }
            }
        }
    }
    //cout<<a<<" "<<mark_Follow[a]<<endl;
    mark_Follow[a] = 0;
    return T;
}

void LR1::GetFirstAndFollow() {
    set<string>::iterator it;
    int i = 0;
    cout << "================================================================================" << endl;
    cout << "\t\t" << "FIRST����" << "                     " << "FOLLOW����" << endl;

    for (it = VN.begin(); it != VN.end(); it++)//����First��
    {
        VN_first_follow[i].VN = *it;
        VN_first_follow[i].FIRST = GetFirst(*it);
        mark_Follow[*it] = 0;
        i++;
    }
    i = 0;
    for (it = VN.begin(); it != VN.end(); it++)//����Follow��
    {
        VN_first_follow[i].FOLLOW = GetFollow(*it);
        i++;
    }
    i = 0;
    for (it = VN.begin(); it != VN.end(); it++)
    {
        /*VN_first_follow[i].VN = *it;
        VN_first_follow[i].FIRST = GetFirst(*it);
        mark_Follow[*it] = 0;
        VN_first_follow[i].FOLLOW = GetFollow(*it);*/
        //-----------���FIRST-------------------- 
        int size = 0;
        cout << setiosflags(ios::left) << setw(16) << VN_first_follow[i].VN;
        set<string>::iterator it;
        for (it = VN_first_follow[i].FIRST.begin(); it != VN_first_follow[i].FIRST.end(); it++)
        {
            cout << *it << " ";
            size = size + (*it).length() + 1;
        }
        for (int j = 0; j < 30 - size; j++)
            cout << ' ';
        //------------���FOLLOW--------------
        set<string>::iterator it1;
        for (it1 = VN_first_follow[i].FOLLOW.begin(); it1 != VN_first_follow[i].FOLLOW.end(); it1++)
            cout << *it1 << " ";
        cout << endl;
        i++;
    }
    cout << "=================================================================================";
    cout << endl << endl;
}

void LR1::InputProduction(string infile) {
    //����һ���ļ�����������
    ifstream inFile;
    //���ļ�
    //inFile.open("MyProduction.txt");
    inFile.open(infile);
    if (inFile)  //������������˵���ļ��򿪳ɹ�
        cout << "FILE open successful" << endl;
    else
        cout << "file doesn't exist" << endl;
    string temp;
    /*
    getline(inFile, temp);
    for (int j = 0; j < temp.length(); j++) {
        VT.insert(temp.substr(j, 1));
    }*/
    int count = 0;//�ļ����� 
    while (getline(inFile, temp)) //���ж�ȡ�ļ����� 
    {
        stringstream ss;
        ss << temp;
        ss >> prod[count].start;
        string discard;
        ss >> discard;
        VN.insert(prod[count].start);//���ս��
        while (ss.rdbuf()->in_avail())
        {
            string cur;
            ss >> cur;
            if (cur[0] < 'A' || cur[0]>'Z')
                VT.insert(cur);
            prod[count].next.push_back(cur);
            prod[count].num++;
        }

        cout << prod[count].start << " -> ";
        vector<string>::iterator it;
        for (it = prod[count].next.begin(); it != prod[count].next.end(); it++)
            cout << *it << " ";
        cout << endl;
        count++;
    }
    ProdCount = count;
    /*
    cout << "�ս��";
    set<string>::iterator it1;
    for (it1 = VN.begin(); it1 != VN.end(); it1++)
        cout << *it1 << ' ';
    cout << endl;*/
    set<string>::iterator it2;
    int k = 0;
    for (it2 = VT.begin(); it2 != VT.end(); it2++)
    {
        loc[*it2] = k;
        k++;
    }
    cout << endl;
}
void LR1::MergeProject(vector<Project>& T)
{
    //sort(T.begin(), T.end());
    //T.erase(unique(T.begin(), T.end()), T.end());
    //T.erase(T.begin());
    vector<Project>::iterator it;
    vector<Project> p;
    for (it = T.begin(); it < T.end(); it++) {
        vector<Project>::iterator it1;
        for (it1 = p.begin(); it1 < p.end(); it1++)
            if (*it != *it1)
            {
                *it1 = *it1 + *it;
                break;
            }
        if (it1 == p.end())
            p.insert(p.end(), *it);
    }
    T = p;
}
bool find_in_vector(vector<Project> T, Project p) {
    vector<Project>::iterator it;
    for (it = T.begin(); it != T.end(); it++) {
        if (*it == p) {
            return true;
        }
    }
    return false;
}
vector<Project> LR1::CLOSURE(Project I) {//��հ���������ıհ��в���������
    vector<Project> T;
    if (I.num >= I.next.size()) { //��Լ��ĿA->����,���߽�����Ŀ 
        return T;
    }
    else {
        string temp = I.next[I.num];
        if (VT.find(temp) != VT.end()) {     //���������ս�� ,�ƽ���Ŀ A������a��  
            return T;
        }
        else {  //��Լ��Ŀ 
            for (int i = 0; i < ProdCount; i++) {//�Բ���ʽ�б����ÿһ������ʽ
                if (prod[i].start == temp) {//�ҵ��ԡ�����ķ��ս����ͷ��
                    Project p;
                    p.start = prod[i].start;
                    if (prod[i].next[0] == "null")
                        p.num = 1;//�ղ���ʽֻ��Լ���ƽ�
                    else
                        p.num = 0;//���ǿղ���ʽ�������ǰ�� 
                    p.next = prod[i].next;
                    set<string> f1;//���ڴ��չ����
                    for (int j = I.num + 1; j < I.next.size(); j++) {
                        set<string> f2;//�����ݴ�first 
                        if (VT.find(I.next[j]) != VT.end()) {//����Ǹ��ս��
                            f2.insert(I.next[j]);//���Լ��ӽ�ȥ
                        }
                        else {//����Ǹ����ս������First�ӽ�ȥ
                            f2 = GetFirst(I.next[j]);
                        }
                        if (f1.find("null") != f1.end()) {//��ÿ�β���֮ǰ�������f1�����null�������˳�ѭ����f1���������null
                                                          //��˵����ǰ���ս���������з��ŵ�First�����п���Ϊnull
                            f1.erase("null");
                        }
                        f1.insert(f2.begin(), f2.end());
                        if (f2.find("null") == f2.end()) {//���������Ϊ�գ�ֱ���˳�
                            break;
                        }
                    }
                    if (f1.size() == 0) {//��ǰ���ս������û����
                        p.tail = I.tail;
                    }
                    else {
                        vector<string> first_tail;
                        if (f1.find("null") != f1.end()) {
                            f1.erase("null");
                            copy(f1.begin(), f1.end(), back_inserter(first_tail));
                            first_tail.insert(first_tail.end(), I.tail.begin(), I.tail.end());
                        }
                        else {
                            copy(f1.begin(), f1.end(), back_inserter(first_tail));
                        }
                        p.tail = first_tail;
                    }
                    if (!find_in_vector(T, p)) {
                        T.push_back(p);
                        vector<Project> ol = CLOSURE(p);
                        vector<Project>::iterator z;
                        for (z = ol.begin(); z != ol.end(); z++) {
                            if (find_in_vector(T, *z)) {
                            }
                            else {
                                T.push_back(*z);
                            }
                        }
                    }
                }
            }
        }
    }
    return T;

}

void LR1::showI(vector<Project> I)
{//չʾ��Ŀ�� 
    vector<Project>::iterator it;
    for (it = I.begin(); it != I.end(); it++) {
        Project p = *it;
        cout << p.start << "->";
        vector<string>::iterator s;
        for (int j = 0; j < p.next.size(); j++) {
            if (j == p.num) cout << "��";
            cout << p.next[j] << " ";

        }if (p.num == p.next.size())cout << "��";
        cout << ",";
        for (int k = 0; k < p.tail.size(); k++) {
            cout << p.tail[k] << '/';
        }
        cout << endl;
    }
}
void LR1::LR1Analyse() {
    Project p;
    //��ʼ��Ŀ S��->.S ,# 
    p.start = prod[0].start + "'";
    p.num = 0;//������ǰ�� 
    p.tail.push_back("#");
    p.next.push_back(prod[0].start);
    proj[0] = CLOSURE(p);//��հ����I[0]
    proj[0].insert(proj[0].begin(), p);///////////////��հ�������һЩ���� 
    ProjCount = 1;
    //������Ŀ�� 
    for (int i = 0; i < ProjCount; i++) {//ÿ����Ŀ��  ��Ŀ��proj[i]����һ��Ԫ��Ϊproject��vector
        if (i == 4)
            int a = 1;
        cout << "===================" << endl;
        cout << "�����ڼ�����Ŀ��I" << i << endl;
        cout << "����Ŀ������Ŀ��Ϊ" << proj[i].size() << endl;
        showI(proj[i]);//չʾ��Ŀ�� 
        cout << "===================" << endl;

        //---------��ACTION��r����-------------- 
        vector<Project>::iterator t;
        for (t = proj[i].begin(); t != proj[i].end(); t++) {//����Ŀ�������ÿ����Ŀ
            Project t2 = *t;
            if (t2.num == t2.next.size()) {//�������
                int num = 0;
                for (int xp = 0; xp < ProdCount; xp++) {//�ڲ���ʽ�б��ж�λ����Ŀ��Ӧ�Ĳ���ʽ�����к�
                    if (prod[xp].start == t2.start && prod[xp].next == t2.next) {
                        num = xp;
                        break;
                    }
                }
                //����stringstream�����к�תΪstring����
                stringstream ss;
                ss << num;
                string s = ss.str();
                for (int q = 0; q < t2.tail.size(); q++) {
                    ACTION[i][t2.tail[q]] = "r" + s;
                }
                if (t2.num == 1 && t2.next[0] == prod[0].start) {//���ý���״̬
                    ACTION[i]["#"] = "acc";
                }
            }
        }
        //---------��Action��S����------------
        set<string>::iterator it;
        for (it = VN.begin(); it != VN.end(); it++) {  //ÿ�����ս��
            vector<Project> temp;
            for (int j = 0; j < proj[i].size(); j++) {//ÿ��proj[i]����һ����Ŀ����vector��,�������ÿ����Ŀlr
                Project lr = proj[i][j];
                if (lr.num < lr.next.size() && lr.next[lr.num] == *it) {//�������Ƿ��ս��
                    vector<Project> t2;
                    lr.num++;
                    t2 = CLOSURE(lr);
                    t2.push_back(lr);
                    temp = temp + t2;
                }
            }
            MergeProject(temp);//�ȶ�ÿ����Ŀ������Ԥ����
            if (temp.size() > 0) {
                int k;
                for (k = 0; k < ProjCount; k++) {//��һ����Ŀ���Ƿ��Ѿ����� 
                    if (cmp_vector(proj[k], temp)) {
                        break;
                    }
                }
                if (k == ProjCount) {
                    //�������µ���Ŀ�� 
                    proj[ProjCount] = temp;
                    cout << "  I" << i << " -- " << *it << " ->" << "I" << ProjCount << endl << endl;
                    GOTO[i][*it] = ProjCount;//����goto�� 
                    ProjCount++;
                }
                else {
                    //��Ŀ���Ѿ����ڣ���Ҫ�Լ�ָ���Լ�
                    cout << "  I" << i << " -- " << *it << "->" << "I" << k << endl << endl;
                    GOTO[i][*it] = k;
                }
            }
        }
        for (it = VT.begin(); it != VT.end(); it++) {  //ÿ���ս��
            vector<Project> temp;
            for (int j = 0; j < proj[i].size(); j++) {//����Ŀ��i���ÿ����Ŀlr
                Project lr = proj[i][j];
                if (lr.num < lr.next.size() && lr.next[lr.num] == *it) {//���������ս��
                    vector<Project> t2;
                    lr.num++;
                    t2 = CLOSURE(lr);//�հ�����Ľ������������ 
                    t2.insert(t2.begin(), lr);/////////��հ�������һЩ���� 
                    temp = temp + t2;
                }
            }
            MergeProject(temp);//�ȶ�ÿ����Ŀ������Ԥ����
            if (temp.size() > 0) {
                int k;
                for (k = 0; k < ProjCount; k++) {//��һ����Ŀ���Ƿ��Ѿ����� 
                    if (cmp_vector(proj[k], temp)) {
                        break;
                    }
                }
                if (k == ProjCount) {
                    //�������µ���Ŀ�� 
                    proj[ProjCount] = temp;
                    cout << "  I" << i << " -- " << *it << "->" << "I" << ProjCount << endl << endl;
                    stringstream ss;
                    ss << ProjCount;
                    string s = ss.str();
                    ACTION[i][*it] = "S" + s;//����ACTION�� 
                    ProjCount++;
                }
                else {
                    //��Ŀ���Ѿ����ڣ���Ҫ�Լ�ָ���Լ�
                    cout << "  I" << i << " -- " << *it << "->" << "I" << k << endl << endl;
                    stringstream ss;
                    ss << k;
                    string s = ss.str();
                    ACTION[i][*it] = "S" + s;
                }
            }
        }
    }
}

void LR1::PrintActionAndGoto() {
    /*map<string, int>::iterator it1;
    for (it1 = loc.begin(); it1 != loc.end(); it1++) {
        cout << setw(8) << (*it1).first<<(*it1).second<<endl;
    }*/
    set<string>::iterator it;
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << setw(27) << setiosflags(ios::right) << "ACTION";
    cout << setw(20) << setiosflags(ios::left) << "  GOTO" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;
    cout << setw(8) << "��Ŀ��" << "|";
    for (it = VT.begin(); it != VT.end(); it++) {
        cout << setw(8) << *it << "|";
    }
    cout << setw(8) << "#" << "|";
    for (it = VN.begin(); it != VN.end(); it++) {
        cout << setw(8) << *it << "|";
    }
    cout << endl;
    for (int j = 0; j < ProjCount; j++) {
        cout << setw(6) << "I" << setw(2) << j << "|";
        for (it = VT.begin(); it != VT.end(); it++) {
            cout << setw(8) << ACTION[j][*it] << "|";
        }
        cout << setw(8) << ACTION[j]["#"] << "|";
        for (it = VN.begin(); it != VN.end(); it++) {
            if (GOTO[j][*it])//GOTO��Ϊ0 
                cout << setw(8) << GOTO[j][*it] << "|";
            else {
                cout << setw(8) << " " << "|";
            }
        }
        cout << endl;
    }
    cout << "-----------------------------------------------------------------------------" << endl;
}