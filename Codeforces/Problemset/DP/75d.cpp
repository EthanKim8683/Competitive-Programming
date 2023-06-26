#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=50;
const I M=250000;
const I L=5000;
const Lli MIN=-1e18;
I lens[N];
I smls[N][L];
I bigs[M];
Lli ress[N];
Lli sums[N];
Lli pres[N];
Lli sufs[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    cin>>lens[i];
    for(I j=0;j<lens[i];j++)cin>>smls[i][j];
  }
  for(I i=0;i<m;i++)cin>>bigs[i];
  fill_n(ress,n,MIN);
  fill_n(pres,n,MIN);
  fill_n(sufs,n,MIN);
  for(I i=0;i<n;i++){
    sums[i]=accumulate(smls[i],smls[i]+lens[i],0ll);
    Lli cur=0,low=0;
    for(I j=0;j<lens[i];j++){
      ress[i]=max(ress[i],cur+smls[i][j]-low);
      cur+=smls[i][j],low=min(low,cur);
    }
    Lli pre=0;
    for(I j=0;j<lens[i];j++){
      pre+=smls[i][j];
      pres[i]=max(pres[i],pre);
    }
    Lli suf=0;
    for(I j=lens[i]-1;j>=0;j--){
      suf+=smls[i][j];
      sufs[i]=max(sufs[i],suf);
    }
  }
  Lli res=MIN,cur=0,low=0;
  for(I i=0;i<m;i++){
    I j=bigs[i]-1;
    res=max(res,ress[j]);
    res=max(res,cur+pres[j]-low);
    cur+=sums[j],low=min(low,cur-sufs[j]);
  }
  printf("%lli\n",res);
}