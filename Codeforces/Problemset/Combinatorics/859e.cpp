#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=100000;
const Lli MOD=1e9+7;
I outs[2*N];
vector<I>incs[2*N];
B viss[2*N];
I dfs(I a){
  if(viss[a])return 0;
  viss[a]=1;
  I res=1;
  for(auto b:incs[a])res+=dfs(b);
  if(outs[a]!=-1)res+=dfs(outs[a]);
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(outs,2*n,-1);
  for(I i=0;i<n;i++){
    I s,t;cin>>s>>t,s--,t--;
    outs[s]=t,incs[t].push_back(s);
  }
  Lli res=1;
  for(I i=0;i<2*n;i++)if(!viss[i]){
    I cnt=dfs(i),a=i,b=i;
    B cyc=0;
    while(a!=-1&&b!=-1&&outs[b]!=-1){
      a=outs[a],b=outs[outs[b]];
      if(a==b){cyc=1;break;}
    }
    (res*=cyc?outs[a]==a?1:2:cnt)%=MOD;
  }
  printf("%lli\n",res);
}
/*
from the survey results we can form a directed graph where each edge begins
at each engineer's current desk and ends at their preferred desk

now, if an engineer takes their preferred desk, the engineer (if they exist)
who originally sat there must take their preferred desk as well

from this we can see that each connected component of size n will fall into one
of two (and a half) cases:

1. if there exists no cycles in the component, there are n arrangements
   involving engineers of this component, as any of the n - 1 engineers (edges)
   may take their preferred desk and the affected engineers will move
   accordingly, in addition to the case when no engineers take their preferred
   desk

2. if there exists one cycle in the component, there are 2 arrangements
   involving engineers of this component, as engineers in the cycle can take
   their preferred seat resulting in another engineer replacing them, while
   engineers outside the cycle will displace an engineer within the cycle,
   again, in addition to the case when no engineers take their preferred desk

2.5. additionally, if the cycle is a self-loop, no engineer can take the
     looped seat, so there is only 1 arrangement

we can multiply the number of ways among all components as each component is
independent to get the total number of possible arrangements
*/