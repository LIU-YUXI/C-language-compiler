#include <QMessageBox>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include "syntax.h"
#include "ui_syntax.h"
#include "../Project1lexer/SyntaxAnalyzer.h"
Syntax::Syntax(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Syntax)
{
    // 设置背景颜色
    QWidget *m_pWidget = new QWidget(this);
    m_pWidget->setGeometry(0, 0, 1621, 957);
    QPalette pal(m_pWidget->palette());
    //pal.setColor(QPalette::Background, QColor(255,255,225));
    pal.setColor(QPalette::Background, QColor(241,254,255));
    m_pWidget->setAutoFillBackground(true);
    m_pWidget->setPalette(pal);
    m_pWidget->show();
    ui->setupUi(this);
    ui->fileBox1->setPlaceholderText("缺省test.txt");
    ui->fileBox2->setPlaceholderText("缺省src.c");
    connect(ui->startBtn, SIGNAL(clicked()), this, SLOT(start()));
    connect(ui->rstBtn, SIGNAL(clicked()), this, SLOT(reset()));
    connect(ui->picBtn,SIGNAL(clicked()), this, SLOT(showpic()));
}

Syntax::~Syntax()
{
    delete ui;
}
void Syntax::showpic(){
    cw=new ChildWindow();
    cw->setWindowTitle("Syntax tree");
    cw->show();
}
void Syntax::start(){
    QString proFile = ui->fileBox1->toPlainText();
    std::string proFilestr = proFile.toLatin1().data();
    if(proFilestr=="")
        proFilestr="test.txt";
    QString srcFile = ui->fileBox2->toPlainText();
    std::string srcFilestr = srcFile.toLatin1().data();
    if(srcFilestr=="")
        srcFilestr="src.c";
    ifstream src(proFilestr);
    if(!src){
        QMessageBox::information(this, "错误",QString("语法文件无法打开！") );
        return;
    }
    src.close();
    src.open(srcFilestr);
    if(!src){
        QMessageBox::information(this, "错误",QString("源码文件无法打开！") );
        return;
    }
    src.close();
    LR1 lr;
    lr.InputProduction(proFilestr);//输入二型文法
    lr.GetFirstAndFollow();//求First和Follow集合
    lr.LR1Analyse();
    lr.PrintActionAndGoto();//打印ACTION GOTO表
    SytaxAnalyzer syer(&lr);
    string ret=syer.Analysis(srcFilestr,"");
    syer.drawTree();
    // 显示词法分析结果
    LexicalAnalysis lexer(lr.loc);
    ui->outputBox4->append(QString::fromStdString(lexer.printWordMap(srcFilestr)));

    // 显示语法产生式
    ReadSources rp(proFilestr);
    list<string>proCodeList = rp.getCodeList();
    int proCodeListSize=proCodeList.size();
    for(int i=0;i<proCodeListSize;i++){
        ui->outputBox2->append(QString::fromStdString(proCodeList.front()));
        proCodeList.pop_front();
    }
    // 显示源码
    ReadSources rs(srcFilestr);
    list<string>srcCodeList = rs.getCodeList();
    int srcCodeListSize=srcCodeList.size();
    for(int i=0;i<srcCodeListSize;i++){
        ui->outputBox1->append(QString::fromStdString(srcCodeList.front()));
        srcCodeList.pop_front();
    }
    // 显示分析过程
    ui->outputBox3->append(QString::fromStdString(ret));
    cout<<syer.SemanticAnalyzer.output.str();
    syer.SemanticAnalyzer.ReturnQuaternary();
    syer.SemanticAnalyzer.ReturnSymbolTable();
    ui->outputBox5->append(QString::fromStdString(syer.SemanticAnalyzer.output.str()));
    this->t1 = new QStandardItemModel();
    t1->setHorizontalHeaderLabels({ "     ","     ","     ","符号表","     ","     ","     ","     " });
    QHeaderView *header = ui->table->verticalHeader();
    header->setHidden(true);// 隐藏行号
    int i=0;
    int row=0;
    int col=0;
    while (i<syer.SemanticAnalyzer.tablesOutput.size()) {
        if(syer.SemanticAnalyzer.tablesOutput[i]=="@"){
            col=0;
            row++;
            i++;
            continue;
        }
        // string hz="汉字";
        // ui->outputBox5->append(QString::fromLocal8Bit(syer.SemanticAnalyzer.tablesOutput[i].data()));
        t1->setItem(row, col, new QStandardItem(QString::fromLocal8Bit(syer.SemanticAnalyzer.tablesOutput[i].data())));
        col++;
        i++;
    }
    ui->table->setModel(t1);
    this->t2 = new QStandardItemModel();
    t2->setHorizontalHeaderLabels({ "                  运行栈                   " });
    QHeaderView *header2 = ui->table2->verticalHeader();
    header2->setHidden(true);// 隐藏行号
    i=0;

    while (!syer.SemanticAnalyzer.FunStack.empty()) {
        stringstream temp;
        stringstream temp2;
        if(syer.SemanticAnalyzer.FunStack.top().type==stackToken::PARAMNUM){
            temp<<"参数个数： "<<syer.SemanticAnalyzer.FunStack.top().num;
        }
        else if(syer.SemanticAnalyzer.FunStack.top().type==stackToken::ADDR){
            temp<<"返回地址： "<<syer.SemanticAnalyzer.FunStack.top().addr;
        }
        else if(syer.SemanticAnalyzer.FunStack.top().type==stackToken::PARAM){
            for(int j=0;j<syer.SemanticAnalyzer.FunStack.top().param.size();j++){
                if(j==0){
                    temp2<<"返回值:";
                    temp2<<syer.SemanticAnalyzer.FunStack.top().param[j].IDName<<" ";
                    t2->setItem(i, 0, new QStandardItem(QString::fromStdString(temp2.str().data())));
                    i++;
                    temp<<"形参变量与局部变量： ";
                }
                else
                    temp<<syer.SemanticAnalyzer.FunStack.top().param[j].IDName<<" ";
            }
        }
        t2->setItem(i, 0, new QStandardItem(QString::fromStdString(temp.str().data())));
        i++;
        syer.SemanticAnalyzer.FunStack.pop();
    }

    IDInfo mainIndex=syer.SemanticAnalyzer.tables[0].table[syer.SemanticAnalyzer.tables[0].FindSymbol("main")];
    stringstream temp4,temp5;
    temp4<<"main参数和局部变量： ";
    for(int j=0;j<syer.SemanticAnalyzer.tables[mainIndex.FunctionTableIndex].table.size();j++){
        if(j==0){
            temp5<<"返回值:";
            temp5<<syer.SemanticAnalyzer.tables[mainIndex.FunctionTableIndex].table[j].IDName<<" ";
            t2->setItem(i++, 0, new QStandardItem(QString::fromStdString(temp5.str().data())));
        }
        else
            temp4<<syer.SemanticAnalyzer.tables[mainIndex.FunctionTableIndex].table[j].IDName<<" ";
    }
    t2->setItem(i++, 0, new QStandardItem(QString::fromStdString(temp4.str().data())));
    stringstream temp3;
    temp3<<"main函数参数个数： "<<mainIndex.FunctionParameterNum;
    t2->setItem(i++, 0, new QStandardItem(QString::fromStdString(temp3.str().data())));
    t2->setItem(i++, 0, new QStandardItem("main函数返回地址"));

    ui->table2->setModel(t2);
    // system("tree.png");
    if(syer.is_syntax_error()){
        QMessageBox::information(this, "错误",QString("源代码有语法错误，详情请看\"语法分析\"") );
        return;
    }
    if(syer.SemanticAnalyzer.isError()){
        ui->outputBox5->append(QString::fromStdString(syer.SemanticAnalyzer.errorMsg.str()));
        QMessageBox::information(this, "错误",QString("源代码在语义分析过程中发现错误，详情请看\"语义分析结果-四元式\"") );
        return;
    }
}

void Syntax::reset(){
//    QPixmap *pixmap = new QPixmap("empty.png");
//    pixmap->scaled(ui->pic->size(), Qt::KeepAspectRatio);
//    ui->pic->setScaledContents(true);
//    ui->pic->clear();
//    ui->pic->setPixmap(*pixmap);
//    ui->pic->show();
    ui->outputBox1->clear();
    ui->outputBox2->clear();
    ui->outputBox3->clear();
    ui->outputBox4->clear();
    ui->outputBox5->clear();
    this->t1->clear();
    ui->table->setModel(t1);
    this->t2->clear();
    ui->table2->setModel(t2);
}
