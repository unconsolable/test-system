/*
File Name: singlechoiceproblem.h
Description: Define class SingleChoiceProblem
Author: unconsolable
*/

#ifndef SINGLECHOICEPROBLEM_H
#define SINGLECHOICEPROBLEM_H

#include "choiceproblem.h"

class SingleChoiceProblem : public ChoiceProblem
{
public:
    // 拷贝控制
    SingleChoiceProblem(double = 0, const std::string& = "", const std::vector<std::string>& = {}, char = 'A');
    virtual double checkAnswer(const QVariant&) override;
    virtual rapidjson::Value toJsonValue(rapidjson::Document& doc) const override;
    virtual ~SingleChoiceProblem() override = default;
    // 答案的Getter和Setter
    char getRightAns() const;
    void setRightAns(char rightAns);
private:
    // 只有一个正确
    char m_charRightAns;
};

// 能够使用QVariant
// Q_DECLARE_METATYPE(SingleChoiceProblem);

#endif // SINGLECHOICEPROBLEM_H
