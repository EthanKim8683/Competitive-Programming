#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=100000;
const I M=100000;
const I LOGA=20;
const I FIXA=1<<LOGA;
const I SQTN=sqrt(N-1)+1;
I a_arr[N];
pair<I,I>qrys[M];
vector<I>blks[SQTN];
I lows[FIXA],upps[FIXA],rems[FIXA];
Lli ress[M];
B cmp(I a,I b){
  return qrys[a].second<qrys[b].second;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<m;i++){
    I l,r;cin>>l>>r,l--;
    qrys[i]={l,r};
    blks[l/SQTN].push_back(i);
  }
  for(I i=0;i<SQTN;i++){
    sort(blks[i].begin(),blks[i].end(),cmp);
    I r1=i*SQTN,pre1=0;
    Lli acc=0;
    for(auto j:blks[i]){
      auto[l2,r2]=qrys[j];
      for(;r1<r2;r1++){
        lows[pre1]++,pre1^=a_arr[r1];
        acc+=lows[pre1^k],upps[pre1]++;
      }
      Lli tot=acc;
      for(I l1=i*SQTN,pre2=0;l1<l2;l1++){
        tot-=upps[pre2^k]-rems[pre2^k];
        pre2^=a_arr[l1],rems[pre2]++;
      }
      for(I l1=i*SQTN,pre2=0;l1<l2;l1++){
        pre2^=a_arr[l1],rems[pre2]=0;
      }
      ress[j]=tot;
    }
    for(I j=i*SQTN,pre1=0;j<n;j++){
      lows[pre1]=0,pre1^=a_arr[j];
      upps[pre1]=0;
    }
  }
  for(I i=0;i<m;i++)printf("%lli\n",ress[i]);
}