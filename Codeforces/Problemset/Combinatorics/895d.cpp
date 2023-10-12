#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=1e6;
const Lli MOD=1e9+7;
Lli facs[N+1];
Lli invs[N+1];
I rems[26];
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  for(I i=0;i<=N;i++)invs[i]=inv(facs[i]);
  S a;cin>>a;
  S b;cin>>b;
  I n=a.size();
  auto cnt=[&](S t){
    fill_n(rems,26,0);
    for(auto c:a)rems[c-'a']++;
    Lli res=0,fac=1;
    for(I i=0;i<26;i++)(fac*=invs[rems[i]])%=MOD;
    for(I i=0;i<n;i++){
      I c=t[i]-'a';
      for(I j=0;j<c;j++){
        if(rems[j]==0)continue;
        (fac*=facs[rems[j]])%=MOD;
        rems[j]--;
        (fac*=invs[rems[j]])%=MOD;
        (res+=facs[n-i-1]*fac)%=MOD;
        (fac*=facs[rems[j]])%=MOD;
        rems[j]++;
        (fac*=invs[rems[j]])%=MOD;
      }
      if(rems[c]==0)break;
      (fac*=facs[rems[c]])%=MOD;
      rems[c]--;
      (fac*=invs[rems[c]])%=MOD;
    }
    return res;
  };
  printf("%lli\n",((cnt(b)-cnt(a)-1)%MOD+MOD)%MOD);
}
/*
for a given string t, assume all characters before the current index are equal,
fix a smaller character at the current index and count the number of ways to
distribute the remaining characters among the remaining indices

we can count the number of permutations of a less than b and subtract the
number of permutations of a less than a and b
*/