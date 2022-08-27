#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I C=1e5;

I c_arr[N];
B vlds[C];
vector<I>adjs[N];
I pars[N];
set<I>neis[C];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(pars,n,-1);
  for(I i=0;i<n;i++){
    I c;cin>>c,c--;
    c_arr[i]=c;
    vlds[c]=true;
  }
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    adjs[a].push_back(b);
    adjs[b].push_back(a);
  }
  for(I i=0;i<n;i++){
    I c=c_arr[i];
    for(auto j:adjs[i])if(c!=c_arr[j])
      neis[c].insert(c_arr[j]);
  }
  I res=c_arr[0],a=neis[res].size();
  for(I i=0;i<C;i++){
    if(!vlds[i])continue;
    I b=neis[i].size();
    if(b==a&&i<res)res=i;
    if(b>a)res=i,a=b;
  }
  printf("%i\n",res+1);
  return 0;
}