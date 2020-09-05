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
    auto b_qVariantVecAns = ans.toList().toVector();
    double b_doubleChoiceMark = m_doubleMark / m_charVecRightAns.size();
    double b_doubleTotalMark = 0;
    for (const auto& b_qVariantChoice : b_qVariantVecAns)
    {
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
    for (const auto& i : m_strVecAnswerList)
    {
        answer.PushBack(i,doc.GetAllocator());
    }
    problem.AddMember("right", answer, doc.GetAllocator());
    return problem;
}
