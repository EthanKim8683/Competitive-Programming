#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
tuple<I,I,I>cons[N];
vector<pair<I,I>>difs[2];
vector<Lli>pres[2];
vector<Lli>sums[2];
Lli sum(I t,Lli&x){
  auto it=upper_bound(pres[t].begin(),pres[t].end(),x);
  I i=it-pres[t].begin();
  Lli pre=it==pres[t].begin()?0:pres[t][i-1];
  Lli sum=it==pres[t].begin()?0:sums[t][i-1];
  x-=pre;
  if(it!=pres[t].end()){
    auto[dif,cnt]=difs[t][i];
    Lli rem=min((Lli)cnt,x);
    sum+=rem*dif,x-=rem;
  }
  return sum;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,s;cin>>n>>s;
  Lli tot=0;
  for(I i=0;i<n;i++){
    I s,a,b;cin>>s>>a>>b;
    tot+=s,cons[i]={s,a,b};
  }
  Lli cnt=(tot+s-1)/s,acc=0;
  for(I i=0;i<n;i++){
    auto[s,a,b]=cons[i];
    acc+=(Lli)s*a;
    I dif=b-a;
    difs[dif>0].push_back({-dif,s});
  }
  Lli lwy=(Lli)cnt*s-tot;
  for(I i=0;i<2;i++)sort(difs[i].begin(),difs[i].end());
  for(I i=0;i<2;i++){
    Lli pre=0,sum=0;
    for(auto[dif,cnt]:difs[i]){
      pre+=cnt,sum+=(Lli)cnt*dif;
      pres[i].push_back(pre);
      sums[i].push_back(sum);
    }
  }
  Lli res=acc;
  for(Lli i=0,j=pres[1].size()?pres[1].back()/s:0;i<=1;i++){
    Lli rem=min(i+j,cnt)*s,cur=acc;
    cur-=sum(1,rem);
    rem=max(rem-lwy,0ll);
    cur-=sum(0,rem);
    res=max(res,cur);
  }
  printf("%lli\n",res);
}