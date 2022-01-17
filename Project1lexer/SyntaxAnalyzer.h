#pragma once

#include"LexicalAnalysis.h"
#include "ActionAndGoto.h"
#include "SemanticAnalysis.h"
#include<stack>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
// extern Production prod[ProductionMax];//产生式列表，产生式左侧符号存在proc[i].start中，产生式右侧符号存在proc.next中（vector）
// 产生式右侧的符号数存在proc[i].num中
// extern map<string, int> GOTO[ProductionMax];//Goto表
// extern map<string, string> ACTION[ProductionMax];//Action表
class SytaxAnalyzer {
private:
    stack<int> StateStack;
    stack<Token> TokenStack;
    vector<Token> SyntaxTree;
    LR1 *lr;

    // string** ActionTable;
    // int** GotoTable;
    // string* ProductionList;// 产生式列表
    // int* ProductionLength; // 产生式右边符号数
    // map<string, int> VnIndex = loc;// 对应非终结符的位置 //从0开始数
                                  
    // int VnNum;// 非终结符数量
    /*
    int VnNum = 2; // 非终结符个数
    map<string, int> VnIndex;// 非终结符在goto表表头的位置 //从0开始数
    // 产生式列表
    string ProductionList[6] = {
            "S`-> S",
            "S -> if (C) S else S",
            "S -> if (C) S",
            "S -> w + w",
            "C -> C && C",
            "C -> w > w"
    };

    // 产生式右侧符号数
    int ProductionLength[6] = {
            1,
            7,
            5,
            3,
            3,
            3
    };

    // ACTION 表
    string ActionTable[27][9] = {
            { "S2" , ""   , ""   , ""   , ""   , ""   , ""   , "S3" , ""   },
            { ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , "r0" },
            { ""   , ""   , "S4" , ""   , ""   , ""   , ""   , ""   , ""   },
            { ""   , ""   , ""   , ""   , "S5" , ""   , ""   , ""   , ""   },
            { ""   , ""   , ""   , ""   , ""   , ""   , ""   , "S7" , ""   },
            { ""   , ""   , ""   , ""   , ""   , ""   , ""   , "S8" , ""   },
            { ""   , ""   , ""   , "S9" , ""   , ""   , "S10", ""   , ""   },
            { ""   , ""   , ""   , ""   , ""   , "S11", ""   , ""   , ""   },
            { ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , "r3" },
            { "S13", ""   , ""   , ""   , ""   , ""   , ""   , "S14", ""   },
            { ""   , ""   , ""   , ""   , ""   , ""   , ""   , "S7" , ""   },
            { ""   , ""   , ""   , "r5" , ""   , ""   , "r5" , "S16", ""   },
            { ""   , "S17", ""   , ""   , ""   , ""   , ""   , ""   , "r2" },
            { ""   , ""   , ""   , "S18", ""   , ""   , ""   , ""   , ""   },
            { ""   , ""   , ""   , ""   , "S19", ""   , ""   , ""   , ""   },
            { ""   , ""   , ""   , "r4" , ""   , ""   , "r4" , ""   , ""   },
            { ""   , ""   , ""   , "r5" , ""   , ""   , "r5" , ""   , ""   },
            { "S2" , ""   , ""   , ""   , ""   , ""   , ""   , "S3" , ""   },
            { ""   , ""   , ""   , ""   , ""   , ""   , ""   , "S7" , ""   },
            { ""   , ""   , ""   , ""   , ""   , ""   , ""   , "S22", ""   },
            { ""   , ""   , ""   , ""   , ""   , ""   , ""   , ""   , "r1" },
            { ""   , ""   , ""   , "S23", ""   , ""   , "S10", ""   , ""   },
            { ""   , "r3" , ""   , ""   , ""   , ""   , ""   , ""   , "r3" },
            { "S13", ""   , ""   , ""   , ""   , ""   , ""   , "S14", ""   },
            { ""   , "S25", ""   , ""   , ""   , ""   , ""   , ""   , "r2" },
            { "S13", ""   , ""   , ""   , ""   , ""   , ""   , "S14", ""   },
            { ""   , "r1" , ""   , ""   , ""   , ""   , ""   , ""   , "r1" }
    };
    // GOTO 表
    int GotoTable[27][2] = {
            { 1 , 0  },
            { 0 , 0  },
            { 0 , 0  },
            { 0 , 0  },
            { 0 , 6  },
            { 0 , 0  },
            { 0 , 0  },
            { 0 , 0  },
            { 0 , 0  },
            { 12, 0  },
            { 0 , 15 },
            { 0 , 0  },
            { 0 , 0  },
            { 0 , 0  },
            { 0 , 0  },
            { 0 , 0  },
            { 0 , 0  },
            { 20, 0  },
            { 0 , 21 },
            { 0 , 0  },
            { 0 , 0  },
            { 0 , 0  },
            { 0 , 0  },
            { 24, 0  },
            { 0 , 0  },
            { 26, 0  },
            { 0 , 0  },
    };
    */
    int getInt(string s) {
        int ret = 0;
        for (int i = 0;i<s.length(); i++) {
            if (s[i] >= '0' && s[i]<='9')
                ret = ret * 10 + s[i] - '0';
            else
                continue;
        }
        return ret;
    }
    int syntax_error;// 是否有语法错误
public:
    SemanticAnalysis SemanticAnalyzer;
    SytaxAnalyzer(LR1* lr){
        this->lr=lr;
    }
    string Analysis(string srcFile, string outFile);
    string parse(vector <Token> tokens);
    void drawTree();
    int is_syntax_error();
};

