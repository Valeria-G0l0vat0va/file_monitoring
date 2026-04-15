#include <QCoreApplication>
#include <QTextStream>
#include <QTimer>
#include <thread>
#include <chrono>

#include "fileManager.h"
#include "console.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream out(stdout);

    console console;
    fileManager& manager = fileManager::Instance();

    QObject::connect(&manager, &fileManager::statusChanged, &console, &console::print);

    out << "Commands:\n";
    out << "add <path>\n";
    out << "remove <path>\n";
    out << "list\n";
    out << "exit\n";
    out.flush();

    std::thread inputThread([&manager]()
    {
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
    });

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &a, [&manager]()
                     { manager.update();});
    timer.start(100);

    int result = a.exec();

    if (inputThread.joinable())
        inputThread.join();

    return result;
}
