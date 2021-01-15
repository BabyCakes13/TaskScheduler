#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Hosts.h"
#include "Task.h"

class Scheduler {
public:
  static void initializeScheduler(Hosts& hosts);
  static Scheduler* getScheduler();
  void scheduleTask(Task task);
private:
  static Scheduler* scheduler;
  // Scheduler() {}
  Scheduler(Hosts& hosts) : hosts(hosts) {}
  Hosts hosts;
};

#endif // SCHEDULER_H
