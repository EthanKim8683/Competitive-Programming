#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const I M=2e5;
const I LOGN=18;
const Lli MOD=998244353;
I a_arr[N];
I b_arr[M];
map<I,I>inds;
I spas[N][LOGN];
I n;
void bld(){
  for(I i=0;i<n;i++)spas[i][0]=a_arr[i];
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<i)<=n;j++)spas[j][i]=min(spas[j][i-1],spas[j+(1<<(i-1))][i-1]);
}
I qry(I l,I r){
  I d=31-__builtin_clz(r-l);
  return min(spas[l][d],spas[r-(1<<d)][d]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  if(m>n)printf("0"),exit(0);
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<m;i++)cin>>b_arr[i];
  bld();
  if(qry(0,n)!=b_arr[0])printf("0"),exit(0);
  for(I i=0;i<n;i++)inds[a_arr[i]]=i;
  Lli res=1;
  for(I i=1;i<m;i++){
    I b=b_arr[i];
    auto it=inds.find(b);
    if(it==inds.end())printf("0"),exit(0);
    I j=it->second;
    if(qry(j,n)<b)printf("0"),exit(0);
    I l=0,r=j;
    while(l<r){
      I m=l+(r-l)/2;
      qry(m,j+1)==b?r=m:l=m+1;
    }
    (res*=j-l+1)%=MOD;
  }
  printf("%lli\n",res);
}
/*
there is a range of positions a border between subarray i and i + 1 can be
located in

this is equal to the range of values before the final occurrence of b[i + 1]
and the latest a[j] such that a[j] < b[i + 1]

the answer is the number of combinations of independent border positions
*/