#include "Scheduler.h"

#include <simgrid/s4u.hpp>
#include <iostream>
#include "simgrid/s4u/VirtualMachine.hpp"

XBT_LOG_EXTERNAL_DEFAULT_CATEGORY(logger);

Scheduler* Scheduler::scheduler = nullptr;

void Scheduler::scheduleTask(Task task) {
    XBT_INFO("Start scheduling task %d with computation amount %f",
             task.id(), task.computationCost());

    s4u_Host* host = hosts.getLightestHost();

    startTaskOnVM(task, host);

    hosts.print();
}

void Scheduler::startTaskOnVM(Task task, s4u_Host* host) {
  auto* vm = new simgrid::s4u::VirtualMachine(std::to_string(task.id()) + "_vm", host, 1);
  XBT_INFO("Assigned host %s to task %d", host->get_name().c_str(), task.id());

  vm->start();
  simgrid::s4u::ActorPtr actor = simgrid::s4u::Actor::create("task", vm, task);
  // TODO Sleep if workaround because host load is not updated fast enough for the next task.
  // Therefore, the scheduler cannot actually load ballance.
  simgrid::s4u::this_actor::sleep_for(0.1);
}

// void Scheduler::waitTaskOnVM() {
//   actor->join();
//   vm->destroy();
// }

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
