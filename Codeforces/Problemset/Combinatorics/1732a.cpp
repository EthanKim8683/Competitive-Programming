#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=20;
const I MAX=1e9;

I a_arr[N];

I gcd(I a,I b){
  return b?gcd(b,a%b):a;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I cur=0;
    for(I i=0;i<n;i++)cur=gcd(cur,a_arr[i]);
    I res=cur==1?0:MAX;
    for(I i=0;i<n;i++)if(gcd(cur,i+1)==1)res=min(res,n-i);
    for(I i=0;i<n;i++)for(I j=0;j<n;j++)if(gcd(cur,gcd(i+1,j+1))==1)res=min(res,n-i+n-j);
    printf("%i\n",res);
  }
}