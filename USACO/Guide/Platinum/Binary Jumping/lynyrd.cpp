#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I M=2e5;
const I LOGM=18;
I p_arr[N];
I a_arr[M];
I invs[N];
vector<I>inds[N];
I ancs[M+1][LOGM];
I spas[LOGM][M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,q;cin>>n>>m>>q;
  for(I i=0;i<n;i++){I p;cin>>p,p_arr[i]=p-1;}
  for(I i=0;i<m;i++){I a;cin>>a,a_arr[i]=a-1;}
  for(I i=0;i<n;i++)invs[p_arr[i]]=i;
  for(I i=0;i<m;i++)inds[a_arr[i]].push_back(i);
  for(I i=0;i<n;i++)inds[i].push_back(m);
  ancs[m][0]=m;
  for(I i=0;i<m;i++){
    I j=p_arr[(invs[a_arr[i]]+1)%n];
    ancs[i][0]=*upper_bound(inds[j].begin(),inds[j].end(),i);
  }
  for(I i=1;i<LOGM;i++)for(I j=0;j<=m;j++)ancs[j][i]=ancs[ancs[j][i-1]][i-1];
  for(I i=0;i<m;i++){
    I j=i;
    for(I k=0;k<LOGM;k++)if((n-1)>>k&1)j=ancs[j][k];
    spas[0][i]=j;
  }
  for(I i=1;i<LOGM;i++)for(I j=0;j+(1<<(i-1))<m;j++)spas[i][j]=min(spas[i-1][j],spas[i-1][j+(1<<(i-1))]);
  while(q--){
    I l,r;cin>>l>>r,l--,r--;
    I d=31-__builtin_clz(r-l+1),upp=min(spas[d][l],spas[d][r-(1<<d)+1]);
    printf("%i",upp<=r);
  }
}