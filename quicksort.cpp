#include "quicksort.h"

QuickSort::QuickSort(QObject *parent) : QThread(parent)
{

}

void QuickSort::recvArray(QVector<int> list)
{
    m_list = list;

}

void QuickSort::run()
{
    qDebug()<<"当前快排线程地址:"<<QThread::currentThread()<<endl;
    QElapsedTimer time;//计时
    time.start();

    quickSort(m_list,0,m_list.size()-1);

    int milsec = time.elapsed();//计时结束
    qDebug()<<"快速排序用时:"<<milsec<<endl;
    emit finish(m_list);//将数据发送给主线程
}

void QuickSort::quickSort(QVector<int> &list, int l, int r)
{
    if(l < r)
    {
        int i = l,j =r;
        int x = list[l];
        while (i<j)
        {
            while(i < j && list[j] >= x)
            {
                j--;
            }
            if(i < j)
            {
                list[i++] = list[j];
            }
            while(i < j && list[i] < x)
            {
                i++;
            }
            if(i < j)
            {
                list[j--] = list [i];
            }
        }
        list[i] = x;
        quickSort(list,l,i - 1);
        quickSort(list,i + 1,r);
    }
}
