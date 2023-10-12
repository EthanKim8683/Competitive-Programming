#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
using I128=__int128;
const I N=2e5;
const Lli BAS=(1ll<<31)-1;
const Lli MOD=(1ll<<61)-1;
I ps[N+1];
Lli hshs[N+1];
set<Lli>curs;
Lli pows[N+1];
Lli fils[N+1];
Lli qry(I l,I r){
  return((hshs[r]-(I128)hshs[l]*pows[r-l])%MOD+MOD)%MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=N;i++)pows[i]=(I128)pows[i-1]*BAS%MOD;
  for(I i=1;i<=N;i++)fils[i]=(fils[i-1]+pows[i-1])%MOD;
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    S s;cin>>s;
    for(auto&c:s)c-='0';
    for(I i=0;i<n;i++)ps[i+1]=ps[i]+s[i];
    for(I i=0;i<n;i++)hshs[i+1]=((I128)hshs[i]*BAS+s[i])%MOD;
    curs.clear();
    for(I i=0;i<m;i++){
      I l,r;cin>>l>>r,l--;
      I cnt=ps[r]-ps[l];
      Lli cur=0;
      cur=(cur+(I128)qry(0,l)*pows[n-l])%MOD;
      cur=(cur+(I128)fils[cnt]*pows[n-r])%MOD;
      cur=(cur+qry(r,n))%MOD;
      curs.insert(cur);
    }
    printf("%i\n",curs.size());
  }
}