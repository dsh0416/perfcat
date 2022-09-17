#include "pch.hpp"

namespace perfcat {
class Process {
  public:
    Process(const std::string& path, const std::vector<const std::string&>& args) : path_(path), args_(args) {};
    ~Process();

  public:
    virtual bool start();
    virtual bool kill();
    virtual bool is_running();

  protected:
    const std::string& path_;
    const std::vector<const std::string&>& args_;

  protected:
    bool started_ = false;
};
}
