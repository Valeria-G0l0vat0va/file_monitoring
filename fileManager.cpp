#include "fileManager.h"

fileManager& fileManager::Instance()
{
    static fileManager s;
    return s;
}

void fileManager::addFile(const QString& path)
{
    QString normalizedPath = path;
    normalizedPath.replace("\\", "/");

    for (int i = 0; i < m_files.size(); ++i)
    {
        if (m_files[i].path() == normalizedPath)
        {
            emit statusChanged("The file is already under surveillance: " + normalizedPath);
            return;
        }
    }

    QFileInfo info(normalizedPath);
    if (!info.exists())
    {
        emit statusChanged("file not exists: " + normalizedPath);
        return;
    }

    if (info.isDir())
    {
        emit statusChanged("Error: This is a folder, not a file: " + normalizedPath);
        return;
    }

    if (!info.isReadable())
    {
        emit statusChanged("Error: there is no access to the file: " + normalizedPath);
        return;
    }

    ViewFile file(normalizedPath);
    file.update();

    m_files.push_back(file);

    m_prevExists.push_back(file.exists());
    m_prevSize.push_back(file.size());

    if(file.exists())
        emit statusChanged("file exists: " + normalizedPath + " size: " + QString::number(file.size()));

}

void fileManager::removeFile(const QString& path)
{
    for( int i = 0; i < m_files.size(); i++)
    {
        if(m_files[i].path() == path)
        {
            m_files.remove(i);
            m_prevExists.remove(i);
            m_prevSize.remove(i);

            emit statusChanged("file deleted from monitoring: " + path);
            return;
        }
    }
    emit statusChanged("file not found: " + path);
}

void fileManager::listFiles()
{
    if (m_files.isEmpty())
    {
        emit statusChanged("No files");
        return;
    }

    for (int i = 0; i < m_files.size(); ++i)
    {
        QString status;
        if(m_files[i].exists())
        {
            status = "exists, size " + QString::number(m_files[i].size());
        }
        else
            status = "missing";
        emit statusChanged(QString::number(i+1) + ". " + m_files[i].path() + " - " + status);
    }
}

void fileManager::init()
{
    if (m_files.isEmpty())
    {
        emit statusChanged("No file for init");
        return;
    }

    for( int i = 0; i < m_files.size(); i++)
    {
        m_files[i].update();

        m_prevExists[i] = m_files[i].exists();
        m_prevSize[i] = m_files[i].size();
    }
    emit statusChanged("Initialization is completed. Observed " + QString::number(m_files.size()) + " files");
}

void fileManager::update()
{
    for(int i = 0; i < m_files.size(); i++)
    {
        m_files[i].update();

        bool exists = m_files[i].exists();
        qint64 size = m_files[i].size();

        if(exists != m_prevExists[i])
        {
            if(!exists)
                emit statusChanged("file is lost: " + m_files[i].path());
            else
                emit statusChanged("file appeared: " + m_files[i].path() + " size " + QString::number(size));
        }
        else if(exists && size != m_prevSize[i])
        {
            emit statusChanged("file changed: " + m_files[i].path() + " new size: " + QString::number(size));
        }

        m_prevExists[i] = exists;
        m_prevSize[i] = size;
    }
}
