#include"./SyntaxAnalyzer.h"
#include "./ActionAndGoto.h"
#include <direct.h>
string SytaxAnalyzer::Analysis(string srcFile, string outFile) {
    this->syntax_error = false;
    LexicalAnalysis lexer(lr->loc);
    lexer.buildTokenVector(srcFile);
    StateStack.push(0);
    // VnIndex.insert(pair<string, int>("S", 0));
    // VnIndex.insert(pair<string, int>("C", 1));
    vector<Token> TokenList = lexer.getTokenList();
    for (int i = 0; i < TokenList.size(); i++) {
        TokenList[i].pos = SyntaxTree.size();
        SyntaxTree.push_back(TokenList[i]);
    }
    TokenList.push_back(Token(1, "#"));
    string ret = parse(TokenList);
    if (outFile == "") {
        cout << ret << endl;
    }
    else {
        ofstream out(outFile);
        out << ret << endl;
        out.close();
    }
    
    // SemanticAnalyzer.PrintQuaternary("SYS.txt");

    return ret;
}
string SytaxAnalyzer::parse(vector <Token> tokens) {
    string ret = "";
    int CurIndex = 0;
    SemanticAnalyzer.AddSymbolToList({ this->lr->prod[1].start,"",-1,-1,-1 });
    while (CurIndex < tokens.size()) {
        Token CurToken = tokens[CurIndex];
        int CurState = StateStack.top();
        // 读取action
        string nextstr = CurToken.getTypestr();
        string next = lr->ACTION[CurState][nextstr];
        if (CurToken.getContent() == "#")
            cout << ("#");
        if (next == "acc")
            break;
        if (next == "") {
            // 语法错误
            ret += "syntax error : near \" ";
            ret += CurToken.getContent();
            ret += " \" in line ";
            stringstream ss;
            ss << CurToken.row;
            ret += ss.str();;
            ret += "\n";
            this->syntax_error = true;
            break;
        }
        int ActionNo = getInt(next);
        if (next[0] == 'S') {// S操作，状态转移
            TokenStack.push(CurToken);
            StateStack.push(ActionNo);
            SemanticAnalyzer.AddSymbolToList({ CurToken.getTypestr(),CurToken.getContent(),CurToken.row,-1,-1 });
        }
        else if (next[0] == 'r') {//规约操作
            if (ActionNo == 0) {
                //accept
                break;
            }
            else {
                // 加入产生式（规约式
                ret += lr->prod[ActionNo].start;
                ret += " -> ";
                for (int i = 0; i < lr->prod[ActionNo].next.size(); i++) {
                    ret += lr->prod[ActionNo].next[i];
                    ret += " ";
                }
                ret += '\n';
                SemanticAnalyzer.Analysis(lr->prod[ActionNo].start, lr->prod[ActionNo].next);
                // 产生式左边的非终结符入栈
                string LeftToken = lr->prod[ActionNo].start;
                Token leftToken_t(-2, LeftToken, true);
                leftToken_t.pos = SyntaxTree.size();
                SyntaxTree.push_back(leftToken_t);
                stack<Token>tempstack;
                if (lr->prod[ActionNo].next[0] != "null") {
                    for (int i = 0; i < lr->prod[ActionNo].num; i++) {
                        StateStack.pop();
                        tempstack.push(TokenStack.top());
                        TokenStack.pop();
                    }
                }
                else {
                    tempstack.push(Token(-2, "null"));
                }
                while (!tempstack.empty())
                {
                    Token t = tempstack.top();
                    if (t.pos != -1) {
                        SyntaxTree[t.pos].father = leftToken_t.pos;
                    }
                    else {
                        t.pos = SyntaxTree.size();
                        t.father = leftToken_t.pos;
                        SyntaxTree.push_back(t);
                    }
                    tempstack.pop();
                }
                TokenStack.push(leftToken_t);
                int NextState = lr->GOTO[StateStack.top()][LeftToken];
                StateStack.push(NextState);

                continue;
            }
        }
        CurIndex++;
    }
    return ret;
}
void SytaxAnalyzer::drawTree() {
    fstream out;
    out.open("graph.dot", ios::out);
    out << "digraph G{ " << endl << "rankdir=LR;" << endl;
    for (int i = 0; i < SyntaxTree.size(); i++) {
        out << "node" << i << "[label=\"" << i << ":" << SyntaxTree[i].getContent() << "\"";
        if (!SyntaxTree[i].is_vn)
            out << ",color=red";
        out << "];" << endl;
        if (SyntaxTree[i].father != -1) {
            out << "node" << SyntaxTree[i].father << " -> node" << i;
            out << ";" << endl;
        }
    }

    out << "}" << endl;
    char cwd[256];
    _getcwd(cwd, 256);
    cout << cwd << endl;
    string pc=string(cwd)+"\"/Graphviz2.38/bin/dot.exe\" -T png graph.dot -o tree.png";
    system(pc.c_str());
    return;
}
int SytaxAnalyzer::is_syntax_error() {
    return this->syntax_error;
}
/*
int main()
{
	LR1 lr;
	lr.InputProduction("test.txt");//输入二型文法 
	lr.GetFirstAndFollow();//求First和Follow集合 
	lr.LR1Analyse();
	lr.PrintActionAndGoto();//打印ACTION GOTO表
	SytaxAnalyzer syer(&lr);
	syer.Analysis("./src.txt", "");
    syer.SemanticAnalyzer.ReturnSymbolTable();
	syer.drawTree();
	system("tree.png");
}
*/
