#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
using Lli=long long int;
const I N=100000;
S cpss="ANOT";
vector<I>inds1[4];
I inds2[4];
I fens[N+1];
I n;
void upd(I i,I val){
  for(;i<=n;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    S a;cin>>a;
    for(auto&c:a)c=lower_bound(cpss.begin(),cpss.end(),c)-cpss.begin();
    n=a.size();
    for(I i=0;i<4;i++)inds1[i].clear();
    for(I i=0;i<n;i++)inds1[a[i]].push_back(i);
    pair<Lli,I>res={0,0};
    I x=0;
    iota(inds2,inds2+4,0);
    do{
      Lli cur=0;
      fill_n(fens,n+1,0);
      for(I i=0,j=0;i<4;i++)for(auto k:inds1[inds2[i]])cur+=max(k+qry(n)-qry(k)-j,0),upd(k+1,1),j++;
      res=max(res,{cur,x}),x++;
    }while(next_permutation(inds2,inds2+4));
    auto[val,y]=res;
    iota(inds2,inds2+4,0);
    I z=0;
    do{
      if(z==y)for(I i=0;i<4;i++)for(auto j:inds1[inds2[i]])printf("%c",cpss[inds2[i]]);
      z++;
    }while(next_permutation(inds2,inds2+4));
    printf("\n");
  }
}