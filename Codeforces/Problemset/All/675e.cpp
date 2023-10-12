#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
const I LOGN=17;
I a_arr[N-1];
pair<I,I>spas[N-1][LOGN];
Lli dp[N-1];
I n;
void bld(){
  for(I i=0;i<n;i++)spas[i][0]={a_arr[i],i};
  for(I i=1;i<LOGN;i++)for(I j=0;j+(1<<i)<=n;j++)spas[j][i]=max(spas[j][i-1],spas[j+(1<<(i-1))][i-1]);
}
pair<I,I>qry(I l,I r){
  I d=31-__builtin_clz(r-l);
  return max(spas[l][d],spas[r-(1<<d)][d]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n-1;i++)cin>>a_arr[i];
  bld();
  for(I i=n-2;i>=0;i--){
    I a=a_arr[i],j=qry(i+1,a_arr[i]).second;
    dp[i]=dp[j]-(a-(j+1))+(n-(i+1));
  }
  printf("%lli\n",accumulate(dp,dp+n-1,0ll));
}
/*
for each group of stations with a certain depth from a station i, the maximum
station reachable is equal to the maximum a[j] among all j in the group of
stations one level above

we can find the total distance from i to all [i + 1, n) using dynamic
programming and a range maximum data structure (like sparse table) by
querying for the station j with maximum a[j] within [i + 1, a[i])

the total distance from j to all [j + 1, n) can then be modified easily
to represent i to all [i + 1, n)
*/