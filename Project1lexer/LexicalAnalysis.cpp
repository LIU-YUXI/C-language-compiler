#include "./LexicalAnalysis.h"
#include <iostream>
void LexicalAnalysis::getWordMap(string srcCode)
{
	if (srcCode == "")
		return;
	regex regexID("^[a-zA-Z][a-zA-Z0-9]{0,}");
	regex regexNUM("^[0-9][0-9]{0,}");
	LexicalHashToken lextoken;
	while (!srcCode.empty()) {
		string thisChar = srcCode.substr(0, 1);
		string charType = getCharType(thisChar);
		std::smatch matchResult;
		if (charType == "LETTER") {
			if (regex_search(srcCode, matchResult, regexID)) {
				// ����ǹؼ���
				if (lextoken.isKeyWord(matchResult.str())) {
					int lexno = lextoken.getToken(matchResult.str());
					cout << "(" << lexno << "," << matchResult.str() << ")    ";
				}
				// ���������ID
				else {
					int lexno = lextoken.getToken("ID");
					cout << "(" << lexno << "," << matchResult.str() << ")    ";
				}
				srcCode = srcCode.c_str() + int( matchResult.length());
			}
		}
		else if (charType == "NUMBER") {
			if (regex_search(srcCode, matchResult, regexNUM)) {
				// ���������
				int lexno = lextoken.getToken("NUM");
				cout << "(" << lexno << "," << matchResult.str() << ")    ";

				srcCode = srcCode.c_str() + int(matchResult.length());
			}
		}
		else if (charType=="BLANK") {
			srcCode = srcCode.c_str() + 1;
		}
		// �����ֿո���ĸ����ķ���
		else if (charType=="SPECIAL") {
			// �������һλ����Ϊ���ſ�����>=������
			if (srcCode.length() > 1) {
				string nextChar = srcCode.substr(1, 2);
				string nextCharType = getCharType(nextChar);
				// ����������ű�
				hash_map<string, int> specialMap = lextoken.getLexicalHashMap();
				if (nextCharType == "SPECIAL" && specialMap.count(thisChar+nextChar)) {
					int lexno = lextoken.getToken(thisChar + nextChar);
					cout << "(" << lexno << "," << thisChar + nextChar << ")    ";
					srcCode = srcCode.c_str() + 2;
				}
				else {// ����ֻ����ǰ�����ַ�
					int lexno = lextoken.getToken(thisChar);
					cout << "(" << lexno << "," << thisChar << ")    ";
					srcCode = srcCode.c_str() + 1;
				}
			}
			else {
				int lexno = lextoken.getToken(thisChar);
				cout << "(" << lexno << "," << thisChar << ")    ";
				srcCode = srcCode.c_str() + 1;
			}
		}
	}
}

string LexicalAnalysis::getCharType(string str) {
	if ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'a' && str[0] <= 'z')) {
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

void LexicalAnalysis::printWordMap(string srcFile) {
	ReadSources rs(srcFile);
	list<string>srcCodeList = rs.getCodeList();
	for (int i = 1; i < srcCodeList.size() + 1; i++) {
		cout << "line " << i;
		getWordMap(srcCodeList.front());
		cout << endl;
		srcCodeList.pop_front();
	}
}

int main()
{
	LexicalAnalysis lexer;
	lexer.printWordMap("./src.txt");
}
