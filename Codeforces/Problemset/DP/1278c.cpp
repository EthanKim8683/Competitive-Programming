#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;
const I MAX=1e9;

I a_arr[2*N];
map<I,I>lfts;
map<I,I>rgts;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<2*n;i++)cin>>a_arr[i];
    I stb=0,blb=0;
    for(I i=0;i<n;i++){
      I a=a_arr[i];
      stb+=a==1;
      blb+=a==2;
    }
    lfts.clear();
    for(I i=0;i<n;i++){
      I a=a_arr[n-1-i];
      I val=stb-blb;
      if(!lfts.count(val))lfts[val]=i;
      stb-=a==1;
      blb-=a==2;
    }
    if(!lfts.count(0))lfts[0]=n;
    for(I i=0;i<n;i++){
      I a=a_arr[n+i];
      stb+=a==1;
      blb+=a==2;
    }
    rgts.clear();
    for(I i=0;i<n;i++){
      I a=a_arr[n+i];
      I val=blb-stb;
      if(!rgts.count(val))rgts[val]=i;
      stb-=a==1;
      blb-=a==2;
    }
    if(!rgts.count(0))rgts[0]=n;
    I res=MAX;
    for(auto[cnt,i]:lfts){
      if(!rgts.count(cnt))continue;
      res=min(res,i+rgts[cnt]);
    }
    printf("%i\n",res);
  }
}