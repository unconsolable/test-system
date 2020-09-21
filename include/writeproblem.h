/*
文件名: writeproblem.h
版本: 1.0
目的与主要功能: 定义简答题类
创建日期: 2020.9.4
描述: 定义简答题类
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
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
