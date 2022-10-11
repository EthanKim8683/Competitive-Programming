#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;

S s;

I dfs(I l,I r,C c){
  if(r-l<=1)return s[l]!=c;
  I m=(r-l)/2;
  I cnt1=dfs(l+m,r,c+1);
  for(I i=l;i<l+m;i++)cnt1+=s[i]!=c;
  I cnt2=dfs(l,l+m,c+1);
  for(I i=l+m;i<r;i++)cnt2+=s[i]!=c;
  return min(cnt1,cnt2);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    cin>>s;
    printf("%i\n",dfs(0,n,'a'));
  }
}