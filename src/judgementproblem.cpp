/*
File Name: judgementproblem.cpp
Description: Implement the class JudgementProblem
Author: unconsolable
*/

#include "judgementproblem.h"

JudgementProblem::JudgementProblem(double _mark, const std::string& _desc, bool _right):
    Problem(JUDGEMENT, _mark, _desc), m_boolRightAns(_right)
{

}

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

rapidjson::Value JudgementProblem::toJsonValue(rapidjson::Document& doc) const
{
    // 获得题目通用信息
    auto problem = Problem::toJsonValue(doc);
    // 增加正确答案Key-Value对
    problem.AddMember("right", m_boolRightAns, doc.GetAllocator());
    // 返回
    return problem;
}

bool JudgementProblem::getRightAns() const
{
    // 获得答案
    return m_boolRightAns;
}

void JudgementProblem::setRightAns(bool rightAns)
{
    // 设置答案
    m_boolRightAns = rightAns;
}
