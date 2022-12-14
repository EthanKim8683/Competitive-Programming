#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
vector<I>adjs[N];
I v_arr[N];
Lli res=0;
void dfs(I a,I p=-1){
  Lli tot1=0,exc1=0;
  Lli tot2=0,exc2=0;
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    Lli v=v_arr[b];
    if(v<0)tot1+=v;
    if(v>0)tot2+=v;
    exc1=max(exc1,v);
    exc2=min(exc2,v);
  }
  Lli v=v_arr[a];
  Lli low=tot1+exc1;
  Lli upp=tot2+exc2;
  res+=max(v-upp,0ll);
  res+=max(low-v,0ll);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  for(I i=0;i<n;i++)cin>>v_arr[i];
  dfs(0);
  printf("%lli\n",res);
}