#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=1e5;
const I L=1e6;
S wrds[N];
I pfxs[L+1];
I kmp(S s){
  I n=s.size();
  for(I i=1,j=0;i<n;i++){
    while(j>0&&s[i]!=s[j])j=pfxs[j-1];
    if(s[i]==s[j])j++;
    pfxs[i]=j;
  }
  return pfxs[n-1];
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>wrds[i];
  S res=wrds[0];
  for(I i=1;i<n;i++){
    S wrd=wrds[i];
    I x=res.size(),y=wrd.size();
    res+=wrd.substr(kmp(wrd.substr(0,min(x,y))+"/"+res.substr(max(x-y,0))));
  }
  printf("%s\n",res.c_str());
}