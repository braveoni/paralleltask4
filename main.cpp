#include "Event.h"

using namespace std;

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
    thread t2(second_stage, "<Second Stage> : ");
    thread t3(third_stage, "<Third Stage> : ");

    t3.join();
    t2.join();
    t1.join();

    return 0;
}
