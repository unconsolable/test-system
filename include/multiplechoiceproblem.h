/*
File Name: multiplechoiceproblem.h
Description: Define class MultipleChoice
Author: unconsolable
*/

#ifndef MULTIPLECHOICEPROBLEM_H
#define MULTIPLECHOICEPROBLEM_H

#include "choiceproblem.h"

class MultipleChoiceProblem : public ChoiceProblem
{
public:
    MultipleChoiceProblem(double = 0, const std::string& = "", const std::vector<std::string>& = {}, const std::vector<char>& = {});
    virtual double checkAnswer(const QVariant&) override;
    virtual rapidjson::Value toJsonValue(rapidjson::Document& doc) const override;
    virtual ~MultipleChoiceProblem() override = default;
    const std::vector<char>& getRightAns() const;
    void setRightAns(const std::vector<char> &rightAns);
private:
    // 正确答案用列表表示，A,B,C
    std::vector<char> m_charVecRightAns;
};

// 能够使用QVariant
// Q_DECLARE_METATYPE(MultipleChoiceProblem);

#endif // MULTIPLECHOICEPROBLEM_H
