#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QVector>
#include <QDebug>
#include <QElapsedTimer>

class Generate : public QThread
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);

    void recvNum(int num);//接收主线程传递过来值
protected:
    void run() override; //生成随机数
signals:
    void sendArray(QVector<int> num);//自定义信号发送数据


private:
    int m_num;

};

#endif // MYTHREAD_H
