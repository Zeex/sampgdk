#ifndef UNLIMIITEDFS_FILTERSCRIPT_H
#define UNLIMIITEDFS_FILTERSCRIPT_H

#include <stack>
#include <string>
#include <sampgdk/amx.h>

namespace unlimitedfs {

class FilterScript {
public:
	FilterScript();
	explicit FilterScript(const std::string &filename);
	~FilterScript();

	AMX *amx()
		{ return &amx_; }
	const AMX *amx() const
		{ return &amx_; }

	bool Load(const std::string &filename);
	bool Unload();

	int Init(cell *retval = 0);
	int Exit(cell *retval = 0);

	bool IsLoaded() const
		{ return loaded_; }
	operator bool() const
		{ return IsLoaded(); }

	void Push(cell value);
	void PushString(const char *s);
	bool Exec(const char *name, bool default_retval = true);

private:
	// Disable copying
	FilterScript(const FilterScript &other);
	FilterScript &operator=(const FilterScript &other);

	AMX amx_;
	bool loaded_;
};

class ExecContext {
public:
	ExecContext(FilterScript *fs) : amx_(fs->amx()) {}

	~ExecContext() {
		while (!heap_args_.empty()) {
			amx_Release(amx_, heap_args_.top());
			heap_args_.pop();
		}
	}

	void PushCell(cell c) {
		amx_Push(amx_, c);
	}

	void PushFloat(float f) {
		amx_Push(amx_, amx_ftoc(f));
	}

	void PushString(const char *s) {
		cell amx_addr;
		amx_PushString(amx_, &amx_addr, 0, s, 0, 0);
		heap_args_.push(amx_addr);
	}

private:
	AMX *amx_;
	std::stack<cell> heap_args_;
};

} // namespace samp

#endif // UNLIMIITEDFS_FILTERSCRIPT_H
