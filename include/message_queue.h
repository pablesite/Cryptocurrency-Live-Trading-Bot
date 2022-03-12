#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <iostream>
#include <deque>
#include <mutex>
#include <condition_variable>

/*
Class for managing queue of data
*/
template <class T>
class MessageQueue
{
public:
    // constructor
    MessageQueue();
    ~MessageQueue();

    // propietary functions
    void send(T &&msg);
    std::deque<T> receive(int &lookbackperiod);

private:
    // queue for data of type <T>
    std::deque<T> _queue;

    // locked variables
    std::condition_variable _cdtMQ;
    std::mutex _mtxMQ;
};

///// The declarations and definitions of the class template member functions should all be in the same header file /////

// constructor
template <typename T>
MessageQueue<T>::MessageQueue()
{
    std::cout << "MQ constructor" << std::endl;
}

template <typename T>
MessageQueue<T>::~MessageQueue()
{
    std::cout << "MQ destructor" << std::endl;
}


// obtain data from the shared queue
template <typename T>
std::deque<T> MessageQueue<T>::receive(int &lookbackperiod)
{
    // lock shared data
    std::unique_lock<std::mutex> lck(_mtxMQ);

    // locked until queue is big enough
    _cdtMQ.wait(lck, [this, lookbackperiod]
                { return !(_queue.size() < lookbackperiod + 1); });

    // maintain the queue with a maximum size
    if (_queue.size() > lookbackperiod)
    {
        _queue.pop_front();
    }

    return _queue;
}

// save data in the shared queue
template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // lock shared data
    std::lock_guard<std::mutex> lck(_mtxMQ);

    // save data in the shared queue
    _queue.push_back(std::move(msg));

    // send a notification to unblock receive method
    _cdtMQ.notify_one();
}

#endif