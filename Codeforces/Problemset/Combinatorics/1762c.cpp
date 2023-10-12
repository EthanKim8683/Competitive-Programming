#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=2e5;
const Lli MOD=998244353;
Lli pows[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  pows[0]=1;
  for(I i=1;i<=N;i++)pows[i]=pows[i-1]*2%MOD;
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    Lli res=0;
    for(I l=0,r=0;r<n;r++){
      if(s[l]!=s[r])l=r;
      (res+=pows[r-l])%=MOD;
    }
    printf("%lli\n",res);
  }
}
/*
up until the final contiguous suffix of an extension, the absolute difference
in the number of 0's and 1's in a prefix must not exceed 1 in anticipation for
a median that is either 0 or 1

however, after the median is not expected to change, the prefix can contain
any amount of the median as long as it does not subceed that of the other
value
*/