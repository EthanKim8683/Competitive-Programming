#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lf=long double;
const I N=1e5;
vector<I>adjs[N];
Lf res=0;
void dfs(I a,I p=-1,I d=1){
  res+=(Lf)1/d;
  for(auto b:adjs[a])if(b!=p)dfs(b,a,d+1);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  dfs(0);
  printf("%.20Lf\n",res);
}