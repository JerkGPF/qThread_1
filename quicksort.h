#ifndef QUICKSORT_H
#define QUICKSORT_H


#include <QThread>
#include <QVector>
#include <QDebug>
#include <QElapsedTimer>

class QuickSort : public QThread
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);
    void recvArray(QVector<int> list);//接收主线程传递过来值
protected:
    void run() override; //生成随机数
signals:
    void finish(QVector<int> finishList);//发送排序完成的数据


private:
    QVector<int> m_list;

    void quickSort(QVector<int> &list,int l,int r);
};

#endif // QUICKSORT_H
