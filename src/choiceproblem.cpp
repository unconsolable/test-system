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
    for (auto& b_strEachChoice : m_strVecAnswerList)
    {
        rapidjson::Value choice;
        choice.SetString(b_strEachChoice.c_str(), b_strEachChoice.size(), doc.GetAllocator());
        answers.PushBack(choice, doc.GetAllocator());
    }
    problem.AddMember("answers", answers, doc.GetAllocator());
    return problem;
}

std::vector<std::string> ChoiceProblem::getAnswerList() const
{
    return m_strVecAnswerList;
}

void ChoiceProblem::setAnswerList(const std::vector<std::string> &answerList)
{
    m_strVecAnswerList = answerList;
}
