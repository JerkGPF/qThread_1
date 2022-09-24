#include "bubblesort.h"

BubbleSort::BubbleSort(QObject *parent) : QThread(parent)
{

}

void BubbleSort::recvArray(QVector<int> list)
{
    m_list = list;
}

void BubbleSort::run()
{
    qDebug()<<"当前冒泡线程地址:"<<QThread::currentThread()<<endl;
    QElapsedTimer time;//计时
    time.start();
    int temp = 0;
    for(int i = 0;i<m_list.size();++i)
    {
        for(int j = 0; j<m_list.size()-i-1;++j)
        {
            if(m_list[j]>m_list[j+1])
            {
                temp = m_list[j];
                m_list[j] = m_list[j+1];
                m_list[j+1] = temp;
            }
        }
    }

    int milsec = time.elapsed();//计时结束
    qDebug()<<"冒泡排序用时:"<<milsec<<endl;
    emit finish(m_list);//将数据发送给主线程
}
