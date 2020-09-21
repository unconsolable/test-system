/*
文件名: problemlistmodel.h
版本: 1.0
目的与主要功能: 实现试题列表模型
创建日期: 2020.9.4
描述: 实现试题列表模型
作者: unconsolable
修改者: unconsolable
联系方式: chenzhipeng2012@gmail.com
*/

#include "problemlistmodel.h"
#include "singlechoiceproblem.h"
#include "multiplechoiceproblem.h"
#include "judgementproblem.h"
#include "writeproblem.h"
#include "rapidjson/prettywriter.h"

/***************************
 * Name:
 *   ProblemListModel
 * Input:
 *   parent 父级模型
 * Return:
 *   none
 * Description:
 *   问题列表构造函数
 ***************************/

ProblemListModel::ProblemListModel(QObject *parent) : QAbstractListModel(parent)
{
}

/***************************
 * Name:
 *   ~ProblemListModel
 * Input:
 *   none
 * Return:
 *   none
 * Description:
 *   问题列表析构函数
 ***************************/

ProblemListModel::~ProblemListModel()
{
    // 析构函数,如下倒序释放内存会引起SIGSEGV
    // for (auto b_iter = m_pProblemVecProList.rbegin(); b_iter != m_pProblemVecProList.rend(); --b_iter)
    // {
    //     delete *b_iter;
    //    *b_iter = nullptr;
    // }
    for (auto i : m_pProblemVecProList)
    {
        if (i)
        {
            delete i;
            i = nullptr;
        }
    }
}

/***************************
 * Name:
 *   addProblem
 * Input:
 *   pos 添加到的位置
 *   _mark 分值
 *   _desc 题干
 *   _ansList 选项列表
 *   _right 单选题正确选项
 * Return:
 *   none
 * Description:
 *   添加单选题
 ***************************/
void ProblemListModel::addProblem(int pos, double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, char _right)
{
    // 发送Model将变化的信号 [begin,end]方式表示
    beginInsertRows(QModelIndex(), pos, pos);
    m_pProblemVecProList.insert(m_pProblemVecProList.begin() + pos, new SingleChoiceProblem(_mark, _desc, _ansList, _right));
    // 发送Model已变化的信号
    endInsertRows();
}

/***************************
 * Name:
 *   addProblem
 * Input:
 *   pos 添加到的位置
 *   _mark 分值
 *   _desc 题干
 *   _ansList 选项列表
 *   _right 多选题正确选项
 * Return:
 *   none
 * Description:
 *   添加多选题
 ***************************/
void ProblemListModel::addProblem(int pos, double _mark, const std::string& _desc, const std::vector<std::string>& _ansList, const std::vector<char>& _right)
{
    // 发送Model将变化的信号 [begin,end]方式表示
    beginInsertRows(QModelIndex(), pos, pos);
    m_pProblemVecProList.insert(m_pProblemVecProList.begin() + pos, new MultipleChoiceProblem(_mark, _desc, _ansList, _right));
    // 发送Model已变化的信号
    endInsertRows();
}
/***************************
 * Name:
 *   addProblem
 * Input:
 *   pos 添加到的位置
 *   _mark 分值
 *   _desc 题干
 *   _right 判断题正确选项
 * Return:
 *   none
 * Description:
 *   添加判断题
 ***************************/
void ProblemListModel::addProblem(int pos, double _mark, const std::string& _desc, bool _right)
{
    // 发送Model将变化的信号 [begin,end]方式表示
    beginInsertRows(QModelIndex(), pos, pos);
    m_pProblemVecProList.insert(m_pProblemVecProList.begin() + pos, new JudgementProblem(_mark, _desc, _right));
    // 发送Model已变化的信号
    endInsertRows();
}
/***************************
 * Name:
 *   addProblem
 * Input:
 *   pos 添加到的位置
 *   _mark 分值
 *   _desc 题干
 *   _keyWords 关键词列表
 * Return:
 *   none
 * Description:
 *   添加简答题
 ***************************/
void ProblemListModel::addProblem(int pos, double _mark, const std::string& _desc, const std::vector<std::string>& _keyWords)
{
    // 发送Model将变化的信号 [begin,end]方式表示
    beginInsertRows(QModelIndex(), pos, pos);
    m_pProblemVecProList.insert(m_pProblemVecProList.begin() + pos, new WriteProblem(_mark, _desc, _keyWords));
    // 发送Model已变化的信号
    endInsertRows();
}
/***************************
 * Name:
 *   toJsonString
 * Input:
 *   none
 * Return:
 *   std::string
 * Description:
 *   将所有题目转为JSON字符串
 ***************************/
std::string ProblemListModel::toJsonString() const
{
    rapidjson::Document b_jsonTestPaper(rapidjson::kObjectType);
    rapidjson::Value b_jsonProblemList(rapidjson::kArrayType);
    // 每个题目转为JSON结构
    for (const auto i : m_pProblemVecProList)
    {
        b_jsonProblemList.PushBack(i->toJsonValue(b_jsonTestPaper), b_jsonTestPaper.GetAllocator());
    }
    // 添加Key-Value
    b_jsonTestPaper.AddMember("problem", b_jsonProblemList, b_jsonTestPaper.GetAllocator());
    // 转换为字符串,参考rapidjson文档
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
    b_jsonTestPaper.Accept(writer);
    return sb.GetString();
}
/***************************
 * Name:
 *   fromJsonDocument
 * Input:
 *   doc JSON解析后的文档
 * Return:
 *   bool
 * Description:
 *   将解析的JSON树转为问题列表
 ***************************/
bool ProblemListModel::fromJsonDocument(const rapidjson::Document& doc)
{
    // 检查是否有为problem的key
    if (!doc.HasMember("problem") || !doc["problem"].IsArray())
    {
        return false;
    }
    for (auto& b_jsonValueEachProblem : doc["problem"].GetArray())
    {
        // 这个用于存选项或者关键词,两个不会同时出现
        std::vector<std::string> tmpAnsListOrKeyWords;
        // 这个用于存多选的选项字符
        std::vector<char> multipleChoice;
        // 根据类型对应构造
        // 分值类型变化为Double
        switch (b_jsonValueEachProblem["type"].GetInt())
        {
        case SINGLE:
            // 存入选项描述
            for (auto& i : b_jsonValueEachProblem["answers"].GetArray())
            {
                tmpAnsListOrKeyWords.emplace_back(i.GetString());
            }
            // 传入题目信息
            addProblem(rowCount(), b_jsonValueEachProblem["mark"].GetDouble(), std::string(b_jsonValueEachProblem["description"].GetString()), tmpAnsListOrKeyWords, b_jsonValueEachProblem["right"].GetInt());
            break;
        case MULTIPLE:
            //存入选项描述
            for (auto& i : b_jsonValueEachProblem["answers"].GetArray())
            {
                tmpAnsListOrKeyWords.emplace_back(i.GetString());
            }
            // 存储选项用的是char,应转为int
            for (auto& i : b_jsonValueEachProblem["right"].GetArray())
            {
                multipleChoice.emplace_back(i.GetInt());
            }
            // 传入题目信息
            addProblem(rowCount(), b_jsonValueEachProblem["mark"].GetDouble(), std::string(b_jsonValueEachProblem["description"].GetString()), tmpAnsListOrKeyWords, multipleChoice);
            break;
        case JUDGEMENT:
            // 直接传true/false即可
            addProblem(rowCount(), b_jsonValueEachProblem["mark"].GetDouble(), std::string(b_jsonValueEachProblem["description"].GetString()),b_jsonValueEachProblem["right"].GetBool());
            break;
        case WRITE:
            // 构造关键词列表
            for (auto& i: b_jsonValueEachProblem["right"].GetArray())
            {
                tmpAnsListOrKeyWords.emplace_back(i.GetString());
            }
            // 传入题目信息
            addProblem(rowCount(), b_jsonValueEachProblem["mark"].GetDouble(), std::string(b_jsonValueEachProblem["description"].GetString()), tmpAnsListOrKeyWords);
            break;
        default:
            return false;
        }
    }
    return true;
}

/***************************
 * Name:
 *   rowCount
 * Input:
 *   parent 无用
 * Return:
 *   none
 * Description:
 *   返回数据数目
 ***************************/

int ProblemListModel::rowCount(const QModelIndex &parent) const
{
    // 用于View显示使用,返回Model中条目
    Q_UNUSED(parent);
    return m_pProblemVecProList.size();
}

/***************************
 * Name:
 *   data
 * Input:
 *   index 数据坐标
 *   role 数据类型
 * Return:
 *   QVariant
 * Description:
 *   输出用于显示的数据
 ***************************/

QVariant ProblemListModel::data(const QModelIndex& index, int role) const
{

    // 返回用于在QListView显示的数据
    // 检查下标是否有效
    if (!index.isValid())
        return QVariant();
    if (index.row() >= static_cast<int>(m_pProblemVecProList.size()))
        return QVariant();
    // 返回题目类型
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        // 格式化返回字符串,类似sprintf
        return QString("第%1题,%2,%3分").arg(index.row() + 1).arg(tr(m_pProblemVecProList[index.row()]->convertType())).arg(m_pProblemVecProList[index.row()]->getMark(),0,'f',1);
    }
    return QVariant();
}

/***************************
 * Name:
 *   headerData
 * Input:
 *   section 无用
 *   orientation 朝向
 *   role 数据类型
 * Return:
 *   QVariant
 * Description:
 *   显示题目表头
 ***************************/

QVariant ProblemListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    // 返回表头
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return tr("题型");
    return QVariant();
}

/***************************
 * Name:
 *   flags
 * Input:
 *   index 坐标
 * Return:
 *   Qt::ItemFlags
 * Description:
 *   返回位置对应数据类型
 ***************************/

Qt::ItemFlags ProblemListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    // 按位或ItemIsEditable,告知Controller能够修改显示的信息
    // 不是修改数据
    // return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    return QAbstractItemModel::flags(index);
}

/***************************
 * Name:
 *   rmProblem
 * Input:
 *   pos
 * Return:
 *   bool
 * Description:
 *   删除pos处问题
 ***************************/

bool ProblemListModel::rmProblem(int pos)
{
    // 向Model告知,便于Model中显示的变化
    beginRemoveRows(QModelIndex(), pos, pos);
    // 删除指针之前**释放**对应资源
    delete m_pProblemVecProList[pos];
    // 再删除指针(即一串对应虚拟地址空间的编号)
    m_pProblemVecProList.erase(m_pProblemVecProList.begin() + pos);
    endRemoveRows();
    return true;
}
/***************************
 * Name:
 *   operator[]
 * Input:
 *   index
 * Return:
 *   Problem*
 * Description:
 *   返回m_pProblemVecProList
 *   中index处存的指针
 ***************************/
Problem* ProblemListModel::operator[](size_t index)
{
    // 检查下标是否有效
    if (index >= m_pProblemVecProList.size())
        return nullptr;
    return m_pProblemVecProList[index];
}

/***************************
 * Name:
 *   totalMark
 * Input:
 *   none
 * Return:
 *   double
 * Description:
 *   计算总分
 ***************************/

double ProblemListModel::totalMark() const
{
    // 计算总分,便于判断是否是
    // 总分低于100分的试卷用于考试
    double totalmark = 0;
    for (auto& i : m_pProblemVecProList)
    {
        totalmark += i->getMark();
    }
    return totalmark;
}
