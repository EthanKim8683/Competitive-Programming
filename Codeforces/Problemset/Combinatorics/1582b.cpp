#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lli=long long int;

const I N=60;

I a_arr[N];
Lli pows[N+1];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  pows[0]=1;
  for(I i=1;i<=N;i++)pows[i]=pows[i-1]*2;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I cnt0=0,cnt1=0;
    for(I i=0;i<n;i++){
      cnt0+=a_arr[i]==0;
      cnt1+=a_arr[i]==1;
    }
    printf("%lli\n",pows[cnt0]*cnt1);
  }
}