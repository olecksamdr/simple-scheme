#ifndef _CELL_TYPE_
#define _CELL_TYPE_

enum cell_type { SYMBOL, NUMBER, LIST, EMPTY_LIST, STRING, CHARACTER, BOOLEAN, PROC};
// Масив який будемо використовувати для виведення типу оюєкта на екран
extern const char *type_arr[8];

#endif