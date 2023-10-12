#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
using C=char;
using B=bool;
map<I,I>rems;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    B all=1;
    for(auto c:s)all&=c==s.front();
    if(all){printf("%i\n",n);continue;}
    Lli res=(Lli)n*n;
    rems.clear();
    I x=n-1,y=0;
    for(auto c:s)x-=c==s.front();
    rems[y]=max(rems[y],x);
    for(auto c:s){
      if(c==s.front())x++;
      if(c!=s.front())y++;
      rems[y]=max(rems[y],x);
    }
    for(auto[y,x]:rems)res-=n-1-x;
    C pre=s.front();
    reverse(s.begin(),s.end());
    while(s.back()==pre)s.pop_back(),res-=n-1;
    reverse(s.begin(),s.end());
    rems.clear();
    x=n-1,y=0;
    for(auto c:s)x-=c==s.front();
    rems[y]=max(rems[y],x);
    for(auto c:s){
      if(c==s.front())x++;
      if(c!=s.front())y++;
      rems[y]=max(rems[y],x);
    }
    for(auto[y,x]:rems)res-=n-1-x;
    printf("%lli\n",res);
  }
}
/*
i hate problems like these
*/