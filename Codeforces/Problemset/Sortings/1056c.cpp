#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e3;
const I M=N;
I p_arr[2*N];
I reqs[2*N];
B viss[2*N];
vector<pair<I,I>>csts;
vector<I>inds;
B cmp(I a,I b){
  return p_arr[a]<p_arr[b];
}
void mov(I x){
  if(x!=-1){
    viss[x]=1;
    I y=reqs[x];
    if(y!=-1&&!viss[y]){
      viss[y]=1,printf("%i\n",y+1),fflush(stdout);
      return;
    }
  }
  while(csts.size()&&viss[csts.back().second])csts.pop_back();
  if(csts.size()){
    auto[cst,y]=csts.back();
    viss[y]=1,printf("%i\n",y+1),fflush(stdout);
    return;
  }
  while(inds.size()&&viss[inds.back()])inds.pop_back();
  I y=inds.back();
  viss[y]=1,printf("%i\n",y+1),fflush(stdout);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<2*n;i++)cin>>p_arr[i];
  fill_n(reqs,2*n,-1);
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    reqs[a]=b,reqs[b]=a;
    if(p_arr[a]<p_arr[b])swap(a,b);
    csts.push_back({p_arr[a]-p_arr[b],a});
  }
  for(I i=0;i<2*n;i++)inds.push_back(i);
  sort(csts.begin(),csts.end());
  sort(inds.begin(),inds.end(),cmp);
  I t;cin>>t;
  if(t==1){
    mov(-1);
    for(I i=0;i<n-1;i++){
      I x;cin>>x,x--;
      mov(x);
    }
    I x;cin>>x,x--;
  }
  if(t==2){
    for(I i=0;i<n;i++){
      I x;cin>>x,x--;
      mov(x);
    }
  }
}