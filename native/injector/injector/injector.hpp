#include "pch.hpp"

#include "process/process.hpp"

namespace perfcat {
class IInjector {
  public:
    IInjector(IProcess& process, const std::string& dll_path) : dll_path_(dll_path) {};
    virtual ~IInjector() = default;
    virtual bool install(std::size_t size, const std::uint8_t* arg);

  protected:
    const std::string& dll_path_ = "";
};
}
