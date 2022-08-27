#include<iostream>
#include<cstdio>

using namespace std;

using I=int;

const I N=1e5;

I adjs[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x]++,adjs[y]++;
  }
  I oc=0,tc=0,ac=0;
  for(I i=0;i<n;i++){
    oc+=adjs[i]==1;
    tc+=adjs[i]==2;
    ac+=adjs[i]==n-1;
  }
  if(oc==2&&tc==n-2)printf("bus topology\n");
  else if(tc==n)printf("ring topology\n");
  else if(ac==1&&oc==n-1)printf("star topology\n");
  else printf("unknown topology\n");
  return 0;
}