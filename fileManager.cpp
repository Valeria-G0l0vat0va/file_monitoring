#include "fileManager.h"

fileManager& fileManager::Instance()
{
    static fileManager s;
    return s;
}

void fileManager::addFile(const QString& path)
{
    ViewFile file(path);
    file.update();

    m_files.push_back(file);

    m_prevExists.push_back(file.exists());
    m_prevSize.push_back(file.size());

    if(file.exists())
        emit statusChanged("Файл существует: " + path + " размер: " + QString::number(file.size()));
    else
        emit statusChanged("Файл не существует: " + path);

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

            emit statusChanged("Файл удален из наблюдения: " + path);
            return;
        }
    }
}

void fileManager::init()
{
    for( int i = 0; i < m_files.size(); i++)
    {
        m_files[i].update();

        m_prevExists[i] = m_files[i].exists();
        m_prevSize[i] = m_files[i].size();
    }
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
                emit statusChanged("Файл потерян: " + m_files[i].path());
            else
                emit statusChanged("Файл появился: " + m_files[i].path() + " размер: " + QString::number(size));
        }
        else if(exists && size != m_prevSize[i])
        {
            emit statusChanged("Файл изменен: " + m_files[i].path() + " новый размер: " + QString::number(size));
        }

        m_prevExists[i] = exists;
        m_prevSize[i] = size;
    }
}
