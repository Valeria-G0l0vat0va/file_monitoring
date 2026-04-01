#include <QCoreApplication>
#include <QTextStream>
#include <thread>
#include <chrono>
#include <QDir>
#include "fileManager.h"
#include "console.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream in(stdin);
    QTextStream out(stdout);

    console console;

    out << "Current directory: " << QDir::currentPath() << Qt::endl;

    fileManager& manager = fileManager::Instance();

    QObject::connect(&manager, &fileManager::statusChanged, &console, &console::print);

    out << "teams:\n";
    out << "add <path>    - add file\n";
    out << "remove <path> - remove file\n";
    out << "list          - show files\n";
    out << "exit          - exit\n";
    out.flush();


    while (true)
    {
        out << "> ";
        out.flush();

        QString line = in.readLine();

        if (line == "exit")
            break;

        if (line.startsWith("add "))
        {
            QString path = line.mid(4);
            manager.addFile(path);
        }
        else if (line.startsWith("remove "))
        {
            QString path = line.mid(7);
            manager.removeFile(path);
        }
        else if (line == "list")
        {
            manager.listFiles();
        }
        else
        {
            out << "unknown team\n";
        }

        manager.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
