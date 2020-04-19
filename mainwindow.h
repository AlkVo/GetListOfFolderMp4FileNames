#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "folderhandle.h"
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void sig_makeListFile(QString selectedPath);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();
    void slot_progressValue(bool isSucced, const int value);

private:
    Ui::MainWindow *ui;

    int m_progresssValue = 0;

    FolderHandle *m_folder = nullptr;

    QThread *m_thread = nullptr;
};

#endif // MAINWINDOW_H
