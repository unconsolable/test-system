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
    // 获得通用信息
    auto problem = Problem::toJsonValue(doc);
    // 序列化选项
    rapidjson::Value answers(rapidjson::kArrayType);
    for (auto& b_strEachChoice : m_strVecAnswerList)
    {
        rapidjson::Value choice;
        // 设置选项字符串为JSON字符串
        choice.SetString(b_strEachChoice.c_str(), b_strEachChoice.size(), doc.GetAllocator());
        // 添加到JSON数组
        answers.PushBack(choice, doc.GetAllocator());
    }
    // 添加Key-Value对
    problem.AddMember("answers", answers, doc.GetAllocator());
    return problem;
}

const std::vector<std::string> &ChoiceProblem::getAnswerList() const
{
    // 返回选项列表
    return m_strVecAnswerList;
}

void ChoiceProblem::setAnswerList(const std::vector<std::string> &answerList)
{
    // 设置选项列表
    m_strVecAnswerList = answerList;
}
