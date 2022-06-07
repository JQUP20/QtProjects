/**
* 线程类基类, Thread.cpp
* zhangyl 2017.03.13
**/


#include <functional>

#include "thread.h"
#include <iostream>

CThread::CThread()
{

}

CThread::~CThread()
{

}

void CThread::Start()
{
    LOG_INFO("CThread::Start()  ... ... ");
   // std::cout << "start ..." << std::endl;
    if (!m_spThread)
        m_spThread.reset(new std::thread(std::bind(&CThread::ThreadProc, this)));
}

void CThread::ThreadProc()
{
   LOG_INFO("CThread::ThreadProc() ...");
    Run();
}

void CThread::Join()
{
    if (m_spThread && m_spThread->joinable())
        m_spThread->join();
}
