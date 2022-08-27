#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;

const I N=2e5;
const I LOGN=18;
const I MAX=1e9;

I spas[N][LOGN];

void bld(){
  for(I i=1;i<LOGN;i++)
    for(I j=0;j+(1<<(i-1))<N;j++)
      spas[j][i]=min(spas[j][i-1],spas[j+(1<<(i-1))][i-1]);
}

I qry(I l,I r){
  I dis=31-__builtin_clz(r-l);
  return min(spas[l][dis],spas[r-(1<<dis)][dis]);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&spas[0][0],&spas[0][0]+sizeof(spas)/sizeof(I),MAX);
  I n,q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>spas[i][0];
  bld();
  while(q--){
    I a,b;cin>>a>>b;
    printf("%i\n",qry(a-1,b));
  }
  return 0;
}