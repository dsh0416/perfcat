#include "pch.hpp"

#include "process.hpp"

namespace perfcat {
class Injector {
  public:
    Injector(Process& process) : process_(process) {};
    ~Injector();
    bool Inject();
    bool Eject();

  private:
    Process& process_;
};
}
