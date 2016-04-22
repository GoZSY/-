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
思路2.动态规划法
class Solution {
public:
bool match(char* str, char* pattern)
{
bool dp[100][100];
int n=strlen(str)+1,m=strlen(pattern)+1;
dp[0][0]=true;
int i,j;
for(i=1;i<n;++i)
dp[i][0]=false; /模式串用0个字符和字符串匹配全为 假/
for(j=1;j<m;++j)
{
if(pattern[j-1]=='')
dp[0][j]=dp[0][j-2];
else
dp[0][j]=false;
}/字符串用0个字符和模式串匹配,把取0字符为真,否则为假/
for(i=1;i<n;++i)
for(j=1;j<m;++j)
{
if(str[i-1]==pattern[j-1]||pattern[j-1]=='.')
dp[i][j]=dp[i-1][j-1];
else if(pattern[j-1]=='')
{
if(pattern[j-2]==str[i-1]||pattern[j-2]=='.')
dp[i][j]=dp[i][j-2]/模式少用和前面一个字符能和i匹配那么，加上这俩个字符也和i匹配，说明取了0个字符/
||dp[i-1][j];/ 如果模式j能和i左边的数匹配那么 把取1个字符,就能和i匹配,因为号左边的数等于str i的位置/
else/ 模式左边的数不等于str i的字符,那么必须取0个字符之后能和i匹配才可以*/
dp[i][j]=dp[i][j-2];
}
else
dp[i][j]=false;
}
return dp[n-1][m-1];
}
};
