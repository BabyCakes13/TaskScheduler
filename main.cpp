/* Copyright (c) 2006-2020. The SimGrid Team. All rights reserved.          */

/* This program is free software; you can redistribute it and/or modify it
 * under the terms of the license (GNU LGPL) which comes with this package. */

/* This example shows how to declare and start your actors.
 *
 * The first step is to declare the code of your actors (what they do exactly does not matter to this example) and then
 * you ask SimGrid to start your actors. There is three ways of doing so:
 *  - Directly, by instantiating your actor as parameter to Actor::create()
 *  - By first registering your actors before instantiating it
 *  - Through the deployment file.
 *
 * This example shows all these solutions, even if you obviously should use only one of these solutions to start your
 * actors. The most advised solution is to use a deployment file, as it creates a clear separation between your
 * application and the settings to test it. This is a better scientific methodology. Actually, starting an actor with
 * Actor::create() is mostly useful to start an actor from another actor.
 */

#include <simgrid/s4u.hpp>
#include <string>
#include <cstdlib>
#include <sstream>

// This declares a logging channel so that XBT_INFO can be used later
XBT_LOG_NEW_DEFAULT_CATEGORY(logger, "The logging channel used in this example.");

class Task {
private:
  int computationCost;
  int taskId=0;
public:
  explicit Task() = default; /* Sending the default message */
  explicit Task(const int& computationCost) : computationCost(computationCost){
    taskId = rand();
  }
  explicit Task(std::vector<std::string> args)
  {
    /* This constructor is used when we start the actor from the deployment file */
    /* args[0] is the actor's name, so the first parameter is args[1] */

    xbt_assert(args.size() >= 2, "The sender is expecting 1 parameter from the deployment file but got %zu",
               args.size() - 1);
    std::stringstream ct(args[1]);
    ct >> computationCost;
    taskId = rand();
  }

  void operator()() const /* This is the main code of the actor */
  {
    XBT_INFO("Start executing task %d with computation amount %d", taskId, computationCost);
    simgrid::s4u::this_actor::execute(computationCost);
    XBT_INFO("Done: %d", taskId);
  }
};

/* Here comes the main function of your program */
int main(int argc, char** argv)
{
  /* When your program starts, you have to first start a new simulation engine, as follows */
  simgrid::s4u::Engine e(&argc, argv);

  /* Then you should load a platform file, describing your simulated platform */
  e.load_platform("small_platform.xml");
  e.register_actor<Task>("task");

  e.load_deployment("tasks.xml");

  /* Once every actors are started in the engine, the simulation can start */
  e.run();

  /* Once the simulation is done, the program is ended */
  return 0;
}
