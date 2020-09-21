/*
文件名: teachermainform.h
版本: 1.0
目的与主要功能: 实现教师窗体类
创建日期: 2020.9.3
描述: 实现教师窗体类
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/

#include "teachermainform.h"
#include "ui_teachermainform.h"
// 每种具体问题的定义
#include "singlechoiceproblem.h"
#include "multiplechoiceproblem.h"
#include "judgementproblem.h"
#include "writeproblem.h"
// 用到的库
#include <QFileDialog>
#include <fstream>
#include <QMessageBox>
#include <QGridLayout>
#include <QTextEdit>
#include <sstream>
// 对每个选项说明的设置
#define SetChoiceDesc()                                                                                             \
    do                                                                                                              \
    {                                                                                                               \
        t_strVecChoiceDescOrKeyWords = &(static_cast<ChoiceProblem *>(curProblem)->getAnswerList());                \
        m_teacherProblemWidget->m_lineEditProblemChoiceA->setText(tr(t_strVecChoiceDescOrKeyWords->at(0).c_str())); \
        m_teacherProblemWidget->m_lineEditProblemChoiceB->setText(tr(t_strVecChoiceDescOrKeyWords->at(1).c_str())); \
        m_teacherProblemWidget->m_lineEditProblemChoiceC->setText(tr(t_strVecChoiceDescOrKeyWords->at(2).c_str())); \
        m_teacherProblemWidget->m_lineEditProblemChoiceD->setText(tr(t_strVecChoiceDescOrKeyWords->at(3).c_str())); \
    }                                                                                                               \
    while (0)
// 对单选和多选选项的设定
// 运算的需要加括号,成员选择不需括号
#define SetChoiceButtonOrBox(ansChar, ControlA, ControlB, ControlC, ControlD, Method, State) \
    do                                                                                       \
    {                                                                                        \
        switch ((ansChar))                                                                   \
        {                                                                                    \
        case 'A':                                                                            \
            m_teacherProblemWidget->ControlA->Method((State));                               \
            break;                                                                           \
        case 'B':                                                                            \
            m_teacherProblemWidget->ControlB->Method((State));                               \
            break;                                                                           \
        case 'C':                                                                            \
            m_teacherProblemWidget->ControlC->Method((State));                               \
            break;                                                                           \
        case 'D':                                                                            \
            m_teacherProblemWidget->ControlD->Method((State));                               \
            break;                                                                           \
        }                                                                                    \
    }                                                                                        \
    while (0)
// 将多选选项添加到vector中
#define AddMultipleChoiceInVector(method, choiceChar)               \
    if (m_teacherProblemWidget->method->checkState() == Qt::Checked) \
            b_charVecRightAns.push_back((choiceChar));

/***************************
 * Name:
 *   TeacherMainForm
 * Input:
 *   parent 父窗体
 * Return:
 *   none
 * Description:
 *   构造出题系统窗体
 ***************************/

TeacherMainForm::TeacherMainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherMainForm)
{
    ui->setupUi(this);
    m_pProblemListModel = new ProblemListModel();
    // 设置View对应的Model
    ui->m_listViewProblem->setModel(m_pProblemListModel);
    // 设置选择模式为单选
    ui->m_listViewProblem->setSelectionMode(QAbstractItemView::SingleSelection);
    // open menu和slot绑定
    connect(ui->m_actionOpenFile, SIGNAL(triggered()), this, SLOT(onFileOpen()));
    // save menu和slot绑定
    connect(ui->m_actionSaveFile, SIGNAL(triggered()), this, SLOT(onFileSave()));
    // new menu和slot绑定
    connect(ui->m_actionNewFile, SIGNAL(triggered()), this, SLOT(onFileNew()));
    // 添加TeacherProblemWidget
    m_teacherProblemWidget = new TeacherProblemWidget(ui->m_widgetProblem);
    // QListView双击事件与slot绑定
    connect(ui->m_listViewProblem, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(on_m_problemListItemDoubleClicked(const QModelIndex&)));
}

/***************************
 * Name:
 *   ~TeacherMainForm
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   析构出题系统窗体
 ***************************/

TeacherMainForm::~TeacherMainForm()
{
    delete ui;
    // 非空再delete并置0
    CheckDeleteSetNull(m_pProblemListModel);
    CheckDeleteSetNull(m_teacherProblemWidget);
}

/***************************
 * Name:
 *   onFileOpen
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   点击打开菜单后的事件
 ***************************/

void TeacherMainForm::onFileOpen()
{
    // 获得文件路径
    QString b_qStrFileDir = QFileDialog::getOpenFileName(this,"Open Paper File","/","JSON files(*.json)");
    // 打开文件
    std::ifstream b_ifStrmProblemList(b_qStrFileDir.toStdString());
    // 判断流是否成功打开
    if (!b_ifStrmProblemList)
    {
        QMessageBox::information(this, "Error", tr("文件打开失败"));
        return;
    }
    // 读入的总字符串
    std::string b_strProListInfo;
    // 读入的一部分字符串
    std::string t_strInput;
    while (b_ifStrmProblemList >> t_strInput)
    {
        // 读入账户文件形成JSON字符串
        b_strProListInfo += t_strInput + ' ';
    }
    rapidjson::Document b_jsonDocProList;
    if (b_jsonDocProList.Parse(b_strProListInfo.c_str()).HasParseError())
    {
        QMessageBox::information(this, "Error", tr("试卷解析失败"));
        return;
    }
    if (!m_pProblemListModel->fromJsonDocument(b_jsonDocProList))
        QMessageBox::information(this, "Error", tr("转为Model失败"));
}
/***************************
 * Name:
 *   onFileSave
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   点击保存菜单后发生的事件
 ***************************/
void TeacherMainForm::onFileSave()
{
    QString b_qStrFileDir = QFileDialog::getOpenFileName(this,"Open Paper File","/","JSON files(*.json)");
    std::ofstream b_ofStrmProblemList(b_qStrFileDir.toStdString());
    if (!b_ofStrmProblemList)
    {
        QMessageBox::information(this, "Error", tr("文件打开失败"));
        return;
    }
    std::string res = m_pProblemListModel->toJsonString();
    b_ofStrmProblemList << res;
}
/***************************
 * Name:
 *   on_m_buttonRm_clicked
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   点击删除按钮后发生的事件
 ***************************/
void TeacherMainForm::on_m_buttonRm_clicked()
{
    // 获得选择的Model
    auto selectModel = ui->m_listViewProblem->selectionModel();
    if (selectModel)
    {
        // 获得对应下标
        QModelIndexList indexList = selectModel->selectedIndexes();
        // 需要检测大小,避免未点击的UB
        if (!indexList.size())
        {
            QMessageBox::information(this, tr("错误"), tr("未点击"));
            return;
        }
        for (auto &i : indexList)
        {
            m_pProblemListModel->rmProblem(i.row());
        }
    }
}
/***************************
 * Name:
 *   on_m_problemListItemDoubleClicked
 * Input:
 *   index 点击的数据坐标
 * Return:
 *   none
 * Description:
 *   双击时实现题目选中
 ***************************/
void TeacherMainForm::on_m_problemListItemDoubleClicked(const QModelIndex& index)
{
    // 获得选择的下标和对应题目的指针
    m_intCurProblemIndex = index.row();
    auto curProblem = (*m_pProblemListModel)[m_intCurProblemIndex];
    // 绘制题面
    m_teacherProblemWidget->onProblemTypeChanged(curProblem->getType());
    // 设置题型
    m_teacherProblemWidget->m_comboBoxProblemType->setCurrentIndex(curProblem->getType());
    // 设置分值
    m_teacherProblemWidget->m_lineEditProblemMark->setText(QString().number(curProblem->getMark(),'f',1));
    // 设置题目描述
    m_teacherProblemWidget->m_plainTextEditProblemDesc->setPlainText(tr(curProblem->getDescription().c_str()));
    // 根据题目类型不同分别显示不同内容
    const std::vector<std::string> *t_strVecChoiceDescOrKeyWords = nullptr;
    std::ostringstream oSStrmKeyWords;
    switch (curProblem->getType())
    {
    case SINGLE:
        // 设置选项文字
        SetChoiceDesc();
        // 设置正确答案
        SetChoiceButtonOrBox(static_cast<SingleChoiceProblem*>(curProblem)->getRightAns(), m_radioProblemRightChoiceA, m_radioProblemRightChoiceB, m_radioProblemRightChoiceC, m_radioProblemRightChoiceD, setChecked, true);
        break;
    case MULTIPLE:
        // 设置选项文字
        SetChoiceDesc();
        // 设置正确答案(组)
        for (auto b_charEachAns : static_cast<MultipleChoiceProblem*>(curProblem)->getRightAns())
        {
            SetChoiceButtonOrBox(b_charEachAns, m_chkBoxProblemRightChoiceA, m_chkBoxProblemRightChoiceB, m_chkBoxProblemRightChoiceC, m_chkBoxProblemRightChoiceD, setCheckState, Qt::Checked);
        }
        break;
    case JUDGEMENT:
        // 设置正确答案
        if (static_cast<JudgementProblem*>(curProblem)->getRightAns())
            m_teacherProblemWidget->m_chkBoxIsRight->setCheckState(Qt::Checked);
        else
            m_teacherProblemWidget->m_chkBoxIsRight->setCheckState(Qt::Unchecked);
        break;
    case WRITE:
        // 设置关键词组
        t_strVecChoiceDescOrKeyWords = &(static_cast<WriteProblem*>(curProblem)->getKeyWords());
        // 每组关键词之间以空格分离
        for (const auto &t_strEachKeyWord : *t_strVecChoiceDescOrKeyWords)
        {
            oSStrmKeyWords << t_strEachKeyWord << std::endl;
        }
        // 显示关键词
        m_teacherProblemWidget->m_plainTextKeyWordList->setPlainText(tr(oSStrmKeyWords.str().c_str()));
        break;
    }
}
/***************************
 * Name:
 *   on_m_buttonFinish_clicked
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   完成修改时,保存题目信息
 ***************************/
void TeacherMainForm::on_m_buttonFinish_clicked()
{
    bool isMarkDouble = false;
    m_teacherProblemWidget->m_lineEditProblemMark->text().toDouble(&isMarkDouble);
    if (!isMarkDouble)
    {
      QMessageBox::information(this, "Error", "分值非数字，重新检查");
      return;
    }
    // 检查分值是否为数字
    // 通用信息不再另外保存
    // 判断题的对错也不再另外保存
    // 题目描述信息
    std::vector<std::string> b_strVecChoiceDesc;
    // 多选题选项
    std::vector<char> b_charVecRightAns;
    // 简答题关键词
    std::vector<std::string> b_strVecRightAns;
    // 单选题正确选项
    char b_charRightAns = 'A';
    // 将需要另外保存的数据存储
    // 保存选项描述
    if (m_teacherProblemWidget->m_intLastProblemTypeIndex == SINGLE || m_teacherProblemWidget->m_intLastProblemTypeIndex == MULTIPLE)
    {
        b_strVecChoiceDesc.push_back(m_teacherProblemWidget->m_lineEditProblemChoiceA->text().toStdString());
        b_strVecChoiceDesc.push_back(m_teacherProblemWidget->m_lineEditProblemChoiceB->text().toStdString());
        b_strVecChoiceDesc.push_back(m_teacherProblemWidget->m_lineEditProblemChoiceC->text().toStdString());
        b_strVecChoiceDesc.push_back(m_teacherProblemWidget->m_lineEditProblemChoiceD->text().toStdString());
        // 保存单选
        if (m_teacherProblemWidget->m_intLastProblemTypeIndex == SINGLE)
        {
            if (m_teacherProblemWidget->m_radioProblemRightChoiceA->isChecked())
                b_charRightAns = 'A';
            else if (m_teacherProblemWidget->m_radioProblemRightChoiceB->isChecked())
                b_charRightAns = 'B';
            else if (m_teacherProblemWidget->m_radioProblemRightChoiceC->isChecked())
                b_charRightAns = 'C';
            else
                b_charRightAns = 'D';
        }
        // 保存多选答案
        if (m_teacherProblemWidget->m_intLastProblemTypeIndex == MULTIPLE)
        {
            AddMultipleChoiceInVector(m_chkBoxProblemRightChoiceA,'A');
            AddMultipleChoiceInVector(m_chkBoxProblemRightChoiceB,'B');
            AddMultipleChoiceInVector(m_chkBoxProblemRightChoiceC,'C');
            AddMultipleChoiceInVector(m_chkBoxProblemRightChoiceD,'D');
        }
    }
    // 保存简答关键词
    if (m_teacherProblemWidget->m_intLastProblemTypeIndex == WRITE)
    {
        std::istringstream isStrm(m_teacherProblemWidget->m_plainTextKeyWordList->toPlainText().toStdString());
        std::string tmpStr;
        while (isStrm >> tmpStr)
        {
            b_strVecRightAns.push_back(tmpStr);
        }
    }
    // 为实现简便，不再标记每个数据变化
    // 而是统一先删除原来，再写新题目
    m_pProblemListModel->rmProblem(m_intCurProblemIndex);
    // 将题目的各项数据传入函数
    switch (m_teacherProblemWidget->m_intLastProblemTypeIndex)
    {
    case SINGLE:
        m_pProblemListModel->addProblem
                (m_intCurProblemIndex, m_teacherProblemWidget->m_lineEditProblemMark->text().toDouble(),
                 m_teacherProblemWidget->m_plainTextEditProblemDesc->toPlainText().toStdString(),
                 b_strVecChoiceDesc, b_charRightAns);
        break;
    case MULTIPLE:
        m_pProblemListModel->addProblem
                (m_intCurProblemIndex, m_teacherProblemWidget->m_lineEditProblemMark->text().toDouble(),
                 m_teacherProblemWidget->m_plainTextEditProblemDesc->toPlainText().toStdString(),
                 b_strVecChoiceDesc, b_charVecRightAns);
        break;
    case JUDGEMENT:
        m_pProblemListModel->addProblem
                (m_intCurProblemIndex, m_teacherProblemWidget->m_lineEditProblemMark->text().toDouble(),
                 m_teacherProblemWidget->m_plainTextEditProblemDesc->toPlainText().toStdString(),
                 m_teacherProblemWidget->m_chkBoxIsRight->checkState() == Qt::Checked);
        break;
    case WRITE:
        m_pProblemListModel->addProblem
                (m_intCurProblemIndex, m_teacherProblemWidget->m_lineEditProblemMark->text().toDouble(),
                 m_teacherProblemWidget->m_plainTextEditProblemDesc->toPlainText().toStdString(),
                 b_strVecRightAns);
        break;
    }


}
/***************************
 * Name:
 *   on_m_buttonAdd_clicked
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   添加一个模板问题,可以自行修改保存
 ***************************/
void TeacherMainForm::on_m_buttonAdd_clicked()
{
    m_pProblemListModel->addProblem(m_pProblemListModel->rowCount(), 1.0, "这是一个题目模板,模板为选择题,根据需求自行更改",{"1","2","3","4"}, 'A');
}
/***************************
 * Name:
 *   onFileNew
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   新建一个空白问题文件,用于存储问题
 ***************************/
void TeacherMainForm::onFileNew()
{
    // 获得文件路径并打开
    QString b_qStrFileDir = QFileDialog::getOpenFileName(this,"Open New File","/","JSON files(*.json)");
    std::ofstream b_ofStrmProblemList(b_qStrFileDir.toStdString());
    // 检查是否成功打开
    if (!b_ofStrmProblemList)
    {
        QMessageBox::information(this, "Error", tr("文件打开失败"));
        return;
    }
    std::string emptyFile("{\n\t\"problem\":[\n\t]\n}");
    b_ofStrmProblemList << emptyFile;
}

