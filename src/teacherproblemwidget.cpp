/*
文件名: teacherproblemwidget.h
版本: 1.0
目的与主要功能: 定义显示题目和辅助出题的Widget
创建日期: 2020.9.8
描述: 定义显示题目和辅助出题的Widget
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/
#include "teacherproblemwidget.h"
#include "problem.h"
#include <QDebug>
// 释放提示性文字
#define CheckDeleteHint()                             \
    do                                                \
    {                                                 \
        CheckDeleteSetNull(m_labelProblemTypeHint);   \
        CheckDeleteSetNull(m_labelProblemMarkHint);   \
        CheckDeleteSetNull(m_labelProblemDescHint);   \
        CheckDeleteSetNull(m_labelProblemAnswerHint); \
    }                                                 \
    while (0)
// 释放公共数据:题型,分值,描述
#define CheckDeleteProblemGeneral()        \
    do                                     \
    {                                      \
        delete m_comboBoxProblemType;      \
        delete m_lineEditProblemMark;      \
        delete m_plainTextEditProblemDesc; \
    }                                      \
    while (0)
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
#define CheckDeleteGridView() CheckDeleteSetNull(m_gridLayoutProblem)
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
// 释放选项
#define CheckDeleteChoice()                          \
    do                                               \
    {                                                \
        CheckDeleteSetNull(m_lineEditProblemChoiceA);\
        CheckDeleteSetNull(m_lineEditProblemChoiceB);\
        CheckDeleteSetNull(m_lineEditProblemChoiceC);\
        CheckDeleteSetNull(m_lineEditProblemChoiceD);\
    }                                                \
    while(0)
// 释放填空答题区
#define CheckDeleteJudgement() CheckDeleteSetNull(m_chkBoxIsRight)
// 释放解答答题区
#define CheckDeleteWrite() CheckDeleteSetNull(m_plainTextKeyWordList)
// 初始化选项
#define InitChoice()                         \
    do                                       \
    {                                        \
    m_lineEditProblemChoiceA = new QLineEdit;\
    m_lineEditProblemChoiceB = new QLineEdit;\
    m_lineEditProblemChoiceC = new QLineEdit;\
    m_lineEditProblemChoiceD = new QLineEdit;\
    }                                        \
    while(0)
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
#define ViewAddChoice()                                                                                        \
    do                                                                                                         \
    {                                                                                                          \
        m_gridLayoutProblem->addWidget(m_lineEditProblemChoiceA, 7, 0, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
        m_gridLayoutProblem->addWidget(m_lineEditProblemChoiceB, 7, 1, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
        m_gridLayoutProblem->addWidget(m_lineEditProblemChoiceC, 7, 2, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
        m_gridLayoutProblem->addWidget(m_lineEditProblemChoiceD, 7, 3, 1, 1, Qt::AlignLeft | Qt::AlignHCenter); \
    }                                                                                                          \
    while (0)
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
// 初始化判断题答题区并添加到View
#define InitJudgementChkBoxAndAddView()                             \
    do                                                              \
    {                                                               \
        m_chkBoxIsRight = new QCheckBox(tr("正确"));                 \
        m_gridLayoutProblem->addWidget(m_chkBoxIsRight, 7, 0, 1, 1); \
    }                                                                \
    while (0)
// 初始化简答答题区并添加到View
#define InitKeyWordPlainTextAndAddView()                                    \
    do                                                                      \
    {                                                                       \
        m_plainTextKeyWordList = new QPlainTextEdit();                      \
        m_gridLayoutProblem->addWidget(m_plainTextKeyWordList, 7, 0, 4, 4); \
    }                                                                       \
    while (0)

/***************************
 * Name:
 *   TeacherProblemWidget
 * Input:
 *   parent 父窗体指针
 * Return:
 *   none
 * Description:
 *   构造题目显示窗体
 ***************************/

TeacherProblemWidget::TeacherProblemWidget(QWidget *parent)
    : QWidget(parent)
{
    // 初始化布局和描述性文字
    m_gridLayoutProblem = new QGridLayout(this);
    m_labelProblemTypeHint = new QLabel(tr("题型"));
    m_labelProblemMarkHint = new QLabel(tr("分值"));
    m_labelProblemDescHint = new QLabel(tr("描述"));
    m_labelProblemAnswerHint = new QLabel(tr("解答"));
    // 添加选择题目类型的下拉框
    m_comboBoxProblemType = new QComboBox;
    m_comboBoxProblemType->addItem(tr("单选题"));
    m_comboBoxProblemType->addItem(tr("多选题"));
    m_comboBoxProblemType->addItem(tr("判断题"));
    m_comboBoxProblemType->addItem(tr("简答题"));
    m_comboBoxProblemType->setEditable(false);
    // 添加填分值的框
    m_lineEditProblemMark = new QLineEdit;
    m_plainTextEditProblemDesc = new QPlainTextEdit;
    // 添加到gridLayout中
    m_gridLayoutProblem->addWidget(m_labelProblemTypeHint, 0, 0, 1, 1);
    m_gridLayoutProblem->addWidget(m_comboBoxProblemType, 0, 1, 1, 1);
    m_gridLayoutProblem->addWidget(m_labelProblemMarkHint, 0, 2, 1, 1);
    m_gridLayoutProblem->addWidget(m_lineEditProblemMark, 0, 3, 1, 1);
    m_gridLayoutProblem->addWidget(m_labelProblemDescHint, 1, 0, 1, 1);
    m_gridLayoutProblem->addWidget(m_plainTextEditProblemDesc, 2, 0, 4, 4);
    m_gridLayoutProblem->addWidget(m_labelProblemAnswerHint, 6, 0, 1, 1);
    connect(m_comboBoxProblemType, SIGNAL(currentIndexChanged(int)), this, SLOT(onProblemTypeChanged(int)));
    // 初始化选项
    InitChoice();
    // 初始化RadioButton并合成为组
    InitRadioButtonAndGroup();
    // View添加选项
    ViewAddChoice();
    // View添加RadioButton
    ViewAddRadioButton();
}

/***************************
 * Name:
 *   ~TeacherProblemWidget
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   析构题目显示窗体
 ***************************/

TeacherProblemWidget::~TeacherProblemWidget()
{
    // 释放提示性字符
    CheckDeleteHint();
    // 释放题目数据
    CheckDeleteProblemGeneral();
    // 释放布局
    CheckDeleteGridView();
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

void TeacherProblemWidget::onProblemTypeChanged(int newtype)
{
    m_boolProblemTypeChanged = true;
    // 释放原有题目类型
    switch(m_intLastProblemTypeIndex)
    {
    case SINGLE: CheckDeleteChoice(); CheckDeleteSingle(); break;
    case MULTIPLE: CheckDeleteChoice(); CheckDeleteMultiple(); break;
    case JUDGEMENT: CheckDeleteJudgement(); break;
    case WRITE: CheckDeleteWrite(); break;
    }
    m_intLastProblemTypeIndex = newtype;
    // 安排新的题目类型
    switch (newtype)
    {
    case SINGLE: InitChoice(); InitRadioButtonAndGroup(); ViewAddChoice(); ViewAddRadioButton(); break;
    case MULTIPLE: InitChoice(); InitChkBoxAndGroup(); ViewAddChoice(); ViewAddChkBox(); break;
    case JUDGEMENT: InitJudgementChkBoxAndAddView(); break;
    case WRITE: InitKeyWordPlainTextAndAddView(); break;
    }
}
