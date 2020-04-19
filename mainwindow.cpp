#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMovie>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_folder = new FolderHandle();
    m_thread = new QThread();

    m_folder->moveToThread(m_thread);

    connect(this,&MainWindow::sig_makeListFile,
            m_folder,&FolderHandle::slot_makeListFile);

    connect(m_folder,&FolderHandle::sig_progressValue,
            this,&MainWindow::slot_progressValue);

    m_thread->start();

    ui->progressBar->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString selectedPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                             "/home",
                                                             QFileDialog::ShowDirsOnly
                                                             | QFileDialog::DontResolveSymlinks);
    QString filterType = ui->lineEdit->text();

    if(selectedPath != "" && filterType != "")
    {

        //设置过滤类型
        m_folder->setFilterType(filterType);
        //生成文件
        emit sig_makeListFile(selectedPath);

        //初始化进度条
        ui->progressBar->show();
        slot_progressValue(true,0);
    }
    else
    {
        ui->progressBar->hide();
    }
}

void MainWindow::slot_progressValue(bool isSucced, const int value)
{
    ui->progressBar->setStyleSheet("QProgressBar{color: rgb(255, 255, 255);}QProgressBar::chunk {background-color: #2ebf91;width: 20px;}");
    if(isSucced)
    {
        ui->progressBar->setValue(value);
    }
    else
    {
        ui->progressBar->setStyleSheet("QProgressBar::chunk {background-color: #2ebf91;width: 20px;}");
    }
}

