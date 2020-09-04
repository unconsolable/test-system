/*
File Name: writeproblem.h
Description:
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
    WriteProblem(int = 0, const std::string& = "", const std::vector<std::string>& = {});
private:
    std::vector<std::string> m_strVecKeyWords;
};

#endif // WRITEPROBLEM_H
