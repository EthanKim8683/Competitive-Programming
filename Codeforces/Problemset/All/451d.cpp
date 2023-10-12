#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
using Lli=long long int;
const I N=1e5;
vector<I>lens;
I pres[2][2];
Lli cons[N+1][2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=1;i<=N;i++){
    cons[i][0]=cons[i-1][0]+i/2;
    cons[i][1]=cons[i-1][1]+i-i/2;
  }
  S s;cin>>s;
  C pre=s[0];I len=1;
  for(I i=1;i<s.size();i++){
    if(s[i]!=pre)lens.push_back(len),len=0;
    len++,pre=s[i];
  }
  lens.push_back(len);
  Lli eve=0,odd=0;I acc=0;
  for(I i=0;i<lens.size();i++){
    I len=lens[i];
    eve+=(Lli)pres[acc&1][i&1]*(len/2);
    odd+=(Lli)pres[acc&1][i&1]*(len-len/2);
    odd+=(Lli)pres[~acc&1][i&1]*(len/2);
    eve+=(Lli)pres[~acc&1][i&1]*(len-len/2);
    eve+=cons[len][0],odd+=cons[len][1];
    acc+=len;
    pres[acc&1][i&1]+=len/2;
    pres[~acc&1][i&1]+=len-len/2;
  }
  printf("%lli %lli\n",eve,odd);
}