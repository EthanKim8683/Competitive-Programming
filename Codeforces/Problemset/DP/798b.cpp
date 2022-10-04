#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=50;
const I X=50;
const I MAX=1e9;

S s_arr[N];
S cycs[X];
I csts[X];
I tmps[X];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>s_arr[i];
  S a=s_arr[0];
  I len=a.size();
  for(I i=0;i<len;i++){
    cycs[i]=a;
    a=a.substr(1)+a.at(0);
  }
  for(I i=0;i<n;i++){
    S a=s_arr[i];
    I k=-1;
    fill_n(tmps,len,MAX);
    for(I j=0;j<len;j++)if(a==cycs[j])tmps[j]=0,k=j;
    if(k==-1)printf("-1\n"),exit(0);
    I cur=0;
    for(I j=0;j<len;j++){
      tmps[k]=cur=min(cur,tmps[k]);
      cur=(cur+1)%len;
      k=(k+1+len)%len;
    }
    for(I j=0;j<len;j++)csts[j]+=tmps[j];
  }
  I res=MAX;
  for(I i=0;i<len;i++)res=min(res,csts[i]);
  printf("%i\n",res);
}