/* 可重入版strtok */
#include <stdio.h>
#include <string.h>

int main()
{
    char buf[] = "hello world c";
    char * p;
    char * save = buf;
    
    /* strtok每次返回被截取剩下的字符串的首地址  保存到p*/
    /* save是传入、传出参数 */
    while((p = strtok_r(save, " ", &save)) != NULL)
    {
        printf("%s\n", p);
    }
    return 0;
}
