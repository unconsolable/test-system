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
#include <numeric>
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

/***************************
 * Name:
 *   StudentMainForm
 * Input:
 *   parent 父窗体
 * Return:
 *   none
 * Description:
 *   构造考试系统页面
 ***************************/

StudentMainForm::StudentMainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentMainForm)
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
    // 添加TeacherProblemWidget
    m_studentProblemWidget = new StudentProblemWidget(ui->m_widgetProblem);
    // QListView双击事件与slot绑定
    connect(ui->m_listViewProblem, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(on_m_problemListItemDoubleClicked(const QModelIndex&)));
}

/***************************
 * Name:
 *   ~StudentMainForm
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   析构考试系统页面
 ***************************/

StudentMainForm::~StudentMainForm()
{
    delete ui;
    CheckDeleteSetNull(m_pProblemListModel);
    CheckDeleteSetNull(m_studentProblemWidget);
    if (m_doubleArrayAnswerMark)
    {
        // 需要单独使用数组的delete
        delete[] m_doubleArrayAnswerMark;
        m_doubleArrayAnswerMark = nullptr;
    }
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
    // 解析字符串，解析出错时报错
    if (b_jsonDocProList.Parse(b_strProListInfo.c_str()).HasParseError())
    {
        QMessageBox::information(this, "Error", tr("试卷解析失败"));
        return;
    }
    // 转换为ProblemListModel
    if (!m_pProblemListModel->fromJsonDocument(b_jsonDocProList))
        QMessageBox::information(this, "Error", tr("转为Model失败"));
    // 计算总分
    if (m_pProblemListModel->totalMark() < 100)
    {
        QMessageBox::information(this, "Error", tr("试卷总分低于100，不能用于考试，程序即将退出"));
        exit(2);
    }
    // 初始化每题得分数组
    m_doubleArrayAnswerMark = new double[m_pProblemListModel->rowCount()]{0};
}

/***************************
 * Name:
 *   onFileSave
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   点击保存菜单后的事件
 ***************************/

void StudentMainForm::onFileSave()
{
    // 计算分数
    double ans = std::accumulate(m_doubleArrayAnswerMark, m_doubleArrayAnswerMark + m_pProblemListModel->rowCount(), 0.0);
    if (ans < 100)
    {
        // 分值未到，报错提醒
        QMessageBox::information(this, tr("Error"), QString().number(ans, 'f', 1) + tr("分，未到100分，继续修改。"));
    }
    else
    {
        // 分值已到，提示提交
        QMessageBox::information(this, tr("Accepted"), QString().number(ans, 'f', 1) + tr("分，到100分,已经提交"));
    }
}

/***************************
 * Name:
 *   on_m_problemListItemDoubleClicked
 * Input:
 *   index 点击坐标
 * Return:
 *   none
 * Description:
 *   双击后选择题目
 ***************************/

void StudentMainForm::on_m_problemListItemDoubleClicked(const QModelIndex& index)
{
    // 获得下标与对应题目的指针
    m_intCurProblemIndex = index.row();
    auto curProblem = (*m_pProblemListModel)[m_intCurProblemIndex];
    // 绘制题面
    m_studentProblemWidget->onProblemTypeChanged(curProblem->getType());
    // 设置题型
    m_studentProblemWidget->m_labelProblemType->setText(tr(curProblem->convertType()));
    // 设置分值
    m_studentProblemWidget->m_labelProblemMark->setText(QString().number(curProblem->getMark(),'f',1) + QString("分"));
    // 设置题目描述
    m_studentProblemWidget->m_plainTextProblemDesc->setPlainText(tr(curProblem->getDescription().c_str()));
    const std::vector<std::string> *t_strVecChoiceDescOrKeyWords = nullptr;
    std::ostringstream oSStrmKeyWords;
    // 单选题需要多设置一个选项信息
    // 根据题目类型不同分别显示不同内容
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

/***************************
 * Name:
 *   on_m_buttonFinish_clicked
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   记下本次作答的得分
 ***************************/

void StudentMainForm::on_m_buttonFinish_clicked()
// 判断是否已经正确提交
{
    QVariant b_variantForAnswer;
    QVector<QVariant> b_variantMultipleAnswer;
    QVariant b_variantTempChoiceAnswer;
    switch ((*m_pProblemListModel)[m_intCurProblemIndex]->getType())
    {
    case SINGLE:
        // 判断单选选择的答案
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
        // 添加多选选择的选项
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
    // 记录这一题的成绩
    m_doubleArrayAnswerMark[m_intCurProblemIndex] = (*m_pProblemListModel)[m_intCurProblemIndex]->checkAnswer(b_variantForAnswer);
    // QMessageBox::information(this, tr("Information"), QString().number(m_doubleTotalMark,'f',1));
}

/***************************
 * Name:
 *   on_m_buttonNext_clicked
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   显示下一题, 会保存当前题目的答案
 ***************************/

void StudentMainForm::on_m_buttonNext_clicked()
{
    // 保存答案
    on_m_buttonFinish_clicked();
    // 下标加1
    int b_intNextColumn = m_intCurProblemIndex + 1;
    // 越界回到开始
    if (b_intNextColumn == m_pProblemListModel->rowCount())
        b_intNextColumn = 0;
    // 获取下标对应的QModelIndex
    QModelIndex b_qModelIndexNext = m_pProblemListModel->index(b_intNextColumn, 0);
    // 设置选中
    ui->m_listViewProblem->setCurrentIndex(b_qModelIndexNext);
    // 发生双击事件
    on_m_problemListItemDoubleClicked(b_qModelIndexNext);
}

/***************************
 * Name:
 *   on_m_buttonPrev_clicked
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   显示上一题, 会保存当前题目的答案
 ***************************/

void StudentMainForm::on_m_buttonPrev_clicked()
{
    // 保存答案
    on_m_buttonFinish_clicked();
    // 下标减1
    int b_intNextColumn = m_intCurProblemIndex - 1;
    // 若为-1回到0
    if (b_intNextColumn == -1)
        b_intNextColumn = m_pProblemListModel->rowCount() - 1;
    // 获取下标对应的QModelIndex
    QModelIndex b_qModelIndexNext = m_pProblemListModel->index(b_intNextColumn, 0);
    // 设置选中
    ui->m_listViewProblem->setCurrentIndex(b_qModelIndexNext);
    // 发生双击事件
    on_m_problemListItemDoubleClicked(b_qModelIndexNext);
}
