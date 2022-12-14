#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=250000;
Lli facs[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;Lli m;cin>>n>>m;
  facs[0]=1;for(I i=1;i<=n;i++)facs[i]=facs[i-1]*i%m;
  Lli res=facs[n];
  for(I i=1;i<n;i++){
    if(i+2<=n){
      Lli cur=1;
      (cur*=facs[i])%=m;
      (cur*=n-i+1)%=m;
      (cur*=facs[n-i-2])%=m;
      (cur*=n-i)%=m;
      (cur*=n-i-1)%=m;
      (cur*=n-i-2+1)%=m;
      (res+=cur)%=m;
    }
    if(i+1<=n){
      Lli cur=1;
      (cur*=facs[i])%=m;
      (cur*=n-i+1)%=m;
      (cur*=facs[n-i-1])%=m;
      (cur*=n-i)%=m;
      (cur*=2)%=m;
      (res+=cur)%=m;
    }
  }
  printf("%lli\n",res);
}