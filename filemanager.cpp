#include "filemanager.h"
#include <QFile>
#include <QDir>

bool FileManager::copy(const QString &source, const QString &destination) {
    QFileInfo fileInfo(source);
    QString target = destination + "/" + fileInfo.fileName();
    return QFile::copy(source, target);
}

bool FileManager::move(const QString &source, const QString &destination) {
    QFileInfo fileInfo(source);
    QString target = destination + "/" + fileInfo.fileName();
    if (QFile::copy(source, target)) {
        QFile::remove(source);
        return true;
    }
    return false;
}

bool FileManager::remove(const QString &path) {
    QFileInfo info(path);
    if (info.isDir())
        return QDir(path).removeRecursively();
    return QFile::remove(path);
}
