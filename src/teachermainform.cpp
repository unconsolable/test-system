/*
File Name: teachermainform.h
Description: Implement TeacherMainForm
Author: unconsolable
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
// 对选项文字的说明
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

TeacherMainForm::TeacherMainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherMainForm)
{
    ui->setupUi(this);
    m_problemListModel = new ProblemListModel();
    // 设置View对应的Model
    ui->m_listViewProblem->setModel(m_problemListModel);
    // 设置选择模式为单选
    ui->m_listViewProblem->setSelectionMode(QAbstractItemView::SingleSelection);
    // open menu和slot绑定
    connect(ui->m_actionOpenFile, SIGNAL(triggered()), this, SLOT(onFileOpen()));
    // save menu和slot绑定
    connect(ui->m_actionSaveFile, SIGNAL(triggered()), this, SLOT(onFileSave()));
    // 添加TeacherProblemWidget
    m_teacherProblemWidget = new TeacherProblemWidget(ui->m_widgetProblem);
}

TeacherMainForm::~TeacherMainForm()
{
    delete ui;
    CheckDeleteSetNull(m_problemListModel);
    CheckDeleteSetNull(m_teacherProblemWidget);
}
// 点击打开菜单后的事件
void TeacherMainForm::onFileOpen()
{
    // 获得文件路径
    QString b_qStrFileDir = QFileDialog::getOpenFileName(this,"Open Paper File","/","JSON files(*.json)");
    // 打开文件
    std::ifstream b_ifStrmProblemList(b_qStrFileDir.toStdString());
    if (!b_ifStrmProblemList)
    {
        QMessageBox::information(this, "Error", tr("文件打开失败"));
        return;
    }
    std::string b_strProListInfo;
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
    if (!m_problemListModel->fromJsonDocument(b_jsonDocProList))
        QMessageBox::information(this, "Error", tr("转为Model失败"));
}
// 点击保存菜单后的事件
void TeacherMainForm::onFileSave()
{
    QString b_qStrFileDir = QFileDialog::getOpenFileName(this,"Open Paper File","/","JSON files(*.json)");
    std::ofstream b_ofStrmProblemList(b_qStrFileDir.toStdString());
    if (!b_ofStrmProblemList)
    {
        QMessageBox::information(this, "Error", tr("文件打开失败"));
        return;
    }
    std::string res = m_problemListModel->toJsonString();
    b_ofStrmProblemList << res;
}
// 删除功能
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
            m_problemListModel->rmProblem(i.row());
        }
    }
}

void TeacherMainForm::on_m_buttonSelect_clicked()
{
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
        // 获得选择的下标和对应题目的指针
        curProblemIndex = indexList[0].row();
        auto curProblem = (*m_problemListModel)[curProblemIndex];
        // 绘制题面
        m_teacherProblemWidget->onProblemTypeChanged(curProblem->getType());
        // 设置题型
        m_teacherProblemWidget->m_comboBoxProblemType->setCurrentIndex(curProblem->getType());
        // 设置分值
        m_teacherProblemWidget->m_lineEditProblemMark->setText(QString().number(curProblem->getMark(),'f',1));
        // 设置题面
        m_teacherProblemWidget->m_plainTextEditProblemDesc->setPlainText(tr(curProblem->getDescription().c_str()));
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
}
