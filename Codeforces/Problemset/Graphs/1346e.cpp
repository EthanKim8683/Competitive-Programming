#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I N=2e5;
const I MAX=1e9;

I ress[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k,k--;
  fill_n(ress,n,MAX);
  ress[k]=0;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    I ta=ress[a],tb=ress[b];
    ress[a]=min(ta+1,tb);
    ress[b]=min(tb+1,ta);
  }
  for(I i=0;i<n;i++){
    if(ress[i]==MAX)printf("-1 ");
    else printf("%i ",ress[i]);
  }
  return 0;
}