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
    if (m_boolRightAns == ans.toBool())
        return m_doubleMark;
    else
        return 0;
}

rapidjson::Value JudgementProblem::toJsonValue(rapidjson::Document& doc) const
{
    auto problem = Problem::toJsonValue(doc);
    problem.AddMember("right", true, doc.GetAllocator());
    return problem;
}

bool JudgementProblem::getRightAns() const
{
    return m_boolRightAns;
}

void JudgementProblem::setRightAns(bool rightAns)
{
    m_boolRightAns = rightAns;
}
