#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "resource.h"

#define NUMBER    1
#define BIANLIANG 2
#define FUHAO     3
#define ERR_NO_ERROR		0
#define ERR_POW_ERROR	1
#define ERR_EXPR_ERROR	2
#define ERR_DIV_BY_ZORE	3

extern char *ch;
extern char token[60];
extern char tok_type;
extern int is_error;//标示错误发生，无错为0，否则非零！

void get_token(void);/*判断字符类型并指向下个字符*/
int isfuhao(char c);/*判断是否是分隔符*/
double calculate(void);
double jj_ys(void);
double ccm_ys(void);
double mi_ys(void);
double kh_zf(void);
double atom(void);