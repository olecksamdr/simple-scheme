#ifndef _CELL_
#define _CELL_

#include <vector>
#include <string>
#include <map>

#include "cell_type.h"

struct environment; // forward declaration; cell and environment reference each other

// a variant that can hold any kind of lisp value
// Всі типи ліспа будемо зберігати в цій структурі
struct cell {
    typedef cell (*proc_type)(const std::vector<cell> &);
    typedef std::vector<cell>::const_iterator iter;
    typedef std::map<std::string, cell> map;
    cell_type type;
    std::string val;
    std::vector<cell> list;
    proc_type proc;
    environment * env;
    cell(cell_type type = SYMBOL);
    cell(cell_type type, const std::string & val);
    cell(proc_type proc);
};

typedef std::vector<cell> cells;
typedef cells::const_iterator cellit;

#endif