#ifndef UFS_FILTERSCRIPT_H
#define UFS_FILTERSCRIPT_H

#include <stack>
#include <string>
#include <sampgdk/sdk.h>

namespace ufs {

class Script {
 public:
  Script();
  explicit Script(const std::string &filename);
  ~Script();

  AMX *amx() { return &amx_; }
  const AMX *amx() const { return &amx_; }

  bool Load(const std::string &filename);
  bool Unload();

  int Init(cell *retval = 0);
  int Exit(cell *retval = 0);

  bool IsLoaded() const { return loaded_; }
  operator bool() const { return IsLoaded(); }

  void Push(cell value);
  void PushString(const char *s);
  bool Exec(const char *name, bool default_retval = true);

 private:
  Script(const Script &other);
  void operator=(const Script &other);

 private:
  AMX amx_;
  bool loaded_;
};

} // namespace samp

#endif // UFS_FILTERSCRIPT_H
