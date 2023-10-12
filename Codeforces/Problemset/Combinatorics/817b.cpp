#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
I a_arr[N];
map<I,I>cnts1;
map<I,I>cnts2;
Lli bin(I n,I k){
  Lli res=1;
  for(I i=n-k+1;i<=n;i++)res*=i;
  for(I i=1;i<=k;i++)res/=i;
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cnts1[a_arr[i]]++;
  I rem=3;
  for(auto[a,cnt]:cnts1)while(rem>0&&cnt>0)cnts2[a]++,rem--,cnt--;
  Lli res=1;
  for(auto[a,cnt]:cnts2)res*=bin(cnts1[a],cnt);
  printf("%lli\n",res);
}