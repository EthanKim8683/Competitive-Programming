#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I LOGN=18;
I x_arr[N];
Lli ps[2*N+1];
pair<I,I>ancs[N][LOGN];
I n;
pair<I,I>jmp(I i,I j){
  I l=0;
  for(I k=0;k<LOGN;k++)if(j>>k&1){
    auto[a,b]=ancs[i][k];
    l+=a,i=b;
  }
  return{l,i};
}
I fnd(I i){
  I l=0,r=n;
  while(l<r){
    I m=l+(r-l)/2;
    jmp(i,m)>=pair<I,I>{1,i}?r=m:l=m+1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>x_arr[i];
  for(I i=0;i<2*n;i++)ps[i+1]=x_arr[i%n]+ps[i];
  for(I i=0;i<n;i++){
    I j=upper_bound(ps,ps+2*n+1,ps[i]+k)-1-ps;
    ancs[i][0]={j/n,j%n};
  }
  for(I i=1;i<LOGN;i++)for(I j=0;j<n;j++){
    auto[a,b]=ancs[j][i-1];auto[c,d]=ancs[b][i-1];
    ancs[j][i]={a+c,d};
  }
  I res=n;
  for(I i=0;i<n;i++)res=min(res,fnd(i));
  printf("%i\n",res);
}