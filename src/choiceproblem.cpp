/*
File Name: choiceproblem.cpp
Description: Implement class ChoiceProblem
Author: unconsolable
*/
#include "choiceproblem.h"

ChoiceProblem::ChoiceProblem(problemType _ty, double _mark, const std::string& _desc, const std::vector<std::string>& _ansList)
    :Problem(_ty, _mark, _desc), m_strVecAnswerList(_ansList)
{

}

rapidjson::Value ChoiceProblem::toJsonValue(rapidjson::Document& doc) const
{
    auto problem = Problem::toJsonValue(doc);
    // 序列化选项
    rapidjson::Value answers(rapidjson::kArrayType);
    for (const auto& b_strEachChoice : m_strVecAnswerList)
    {
        answers.PushBack(b_strEachChoice, doc.GetAllocator());
    }
    problem.AddMember("answers", answers, doc.GetAllocator());
    return problem;
}
