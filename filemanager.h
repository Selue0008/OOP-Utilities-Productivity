#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>

class FileManager {
public:
    bool copy(const QString &source, const QString &destination);
    bool move(const QString &source, const QString &destination);
    bool remove(const QString &path);
};

#endif 
