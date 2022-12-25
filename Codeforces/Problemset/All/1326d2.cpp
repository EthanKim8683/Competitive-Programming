#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=1e6;
const I MIN=-1e9;
I pres[2*N+1];
S kmp(S s){
  I j=0;
  for(I i=1;i<s.size();i++){
    while(j>0&&s[i]!=s[j])j=pres[j-1];
    if(s[i]==s[j])j++;
    pres[i]=j;
  }
  return s.substr(0,j);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    I n=s.size();
    I i=0;
    for(;i<n-i-1;i++)if(s[i]!=s[n-i-1])break;
    S frw=s.substr(i,n-2*i),bkw=frw;
    reverse(bkw.begin(),bkw.end());
    S j=kmp(bkw+"."+frw);
    S k=kmp(frw+"."+bkw);
    S res=j.size()>k.size()?j:k;
    res=s.substr(0,i)+res;
    res=res+s.substr(n-i,i);
    printf("%s\n",res.c_str());
  }
}