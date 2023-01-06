#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=5e5;
const I L=60;
const Lli MOD=1e9+7;
Lli a_arr[N];
Lli pows[L+1];
Lli cnts[L];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=L;i++)pows[i]=pows[i-1]*2%MOD;
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    fill_n(cnts,L,0);
    for(I i=0;i<n;i++)for(I j=0;j<L;j++)(cnts[j]+=a_arr[i]>>j&1)%=MOD;
    Lli res=0;
    for(I i=0;i<n;i++){
      Lli sum1=0,sum2=0;
      for(I j=0;j<L;j++){
        if(a_arr[i]>>j&1){
          (sum1+=pows[j]*cnts[j])%=MOD;
          (sum2+=pows[j]*n)%=MOD;
        }else{
          (sum1+=pows[j]*0)%=MOD;
          (sum2+=pows[j]*cnts[j])%=MOD;
        }
      }
      Lli cur=1;
      (cur*=sum1)%=MOD;
      (cur*=sum2)%=MOD;
      (res+=cur)%=MOD;
    }
    printf("%lli\n",res);
  }
}