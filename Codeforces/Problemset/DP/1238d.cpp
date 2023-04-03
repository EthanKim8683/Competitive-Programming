#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using Lli=long long int;
const I N=3e5;
Lli dp[N];
vector<I>inds[2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  for(I i=0;i<n;i++)inds[s[i]-'A'].push_back(i);
  Lli res=0;
  for(I i=0;i<n;i++){
    I k=s[i]=='A',l=1-k;
    auto it1=lower_bound(inds[l].begin(),inds[l].end(),i);
    auto it2=lower_bound(inds[k].begin(),inds[k].end(),i);
    if(it1!=inds[l].begin()&&it2!=inds[k].begin()){
      I x=*prev(it1),y=*prev(it2);
      res+=x<y?x+1:i-1;
    }else if(it1!=inds[l].begin()){
      res+=i;
    }
  }
  printf("%lli\n",res);
}