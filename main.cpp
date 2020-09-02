#include "loginwindow.h"

#include <QApplication>
#include <fstream>

rapidjson::Document accountDocument;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::fstream accountFstrm("account.json", std::ios::in | std::ios::out);
    std::string accountInfoStr;
    std::string tmp;
    while (accountFstrm >> tmp)
    {
        accountInfoStr += tmp + ' ';
    }
    if (accountDocument.Parse(accountInfoStr.c_str()).HasParseError())
    {
        QMessageBox::information(nullptr, "错误", "解析账户文件错误");
        a.exit();
    }
    LoginWindow w;
    w.show();
    return a.exec();
}
