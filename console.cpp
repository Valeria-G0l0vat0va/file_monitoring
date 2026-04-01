#include "console.h"

console::console(QObject *parent)
    :QObject(parent)
{}

void console::print(const QString& message)
{
    QTextStream out(stdout);
    out<< message<< Qt::endl;
}
