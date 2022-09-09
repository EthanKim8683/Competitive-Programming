#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

const I N=100000;
const Lli MAX=1e18;

I c_arr[3][N];
vector<I>adjs[N];
vector<I>cols[3];
I prms[]{0,1,2};
I bsts[3];
I ress[N];

void dfs(I a,I c=0,I p=-1){
  cols[c].push_back(a);
  for(auto b:adjs[a])if(b!=p)dfs(b,(c+1)%3,a);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>c_arr[0][i];
  for(I i=0;i<n;i++)cin>>c_arr[1][i];
  for(I i=0;i<n;i++)cin>>c_arr[2][i];
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  for(I i=0;i<n;i++)
    if(adjs[i].size()>2){printf("-1\n");return 0;}
  for(I i=0;i<n;i++)
    if(adjs[i].size()==1){dfs(i);break;}
  Lli res=MAX;
  do{
    Lli tot=0;
    for(I i=0;i<3;i++)for(auto j:cols[prms[i]])
      tot+=c_arr[i][j];
    if(tot<res)res=tot,copy_n(prms,3,bsts);
  }while(next_permutation(prms,prms+3));
  printf("%lli\n",res);
  for(I i=0;i<3;i++)for(auto j:cols[bsts[i]])
    ress[j]=i;
  for(I i=0;i<n;i++)printf("%i ",ress[i]+1);
  return 0;
}