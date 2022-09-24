#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using Lli=long long int;

const I N=1e6;

I degs[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b;
    degs[a-1]++,degs[b-1]++;
  }
  Lli res=0;
  for(I i=0;i<n;i++){
    Lli d=degs[i];
    res+=d*(d-1)-d*(n-1-d)+(n-1-d)*(n-2-d);
  }
  printf("%lli\n",res/6);
  return 0;
}