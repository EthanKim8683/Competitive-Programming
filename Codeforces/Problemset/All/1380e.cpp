#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I M=2e5;
I t_arr[N];
set<I>grps[M+1];
I pars[M+1];
I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>t_arr[i];
  fill_n(pars,m+1,-1);
  for(I i=0;i<n;i++)grps[t_arr[i]].insert(i);
  I res=0;
  for(I i=1;i<=m;i++)for(auto j:grps[i])res+=grps[i].find(j-1)==grps[i].end();
  printf("%i\n",res-1);
  for(I i=0;i<m-1;i++){
    I a,b;cin>>a>>b,a=fnd(a),b=fnd(b);
    if(grps[a].size()<grps[b].size())swap(a,b);
    pars[b]=a;
    for(auto j:grps[b]){
      res-=grps[a].find(j+1)!=grps[a].end();
      res-=grps[a].find(j-1)!=grps[a].end();
    }
    for(auto j:grps[b])grps[a].insert(j);
    grps[b].clear();
    printf("%i\n",res-1);
  }
}
/*
the number of operations required is the total number of "groups" (minus one)
of discs among all towers, where a group is a contigious sub-tower of tower
containing discs with radius i, i + 1, i + 2, ... i + k

this is because we can move the group containing i onto the group containing
i + 1 (if they are different), reducing the number of groups by 1 each time

we can merge towers using small-to-large merging
*/