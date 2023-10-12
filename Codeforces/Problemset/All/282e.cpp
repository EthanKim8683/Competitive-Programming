#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I LOGA=40;
Lli a_arr[N];
I nods[N*LOGA][2];
Lli pres[N+1],sufs[N+1];
I cur=1;
void add(Lli x){
  for(I i=LOGA-1,j=0;i>=0;i--){
    I k=x>>i&1;
    if(nods[j][k]==-1)nods[j][k]=cur,cur++;
    j=nods[j][k];
  }
}
Lli qry(Lli x){
  Lli res=0;
  for(I i=LOGA-1,j=0;i>=0;i--){
    I k=x>>i&1;
    if(nods[j][!k]!=-1){j=nods[j][!k],res|=1ll<<i;continue;}
    if(nods[j][k]!=-1){j=nods[j][k];continue;}
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&nods[0][0],&nods[0][0]+(N*LOGA)*2,-1);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)pres[i+1]=pres[i]^a_arr[i];
  for(I i=n;i>0;i--)sufs[i-1]=sufs[i]^a_arr[i-1];
  Lli res=0;
  for(I i=0;i<=n;i++)add(pres[i]),res=max(res,qry(sufs[i]));
  printf("%lli\n",res);
}