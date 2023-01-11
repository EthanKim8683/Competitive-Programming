#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
I a_arr[N],b_arr[N],c_arr[N];
vector<I>adjs[N];
I cnts[N][2];
Lli dfs(I a,I p=-1){
  if(b_arr[a]!=c_arr[a])cnts[a][b_arr[a]]++;
  Lli res=0;
  for(auto b:adjs[a])if(b!=p){
    a_arr[b]=min(a_arr[b],a_arr[a]);
    res+=dfs(b,a);
    cnts[a][0]+=cnts[b][0],cnts[a][1]+=cnts[b][1];
  }
  I dif=min(cnts[a][0],cnts[a][1]);
  cnts[a][0]-=dif,cnts[a][1]-=dif;
  res+=(Lli)2*dif*a_arr[a];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i]>>b_arr[i]>>c_arr[i];
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v),adjs[v].push_back(u);
  }
  Lli res=dfs(0);
  if(cnts[0][0]||cnts[0][1])printf("-1\n"),exit(0);
  printf("%lli\n",res);
}