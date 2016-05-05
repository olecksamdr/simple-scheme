#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <cstdlib>
#include <stdio.h>


#include "utils.h"
#include "cell_type.h"
#include "cell.h"
#include "scheme_procedure.h"
// Масив який будемо використовувати для виведення типу обєкта на екран
const char *type_arr[8] = {"SYMBOL", "NUMBER", "LIST", "EMPTY_LIST", "STRING", "CHARACTER", "BOOLEAN", "PROC"};

// ALIAS
// read_from => make_list_obj

// need to create : CHARACTER




const cell false_sym(BOOLEAN, "#f");
const cell true_sym(BOOLEAN, "#t"); // anything that isn't false_sym is true
const cell nil(EMPTY_LIST, "nil");

////////////////////// environment

// a dictionary that (a) associates symbols with cells, and
// (b) can chain to an "outer" dictionary
struct environment {
    environment(environment * outer = 0) : outer_(outer) {}

    environment(const cells & parms, const cells & args, environment * outer)
    : outer_(outer)
    {
        cellit a = args.begin();
        for (cellit p = parms.begin(); p != parms.end(); ++p)
            env_[p->val] = *a++;
    }

    // map a variable name onto a cell
    typedef std::map<std::string, cell> map;

    // return a reference to the innermost environment where 'var' appears
    map & find(const std::string & var)
    {
        if (env_.find(var) != env_.end())
            return env_; // the symbol exists in this environment
        if (outer_)
            return outer_->find(var); // attempt to find the symbol in some "outer" env
        std::cout << "unbound symbol '" << var << "'\n";
        exit(1);
    }

    // return a reference to the cell associated with the given symbol 'var'
    cell & operator[] (const std::string & var)
    {
        return env_[var];
    }
    
private:
    map env_; // inner symbol->cell mapping
    environment * outer_; // next adjacent outer env, or 0 if there are no further environments
};

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
        else{
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

    if (isCharacter(token)) {
        return cell(CHARACTER, parseCharacter(token));
    }

    if (isString(token)) {
        return cell(STRING, token);
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
void read(const std::string & s)
{
    std::list<std::string> tokens(tokenize(s));
	if (tokens.size() > 0) {
		print_tokens(make_lisp_obj(tokens));
	}
}


// the default read-eval-print-loop
void repl(const std::string & prompt)
{
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
		
		read(line);
    }
}

int main ()
{
    std::cout << "Smiple Sheme interpretator press ctr+c to exit" << std::endl;
    repl("> ");
}