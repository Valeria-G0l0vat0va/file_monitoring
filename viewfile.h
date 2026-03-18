#ifndef VIEWFILE_H
#define VIEWFILE_H
#include <QFileInfo>


class ViewFile
{
public:
    ViewFile(const QString& path);
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
