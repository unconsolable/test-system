/*
文件名: choiceproblem.h
版本: 1.0
目的与主要功能: 定义选择题类
创建日期: 2020.9.3
描述: 定义选择题类
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/

#ifndef CHOICEPROBLEM_H
#define CHOICEPROBLEM_H

#include "problem.h"
#include <vector>

class ChoiceProblem : public Problem
{
public:
    // 构造选择题
    ChoiceProblem(problemType = SINGLE, double = 0, const std::string& = "", const std::vector<std::string>& = {});
    // 不针对具体题目,仍定义为纯虚函数
    virtual double checkAnswer(const QVariant&) override = 0;
    // 转为JSON节点类型,便于后续转为JSON文本
    virtual rapidjson::Value toJsonValue(rapidjson::Document& doc) const override;
    virtual ~ChoiceProblem() override = default;
    // 选项字符的Setter和Getter
    const std::vector<std::string>& getAnswerList() const;
    void setAnswerList(const std::vector<std::string> &AnswerList);
protected:
    // 共通:选项
    std::vector<std::string> m_strVecAnswerList;
};

// 能够使用QVariant
// Q_DECLARE_METATYPE(ChoiceProblem);

#endif // CHOICEPROBLEM_H
