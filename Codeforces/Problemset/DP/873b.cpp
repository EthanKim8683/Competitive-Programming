#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=100000;

map<I,I>mins;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  I cnt0=0,cnt1=0;
  mins[0]=0;
  I res=0;
  for(I i=0;i<n;i++){
    cnt0+=s[i]=='0';
    cnt1+=s[i]=='1';
    I dif=cnt1-cnt0;
    if(!mins.count(dif)){mins[dif]=i+1;continue;}
    res=max(res,i+1-mins[dif]);
  }
  printf("%i\n",res);
}