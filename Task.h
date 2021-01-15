#ifndef TASK_H
#define TASK_H

#include <string>
#include <simgrid/s4u.hpp>
#include <vector>
#include <sstream>

typedef enum taskState {
  FREE, ALLOCATED, SCHEDULED, WAIT, EXECUTE, COMPLETE
} taskState;

class Task {
public:
  Task() = default; /* Sending the default message */
  Task(const int& computationCost) : computationCost_(computationCost){
    id_ = rand();
  }
  Task(std::vector<std::string> args);
  void operator()() const;

  int id() {
    return id_;
  }

  int computationCost() {
    return computationCost_;
  }

private:
  int id_=0;
  int computationCost_;
  taskState state;
};

#endif // TASK_H
