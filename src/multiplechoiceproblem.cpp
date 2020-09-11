/*
File Name: multiplechoiceproblem.h
Description: Implement class MultipleChoice
Author: unconsolable
*/

#include "multiplechoiceproblem.h"

MultipleChoiceProblem::MultipleChoiceProblem(double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, const std::vector<char>& _right):
    ChoiceProblem(MULTIPLE, _mark, _desc, _ansList), m_charVecRightAns(_right)
{

}

double MultipleChoiceProblem::checkAnswer(const QVariant & ans)
{
    // 获得选项表
    auto b_qVariantVecAns = ans.value<QVector<QVariant>>();
    // 每个选项的分数
    double b_doubleChoiceMark = m_doubleMark / m_charVecRightAns.size();
    double b_doubleTotalMark = 0;
    // 每个选项遍历
    for (const auto& b_qVariantChoice : b_qVariantVecAns)
    {
        // 和正确选项核对
        for (const auto& b_charRightChoice : m_charVecRightAns)
        {
            if (b_qVariantChoice.toChar() == b_charRightChoice)
            {
                // 找到匹配选项时加分
                b_doubleTotalMark += b_doubleChoiceMark;
                break;
            }
        }
    }
    return b_doubleTotalMark;
}

rapidjson::Value MultipleChoiceProblem::toJsonValue(rapidjson::Document& doc) const
{
    auto problem = ChoiceProblem::toJsonValue(doc);
    rapidjson::Value answer(rapidjson::kArrayType);
    // 设置多选选项,选项用char表示,应转为int存
    for (const auto& b_charEachRight: m_charVecRightAns)
    {
        rapidjson::Value choice;
        choice.SetInt(b_charEachRight);
        answer.PushBack(choice, doc.GetAllocator());
    }
    problem.AddMember("right", answer, doc.GetAllocator());
    return problem;
}

const std::vector<char>& MultipleChoiceProblem::getRightAns() const
{
    return m_charVecRightAns;
}

void MultipleChoiceProblem::setRightAns(const std::vector<char> &rightAns)
{
    m_charVecRightAns = rightAns;
}
