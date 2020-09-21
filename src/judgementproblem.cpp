/*
文件名: judgementproblem.h
版本: 1.0
目的与主要功能: 实现判断题类
创建日期: 2020.9.4
描述: 实现判断题类
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/

#include "judgementproblem.h"

/***************************
 * Name:
 *   JudegmentProblem
 * Input:
 *   _mark 分值
 *   _desc 描述
 *   _right 是否正确
 * Return:
 *   none
 * Description:
 *   判断题构造函数
 ***************************/

JudgementProblem::JudgementProblem(double _mark, const std::string& _desc, bool _right):
    Problem(JUDGEMENT, _mark, _desc), m_boolRightAns(_right)
{

}

/***************************
 * Name:
 *   checkAnswer
 * Input:
 *   ans 存储答案的QVariant
 * Return:
 *   double
 * Description:
 *   计算得分
 ***************************/

double JudgementProblem::checkAnswer(const QVariant & ans)
{
    // 判断答案是否相符
    if (m_boolRightAns == ans.toBool())
        // 相符给分
        return m_doubleMark;
    else
        // 不相符不给分
        return 0;
}

/***************************
 * Name:
 *   toJsonValue
 * Input:
 *   doc 提供Allocator的Document
 * Return:
 *   rapidjson::value
 * Description:
 *   将判断题转为JSON数据节点
 ***************************/

rapidjson::Value JudgementProblem::toJsonValue(rapidjson::Document& doc) const
{
    // 获得题目通用信息
    auto problem = Problem::toJsonValue(doc);
    // 增加正确答案Key-Value对
    problem.AddMember("right", m_boolRightAns, doc.GetAllocator());
    // 返回
    return problem;
}

/***************************
 * Name:
 *   getRightAns
 * Input:
 *   none
 * Return:
 *   bool
 * Description:
 *   返回存储题目
 *   选对或错的成员变量
 ***************************/

bool JudgementProblem::getRightAns() const
{
    // 获得答案
    return m_boolRightAns;
}

/***************************
 * Name:
 *   setRightAns
 * Input:
 *   rightAns
 * Return:
 *   none
 * Description:
 *   设置选对或选错
 ***************************/

void JudgementProblem::setRightAns(bool rightAns)
{
    // 设置答案
    m_boolRightAns = rightAns;
}
