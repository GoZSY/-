/***********************************
思路1:最终得到str == '\0'和pattern == '\0'则可判断相等
在匹配过程中可以分为三种情况进行分析。
情况1.（匹配||(*pattern == '.' && *str!='\0')）&&pattern的下一位是'*'
情况2.（匹配||(*pattern == '.' && *str!='\0')）&&pattern的下一位不是'*'
情况3.不匹配&&(*pattern ！= '.' || *str=='\0')
第一种情况比较复杂，
'*'可以代表前边的字符可以为0,1，>=2三种情况，
当代表前边的符号个数为0时，跳过当前匹配位，与下一位进行匹配，str不变，pattern+2；
当代表前边的符号个数为1时，与下一位进行匹配，str+1,pattern+2,
当代表前边的符号个数>=2时，匹配位继续与原始字符串下一位匹配，str+1，pattern不变；

第二种情况属于正常匹配，str+1,pattern+1

第三种情况直接返回false，不会完成匹配。
************************************/
class Solution {
public:
    bool match(char* str, char* pattern)
    {
        if(str==NULL||pattern==NULL)
            return false;
        return matchCore(str,pattern);
    }
    bool matchCore(char* str, char* pattern)
    {
        if(*str=='\0'&&*pattern=='\0')
            return true;
        if(*str!='\0'&&*pattern=='\0')
            return false;
        if(*(pattern+1)=='*')
        {
            if(*pattern==*str||(*pattern=='.'&&*str!='\0'))
                return matchCore(str+1,pattern+2)||matchCore(str+1,pattern)||matchCore(str,pattern+2);
            else
                return matchCore(str,pattern+2);
        }
        if(*str==*pattern||(*pattern=='.'&&*str!='\0'))
            return matchCore(str+1,pattern+1);
        return false;
    }
};
