#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
* reference: https://zhuanlan.zhihu.com/p/1903903271699092490
*/


/**
* Longest Palindromic Substring
* Given a string s, return the longest palindromic substring in s.
*/
char* longest_palindromic_substring(char *str)
{
    int len = strlen(str);
    bool dp[len][len];
    if(len < 2)
        return str;
    
    memset(dp, 0, sizeof(dp));
    int max_len = 1;
    int start = 0;
    for(int i = 0; i < len; i++)
        dp[i][i] = true;
    for(int j = 1; j < len; j++)
    {        
        for(int i = 0; i < j; i++)
        {   
            if(str[i] == str[j])
            {   
                if(j - i < 3) 
                    dp[i][j] = true;
                else 
                    dp[i][j] = dp[i + 1][j - 1];
            }
            if(dp[i][j] && (j - i + 1 > max_len))
            {                
                max_len = j - i + 1;
                start = i;
            }
        }
    }
    char *res = (char *)malloc(sizeof(char) * (max_len + 1));
    strncpy(res, str + start, max_len);
    res[max_len] = '\0';
    return res;
}


int main()
{
    char str[] = "babadabcdcbaabcdefgfedcba";
    char *res = longest_palindromic_substring(str);
    printf("%s\n", res);
    return 0;
}