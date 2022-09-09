#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using Lli=long long int;

const I N=3000;

vector<I>adjs[N];
I cnts[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b;
    adjs[a-1].push_back(b-1);
  }
  Lli res=0;
  for(I i=0;i<n;i++){
    fill_n(cnts,n,0);
    for(auto j:adjs[i])
      for(auto k:adjs[j])
        cnts[k]+=i!=k;
    for(I j=0;j<n;j++)
      res+=cnts[j]*(cnts[j]-1)/2;
  }
  printf("%lli\n",res);
  return 0;
}