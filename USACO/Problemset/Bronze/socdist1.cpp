#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I MIN=-1e9;
const I MAX=1e9;
vector<I>csts1;
vector<I>csts2;
vector<I>lens;
I main(){
#ifndef ETHANKIM8683
  freopen("socdist1.in","r",stdin);
  freopen("socdist1.out","w",stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S stls;cin>>stls;
  I i=0,j=n-1,pre=0,pst=0;
  for(;i<=n-1;i++,pre++)if(stls[i]!='0')break;
  for(;j>=0;j--,pst++)if(stls[j]!='0')break;
  if(pre==n)printf("%i\n",n-1),exit(0);
  csts1.push_back(pre);
  csts1.push_back(pst);
  csts2.push_back(pre/2);
  csts2.push_back(pst/2);
  I len=1,low=MAX;
  for(I k=i+1;k<=j;k++){
    if(stls[k]=='0')len++;
    else{
      csts1.push_back(len/2);
      csts2.push_back(len/3);
      low=min(low,len);
      len=1;
    }
  }
  sort(csts1.begin(),csts1.end(),greater<I>());
  sort(csts2.begin(),csts2.end(),greater<I>());
  I res=MIN;
  if(csts1.size()>=2)res=max(res,csts1[1]);
  if(csts2.size()>=1)res=max(res,csts2[0]);
  res=min(res,low);
  printf("%i\n",res);
}