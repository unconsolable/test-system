#include "loginwindow.h"

#include <QApplication>
#include <fstream>

rapidjson::Document g_jsonDocumentAccount;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::fstream b_fstrmAccount("account.json", std::ios::in | std::ios::out);
    std::string b_strAccountInfoStr;
    std::string t_strInput;
    while (b_fstrmAccount >> t_strInput)
    {
        b_strAccountInfoStr += t_strInput + ' ';
    }
    if (g_jsonDocumentAccount.Parse(b_strAccountInfoStr.c_str()).HasParseError())
    {
        QMessageBox::information(nullptr, "错误", "解析账户文件错误");
        a.exit();
    }
    LoginWindow w;
    w.show();
    return a.exec();
}
