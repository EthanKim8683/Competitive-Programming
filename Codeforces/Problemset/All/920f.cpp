#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=3e5;
const I LOGN=19;
const I FIXN=1<<LOGN;
const I A=1e6;
I a_arr[N];
I cnts[A+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=1;i<=A;i++)for(I j=i;j<=A;j+=i)cnts[j]++;
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  while(m--){
    I t,l,r;cin>>t>>l>>r,l--,r--;
    if(t==1){

    }
    if(t==2){

    }
  }
}