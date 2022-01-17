#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;
//四元式
struct Quaternary
{
	int index;//四元式标号
	string operatorType;//操作类型
	string arg1;//操作数1
	string arg2;//操作数2
	string result;//结果
};

//语义分析中的符号
struct SemanticSymbol
{
	string token; //token类型
	string value; //值
	int row;//行
	int tableIndex;//符号所在table的index
	int index;//符号在table内部的index
};

//标识符信息，即函数、变量、临时变量、常量的具体信息
struct IdentifierInfo
{
	//几种标识符类型，分别为函数、变量、临时变量、常量、返回值
	enum IdentifierType { Function, Variable, TempVar, ConstVar, ReturnVar };

	IdentifierType IdentifierType;//标识符的类型
	string SpecifierType;//变(常)量类型/函数返回类型
	string IdentifierName;//标识符名称/常量值
	int FunctionParameterNum;//函数参数个数
	int FunctionEntry;//函数入口地址(四元式的标号)
	int FunctionTableIndex;//函数的函数符号表在整个程序的符号表列表中的索引

};

//语义分析中的符号表
struct SemanticSymbolTable
{
	//几种表的类型，分别为全局表、函数表、块级表、临时表
	enum TableType { GlobalTable, FunctionTable, BlockTable, TempTable };

	TableType tableType;//表的类型
	vector<IdentifierInfo> table;//符号表
	string tableName;//表名

	//构造函数
	SemanticSymbolTable(const TableType tableType_, const string tableName_);
	//寻找一个变量
	int FindSymbol(const string idName);
	//加入一个变量，返回加入的位置
	int AddSymbol(const IdentifierInfo id);
};
// 活动记录的成员
struct stackToken {
	enum tokenType {ADDR,PARAM,PARAMNUM};
	tokenType type;
	int addr;// 返回地址
	int num;
	vector<IdentifierInfo> param;// 参数和所有局部变量

};
//语义分析
class SemanticAnalysis
{
public:
	vector<Quaternary> quaternary;//四元式
	int mainIndex;//main函数对应的四元式标号
	int backpatchingLevel;//回填层次
	vector<int> backpatchingList;//回填列表
	int nextQuaternaryIndex;//下一个四元式标号
	int tmpVarCount;//临时变量计数
	vector<SemanticSymbol> symbolList;//语义分析过程的符号流
	vector<SemanticSymbolTable> tables;//程序所有符号表
	vector<int> currentTableStack;//当前作用域对应的符号表索引栈
	stack<stackToken> FunStack;
	//构造函数
	SemanticAnalysis();
	//将所有的符号信息放入symbol_list
	void AddSymbolToList(const SemanticSymbol symbol);
	//分析过程
	int Analysis(const string productionLeft, const vector<string> productionRight);
	//打印四元式表
	void PrintQuaternary(const string filePath);
	//打印所有符号表
	void PrintSymbolTable();
	//打印单张符号表
	void PrintOneTable(SemanticSymbolTable SingleTable);
private:

	int AnalysisProduction_Program(const string production_left, const vector<string> production_right);
	// int AnalysisProduction_StatString(const string production_left, const vector<string> production_right);
	int AnalysisProduction_State(const string production_left, const vector<string> production_right);
	int AnalysisProduction_CreateFunTable_m(const string production_left, const vector<string> production_right);
	// int AnalysisProduction_FunSpecifier(const string production_left, const vector<string> production_right);
	int AnalysisProduction_StatType(const string production_left, const vector<string> production_right);
	// int AnalysisProduction_VarStat(const string production_left, const vector<string> production_right);
	int AnalysisProduction_FuncStat(const string production_left, const vector<string> production_right);
	// int AnalysisProduction_FormalPara(const string production_left, const vector<string> production_right);
	// int AnalysisProduction_ParaList(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Para(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Block(const string production_left, const vector<string> production_right);
	// int AnalysisProduction_Inner(const string production_left, const vector<string> production_right);
	int AnalysisProduction_InnerVar(const string production_left, const vector<string> production_right);
	// int AnalysisProduction_String(const string production_left, const vector<string> production_right);
	// int AnalysisProduction_Sentense(const string production_left, const vector<string> production_right);
	// int AnalysisProduction_For(const string production_left, const vector<string> production_right);
	// int AnalysisProduction_CaseBlock(const string production_left, const vector<string> production_right);
	// int AnalysisProduction_DefaultBlock(const string production_left, const vector<string> production_right);
	//----
	int AnalysisProduction_Equal(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Return(const string production_left, const vector<string> production_right);
	int AnalysisProduction_While(const string production_left, const vector<string> production_right);
	int AnalysisProduction_If(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Else(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Whilem1(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Whilem2(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Ifm1(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Ifm2(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Ifm3(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Expr(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Relop(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Add(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Item(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Factor(const string production_left, const vector<string> production_right);
	int AnalysisProduction_FTYPE(const string production_left, const vector<string> production_right);
	int AnalysisProduction_Call(const string production_left, const vector<string> production_right);
	int AnalysisProduction_ActualPara(const string production_left, const vector<string> production_right);
	int AnalysisProduction_ActualParaList(const string production_left, const vector<string> production_right);
};