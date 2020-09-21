/*
File Name: writeproblem.h
Description: Define the class of the write problem
Author: unconsolable
*/

#ifndef WRITEPROBLEM_H
#define WRITEPROBLEM_H

#include "problem.h"
#include <vector>
#include <string>

class WriteProblem : public Problem
{
public:
    // 构造函数
    WriteProblem(double = 0, const std::string& = "", const std::vector<std::string>& = {});
    // 判分函数
    virtual double checkAnswer(const QVariant&) override;
    // 转为JSON节点
    virtual rapidjson::Value toJsonValue(rapidjson::Document& doc) const override;
    // 析构函数
    virtual ~WriteProblem() = default;
    // 获得关键词列表
    const std::vector<std::string>& getKeyWords() const;
    // 设置关键词列表
    void setKeyWords(const std::vector<std::string> &keyWords);

private:
    // 存储关键词
    std::vector<std::string> m_strVecKeyWords;
};

// 能够使用QVariant
// Q_DECLARE_METATYPE(WriteProblem);

#endif // WRITEPROBLEM_H
