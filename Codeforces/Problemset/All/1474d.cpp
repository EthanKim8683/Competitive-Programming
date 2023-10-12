#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
const I LOGN=18;
const Lli MAX=1e18;
I a_arr[N];
Lli sums[N];
Lli spas[2][N][LOGN];
I n;
void bld(I t){
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<i)<=n;j++)spas[t][j][i]=min(spas[t][j][i-1],spas[t][j+(1<<(i-1))][i-1]);
}
Lli qry(I t,I l,I r){
  if(r-l<=0)return MAX;
  I d=31-__builtin_clz(r-l);
  return min(spas[t][l][d],spas[t][r-(1<<d)][d]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    Lli sum=0;
    for(I i=n-1;i>=0;i--)sum=a_arr[i]-sum,spas[i&1][i][0]=sum,spas[~i&1][i][0]=MAX;
    bld(0),bld(1);
    B res=sum==0&&qry(0,0,n)>=0&&qry(1,0,n)>=0;
    for(I i=0;i+1<n;i++){
      Lli dif=a_arr[i]-a_arr[i+1];
      res|=spas[0][0][0]+(i&1?2*dif:-2*dif)==0&&qry(i&1,0,i+1)-2*dif>=0&&qry(~i&1,0,i+1)+2*dif>=0&&spas[~i&1][i+1][0]+dif>=0&&qry(i&1,i+2,n)>=0&&qry(~i&1,i+2,n)>=0;
    }
    printf("%s\n",res?"YES":"NO");
  }
}