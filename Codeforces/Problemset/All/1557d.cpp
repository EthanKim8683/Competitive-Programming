#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=3e5;
const I LOGK=20;
const I FIXK=1<<LOGK;
const I MIN=-1e9;
vector<pair<I,I>>segs[N];
vector<I>cpss;
pair<I,I>vals[2*FIXK];
pair<I,I>dels[2*FIXK];
pair<I,I>dp[N];
B uses[N];
void app(I i,pair<I,I>val){
  vals[i]=max(vals[i],val);
  if(i<FIXK)dels[i]=max(dels[i],val);
}
void psh(I i){
  for(I j=LOGK-1;j>0;j--){
    I k=(i+FIXK)>>j;
    app(k<<1,dels[k]),app(k<<1|1,dels[k]),dels[k]={MIN,-1};
  }
}
void pll(I i){
  for(i+=FIXK;i>>=1;)vals[i]=max(vals[i],max(max(vals[i<<1],vals[i<<1|1]),dels[i]));
}
void upd(I l,I r,pair<I,I>val){
  psh(l),psh(r-1);
  for(I i=l+FIXK,j=r+FIXK;i<j;i>>=1,j>>=1){
    if(i&1)app(i++,val);
    if(j&1)app(--j,val);
  }
  pll(l),pll(r-1);
}
pair<I,I>qry(I l,I r){
  psh(l),psh(r-1);
  pair<I,I>res={MIN,-1};
  for(I i=l+FIXK,j=r+FIXK;i<j;i>>=1,j>>=1){
    if(i&1)res=max(res,vals[i++]);
    if(j&1)res=max(res,vals[--j]);
  }
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I j=0;j<m;j++){
    I i,l,r;cin>>i>>l>>r,i--,l--;
    segs[i].push_back({l,r});
    cpss.push_back(l);
    cpss.push_back(r);
  }
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  fill_n(vals,2*FIXK,pair<I,I>{MIN,-1});
  fill_n(dels,2*FIXK,pair<I,I>{MIN,-1});
  for(I i=0;i<n;i++){
    dp[i]={1,-1};
    for(auto&[l,r]:segs[i]){
      l=lower_bound(cpss.begin(),cpss.end(),l)-cpss.begin();
      r=lower_bound(cpss.begin(),cpss.end(),r)-cpss.begin();
      auto[val,j]=qry(l,r);
      dp[i]=max(dp[i],{val+1,j});
    }
    for(auto[l,r]:segs[i])upd(l,r,{dp[i].first,i});
  }
  I j=max_element(dp,dp+n)-dp;
  printf("%i\n",n-dp[j].first);
  for(;j!=-1;j=dp[j].second)uses[j]=1;
  for(I i=0;i<n;i++)if(!uses[i])printf("%i ",i+1);
}