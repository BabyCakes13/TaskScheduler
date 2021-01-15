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
    it!=hosts.end(); ++it) {
      // std::cout << ' ' << (*it)->get_name() << "\t" << (*it)->get_speed() << "\n";

      printf("%10s %15.5f %15.5f\n", (*it)->get_name().c_str(),
                                   (*it)->get_speed(),
                                   (*it)->get_load());
    }

  std::cout << '\n';
}

bool Hosts::compareSpeed(simgrid::s4u::Host* host1, simgrid::s4u::Host* host2) {
  return (host1->get_speed() < host2->get_speed());
}

void Hosts::sortAscendingProcessing() {
  std::sort(hosts.begin(), hosts.end(), compareSpeed);
}

simgrid::s4u::Host* Hosts::getLightestHost() {
  simgrid::s4u::Host* lightest = *std::min_element(hosts.begin(),
                                                   hosts.end(),
                          [] (simgrid::s4u::Host* host1, simgrid::s4u::Host* host2)
                              {
                                std::cout << host1->get_load() << " and " << host2->get_load() << "\n";
                                return host1->get_load() < host2->get_load();});
  std::cout<<"Lightes is " << lightest->get_name() << " with load " << lightest->get_load() <<"\n";
  return lightest;
}
