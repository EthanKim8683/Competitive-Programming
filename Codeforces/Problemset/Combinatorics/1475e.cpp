#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1000;
const Lli MOD=1e9+7;
I a_arr[N];
Lli facs[N+1];
Lli mpw(Lli x,Lli y){Lli res=1;for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;return res;}
Lli inv(Lli x){return mpw(x,MOD-2);}
Lli bin(I n,I k){return facs[n]*inv(facs[n-k]*facs[k])%MOD;}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  I t;cin>>t;
  while(t--){
    I n,k;cin>>n>>k;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    I a=a_arr[n-k];
    I low=lower_bound(a_arr,a_arr+n,a)-a_arr,upp=upper_bound(a_arr,a_arr+n,a)-a_arr;
    printf("%lli\n",bin(upp-low,(n-k)-low));
  }
}