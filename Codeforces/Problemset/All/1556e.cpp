#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I LOGN=17;
const Lli MAX=1e18;
const Lli MIN=-MAX;
I a_arr[N];
I b_arr[N];
Lli ps[N+1];
Lli spas[2][N][LOGN];
I n;
void bld(){
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<i)<=n;j++)spas[0][j][i]=min(spas[0][j][i-1],spas[0][j+(1<<(i-1))][i-1]),spas[1][j][i]=max(spas[1][j][i-1],spas[1][j+(1<<(i-1))][i-1]);
}
pair<Lli,Lli>qry(I l,I r){
  I d=31-__builtin_clz(r-l);
  return{min(spas[0][l][d],spas[0][r-(1<<d)][d]),max(spas[1][l][d],spas[1][r-(1<<d)][d])};
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&spas[0][0][0],&spas[0][0][0]+N*LOGN,MAX);
  fill(&spas[1][0][0],&spas[1][0][0]+N*LOGN,MIN);
  I q;cin>>n>>q;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>b_arr[i];
  for(I i=0;i<n;i++)ps[i+1]=ps[i]+b_arr[i]-a_arr[i];
  for(I i=0;i<n;i++)spas[0][i][0]=spas[1][i][0]=ps[i+1];
  bld();
  while(q--){
    I l,r;cin>>l>>r,l--,r--;
    if(ps[r+1]-ps[l]!=0){printf("-1\n");continue;}
    auto[low,upp]=qry(l,r+1);
    if(low-ps[l]<0){printf("-1\n");continue;}
    printf("%lli\n",upp-ps[l]);
  }
}