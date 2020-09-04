#include "writeproblem.h"

WriteProblem::WriteProblem(int _mark, const std::string& _desc, const std::vector<std::string>& _keyWords):
    Problem(WRITE, _mark, _desc), m_strVecKeyWords(_keyWords)
{

}
