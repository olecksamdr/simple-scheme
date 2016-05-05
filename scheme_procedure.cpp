#include "scheme_procedure.h"

#include <cstdlib>

#include "utils.h"
#include "cell.h"
#include "cell_type.h"

cell proc_add(const cells & c)
{
    long n(atol(c[0].val.c_str()));
    for (cellit i = c.begin()+1; i != c.end(); ++i) n += atol(i->val.c_str());
    return cell(NUMBER, str(n));
}

cell proc_sub(const cells & c)
{
    long n(atol(c[0].val.c_str()));
    for (cellit i = c.begin()+1; i != c.end(); ++i) n -= atol(i->val.c_str());
    return cell(NUMBER, str(n));
}

cell proc_mul(const cells & c)
{
    long n(1);
    for (cellit i = c.begin(); i != c.end(); ++i) n *= atol(i->val.c_str());
    return cell(NUMBER, str(n));
}

cell proc_div(const cells & c)
{
    long n(atol(c[0].val.c_str()));
    for (cellit i = c.begin()+1; i != c.end(); ++i) n /= atol(i->val.c_str());
    return cell(NUMBER, str(n));
}