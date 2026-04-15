#ifndef CONSOLE_H
#define CONSOLE_H
#include <QObject>
#include <QTextStream>

class console : public QObject
{
    Q_OBJECT
public:
    console(QObject *parent = nullptr);
public slots:
    void print(const QString& message);
};

#endif // CONSOLE_H
