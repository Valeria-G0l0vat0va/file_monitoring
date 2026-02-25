#include <QCoreApplication>
#include <QFileInfo>
#include <iostream>

int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);
   bool exists = QFileInfo::exists("C:/Users/golov/OneDrive/Документы");
   std::cout << (exists ? "true" : "false") << std::endl;
    return 0;
}
