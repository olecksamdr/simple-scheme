#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <cstdlib>

// ALIAS
// read_from => make_list_obj

// need to create : CHARACTER

// return given mumber as a string
std::string str(long n) { std::ostringstream os; os << n; return os.str(); }

// return true iff given character is '0'..'9'
bool isdig(char c) { return isdigit(static_cast<unsigned char>(c)) != 0; }


////////////////////// cell

enum cell_type { SYMBOL, NUMBER, LIST, EMPTY_LIST, STRING, BOOLEAN, PROC};
const char *type_arr[7] = {"SYMBOL", "NUMBER", "LIST", "EMPTY_LIST", "STRING", "BOOLEAN", "PROC"};

struct environment; // forward declaration; cell and environment reference each other

// a variant that can hold any kind of lisp value
struct cell {
    typedef cell (*proc_type)(const std::vector<cell> &);
    typedef std::vector<cell>::const_iterator iter;
    typedef std::map<std::string, cell> map;
    cell_type type;
    std::string val;
    std::vector<cell> list;
    proc_type proc;
    environment * env;
    cell(cell_type type = SYMBOL) : type(type), env(0) {};
    cell(cell_type type, const std::string & val) : type(type), val(val), env(0) {};
    cell(proc_type proc) : type(PROC), proc(proc), env(0) {};
};

typedef std::vector<cell> cells;
typedef cells::const_iterator cellit;

const cell false_sym(BOOLEAN, "#f");
const cell true_sym(BOOLEAN, "#t"); // anything that isn't false_sym is true
const cell nil(EMPTY_LIST, "nil");

bool isBool(const std::string & token) {
    if (token.length() == 2) {
        if (token[0] == '#' && (token[1] == 'f' || token[1] == 't'))
            return true;
        else return false;
    } else {
        return false;
    };
}

bool isNill(cell & c) {
    return c.val == "nil";
}

////////////////////// parse, read and user interaction

// convert given string to list of tokens
std::list<std::string> tokenize(const std::string & str)
{
    std::list<std::string> tokens;
    const char * s = str.c_str();
    while (*s) {
        while (*s == ' ')
            ++s;
        if (*s == '(' || *s == ')')
            tokens.push_back(*s++ == '(' ? "(" : ")");
        else {
            const char * t = s;
            while (*t && *t != ' ' && *t != '(' && *t != ')')
                ++t;
            tokens.push_back(std::string(s, t));
            s = t;
        }
    }
    return tokens;
}

void print_tokens(cell c) {
    if (c.type == EMPTY_LIST) {
        std::cout << type_arr[c.type] << "()" << std::endl;
    }
    /* print LIST (2 3) like 
        LIST( 
            NUMBER 2
            NUMBER 3
        )
    */
    if (c.type == LIST) {
        std::cout << type_arr[c.type] << " ( " << std::endl;
        for (int i = 0; i < c.list.size(); i++) {
            std::cout << "  " << type_arr[c.list[i].type] << " ";
            std::cout << c.list[i].val << std::endl;
        }
        std::cout << " )" << std::endl;
    } else {
        std::cout << type_arr[c.type] << " ";
        std::cout << c.val << std::endl;
    }
}

// numbers become NUMBER;
// #f, #t become BOOLEAN;
cell atom(const std::string & token)
{
    if (isdig(token[0]) || (token[0] == '-' && isdig(token[1])))
        return cell(NUMBER, token);
    if (isBool(token)) {
        switch (token[1]) {
            case 't': return true_sym;
            case 'f': return false_sym;
        }
    }
    return cell(SYMBOL, token);
}

// return the Lisp expression in the given tokens
cell make_lisp_obj(std::list<std::string> & tokens)
{
    const std::string token(tokens.front());
    tokens.pop_front();
    if (token == "(") {
        cell c(LIST);
        while (tokens.front() != ")")
            c.list.push_back(make_lisp_obj(tokens));
        tokens.pop_front();

        if (c.list.size() == 0) 
            c.type = EMPTY_LIST;

        return c;
    }
    else
        return atom(token);
}

// return the Lisp expression represented by the given string
cell read(const std::string & s)
{
    std::list<std::string> tokens(tokenize(s));
    return make_lisp_obj(tokens);
}


// the default read-eval-print-loop
void repl(const std::string & prompt)
{
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        print_tokens(read(line));
    }
}

int main ()
{
    repl("> ");
}