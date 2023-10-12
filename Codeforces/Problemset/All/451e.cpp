#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=20;
const Lli MOD=1e9+7;
Lli f_arr[N];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(Lli n,Lli k){
  if(n<k)return 0;
  Lli num=1,den=1;
  for(Lli i=n-k+1;i<=n;i++)(num*=i%MOD)%=MOD;
  for(Lli i=1;i<=k;i++)(den*=i%MOD)%=MOD;
  return num*inv(den)%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;Lli s;cin>>n>>s;
  for(I i=0;i<n;i++)cin>>f_arr[i];
  Lli res=0;
  for(I i=0;i<(1<<n);i++){
    Lli rem=s;
    for(I j=0;j<n;j++)if(i>>j&1)rem-=f_arr[j]+1;
    (res+=(__builtin_popcount(i)%2==0?1:-1)*bin(rem+n-1,n-1))%=MOD;
  }
  printf("%lli\n",(res+MOD)%MOD);
}
/*
we can use the principle of inclusion exclusion to subtract all ways to make
s where the number of flowers chosen from any box i exceeds f[i]

for any set of boxes B, the number of ways to choose flowers such that all
i in B contribute greater than f[i] flowers is equal to the number of
flowers remaining after subtracting f[i] + 1 from s for all such i
distributed among all n boxes

this is because, after assigning the boxes in B a contribution strictly
greater than they are able, the remaining required flowers can come from
any box, chosen or not, and still result in a selection exceeding in all
boxes B
*/