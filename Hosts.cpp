#include "Hosts.h"

#include <iostream>

Hosts::Hosts(simgrid::s4u::Engine& engine) {
  hosts = engine.get_all_hosts();
  excludeMaster();
  sortAscendingProcessing();
}

void Hosts::excludeMaster() {
  hosts.erase(std::remove_if(hosts.begin(),
                             hosts.end(),
                             [] (simgrid::s4u::Host* host) {return host->get_name() == "master";}));
}

void Hosts::print() {
  for (std::vector<simgrid::s4u::Host*>::iterator it=hosts.begin();
    it!=hosts.end(); ++it)
    std::cout << ' ' << (*it)->get_name() << "\t" << (*it)->get_speed() << "\n";
  std::cout << '\n';
}

bool Hosts::compareSpeed(simgrid::s4u::Host* host1, simgrid::s4u::Host* host2) {
  return (host1->get_speed() < host2->get_speed());
}

void Hosts::sortAscendingProcessing() {
  std::sort(hosts.begin(), hosts.end(), compareSpeed);
}
