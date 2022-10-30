#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

vector<I>inds[26];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S s;cin>>s;
    S t;cin>>t;
    I n=s.size(),m=t.size();
    for(I i=0;i<26;i++)inds[i].clear();
    for(I i=0;i<n;i++)inds[s[i]-'a'].push_back(i);
    I j=-1,res=1;
    for(I i=0;i<m;i++){
      I c=t[i]-'a';
      auto it=upper_bound(inds[c].begin(),inds[c].end(),j);
      if(it!=inds[c].end()){j=*it;continue;}
      j=-1,res++;
      it=upper_bound(inds[c].begin(),inds[c].end(),j);
      if(it!=inds[c].end()){j=*it;continue;}
      res=-1;break;
    }
    printf("%i\n",res);
  }
}