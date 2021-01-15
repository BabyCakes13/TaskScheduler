
#include "Task.h"

XBT_LOG_EXTERNAL_DEFAULT_CATEGORY(logger);
Task::Task(std::vector<std::string> args)
{
  /* This constructor is used when we start the actor from the deployment file */
  /* args[0] is the actor's name, so the first parameter is args[1] */

  xbt_assert(args.size() >= 2, "The sender is expecting 1 parameter from the deployment file but got %zu",
             args.size() - 1);
  std::stringstream ct(args[1]);
  ct >> computationCost;
  id = rand();
}

void Task::operator()() const
{
  XBT_INFO("Start executing task %d with computation amount %d", id, computationCost);
  double clock_sta = simgrid::s4u::Engine::get_clock();
  simgrid::s4u::this_actor::execute(computationCost);
  double clock_end = simgrid::s4u::Engine::get_clock();
  XBT_INFO("Done task %d in %f seconds.", id, clock_end - clock_sta);
}
