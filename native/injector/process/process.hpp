#include "pch.hpp"

namespace perfcat {
class IProcess {
public:
  IProcess(const std::string& work_dir,
           const std::vector<const std::string&>& args)
      : work_dir_(work_dir), args_(args){};
  virtual ~IProcess() = default;

public:
  virtual bool start();
  virtual bool kill();
  virtual bool is_running();

protected:
  const std::string& work_dir_;
  const std::vector<const std::string&>& args_;

protected:
  bool started_ = false;
};
} // namespace perfcat
