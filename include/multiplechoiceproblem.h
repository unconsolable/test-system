/*
文件名: multiplechoiceproblem.h
版本: 1.0
目的与主要功能: 定义多选题类
创建日期: 2020.9.3
描述: 定义多选题类
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/

#ifndef MULTIPLECHOICEPROBLEM_H
#define MULTIPLECHOICEPROBLEM_H

#include "choiceproblem.h"

class MultipleChoiceProblem : public ChoiceProblem
{
public:
    // 构造函数
    MultipleChoiceProblem(double = 0, const std::string& = "", const std::vector<std::string>& = {}, const std::vector<char>& = {});
    // 计算得分函数
    virtual double checkAnswer(const QVariant&) override;
    // 转为JSON数据节点
    virtual rapidjson::Value toJsonValue(rapidjson::Document& doc) const override;
    // 虚析构函数
    virtual ~MultipleChoiceProblem() override = default;
    // 获得正确答案集
    const std::vector<char>& getRightAns() const;
    // 设置正确答案集
    void setRightAns(const std::vector<char> &rightAns);
private:
    // 正确答案用列表表示，A,B,C
    std::vector<char> m_charVecRightAns;
};

// 能够使用QVariant
// Q_DECLARE_METATYPE(MultipleChoiceProblem);

#endif // MULTIPLECHOICEPROBLEM_H
