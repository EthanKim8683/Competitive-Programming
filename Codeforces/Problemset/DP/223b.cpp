#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
const I N=2e5;
const I MIN=-1e9;
const I MAX=1e9;
I dp1[N],dp2[N],dp3[26];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  S t;cin>>t;
  I n=s.size(),m=t.size();
  fill_n(dp3,26,MIN);
  for(I i=0;i<n;i++){
    I j=s[i]-'a';
    I cur=MIN;
    for(I k=0;k<26;k++){
      I l=dp3[k];
      if(l!=MIN&&l+1<m&&t[l+1]==s[i])cur=max(cur,l+1);
    }
    if(s[i]==t[0])cur=max(cur,0);
    dp3[j]=max(dp3[j],cur);
    dp1[i]=dp3[j];
  }
  fill_n(dp3,26,MAX);
  for(I i=n-1;i>=0;i--){
    I j=s[i]-'a';
    I cur=MAX;
    for(I k=0;k<26;k++){
      I l=dp3[k];
      if(l!=MAX&&l-1>=0&&t[l-1]==s[i])cur=min(cur,l-1);
    }
    if(s[i]==t[m-1])cur=min(cur,m-1);
    dp3[j]=min(dp3[j],cur);
    dp2[i]=dp3[j];
  }
  B res=1;
  for(I i=0;i<n;i++)res&=dp1[i]>=dp2[i];
  printf("%s\n",res?"Yes":"No");
}