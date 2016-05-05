#include "cell.h"

cell::cell(cell_type type) : type(type), env(0) {};
cell::cell(cell_type type, const std::string & val) : type(type), val(val), env(0) {};
cell::cell(proc_type proc) : type(PROC), proc(proc), env(0) {};