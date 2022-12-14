#include<bits/stdc++.h>
using namespace std;
using I=int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I r,g,b;cin>>r>>g>>b;
  I res=0;
  for(I i=0;i<3;i++)for(I j=0;j<3;j++)for(I k=0;k<3;k++){
    I x=r-i,y=g-j,z=b-k;
    if(x<0)continue;
    if(y<0)continue;
    if(z<0)continue;
    if(abs(x-y)%3)continue;
    if(abs(x-z)%3)continue;
    if(abs(y-z)%3)continue;
    I low=min(min(x,y),z),cur=low;
    cur+=abs(x-low)/3;
    cur+=abs(y-low)/3;
    cur+=abs(z-low)/3;
    res=max(res,cur);
  }
  printf("%i\n",res);
}