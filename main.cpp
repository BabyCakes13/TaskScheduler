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
#include <sstream>

// This declares a logging channel so that XBT_INFO can be used later
XBT_LOG_NEW_DEFAULT_CATEGORY(s4u_actor_create, "The logging channel used in this example");

/* Our first class of actors is simply implemented with a function, that takes a single string as parameter.
 *
 * Later, this actor class is instantiated within the simulation.
 */
static void receiver(const std::string& mailbox_name)
{
  simgrid::s4u::Mailbox* mailbox = simgrid::s4u::Mailbox::by_name(mailbox_name);

  XBT_INFO("Hello s4u, I'm ready to get any message you'd want on %s", mailbox->get_cname());

  const auto* msg1 = static_cast<std::string*>(mailbox->get());
  const auto* msg2 = static_cast<std::string*>(mailbox->get());
  const auto* msg3 = static_cast<std::string*>(mailbox->get());
  XBT_INFO("I received '%s', '%s' and '%s'", msg1->c_str(), msg2->c_str(), msg3->c_str());
  delete msg1;
  delete msg2;
  delete msg3;
  XBT_INFO("I'm done. See you.");
}

/* Our second class of actors is also a function */
static void forwarder(int argc, char** argv)
{
  xbt_assert(argc >= 3, "Actor forwarder requires 2 parameters, but got only %d", argc - 1);
  simgrid::s4u::Mailbox* in    = simgrid::s4u::Mailbox::by_name(argv[1]);
  simgrid::s4u::Mailbox* out   = simgrid::s4u::Mailbox::by_name(argv[2]);
  auto* msg                    = static_cast<std::string*>(in->get());
  XBT_INFO("Forward '%s'.", msg->c_str());
  out->put(msg, msg->size());
}

/* Declares a third class of actors which sends a message to the mailbox 'mb42'.
 * The sent message is what was passed as parameter on creation (or 'GaBuZoMeu' by default)
 *
 * Later, this actor class is instantiated twice in the simulation.
 */
class Sender {
public:
  std::string mbox  = "mb42";
  std::string msg = "GaBuZoMeu";
  explicit Sender() = default; /* Sending the default message */
  explicit Sender(const std::string& arg) : msg(arg) { /* Sending the specified message */}
  explicit Sender(std::vector<std::string> args)
  {
    /* This constructor is used when we start the actor from the deployment file */
    /* args[0] is the actor's name, so the first parameter is args[1] */

    xbt_assert(args.size() >= 3, "The sender is expecting 2 parameters from the deployment file but got %zu",
               args.size() - 1);
    msg  = args[1];
    mbox = args[2];
  }
  void operator()() const /* This is the main code of the actor */
  {
    XBT_INFO("Hello s4u, I have something to send");
    simgrid::s4u::Mailbox* mailbox = simgrid::s4u::Mailbox::by_name(mbox);

    mailbox->put(new std::string(msg), msg.size());
    XBT_INFO("I'm done. See you.");
  }
};

class Task {
private:
  int computationCost;
public:
  explicit Task() = default; /* Sending the default message */
  explicit Task(const int& computationCost) : computationCost(computationCost) {}
  explicit Task(std::vector<std::string> args)
  {
    /* This constructor is used when we start the actor from the deployment file */
    /* args[0] is the actor's name, so the first parameter is args[1] */

    xbt_assert(args.size() >= 2, "The sender is expecting 1 parameter from the deployment file but got %zu",
               args.size() - 1);
    std::stringstream ct(args[1]);
    ct >> computationCost;
  }

  void operator()() const /* This is the main code of the actor */
  {
    XBT_INFO("Start executing...");
    simgrid::s4u::this_actor::execute(computationCost);
    XBT_INFO("Done.");
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

  /* Once every actors are started in the engine, the simulation can start */
  e.run();

  /* Once the simulation is done, the program is ended */
  return 0;
}
