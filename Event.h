#ifndef PARALLELTASK4_EVENT_H
#define PARALLELTASK4_EVENT_H

#include <iostream>
#include <mutex>
#include <condition_variable>

using namespace std;

class Event {
public:
    void wait_event(const char* str) {
        unique_lock<mutex> lock(mtx_);
        cout << str << "Waiting" << endl;
        cv_.wait(lock, [this]{ return ready; });

        cout << str << "Run" << endl;
    }

    void set_event(const char* str) {
        lock_guard<mutex> lock(mtx_);
        cout << str << "Processed" << endl;
        ready = true;
        cv_.notify_all();
    }

    void reset_event(const char* str) {
        lock_guard<mutex> lock(mtx_);
        cout << str << "Reset" << endl;
        ready = false;
    }

private:
    bool ready = false;
    mutex mtx_;
    condition_variable cv_;
};


#endif //PARALLELTASK4_EVENT_H
