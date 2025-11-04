#include "mainwindow.h"
#include <QInputDialog>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Directory Tree
    model = new QFileSystemModel(this);
    model->setRootPath(QDir::rootPath());

    treeView = new QTreeView(this);
    treeView->setModel(model);
    treeView->setRootIndex(model->index(QDir::homePath()));
    treeView->setColumnWidth(0, 250);

    // Buttons
    copyBtn = new QPushButton("Copy");
    moveBtn = new QPushButton("Move");
    deleteBtn = new QPushButton("Delete");

    connect(copyBtn, &QPushButton::clicked, this, &MainWindow::copyFile);
    connect(moveBtn, &QPushButton::clicked, this, &MainWindow::moveFile);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteFile);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(copyBtn);
    btnLayout->addWidget(moveBtn);
    btnLayout->addWidget(deleteBtn);

    mainLayout->addWidget(treeView);
    mainLayout->addLayout(btnLayout);

    setCentralWidget(centralWidget);
    setWindowTitle("Smart File Manager");
    resize(700, 500);
}

MainWindow::~MainWindow() {}

QString MainWindow::getSelectedPath() {
    QModelIndex index = treeView->currentIndex();
    if (!index.isValid()) return QString();
    return model->filePath(index);
}

void MainWindow::copyFile() {
    QString src = getSelectedPath();
    if (src.isEmpty()) return;

    QString dest = QFileDialog::getExistingDirectory(this, "Select Destination Folder");
    if (dest.isEmpty()) return;

    if (fileManager.copy(src, dest))
        QMessageBox::information(this, "Success", "File copied successfully!");
    else
        QMessageBox::warning(this, "Error", "Failed to copy file!");
}

void MainWindow::moveFile() {
    QString src = getSelectedPath();
    if (src.isEmpty()) return;

    QString dest = QFileDialog::getExistingDirectory(this, "Select Destination Folder");
    if (dest.isEmpty()) return;

    if (fileManager.move(src, dest))
        QMessageBox::information(this, "Success", "File moved successfully!");
    else
        QMessageBox::warning(this, "Error", "Failed to move file!");
}

void MainWindow::deleteFile() {
    QString target = getSelectedPath();
    if (target.isEmpty()) return;

    if (fileManager.remove(target))
        QMessageBox::information(this, "Deleted", "File deleted successfully!");
    else
        QMessageBox::warning(this, "Error", "Failed to delete file!");
}
