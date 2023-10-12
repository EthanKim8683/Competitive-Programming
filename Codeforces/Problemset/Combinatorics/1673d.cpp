#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const Lli MOD=1e9+7;
map<I,I>cnts1,cnts2,difs;
vector<pair<I,I>>vars;
Lli res=0;
Lli b,c,r,d,e;
B dfs(I val,I i=0){
  if(i==vars.size()){
    (res+=((r-1)/val+1)%MOD*((r-1)/val+1)%MOD)%=MOD;
    return c-val<b||e+val>d;
  }
  auto[p,cnt]=vars[i];
  for(I j=0;j<=cnt;j++){
    if(dfs(val,i+1))return 1;
    val*=p;
  }
  return 0;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I q,y;cin>>b>>q>>y;
    I z;cin>>c>>r>>z;
    d=b+(Lli)q*(y-1),e=c+(Lli)r*(z-1);
    if(c<b||e>d){printf("0\n");continue;}
    if((c-b)%q!=0){printf("0\n");continue;}
    cnts1.clear(),cnts2.clear();
    I t=q;
    for(I i=2;i*i<=t;i++)for(;t%i==0;t/=i)cnts1[i]++;
    if(t>1)cnts1[t]++;
    t=r;
    for(I i=2;i*i<=t;i++)for(;t%i==0;t/=i)cnts2[i]++;
    if(t>1)cnts2[t]++;
    difs.clear();
    for(auto[p,cnt]:cnts1)difs[p]=cnts2[p]-cnt;
    for(auto[p,cnt]:cnts2)difs[p]=cnt-cnts1[p];
    B vld=1;
    I pre=1;
    vars.clear();
    for(auto[p,dif]:difs){
      vld&=dif>=0;
      if(dif==0)vars.push_back({p,cnts2[p]});
      if(dif>0)for(I j=0;j<cnts2[p];j++)pre*=p;
    }
    if(!vld){printf("0\n");continue;}
    res=0;
    if(dfs(pre)){printf("-1\n");continue;}
    printf("%lli\n",res);
  }
}
/*
the common difference of C is the lcm of the common differences of A and B

to find all possible common differences of A, we can look at the prime factors
of q and r

if r has more of a prime factor p, the common difference of A must have that
exact same amount

if r has the same amount of a prime factor p, the common difference of A can
have at most that amount

if r has fewer of a prime factor p, A does not exist

furthermore, there are infinitely many arithmetic sequences if it is possible
to start before b and have first common element equal to c or end after
b + q * (y - 1) and have last common element equal to c + r * (z - 1)
*/