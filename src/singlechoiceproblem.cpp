/*
File Name: singlechoiceproblem.h
Description: Implement class SingleChoiceProblem
Author: unconsolable
*/

#include "singlechoiceproblem.h"

SingleChoiceProblem::SingleChoiceProblem(problemType _ty, int _mark, const std::string& _desc, const std::vector<std::string>& _ansList, char _right):
    ChoiceProblem(_ty, _mark, _desc, _ansList), m_charRightAns(_right)
{

}
