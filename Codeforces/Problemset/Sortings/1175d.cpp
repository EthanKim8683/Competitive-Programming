#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=3e5;
I a_arr[N];
Lli sufs[N];
I inds[N-1];
I ress[N];
B cmp(I a,I b){
  return sufs[a+1]>sufs[b+1];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  sufs[n-1]=a_arr[n-1];
  for(I i=n-2;i>=0;i--)sufs[i]=sufs[i+1]+a_arr[i];
  iota(inds,inds+n-1,0);
  sort(inds,inds+n-1,cmp);
  ress[0]=1;
  for(I i=0;i<k-1;i++)ress[inds[i]+1]++;
  for(I i=0;i+1<n;i++)ress[i+1]+=ress[i];
  Lli res=0;
  for(I i=0;i<n;i++)res+=(Lli)ress[i]*a_arr[i];
  printf("%lli\n",res);
}