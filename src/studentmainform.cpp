/*
File Name: studentmainform.h
Description: Implement StudentMainForm
Author: unconsolable
*/

#include "studentmainform.h"
#include "ui_studentmainform.h"
// 每种具体问题的定义
#include "singlechoiceproblem.h"
#include "multiplechoiceproblem.h"
#include "judgementproblem.h"
#include "writeproblem.h"
#include <cstdlib>
// 用到的库
#include <QFileDialog>
#include <fstream>
#include <QMessageBox>
#include <QGridLayout>
#include <QTextEdit>
#include <sstream>
// 对每个选项说明的设置
#define SetChoiceDesc()                                                                                          \
    do                                                                                                           \
    {                                                                                                            \
        t_strVecChoiceDescOrKeyWords = &(static_cast<ChoiceProblem *>(curProblem)->getAnswerList());             \
        m_studentProblemWidget->m_labelProblemChoiceA->setText(tr(t_strVecChoiceDescOrKeyWords->at(0).c_str())); \
        m_studentProblemWidget->m_labelProblemChoiceB->setText(tr(t_strVecChoiceDescOrKeyWords->at(1).c_str())); \
        m_studentProblemWidget->m_labelProblemChoiceC->setText(tr(t_strVecChoiceDescOrKeyWords->at(2).c_str())); \
        m_studentProblemWidget->m_labelProblemChoiceD->setText(tr(t_strVecChoiceDescOrKeyWords->at(3).c_str())); \
    } while (0)
StudentMainForm::StudentMainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentMainForm)
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
    m_studentProblemWidget = new StudentProblemWidget(ui->m_widgetProblem);
    // QListView双击事件与slot绑定
    connect(ui->m_listViewProblem, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(on_m_problemListItemDoubleClicked(const QModelIndex&)));
}
// 析构函数
StudentMainForm::~StudentMainForm()
{
    delete ui;
    CheckDeleteSetNull(m_problemListModel);
    CheckDeleteSetNull(m_studentProblemWidget);
}
// 点击打开菜单后的事件
void StudentMainForm::onFileOpen()
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
void StudentMainForm::onFileSave()
{
    if (abs(m_doubleTotalMark - 100) >= 0.001)
    {
        QMessageBox::information(this, tr("Error"), tr("未到100分,检查后提交"));
    }
    else
    {
        QMessageBox::information(this, tr("Accepted"), tr("到100分,已经提交"));
    }
}
void StudentMainForm::on_m_problemListItemDoubleClicked(const QModelIndex& index)
{
    // 获得下标与对应题目的指针
    m_intCurProblemIndex = index.row();
    auto curProblem = (*m_problemListModel)[m_intCurProblemIndex];
    // 绘制题面
    m_studentProblemWidget->onProblemTypeChanged(curProblem->getType());
    // 设置题型
    m_studentProblemWidget->m_labelProblemType->setText(tr(curProblem->convertType()));
    // 设置分值
    m_studentProblemWidget->m_labelProblemMark->setText(QString().number(curProblem->getMark(),'f',1) + QString("分"));
    // 设置题目描述
    m_studentProblemWidget->m_labelProblemDesc->setText(tr(curProblem->getDescription().c_str()));
    // 根据题目类型不同分别显示不同内容
    const std::vector<std::string> *t_strVecChoiceDescOrKeyWords = nullptr;
    std::ostringstream oSStrmKeyWords;
    switch (curProblem->getType())
    {
    case SINGLE:
        SetChoiceDesc();
        break;
    case MULTIPLE:
        SetChoiceDesc();
        break;
    case JUDGEMENT:
        break;
    case WRITE:
        break;
    default:
        break;
    }
}

void StudentMainForm::on_m_buttonFinish_clicked()
{
    QVariant b_variantForAnswer;
    QVector<QVariant> b_variantMultipleAnswer;
    QVariant b_variantTempChoiceAnswer;
    switch ((*m_problemListModel)[m_intCurProblemIndex]->getType())
    {
    case SINGLE:
        // 判断单选的答案
        if (m_studentProblemWidget->m_radioProblemRightChoiceA->isChecked())
            b_variantForAnswer.setValue('A');
        else if (m_studentProblemWidget->m_radioProblemRightChoiceB->isChecked())
            b_variantForAnswer.setValue('B');
        else if (m_studentProblemWidget->m_radioProblemRightChoiceC->isChecked())
            b_variantForAnswer.setValue('C');
        else
            b_variantForAnswer.setValue('D');
        break;
    case MULTIPLE:
        // 添加多选
        if (m_studentProblemWidget->m_chkBoxProblemRightChoiceA->checkState() == Qt::Checked)
        {
            b_variantTempChoiceAnswer.setValue('A');
            b_variantMultipleAnswer.push_back(b_variantTempChoiceAnswer);
        }
        if (m_studentProblemWidget->m_chkBoxProblemRightChoiceB->checkState() == Qt::Checked)
        {
            b_variantTempChoiceAnswer.setValue('B');
            b_variantMultipleAnswer.push_back(b_variantTempChoiceAnswer);
        }
        if (m_studentProblemWidget->m_chkBoxProblemRightChoiceC->checkState() == Qt::Checked)
        {
            b_variantTempChoiceAnswer.setValue('C');
            b_variantMultipleAnswer.push_back(b_variantTempChoiceAnswer);
        }
        if (m_studentProblemWidget->m_chkBoxProblemRightChoiceD->checkState() == Qt::Checked)
        {
            b_variantTempChoiceAnswer.setValue('D');
            b_variantMultipleAnswer.push_back(b_variantTempChoiceAnswer);
        }
        // 设置答案序列
        b_variantForAnswer.setValue(b_variantMultipleAnswer);
        break;
    case JUDGEMENT:
        // 设置判断题答案
        b_variantForAnswer.setValue(m_studentProblemWidget->m_chkBoxIsRight->checkState() == Qt::Checked);
        break;
    case WRITE:
        // 设置简答题答案
        b_variantForAnswer.setValue(m_studentProblemWidget->m_plainTextWriteAnswer->toPlainText());
        break;
    }
    // 计算增加的成绩
    m_doubleTotalMark += (*m_problemListModel)[m_intCurProblemIndex]->checkAnswer(b_variantForAnswer);
    QMessageBox::information(this, tr("Information"), QString().number(m_doubleTotalMark,'f',1));
}
