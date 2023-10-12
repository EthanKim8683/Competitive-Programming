#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
const I N=5e6;
I zfns[2*N+1];
I degs[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  S s;cin>>s;
  I n=s.size();
  S t=s+"_";
  reverse(t.begin(),t.end()),t=s+t;
  for(I i=1,l=0,r=0;i<2*n+1;i++){
    if(i<r)zfns[i]=min(r-i,zfns[i-l]);
    while(i+zfns[i]<2*n+1&&t[zfns[i]]==t[i+zfns[i]])zfns[i]++;
    if(i+zfns[i]>r)l=i,r=i+zfns[i];
  }
  degs[0]=1;
  for(I i=1;i<n;i++){
    if(zfns[2*n-i]>=i+1)degs[i]=1;
    I pre=degs[(i+1)/2-1];
    if(pre==0)continue;
    if(zfns[2*n-i]>=(i+1)/2)degs[i]=max(degs[i],pre+1);
  }
  printf("%i\n",accumulate(degs,degs+n,0));
}