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
#include "simgrid/s4u/VirtualMachine.hpp"
#include <string>
#include <cstdlib>
#include <sstream>
#include "Task.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(logger, "The logging channel used in this example.");

/* Here comes the main function of your program */
int main(int argc, char** argv)
{
  simgrid::s4u::Engine e(&argc, argv);

  e.load_platform("small_platform.xml");

  s4u_Host* pm0 = simgrid::s4u::Host::by_name("Fafard");
  auto* vm0 = new simgrid::s4u::VirtualMachine("VM0", pm0, 1);

  vm0->start();
  simgrid::s4u::Actor::create("task", pm0, Task(999));
  vm0->destroy();

  e.run();

  /* Once the simulation is done, the program is ended */
  return 0;
}
