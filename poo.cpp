#include<bits/stdc++.h>
using namespace std;
const int MAX=1001;
struct hp{
    int num[MAX];
    
    hp&operator=(const char*);
    hp&operator=(int);
    hp();
    hp(int);
    
    bool operator>(const hp&)const;
    bool operator<(const hp&)const;
    bool operator<=(const hp&)const;
    bool operator>=(const hp&)const;
    bool operator!=(const hp&)const;
    bool operator==(const hp&)const;

    hp operator+(const hp&)const;
    hp operator-(const hp&)const;
    hp operator*(const hp&)const;
    hp operator/(const hp&)const;
    hp operator%(const hp&)const;
    
    hp&operator+=(const hp&);
    hp&operator-=(const hp&);
    hp&operator*=(const hp&);
    hp&operator/=(const hp&);
    hp&operator%=(const hp&);
};
// num[0]用来保存数字位数。利用10000进制可以节省空间和时间。
hp&hp::operator=(const char* c){
    memset(num,0,sizeof(num));
    int n=strlen(c),j=1,k=1;
    for(int i=1;i<=n;i++){
        if(k==10000) j++,k=1;// 10000进制，4个数字才算1位。
        num[j]+=k*(c[n-i]-'0');
        k*=10;
    }
    num[0]=j;
    return *this;
}

hp&hp::operator=(int a){
    char s[MAX];
    sprintf(s,"%d",a);
    return *this=s;
}
hp::hp(){
	memset(num,0,sizeof(num)); 
	num[0]=1;
}
hp::hp(int n){
	*this=n;
}// 目的：支持“hp a=1;”之类的代码。

// 如果位数不等，大小是可以明显看出来的。如果位数相等，就需要逐位比较。
bool hp::operator > (const hp &b) const{
    if(num[0]!=b.num[0]) return num[0]>b.num[0];
    for(int i=num[0];i>=1;i--)
        if(num[i]!=b.num[i])
            return (num[i]>b.num[i]);
    return false;
}
bool hp::operator<(const hp &b)const{return b>*this;}
bool hp::operator<=(const hp &b)const{return !(*this>b);}
bool hp::operator>=(const hp &b)const{return !(b>*this);}
bool hp::operator!=(const hp &b)const{return (b>*this)||(*this>b);}
bool hp::operator==(const hp &b)const{return !(b>*this)&&!(*this>b);}
// 注意：最高位的位置和位数要匹配。
//加法 
hp hp::operator+(const hp&b)const{
    hp c;
    c.num[0]=max(num[0],b.num[0]);
    for(int i=1;i<=c.num[0];i++){
        c.num[i]+=num[i]+b.num[i];
        if(c.num[i]>=10000){// 进位
            c.num[i]-=10000;
            c.num[i+1]++;
        }
    }
    if(c.num[c.num[0]+1]>0) c.num[0]++;// 9999+1，计算完成后多了一位
    return c;
}
//减法 
hp hp::operator-(const hp&b)const{
   hp c;
   c.num[0]=num[0];
   for (int i=1;i<=c.num[0];i++){
       c.num[i]+=num[i]-b.num[i];
       if(c.num[i]<0){  // 退位
            c.num[i]+=10000;
            c.num[i+1]--;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;// 100000000-99999999
    return c;
}
//顺便声明 
hp&hp::operator+=(const hp &b){return *this=*this+b;}
hp&hp::operator-=(const hp &b){return *this=*this-b;}
//乘法 
hp hp::operator*(const hp&b)const{
    hp c;
    c.num[0]=num[0]+b.num[0]+1;
    for(int i=1;i<=num[0];i++){
        for(int j=1;j<=b.num[0];j++){
            c.num[i+j-1]+=num[i]*b.num[j];            // 和小学竖式的算法一模一样
            c.num[i+j]+=c.num[i+j-1]/10000;            // 进位
            c.num[i+j-1]%=10000;
        }
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999*0
    return c;
}
//同上 
hp&hp::operator*=(const hp &b){return *this=*this*b;}
hp hp::operator/(const hp&b)const{
    hp c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        // 以下三行的含义是：d=d*10000+num[i];
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        d.num[0]++;
        d.num[1]=num[i];

        // 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
        // 注意，这里是二分优化后除法和朴素除法的区别！
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*hp(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*hp(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999/99999999
    return c;            
}
hp hp::operator%(const hp&b)const{
    hp c, d;
    c.num[0]=num[0]+b.num[0]+1;
    d.num[0]=0;
    for(int i=num[0];i>=1;i--){
        // 以下三行的含义是：d=d*10000+num[i];
        memmove(d.num+2, d.num+1, sizeof(d.num)-sizeof(int)*2);
        d.num[0]++;
        d.num[1]=num[i];

        // 以下循环的含义是：c.num[i]=d/b; d%=b; 利用二分查找求c.num[i]的上界。
        // 注意，这里是二分优化后除法和朴素除法的区别！
        int left=0,right=9999,mid;
        while(left<right){
            mid = (left+right)/2;
            if(b*hp(mid)<=d) left=mid+1;
            else right=mid;
        }
        c.num[i]=right-1;
        d=d-b*hp(right-1);
    }
    while(c.num[c.num[0]]==0&&c.num[0]>1) c.num[0]--;    // 99999999/99999999
    return d;            
}
hp&hp::operator/=(const hp &b){return *this=*this/b;}
hp&hp::operator%=(const hp &b){return *this=*this%b;}
ostream&operator<<(ostream &o,hp &n){
    o<<n.num[n.num[0]];
    for(int i=n.num[0]-1;i>=1;i--){
        o.width(4);
        o.fill('0');
        o<<n.num[i];
    }
    return o;
}
istream & operator>>(istream &in, hp &n){
    char s[MAX];
    in>>s;
    n=s;
    return in;
}
inline int read(){
	int ans=0,flag=1;
	char ch=getchar();
	while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();
	if(ch=='-') flag=-1,ch=getchar();
	while(ch>='0'&&ch<='9'){
		ans=ans*10+ch-'0';
		ch=getchar();
	}
	return ans*flag;
}
hp quickPower(hp a, long long b)//是求a的b次方
{
	hp ans = 1, base = a;//ans为答案，base为a^(2^n)
	while(b > 0)//b是一个变化的二进制数，如果还没有用完
    {
		if(b & 1)//&是位运算，b&1表示b在二进制下最后一位是不是1，如果是：
			ans = ans * base;//把ans乘上对应的a^(2^n)
		 
        base = base * base;//base自乘，由a^(2^n)变成a^(2^(n+1))
		b >>= 1;//位运算，b右移一位，如101变成10（把最右边的1移掉了），10010变成1001。现在b在二进制下最后一位是刚刚的倒数第二位。结合上面b & 1食用更佳
	}
	return ans;
}

hp quickPowerMod(hp a, long long b, hp m)//是求a的b次方
{
	hp ans = 1, base = a;//ans为答案，base为a^(2^n)
	while(b > 0)
    {
		if(b & 1)
			ans = (ans *base) % m;
		
        base = (base * base) % m;
		b >>= 1;
	}
	return ans;
}

int main(){
    hp a,c;
    ios::sync_with_stdio(false);

    long long b;
    cin>>a>>b>>c;
     
    for(int i = 0;i < b;i++)
    {
        a = (a * c)%c;
    }

    cout<<a<<endl;
    return 0;
}