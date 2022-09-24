#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //1.创建子线程对象
    Generate* gen = new Generate;
    BubbleSort* bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;
    //2.启动子线程
    connect(ui->start,&QPushButton::clicked,[=]()
    {
       //2.1发送信号告知子线程需要多少个数据
        emit starting(10000);
        //2.2启动子线程
        gen->start();
    });
    //3.子线程接收数据
    connect(this,&MainWindow::starting,gen,&Generate::recvNum);
    //4.主线程接收数据
    connect(gen,&Generate::sendArray,this,[=](QVector<int> list)
    {
        //4.1随机数生成完毕，调用子线程进行排序
        for (int i = 0;i < list.size();++i) {
            ui->random->addItem(QString::number(list.at(i)));
        }
        //4.2启动排序线程
        bubble->start();
        quick->start();
    });
    //5.随机数线程发送数据给排序线程
    connect(gen,&Generate::sendArray,bubble,&BubbleSort::recvArray);
    connect(gen,&Generate::sendArray,quick,&QuickSort::recvArray);
    //6.主线程接收数据
    connect(bubble,&BubbleSort::finish,this,[=](QVector<int> list)
    {
        //6.1冒泡排序完成
        for (int i = 0;i < list.size();++i) {
            ui->boubbleSort->addItem(QString::number(list.at(i)));
        }
    });
    connect(quick,&QuickSort::finish,this,[=](QVector<int> list)
    {
        //6.2快速排序完成
        for (int i = 0;i < list.size();++i) {
            ui->quickSort->addItem(QString::number(list.at(i)));
        }

    });

    //7.释放资源
    connect(this,&MainWindow::destroyed,this,[=]()
    {
       gen->quit();
       gen->wait();
       gen->deleteLater();

       bubble->quit();
       bubble->wait();
       bubble->deleteLater();

       quick->quit();
       quick->wait();
       quick->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

