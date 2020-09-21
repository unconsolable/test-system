/*
文件名: choiceproblem.h
版本: 1.0
目的与主要功能: 实现选择题类
创建日期: 2020.9.3
描述: 实现选择题类
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/
#include "choiceproblem.h"

/***************************
 * Name:
 *   ChoiceProblem
 * Input:
 *   _ty 题目类型
 *   _mark 题目分值
 *   _desc 题目描述
 *   _ansList 选项列表
 * Return:
 *   none
 * Description:
 *   单选题构造函数
 ***************************/

ChoiceProblem::ChoiceProblem(problemType _ty, double _mark, const std::string& _desc, const std::vector<std::string>& _ansList)
    :Problem(_ty, _mark, _desc), m_strVecAnswerList(_ansList)
{

}

/***************************
 * Name:
 *   toJsonValue
 * Input:
 *   doc 提供Allocator的Document
 * Return:
 *   rapidjson::value
 * Description:
 *   将单选题转为JSON数据节点
 ***************************/

rapidjson::Value ChoiceProblem::toJsonValue(rapidjson::Document& doc) const
{
    // 获得通用信息
    auto problem = Problem::toJsonValue(doc);
    // 序列化选项array
    rapidjson::Value answers(rapidjson::kArrayType);
    for (auto& b_strEachChoice : m_strVecAnswerList)
    {
        // 用于存储某一选项字符串
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

/***************************
 * Name:
 *   getAnswerList
 * Input:
 *   none
 * Return:
 *   const std::vector<std::string>&
 * Description:
 *   获取选项列表
 ***************************/

const std::vector<std::string> &ChoiceProblem::getAnswerList() const
{
    // 返回选项列表
    return m_strVecAnswerList;
}

/***************************
 * Name:
 *   setAnswerList
 * Input:
 *   const std::vector<std::string>&
 * Return:
 *   none
 * Description:
 *   获取选项列表
 ***************************/

void ChoiceProblem::setAnswerList(const std::vector<std::string> &answerList)
{
    // 设置选项列表
    m_strVecAnswerList = answerList;
}
