#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I M=1e5;
const I D=1e6;
const Lli MAX=1e13;
tuple<I,I,I,I>flts[M];
Lli csts[N];
Lli incs[D+1],outs[D+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<m;i++){
    I d,f,t,c;cin>>d>>f>>t>>c;
    flts[i]={d,f,t,c};
  }
  sort(flts,flts+m);
  fill_n(csts,n,MAX);
  fill_n(incs,D+1,MAX*n);
  Lli cur=MAX*n;
  for(I i=0;i<m;i++){
    auto[d,f,t,c]=flts[i];
    if(t!=0)continue;
    f--;
    Lli dif=min(csts[f],(Lli)c)-csts[f];
    cur+=dif,csts[f]+=dif;
    incs[d]=cur;
  }
  fill_n(csts,n,MAX);
  fill_n(outs,D+1,MAX*n);
  cur=MAX*n;
  for(I i=m-1;i>=0;i--){
    auto[d,f,t,c]=flts[i];
    if(f!=0)continue;
    t--;
    Lli dif=min(csts[t],(Lli)c)-csts[t];
    cur+=dif,csts[t]+=dif;
    outs[d]=cur;
  }
  for(I i=0;i<D;i++)incs[i+1]=min(incs[i+1],incs[i]);
  for(I i=D-1;i>0;i--)outs[i-1]=min(outs[i-1],outs[i]);
  Lli res=MAX;
  for(I i=0;i+k+1<=D;i++)res=min(res,incs[i]+outs[i+k+1]);
  printf("%lli\n",res>=MAX?-1:res);
}