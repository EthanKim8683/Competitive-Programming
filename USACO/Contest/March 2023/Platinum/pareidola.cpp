#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
using B=bool;
using Lli=long long int;
const I N=2e5;
const I SQTU=448;
const I MAX=1e9;
const I MIN=-MAX;
vector<pair<I,C>>upds[SQTU];
set<I>acts;
set<I>inds[4];
I lows[N],upps[N];
Lli pres[N];
set<pair<I,I>>rngs;
S t;
I n;
Lli unf=0;
I fnd1(I i,I t){
  if(t==0)return i;
  if(t==1){
    auto it=inds[0].lower_bound(i);
    if(it!=inds[0].begin())return fnd1(*prev(it),0);
  }
  if(t==2){
    auto it=inds[1].lower_bound(i);
    if(it!=inds[1].begin())return fnd1(*prev(it),1);
  }
  if(t==3){
    auto it=inds[2].lower_bound(i);
    if(it!=inds[2].begin())return fnd1(*prev(it),2);
  }
  if(t==4){
    auto it=inds[2].lower_bound(i);
    if(it!=inds[2].begin())return fnd1(*prev(it),3);
  }
  if(t==5){
    auto it=inds[3].lower_bound(i);
    if(it!=inds[3].begin())return fnd1(*prev(it),4);
  }
  return-1;
}
I fnd2(I i,I t){
  if(t==5)return i;
  if(t==4){
    auto it=inds[1].upper_bound(i);
    if(it!=inds[1].end())return fnd2(*it,5);
  }
  if(t==3){
    auto it=inds[3].upper_bound(i);
    if(it!=inds[3].end())return fnd2(*it,4);
  }
  if(t==2){
    auto it=inds[2].upper_bound(i);
    if(it!=inds[2].end())return fnd2(*it,3);
  }
  if(t==1){
    auto it=inds[2].upper_bound(i);
    if(it!=inds[2].end())return fnd2(*it,2);
  }
  if(t==0){
    auto it=inds[1].upper_bound(i);
    if(it!=inds[1].end())return fnd2(*it,1);
  }
  return-1;
}
void bld(){
  for(I i=0;i<4;i++)inds[i].clear();
  for(I i=0;i<n;i++){
    if(t[i]=='b')inds[0].insert(i);
    if(t[i]=='e')inds[1].insert(i);
    if(t[i]=='s')inds[2].insert(i);
    if(t[i]=='i')inds[3].insert(i);
  }
  fill_n(lows,n,-1),fill_n(upps,n,-1);
  for(I i=0;i<n;i++){
    if(t[i]=='e')lows[i]=fnd1(i,5);
    if(t[i]=='b')upps[i]=fnd2(i,0);
  }
  fill_n(pres,n,0),unf=0;
  for(I i=0;i<n;i++){
    I j=-1;
    if(t[i]=='b')j=fnd2(i,0);
    if(j!=-1)pres[j]=max(pres[j],pres[i]+i+1);
    if(i+1<n)pres[i+1]=max(pres[i+1],pres[i]);
    unf+=pres[i];
  }
}
void upd(I i,C c){
  auto add=[&](I l,I r){
    if(r!=fnd2(l,0)||l!=fnd1(r,5))return;
    rngs.insert({l,r});
  };
  if(c=='b')add(fnd1(i,0),fnd2(i,0));
  if(c=='e')add(fnd1(i,1),fnd2(i,1)),add(fnd1(i,5),fnd2(i,5));
  if(c=='s')add(fnd1(i,2),fnd2(i,2)),add(fnd1(i,3),fnd2(i,3));
  if(c=='i')add(fnd1(i,4),fnd2(i,4));
}
void ins(I i,C c){
  if(c=='b')inds[0].insert(i);
  if(c=='e')inds[1].insert(i);
  if(c=='s')inds[2].insert(i);
  if(c=='i')inds[3].insert(i);
}
void ers(I i,C c){
  if(c=='b')inds[0].erase(i);
  if(c=='e')inds[1].erase(i);
  if(c=='s')inds[2].erase(i);
  if(c=='i')inds[3].erase(i);
}
Lli slv(){
  Lli res=unf;
  for(auto[l,r]:rngs){
    printf("(%i %i) ",l,r);
    res+=upps[l]-r;
    res+=(Lli)(l-lows[r])*(n-r);
  }
  printf("\n");
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>t;
  n=t.size();
  bld();
  printf("%lli\n",unf);
  I u;cin>>u;
  I siz=sqrt(u);
  for(I i=0;i<(u+siz-1)/siz;i++){
    I fix=min(siz,u-i*siz);
    acts.clear();
    for(I j=0;j<fix;j++){
      I p;C c;cin>>p>>c,p--;
      upds[j].clear();
      upds[j].push_back({p,c});
      acts.insert(p);
    }
    for(I j=0;j<fix;j++){
      auto[p,c]=upds[j][0];
      t[p]='*';
      if(j+1<fix)for(auto upd:upds[j])upds[j+1].push_back(upd);
      for(auto k:acts)if(t[k]!='*')upds[j].push_back({k,t[k]});
    }
    bld();
    for(I j=0;j<fix;j++){
      rngs.clear();
      for(auto[p,c]:upds[j])ins(p,c);
      for(auto[p,c]:upds[j])upd(p,c);
      printf("%lli\n",slv());
      for(auto[p,c]:upds[j])ers(p,c);
    }
    for(auto[p,c]:upds[fix-1])t[p]=c;
  }
  /*
  SQRT DECOMPOSITION:

  each index `i` stores:
  - dp[i][0:6]
  - each in dp[i][0:6] stores next node

  in preprocessing:
  - curs stores previous node (for linking)
    as well as lowest ending index (for
    updating)
  
  if update to 'b':
    link dp[i][1] with dp[0:i][0]

  elif update to 'e':
    link dp[i][2] with dp[0:i][1]
    link dp[i][5] with i

  elif update to 's':
    link dp[i][3] with dp[0:i][2]
    link dp[i][4] with dp[0:i][3]

  elif update to 'i':
    link dp[i][5] with dp[0:i][4]
  
  elif update from 'b':
    dp[0:i][0] = MAX
    link dp[prev('b')][1] with dp[0:i][0]
  
  elif update from 'e':
    dp[0:i][1] = MAX
    dp[0:i][5] = prev('e')
    link dp[prev('b')][2] with dp[0:i][1]
  
  elif update from 's':
    dp[0:i][2] = MAX
    dp[0:i][3] = MAX
    link dp[prev('b')][3] with dp[0:i][2]
    link dp[prev('b')][4] with dp[0:i][3]
  
  elif update from 'i':
    dp[0:i][4] = MAX
    link dp[prev('b')][5] with dp[0:i][4]

  alternatively,
  we could solve either *only* "update to"
  or "update from", whichever is more
  convenient

  technically you only need to apply changes
  to the latest 'b', the ones before will
  follow

  get max of all 'b's with same 'e' (always
  the last one), and apply for all `i` >= 'e'

  really, it's a range update range query
  situation, except we'd need to undo the
  updates each query. range update for
  maximum, range query for sum
  */
}