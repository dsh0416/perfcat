#include "pch.hpp"

#include "process/process.hpp"

namespace perfcat {
class IInjector {
public:
  IInjector(IProcess& process, const std::vector<std::uint8_t>& library)
      : library_(library){};
  virtual ~IInjector() = default;
  virtual bool install(const std::vector<uint8_t>& args);

protected:
  const std::vector<std::uint8_t>& library_;
};
} // namespace perfcat
