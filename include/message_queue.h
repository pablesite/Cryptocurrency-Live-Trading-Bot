#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

// #include <string>
// #include <vector>
#include <mutex>
#include <deque>
#include <condition_variable>


template <class T>
class MessageQueue
{
public:
    MessageQueue();
    void send(T &&msg);
    void unblockThread();
    std::deque<T> receive(double &lookbackperiod);

private:
    std::condition_variable _cdtMQ;
    std::mutex _mtxMQ;
    std::deque<T> _queue;
};

///// The declarations and definitions of the class template member functions should all be in the same header file /////

template <typename T>
MessageQueue<T>::MessageQueue()
{
    // std::cout << "MQ constructor" << std::endl;
}

template <typename T>
std::deque<T> MessageQueue<T>::receive(double &lookbackperiod)
{
    std::cout << "\n 1";
    std::unique_lock<std::mutex> lck(_mtxMQ);

    std::cout << ", 2";

    _cdtMQ.wait(lck, [this, lookbackperiod]
                { return !(_queue.size() < lookbackperiod + 1); });

    std::cout << ", 3";

    std::cout << ", 4 (Size of queue: " << _queue.size() << ")";
    if (_queue.size() > lookbackperiod)
    {
        _queue.pop_front();
    }
     std::cout << ", 5.";

    //std::cout << _queue.size() << std::endl;
    //std::cout << _queue.size() << std::endl;
    // return msg and remove from _queue
    //T msg = std::move(_queue.front());

    //_queue.pop_front(); // si lo comento, siempre obtendría el mismo dato... no se, pensar mejor

    return _queue;
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // lock shared data
    std::lock_guard<std::mutex> lck(_mtxMQ);
    // before add a msg in the queue, clear it for having only last Traffic Light Phase in _queue
    // _queue.clear();
    // if (_queue.size() > 60)
    // {
    //     _queue.pop_front();
    // }
    // add a new message to the queue
    _queue.push_back(std::move(msg));

    // send a notification
    _cdtMQ.notify_one();
}

template <typename T>
void MessageQueue<T>::unblockThread()
{
    // lock shared data
    std::lock_guard<std::mutex> lck(_mtxMQ);
    // send a notification
    _cdtMQ.notify_one();
}

#endif