/*
文件名: studentproblemwidget.h
版本: 1.0
目的与主要功能: 实现显示题目和提供作答区的Widget
创建日期: 2020.9.10
描述: 实现显示题目和提供作答区的Widget
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/

#include "studentproblemwidget.h"
#include "problem.h"
// 初始化选项
#define InitChoice()                        \
    do                                      \
    {                                       \
        m_labelProblemChoiceA = new QLabel; \
        m_labelProblemChoiceB = new QLabel; \
        m_labelProblemChoiceC = new QLabel; \
        m_labelProblemChoiceD = new QLabel; \
    } while (0)
// 初始化单选答题区
#define InitRadioButtonAndGroup()                                       \
    do                                                                  \
    {                                                                   \
        m_radioProblemRightChoiceA = new QRadioButton(tr("A"));         \
        m_radioProblemRightChoiceB = new QRadioButton(tr("B"));         \
        m_radioProblemRightChoiceC = new QRadioButton(tr("C"));         \
        m_radioProblemRightChoiceD = new QRadioButton(tr("D"));         \
        m_btnGroupSingleChoice = new QButtonGroup(this);                \
        m_btnGroupSingleChoice->addButton(m_radioProblemRightChoiceA);  \
        m_btnGroupSingleChoice->addButton(m_radioProblemRightChoiceB);  \
        m_btnGroupSingleChoice->addButton(m_radioProblemRightChoiceC);  \
        m_btnGroupSingleChoice->addButton(m_radioProblemRightChoiceD);  \
    }                                                                   \
    while(0)
// 初始化多选答题区
#define InitChkBoxAndGroup()                                              \
    do                                                                    \
    {                                                                     \
        m_chkBoxProblemRightChoiceA = new QCheckBox(tr("A"));             \
        m_chkBoxProblemRightChoiceB = new QCheckBox(tr("B"));             \
        m_chkBoxProblemRightChoiceC = new QCheckBox(tr("C"));             \
        m_chkBoxProblemRightChoiceD = new QCheckBox(tr("D"));             \
    } while (0)
// 添加选项到网格
#define ViewAddChoice()                                                                                      \
    do                                                                                                       \
    {                                                                                                        \
        m_gridLayoutProblem->addWidget(m_labelProblemChoiceA, 7, 0, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
        m_gridLayoutProblem->addWidget(m_labelProblemChoiceB, 7, 1, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
        m_gridLayoutProblem->addWidget(m_labelProblemChoiceC, 7, 2, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
        m_gridLayoutProblem->addWidget(m_labelProblemChoiceD, 7, 3, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
    } while (0)
// 添加单选区到网格
#define ViewAddRadioButton()                                                                                     \
    do                                                                                                           \
    {                                                                                                            \
        m_gridLayoutProblem->addWidget(m_radioProblemRightChoiceA, 8, 0, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
        m_gridLayoutProblem->addWidget(m_radioProblemRightChoiceB, 8, 1, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
        m_gridLayoutProblem->addWidget(m_radioProblemRightChoiceC, 8, 2, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
        m_gridLayoutProblem->addWidget(m_radioProblemRightChoiceD, 8, 3, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
    } while (0)
// 添加多选区到网格
#define ViewAddChkBox()                                                                                           \
    do                                                                                                            \
    {                                                                                                             \
        m_gridLayoutProblem->addWidget(m_chkBoxProblemRightChoiceA, 8, 0, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
        m_gridLayoutProblem->addWidget(m_chkBoxProblemRightChoiceB, 8, 1, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
        m_gridLayoutProblem->addWidget(m_chkBoxProblemRightChoiceC, 8, 2, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
        m_gridLayoutProblem->addWidget(m_chkBoxProblemRightChoiceD, 8, 3, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
    }                                                                                                             \
    while (0)
// 初始化判断题答题区并添加到GridLayout
#define InitJudgementChkBoxAndAddView()                             \
    do                                                              \
    {                                                               \
        m_chkBoxIsRight = new QCheckBox(tr("正确"));                 \
        m_gridLayoutProblem->addWidget(m_chkBoxIsRight, 7, 0, 1, 1); \
    }                                                                \
    while (0)
// 初始化简答答题区并添加到GridLayout
#define InitWritePlainTextAndAddView()                                      \
    do                                                                      \
    {                                                                       \
        m_plainTextWriteAnswer = new QPlainTextEdit();                      \
        m_gridLayoutProblem->addWidget(m_plainTextWriteAnswer, 7, 0, 4, 4); \
    }                                                                       \
    while (0)
// 释放题目通用信息
#define DeleteProblemGeneral()           \
    do                                   \
    {                                    \
        delete m_labelProblemType;       \
        delete m_labelProblemMark;       \
        delete m_plainTextProblemDesc;   \
        delete m_labelProblemAnswerHint; \
    } while (0)
// 释放GridView
#define DeleteGridView() delete m_gridLayoutProblem
// 释放选项
#define CheckDeleteChoice()                        \
    do                                             \
    {                                              \
        CheckDeleteSetNull(m_labelProblemChoiceA); \
        CheckDeleteSetNull(m_labelProblemChoiceB); \
        CheckDeleteSetNull(m_labelProblemChoiceC); \
        CheckDeleteSetNull(m_labelProblemChoiceD); \
    } while (0)
// 释放单选答题区
#define CheckDeleteSingle()                             \
    do                                                  \
    {                                                   \
        CheckDeleteSetNull(m_radioProblemRightChoiceB); \
        CheckDeleteSetNull(m_radioProblemRightChoiceA); \
        CheckDeleteSetNull(m_radioProblemRightChoiceC); \
        CheckDeleteSetNull(m_radioProblemRightChoiceD); \
        CheckDeleteSetNull(m_btnGroupSingleChoice);     \
    }while(0)
// 释放多选答题区
#define CheckDeleteMultiple()                           \
    do                                                  \
    {                                                   \
        CheckDeleteSetNull(m_chkBoxProblemRightChoiceA);\
        CheckDeleteSetNull(m_chkBoxProblemRightChoiceB);\
        CheckDeleteSetNull(m_chkBoxProblemRightChoiceC);\
        CheckDeleteSetNull(m_chkBoxProblemRightChoiceD);\
    }                                                   \
    while(0)
// 释放填空答题区
#define CheckDeleteJudgement() CheckDeleteSetNull(m_chkBoxIsRight)
// 释放解答答题区
#define CheckDeleteWrite() CheckDeleteSetNull(m_plainTextWriteAnswer)

/***************************
 * Name:
 *   StudentProblemWidget
 * Input:
 *   parent 父窗体指针
 * Return:
 *   none
 * Description:
 *  构造StudentProblemWidget类
 *  构造通用信息(网格布局等)
 ***************************/

StudentProblemWidget::StudentProblemWidget(QWidget *parent)
    : QWidget(parent)
{
    // 初始化布局和题目信息控件
    m_gridLayoutProblem = new QGridLayout(this);
    m_labelProblemType = new QLabel;
    m_labelProblemMark = new QLabel;
    m_plainTextProblemDesc = new QPlainTextEdit;
    m_plainTextProblemDesc->setReadOnly(true);
    m_labelProblemAnswerHint = new QLabel(tr("解答"));
    // 设置最小宽度
    m_gridLayoutProblem->setColumnMinimumWidth(0, 150);
    m_gridLayoutProblem->setColumnMinimumWidth(1, 150);
    m_gridLayoutProblem->setColumnMinimumWidth(2, 150);
    m_gridLayoutProblem->setColumnMinimumWidth(3, 150);
    // 设置最小高度
    m_gridLayoutProblem->setRowMinimumHeight(0, 70);
    m_gridLayoutProblem->setRowMinimumHeight(1, 70);
    m_gridLayoutProblem->setRowMinimumHeight(2, 70);
    m_gridLayoutProblem->setRowMinimumHeight(3, 70);
    // 添加到GridLayout中
    m_gridLayoutProblem->addWidget(m_labelProblemType, 0, 0, 1, 2);
    m_gridLayoutProblem->addWidget(m_labelProblemMark,0, 2, 1, 2);
    m_gridLayoutProblem->addWidget(m_plainTextProblemDesc, 1, 0, 5, 4);
    m_gridLayoutProblem->addWidget(m_labelProblemAnswerHint, 6, 0, 1, 2);
}

/***************************
 * Name:
 *   StudentProblemWidget
 * Input:
 *   parent 父窗体指针
 * Return:
 *   none
 * Description:
 *  析构StudentProblemWidget类
 *  析构所有控件
 ***************************/

StudentProblemWidget::~StudentProblemWidget()
{
    // 释放题目数据
    DeleteProblemGeneral();
    // 释放布局
    DeleteGridView();
    // 释放选择题的选项
    CheckDeleteChoice();
    // 释放单选
    CheckDeleteSingle();
    // 释放多选
    CheckDeleteMultiple();
    // 释放判断
    CheckDeleteJudgement();
    // 释放简答
    CheckDeleteWrite();
}

/***************************
 * Name:
 *   onProblemTypeChanged
 * Input:
 *   newtype 新类型的编号
 * Return:
 *   none
 * Description:
 *   释放原问题对应控件
 *   添加新问题对应控件
 ***************************/

void StudentProblemWidget::onProblemTypeChanged(int newtype)
{
    // 释放原有类型特有控件
    switch(m_intLastProblemTypeIndex)
    {
    case SINGLE: CheckDeleteChoice(); CheckDeleteSingle(); break;
    case MULTIPLE: CheckDeleteChoice(); CheckDeleteMultiple(); break;
    case JUDGEMENT: CheckDeleteJudgement(); break;
    case WRITE: CheckDeleteWrite(); break;
    default: break; //对于-1这种不需任何删除
    }
    // 记录之前类型便于后续删除题目面板控件
    m_intLastProblemTypeIndex = newtype;
    // 添加新的类型特有控件
    switch (newtype)
    {
    case SINGLE: InitChoice(); InitRadioButtonAndGroup(); ViewAddChoice(); ViewAddRadioButton(); break;
    case MULTIPLE: InitChoice(); InitChkBoxAndGroup(); ViewAddChoice(); ViewAddChkBox(); break;
    case JUDGEMENT: InitJudgementChkBoxAndAddView(); break;
    case WRITE: InitWritePlainTextAndAddView(); break;
    }
}






