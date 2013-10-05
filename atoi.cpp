#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
 
#define MAXV (1<<20)
#define max(a,b) ((a) > (b) ? a: b)
#define min(a,b) ((a) < (b) ? a: b)
#define ll __int64
const int N = 500000 + 5;

#define isSpace(c)  (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\b' || c == '\f')
#define isDigit(c) (c >= '0' && c <= '9')
#define isAlph(c)  (c >= 'a' && c <= 'f')
#define tolower(c) (c >= 'A' && c <= 'F' ? 'a' + c - 'A': c)
enum status{kInValid = 0,kValid};
int g_status = kValid;

int StrToInt(const char *str,unsigned int BASE = 0){
	g_status = kValid;
	if(str != NULL ){
		int num = 0;
		bool sign = false;
		bool mark = false;   //是否存在有效数字
		//去掉前缀空格，换行等字符
		while(isSpace(*str))
			str++;
		//判断符号
		if(*str == '-'  || *str == '+'){
			sign = (*str == '-');
		    str++;
		}
        
		if(BASE == 0){
			if( *str == '0'){ 
				if(*(str+1) == 'x' || *(str+1) == 'X')
					BASE = 16;
				else
					BASE = 8;
			}else
				BASE = 10;
		}
		
		if(BASE == 16 && *str == '0' && (*(str+1) == 'x' || *(str+1) == 'X'))
			str += 2;

		//计算MAX,MIN
		static const int MAX = (int)((unsigned)~0 >> 1);
		const  int MAX_DIV = (int)(((unsigned)~0 >> 1) / BASE);
		const  int MAX_RAD = (int)(((unsigned)~0 >> 1) % BASE);
		static const int MIN = -(int)((unsigned)~0 >> 1) - 1;
		const int MIN_DIV = (int)((((unsigned)~0 >> 1) + 1) / BASE);
		const int MIN_RAD = (int)((((unsigned)~0 >> 1) + 1) % BASE);

		while(*str){
			//处理大小写
			unsigned int val; 
			if(isDigit(*str))
				val =  *str - '0';
			else if(isDigit(tolower(*str)))
				val = tolower(*str) - 'a' + 10;
			else 
				break;

			if(val >= BASE)
				break;
			//溢出
			if(!sign && (num > MAX_DIV || (num == MAX_DIV && val > MAX_RAD))){
				g_status = kInValid;
				num = MAX;
				break;
			}else if(sign && (num > MIN_DIV || (num == MIN_DIV && val > MIN_RAD))){
				g_status = kInValid;
				num = MIN;
				break;
			}
			
			mark = true;
			num = num * BASE + val;
			str++;
		}
        if(mark){
			if(sign && num > 0)
				num = 0 - num;
			return num;
		}
	}
	g_status = kInValid;
	return 0;
}

int main(){
	char str[100 + 2];
	while(scanf("%s",str) != EOF){
		int Base = 0;
		int num = StrToInt(str);
		if(g_status)
			printf("%d\n",num);
		else
			printf("Bad Input\n");
	}
	return 0;
}
