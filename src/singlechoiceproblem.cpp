/*
File Name: singlechoiceproblem.h
Description: Implement class SingleChoiceProblem
Author: unconsolable
*/

#include "singlechoiceproblem.h"

SingleChoiceProblem::SingleChoiceProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, char _right):
    ChoiceProblem(SINGLE, _mark, _desc, _ansList), m_charRightAns(_right)
{

}

double SingleChoiceProblem::checkAnswer(const QVariant& ans)
{
    if (m_charRightAns == ans.toChar())
        return m_doubleMark;
    else
        return 0;
}

rapidjson::Value SingleChoiceProblem::toJsonValue(rapidjson::Document& doc) const
{
    auto problem = ChoiceProblem::toJsonValue(doc);
    // 选项在JSON里会变成数字
    problem.AddMember("right",m_charRightAns,doc.GetAllocator());
    return problem;
}
