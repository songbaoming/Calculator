#include "Calculator.h"

double calculate(void)
{
	get_token();
	return jj_ys();
}

double jj_ys(void)
{
	double result;

	result = ccm_ys();
	while (!is_error){
		switch (*token){
		case '+':
			get_token();
			result += ccm_ys();
			break;
		case '-':
			get_token();
			result -= ccm_ys();
			break;
		default:
			return result;
		}
	}
	return result;
}

double ccm_ys(void)
{
	double result, temp;

	result = mi_ys();
	while (!is_error){
		switch (*token){
		case '*':
			get_token();
			result *= mi_ys();
			break;
		case '/':
			get_token();
			if (!(temp = mi_ys()))
				is_error = ERR_DIV_BY_ZORE;
			else
				result /= temp;
			break;
		case '%':
			get_token();
			result = fmod(result, mi_ys());
			break;
		default:
			return result;
		}
	}
	return result;
}

double mi_ys(void)
{
	double result, exp;

	result = kh_zf();
	if (*token == '^'){
		get_token();
		exp = mi_ys();
		if ((result < 0 && exp != (int)exp) || (result == 0 && exp < 0))
		{
			is_error = (ERR_POW_ERROR);
			return result;
		}
		result = pow(result, exp);
	}

	return result;
}

double kh_zf(void)
{
	double result;

	switch (*token){
	case '(':
		get_token();
		result = jj_ys();
		if (*token != ')')
			is_error = (ERR_EXPR_ERROR);
		get_token();
		return result;
	case '+':
		get_token();
		return kh_zf();
	case '-':
		get_token();
		return -kh_zf();
	default:
		return atom();
	}
}

double atom(void)
{
	double result;

	if (tok_type == NUMBER)
		result = atof(token);
	else{
		is_error = (ERR_EXPR_ERROR);
		result = 0;
	}

	get_token();
	return result;
}

/*判断字符类型并指向下个字符*/
void get_token(void)
{
	char *temp;
	tok_type = 0;
	temp = token;
	*temp = '\0';

	if (!*ch) return;/*表达式到达结尾*/
	if (isspace(*ch)) ch++;/*为了跳过空格*/
	if (strchr("+-*/%^()", *ch)){
		tok_type = FUHAO;
		*temp++ = *ch++;
	}
	else if (isalpha(*ch)){
		while (!isfuhao(*ch)) *temp++ = *ch++;
		tok_type = BIANLIANG;
	}
	else if (isdigit(*ch) || *ch == '.'){
		while (isdigit(*ch) || *ch == '.' || toupper(*ch) == 'E') *temp++ = *ch++;
		tok_type = NUMBER;
	}
	*temp = '\0';
}

/*判断是否是分隔符*/
int isfuhao(char c)
{
	if (strchr("+-*/%^()", c) || c == 9 || c == '\r' || c == 0)
		return 1;
	return 0;
}