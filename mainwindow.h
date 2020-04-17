#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QFileInfoList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //获取所有的文件夹地址
    QFileInfoList  getAllFolderListPath(QString path);

    //获取所有的文件名称
    QStringList getAllFileName(QString preName,QFileInfoList allFileInfoList);

    //写入文件
    bool writeFileIntoTxt(QString savePath,QStringList fileList);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
