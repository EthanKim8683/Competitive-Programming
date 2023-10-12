#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=1e5;
const Lli MAX=1e18;
vector<I>inds[26];
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
  I q;cin>>q;
  while(q--){
    cin>>n;
    S s;cin>>s;
    S t;cin>>t;
    fill_n(fens,n+1,0);
    for(I i=0;i<26;i++)inds[i].clear();
    for(I i=n-1;i>=0;i--)inds[s[i]-'a'].push_back(i);
    Lli cst=0,res=MAX;
    for(I i=0;i<n;i++){
      I c=t[i]-'a',low=n+1;
      for(I j=0;j<c;j++)if(inds[j].size()){
        I k=inds[j].back();
        low=min(low,k+qry(n)-qry(k));
      }
      if(low!=n+1)res=min(res,cst+max(low-i,0));
      if(!inds[c].size())break;
      I k=inds[c].back();inds[c].pop_back();
      cst+=max(k+qry(n)-qry(k)-i,0),upd(k+1,1);
    }
    printf("%lli\n",res==MAX?-1:res);
  }
}