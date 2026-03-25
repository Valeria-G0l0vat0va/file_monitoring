#include <QCoreApplication>
#include <QTextStream>
#include <thread>
#include <chrono>

#include "fileManager.h"

class Console : public QObject
{
    Q_OBJECT
public slots:
    void print(const QString& msg)
    {
        QTextStream out(stdout);
        out << msg << Qt::endl;
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream in(stdin);
    QTextStream out(stdout);

    fileManager& manager = fileManager::Instance();
    Console console;

    QObject::connect(&manager, &fileManager::statusChanged, &console, &Console::print);

    out << "Команды:\n";
    out << "add <путь>    - добавить файл\n";
    out << "remove <путь> - удалить файл\n";
    out << "exit          - выход\n";

    while (true)
    {
        out << "> ";

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
        else
        {
            out << "Неизвестная команда\n";
        }

        // Проверяем изменения файлов
        manager.update();

        // небольшая пауза
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}
