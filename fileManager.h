#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QObject>
#include <QVector>
#include "viewfile.h"

class fileManager :  public QObject
{
    Q_OBJECT
public:
    static fileManager& Instance();

    void addFile(const QString& path);
    void removeFile(const QString& path);

    void init();
    void update();

signals:
    void statusChanged(const QString& message);

private:
    fileManager(){}
    ~fileManager(){}
    fileManager(fileManager const&);
    fileManager& operator=(fileManager const&);

    QVector<ViewFile> m_files;
    QVector<bool> m_prevExists;
    QVector<qint64> m_prevSize;
};
#endif // FILEMANAGER_H
