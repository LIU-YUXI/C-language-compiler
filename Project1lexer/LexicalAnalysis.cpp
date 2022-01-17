#include "./LexicalAnalysis.h"
#include <iostream>
#include <sstream>
stringstream LexicalAnalysis::getWordMap(string srcCode)
{
    stringstream ret;
	if (srcCode == "")
        return ret;
	regex regexID("^[a-zA-Z][a-zA-Z0-9]{0,}");
    // regex regexNUM("^[0-9][0-9]{0,}");
    regex regexNUM("^[0-9]{0,}[.]{0,2}[0-9][0-9]{0,}");
    LexicalHashToken lextoken(this->loc);
	while (!srcCode.empty()) {
		string thisChar = srcCode.substr(0, 1);
		string charType = getCharType(thisChar);
		std::smatch matchResult;
		if (charType == "LETTER") {
			if (regex_search(srcCode, matchResult, regexID)) {
				// 如果是关键字
				if (lextoken.isKeyWord(matchResult.str())) {
					int lexno = lextoken.getToken(matchResult.str());
                    ret << "(" << lexno << "," << matchResult.str() << ")    ";
				}
				// 否则可能是ID
				else {
					int lexno = lextoken.getToken("id");
                    ret << "(" << lexno << "," << matchResult.str() << ")    ";
				}
				srcCode = srcCode.c_str() + int( matchResult.length());
			}
		}
		else if (charType == "NUMBER") {
			if (regex_search(srcCode, matchResult, regexNUM)) {
				// 如果是数字
				int lexno = lextoken.getToken("num");
                ret << "(" << lexno << "," << matchResult.str() << ")    ";

				srcCode = srcCode.c_str() + int(matchResult.length());
			}
		}
		else if (charType=="BLANK") {
			srcCode = srcCode.c_str() + 1;
		}
		// 除数字空格字母以外的符号
		else if (charType=="SPECIAL") {
			// 先往后读一位，因为符号可能是>=这样的
			if (srcCode.length() > 1) {
				string nextChar = srcCode.substr(1, 1);
				string nextCharType = getCharType(nextChar);
				// 读出特殊符号表
				map<string, int> specialMap = lextoken.getLexicalHashMap();
				string char2= thisChar + nextChar;
				if (nextCharType == "SPECIAL" && specialMap.count(thisChar+nextChar)) {
					int lexno = lextoken.getToken(thisChar + nextChar);
                    ret << "(" << lexno << "," << thisChar + nextChar << ")    ";
					srcCode = srcCode.c_str() + 2;
				}
				else {// 否则只看当前特殊字符
					int lexno = lextoken.getToken(thisChar);
                    ret << "(" << lexno << "," << thisChar << ")    ";
					srcCode = srcCode.c_str() + 1;
				}
			}
			else {
				int lexno = lextoken.getToken(thisChar);
                ret << "(" << lexno << "," << thisChar << ")    ";
				srcCode = srcCode.c_str() + 1;
			}
		}
	}
    return ret;
}

string LexicalAnalysis::getCharType(string str) {
	if ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')) {
		return "LETTER";
	}
	else if(str[0]>='0'&&str[0]<='9'){
		return "NUMBER";
	}
	else if (str[0] == ' ' || str[0] == '\t' || str[0] == '\n' || str[0] == '\r') {
		return "BLANK";
	}
	else {
		return "SPECIAL";
	}

}

string LexicalAnalysis::printWordMap(string srcFile) {
	ReadSources rs(srcFile);
	list<string>srcCodeList = rs.getCodeList();
	int length = srcCodeList.size() + 1;
    // list<string>::iterator itor = srcCodeList.begin();
    /*
	cout << endl << "源码" << endl;
	for (int i = 1; i < length; i++) {
		cout << "line " << i << " ";
		cout << *itor++ << endl;
	}
	cout << endl << "词法分析结果" << endl;
    */
    string ret;
	for (int i = 1; i < length ; i++) {
        stringstream t;
        t<< "line " << i<<" ";
        ret+=t.str();
        ret+=getWordMap(srcCodeList.front()).str();
        ret+="\n" ;
		srcCodeList.pop_front();
	}
    return ret;
}
/*
void LexicalAnalysis::buildTokenList(string srcFile) {
	ReadSources rs(srcFile);
	list<string>srcCodeList = rs.getCodeList();
	int length = srcCodeList.size() + 1;
	list<string>::iterator itor = srcCodeList.begin();
	for (int i = 1; i < length; i++) {
		this->buildToken(srcCodeList.front());
		srcCodeList.pop_front();
	}
}
*/
void LexicalAnalysis::buildTokenVector(string srcFile)
{
	ReadSources rs(srcFile);
	list<string>srcCodeList = rs.getCodeList();
	int length = srcCodeList.size() + 1;
	list<string>::iterator itor = srcCodeList.begin();
	regex regexID("^[a-zA-Z][a-zA-Z0-9]{0,}");
    // regex regexNUM("^[0-9][0-9]{0,}");
    regex regexNUM("^[0-9]{0,}[.]{0,2}[0-9][0-9]{0,}");
    LexicalHashToken lextoken(this->loc);
	for (int i = 1; i < length; i++) {
		string srcCode = srcCodeList.front();
		while (!srcCode.empty()) {
			string thisChar = srcCode.substr(0, 1);
			string charType = getCharType(thisChar);
			std::smatch matchResult;
			if (charType == "LETTER") {
				if (regex_search(srcCode, matchResult, regexID)) {
					// 如果是关键字
					if (lextoken.isKeyWord(matchResult.str())) {
						int lexno = lextoken.getToken(matchResult.str());
                        this->TokenList.push_back(Token(lexno, matchResult.str(),i));
						// cout << "(" << lexno << "," << matchResult.str() << ")    ";
					}
					// 否则可能是ID
					else {
						int lexno = lextoken.getToken("id");
                        this->TokenList.push_back(Token(lexno, matchResult.str(),string("id"),i));
						// cout << "(" << lexno << "," << matchResult.str() << ")    ";
					}
					srcCode = srcCode.c_str() + int(matchResult.length());
				}
			}
			else if (charType == "NUMBER") {
				if (regex_search(srcCode, matchResult, regexNUM)) {
					// 如果是数字
					int lexno = lextoken.getToken("num");
                    this->TokenList.push_back(Token(lexno, matchResult.str(),string("num"),i));
					//cout << "(" << lexno << "," << matchResult.str() << ")    ";

					srcCode = srcCode.c_str() + int(matchResult.length());
				}
			}
			else if (charType == "BLANK") {
				srcCode = srcCode.c_str() + 1;
			}
			// 除数字空格字母以外的符号
			else if (charType == "SPECIAL") {
				// 先往后读一位，因为符号可能是>=这样的
				if (srcCode.length() > 1) {
					string nextChar = srcCode.substr(1, 1);
					string nextCharType = getCharType(nextChar);
					// 读出特殊符号表
					map<string, int> specialMap = lextoken.getLexicalHashMap();
					string char2 = thisChar + nextChar;
					if (nextCharType == "SPECIAL" && specialMap.count(thisChar + nextChar)) {
						int lexno = lextoken.getToken(thisChar + nextChar);
                        this->TokenList.push_back(Token(lexno, thisChar + nextChar,i));
						// cout << "(" << lexno << "," << thisChar + nextChar << ")    ";
						srcCode = srcCode.c_str() + 2;
					}
					else {// 否则只看当前特殊字符
						int lexno = lextoken.getToken(thisChar);
                        this->TokenList.push_back(Token(lexno, thisChar,i));
						// cout << "(" << lexno << "," << thisChar << ")    ";
						srcCode = srcCode.c_str() + 1;
					}
				}
				else {
					int lexno = lextoken.getToken(thisChar);
					// cout << "(" << lexno << "," << thisChar << ")    ";
                    this->TokenList.push_back(Token(lexno, thisChar,i));
					srcCode = srcCode.c_str() + 1;
				}
			}
		}
		srcCodeList.pop_front();
	}
}

vector<Token> LexicalAnalysis::getTokenList() {
	return this->TokenList;
}

