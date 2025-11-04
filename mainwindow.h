#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QFileSystemModel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "filemanager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void copyFile();
    void moveFile();
    void deleteFile();

private:
    QFileSystemModel *model;
    QTreeView *treeView;
    FileManager fileManager;
    QPushButton *copyBtn;
    QPushButton *moveBtn;
    QPushButton *deleteBtn;

    QString getSelectedPath();
};

#endif // MAINWINDOW_H
