#include <simgrid/s4u.hpp>
#include "simgrid/s4u/VirtualMachine.hpp"
#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "Task.h"
#include "Scheduler.h"
#include "Hosts.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(logger, "The logging channel used in this example.");

static int task_create(int argc, char** argv){
  auto task = Task(atoi(argv[1]));
  std::cout << "Task is " << argv[0] << "  " << argv[1] << "\n";

  Scheduler* scheduler = Scheduler::getScheduler();
  if (scheduler == nullptr) {
    return 1;
  }
  scheduler->scheduleTask(task);

  return 0;
}

int main(int argc, char** argv) {
  simgrid::s4u::Engine e(&argc, argv);

  e.load_platform("small_platform.xml");

  Hosts hosts(e);
  hosts.print();
  Scheduler::initializeScheduler(hosts);

  e.register_function("task_create", &task_create);
  e.load_deployment("tasks.xml");
  e.run();
  XBT_INFO("Total Simulation time %f", e.get_clock());

  return 0;
}
