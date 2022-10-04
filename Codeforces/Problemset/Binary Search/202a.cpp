#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;
using C=char;

const I N=10;

S s;

S fnd(I l,I r){
  if(l>r)return "";
  C a=0;
  for(I i=l;i<=r;i++)
    a=max(a,s[i]);
  I j=l,k=r;
  for(;j<=r;j++)if(s[j]==a)break;
  for(;k>=l;k--)if(s[k]==a)break;
  S b(1,a);
  if(j==k)return b;
  S mid=fnd(j+1,k-1);
  if(b>mid)return b+b;
  return b+mid+b;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>s;
  printf("%s\n",fnd(0,s.size()-1).c_str());
}