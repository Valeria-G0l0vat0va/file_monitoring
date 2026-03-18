#ifndef VIEWFILE_H
#define VIEWFILE_H
<<<<<<< HEAD
#include <QFileInfo>


class ViewFile
{
public:
    ViewFile(const QString& path);
=======
#include <QObject>
#include <QFileInfo>


class ViewFile : public QObject
{
    Q_OBJECT
public:
    ViewFile(const QString& path, QObject *parent = nullptr);
>>>>>>> main
    QString path() const;
    bool exists() const;
    qint64 size() const;
    void update();
private:
    QString m_path;
    qint64 m_size;
    bool m_exists;
};

#endif // VIEWFILE_H
