#include "Scheduler.h"

#include <simgrid/s4u.hpp>
#include <iostream>

XBT_LOG_EXTERNAL_DEFAULT_CATEGORY(logger);

Scheduler* Scheduler::scheduler = nullptr;

void Scheduler::scheduleTask(Task task) {
    XBT_INFO("Start scheduling task %d with computation amount %d",
             task.id(), task.computationCost());

    s4u_Host* host = hosts.get(0);
    simgrid::s4u::ActorPtr actor = simgrid::s4u::Actor::create("task", host, task);
}

Scheduler* Scheduler::getScheduler() {
  if(scheduler == nullptr) {
    std::cout << "Scheduler was not called with hosts, so we shall NOT create it.";
  }
  return scheduler;
}

void Scheduler::initializeScheduler(Hosts& hosts) {
  if(scheduler != nullptr) {
    std::cout << "Scheduler was initialized multiple times";
    return;
  }
  scheduler = new Scheduler(hosts);
}
