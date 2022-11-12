#include<bits/stdc++.h>

using namespace std;

using I=int;
using B=bool;

const I N=2e5;
const I M=2e5;
const I LOGN=17;
const I MAX=1e9;

I a_arr[N];
I dp[N+1];
I spas[N][LOGN];
I n;

void bld(){
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<(i-1))<n;j++)
    spas[j][i]=max(spas[j][i-1],spas[j+(1<<(i-1))][i-1]);
}

I qry(I l,I r){
  I d=31-__builtin_clz(r-l);
  return max(spas[l][d],spas[r-(1<<d)][d]);
}

B chk(I i,I j){
  return qry(i,i+j)<=dp[j];
}

I fnd(I i){
  I l=0,r=n-i;
  while(l<r){
    I m=l+(r-l+1)/2;
    if(chk(i,m))l=m;
    else r=m-1;
  }
  return l;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    fill_n(dp,n+1,0);
    I m;cin>>m;
    for(I i=0;i<m;i++){
      I p,s;cin>>p>>s;
      dp[s]=max(dp[s],p);
    }
    for(I i=n;i>0;i--)dp[i-1]=max(dp[i-1],dp[i]);
    for(I i=0;i<n;i++)for(I j=0;j<LOGN;j++)spas[i][j]=MAX;
    for(I i=0;i<n;i++)spas[i][0]=a_arr[i];
    bld();
    I cur=0,res=0;
    B vld=1;
    while(cur<n){
      I dis=fnd(cur);
      if(!dis){vld=0;break;}
      cur+=dis,res++;
    }
    if(!vld){printf("-1\n");continue;}
    printf("%i\n",res);
  }
}