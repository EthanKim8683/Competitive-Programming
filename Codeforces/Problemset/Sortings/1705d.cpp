#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
vector<pair<I,I>>segs1,segs2;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I n;cin>>n;
    S s;cin>>s;
    S t;cin>>t;
    if(s.front()!=t.front()||s.back()!=t.back()){printf("-1\n");continue;}
    segs1.clear(),segs2.clear();
    I l=0;
    for(I r=0;r<n;r++){
      if(s[r]!=s[l]){
        if(s[l]=='1')segs1.push_back({l,r-1});
        l=r;
      }
    }
    if(s[l]=='1')segs1.push_back({l,n-1});
    l=0;
    for(I r=0;r<n;r++){
      if(t[r]!=t[l]){
        if(t[l]=='1')segs2.push_back({l,r-1});
        l=r;
      }
    }
    if(t[l]=='1')segs2.push_back({l,n-1});
    if(segs1.size()!=segs2.size()){printf("-1\n");continue;}
    I m=segs1.size();
    Lli res=0;
    for(I i=0;i<m;i++){
      auto[l1,r1]=segs1[i];auto[l2,r2]=segs2[i];
      res+=abs(l1-l2)+abs(r1-r2);
    }
    printf("%lli\n",res);
  }
}