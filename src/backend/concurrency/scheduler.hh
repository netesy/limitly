#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "channel.hh"
#include <functional>

// A Task is a void function that takes no arguments.
using Task = std::function<void()>;

class Scheduler {
public:
    Scheduler();
    ~Scheduler();

    void submit(Task task);
    bool get_next_task(Task& task);
    void shutdown();

private:
    Channel<Task> task_queue_;
};

#endif // SCHEDULER_H
