#ifndef HOSTS_H
#define HOSTS_H

#include <vector>
#include "Resource.h"
#include <simgrid/s4u.hpp>

class Hosts {
private:
  std::vector<simgrid::s4u::Host*> hosts;
  static bool compareSpeed(simgrid::s4u::Host*, simgrid::s4u::Host*);
public:
  Hosts(simgrid::s4u::Engine&);
  void excludeMaster();
  void sortAscendingProcessing();
  simgrid::s4u::Host* get(int index) {
    return hosts[index];
  }
  void print();
};

#endif // HOSTS_H
