#include <QCoreApplication>
#include <QTextStream>
#include <QDir>
#include <QTimer>
#include <thread>

#include "fileManager.h"
#include "console.h"


void checkFiles()
{
    fileManager::Instance().update();
}

void handleUserCommands()
{
    fileManager& manager = fileManager::Instance();
    QTextStream in(stdin);

    while (true)
    {
        QString line = in.readLine();

        if (line == "exit")
        {
            QCoreApplication::quit();
            break;
        }
        else if (line.startsWith("add "))
            manager.addFile(line.mid(4));
        else if (line.startsWith("remove "))
            manager.removeFile(line.mid(7));
        else if (line == "list")
            manager.listFiles();
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream out(stdout);

    console console;
    fileManager& manager = fileManager::Instance();

    QObject::connect(&manager, &fileManager::statusChanged, &console, &console::print);

    out << "Current directory: " << QDir::currentPath() << Qt::endl;

    out << "Commands:\n";
    out << "add <path>\n";
    out << "remove <path>\n";
    out << "list\n";
    out << "exit\n";
    out.flush();

    std::thread inputThread(handleUserCommands);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, checkFiles);
    timer.start(100);

    int result = a.exec();

    if (inputThread.joinable())
        inputThread.join();

    return result;
}
