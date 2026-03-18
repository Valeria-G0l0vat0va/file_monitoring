#include "viewfile.h"

ViewFile::ViewFile(const QString& path, QObject *parent)
: QObject(parent), m_path(path), m_size(0), m_exists(false)
{}

QString ViewFile::path() const
{
    return m_path;
}

bool ViewFile::exists() const
{
    return m_exists;
}

qint64 ViewFile::size() const
{
    return m_size;
}

void ViewFile::update() const
{
    QFileInfo info(m_path);
    info.refresh();
    m_exists = info.exists();
    m_size = info.size();
}
