#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <QThread>
#include <QVector>
#include <QDebug>
#include <QElapsedTimer>

class BubbleSort : public QThread
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);
    void recvArray(QVector<int> list);//接收主线程传递过来值
protected:
    void run() override; //进行排序
signals:
    void finish(QVector<int> finishList);//发送排序完成的数据
private:
    QVector<int> m_list;

};

#endif // BUBBLESORT_H
