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

Event first, second, third;

void first_stage(const char* str) {
    cout << "Processing First Stage" << endl;
    this_thread::sleep_for(chrono::milliseconds(5000));
    first.set_event(str);
}

void second_stage(const char* str) {
    first.wait_event(str);
    cout << "Processing Second Stage" << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    second.set_event(str);
}

void third_stage(const char* str) {
    second.wait_event(str);
    cout << "Processing Third Stage" << endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
    third.set_event(str);
}

int main() {
    cout << "Hardware Concurrency: " << thread::hardware_concurrency() << endl;

    thread t1(first_stage, "<First Stage>: ");
    thread t2(second_stage, "<Second Stage 1> : ");
    thread t3(second_stage, "<Second Stage 2> : ");
    thread t4(third_stage, "<Third Stage> : ");

    t4.join();
    t3.join();
    t2.join();
    t1.join();

    return 0;
}
