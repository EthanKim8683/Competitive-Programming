#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
using C=char;
I cnts[26];
vector<C>upps,lows;
I n,k;
S s;
B chk(I x){
  fill_n(cnts,26,0);
  lows.clear(),upps.clear();
  for(I i=0;i<x;i++)cnts[s[i]-'a']++;
  I rem=n/k,upp=0;
  for(I i=0;i<26;i++){
    I cnt=cnts[i],cur=(k-cnt%k)%k;
    for(I j=0;j<cur;j++)upps.push_back(i+'a');
    rem-=(cnt+k-1)/k;
  }
  if(rem<0)return 0;
  for(I i=0;i<rem*k;i++)upps.push_back('z');
  sort(upps.begin(),upps.end(),greater<I>());
  for(I i=x,j=0;i<n;i++,j++){
    if(upps[j]>s[i])return 1;
    if(upps[j]<s[i])return 0;
  }
  return 1;
}
I fnd(){
  I l=0,r=n-1;
  while(l<r){
    I m=l+(r-l+1)/2;
    chk(m)?l=m:r=m-1;
  }
  return l;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    cin>>n>>k;
    cin>>s;
    if(n%k!=0){printf("-1\n");continue;}
    fill_n(cnts,26,0);
    for(I i=0;i<n;i++)cnts[s[i]-'a']++;
    B vld=1;
    for(I i=0;i<26;i++)vld&=cnts[i]%k==0;
    if(vld){printf("%s\n",s.c_str());continue;}
    I x=fnd();
    fill_n(cnts,26,0);
    upps.clear();
    for(I i=0;i<x;i++)cnts[s[i]-'a']++;
    I rem=n/k;
    for(I i=0;i<26;i++)rem-=(cnts[i]+k-1)/k;
    I res=s[x]-'a'+1;
    for(;res<26;res++){
      I cur=rem-(cnts[res]%k==0);
      if(cur>=0){cnts[res]++;break;}
    }
    for(I i=0;i<26;i++){
      I cur=(k-cnts[i]%k)%k;
      for(I j=0;j<cur;j++)upps.push_back(i+'a');
    }
    rem=n/k;
    for(I i=0;i<26;i++)rem-=(cnts[i]+k-1)/k;
    for(I i=0;i<rem*k;i++)upps.push_back('a');
    sort(upps.begin(),upps.end());
    printf("%s%c",s.substr(0,x).c_str(),res+'a');
    for(auto c:upps)printf("%c",c);
    printf("\n");
  }
}