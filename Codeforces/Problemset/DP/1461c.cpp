#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lf=long double;

const I N=1e5;

I a_arr[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I cnt=n;
    for(I i=n-1;i>=0;i--){
      if(a_arr[i]-1!=i)break;
      cnt--;
    }
    Lf res=!!cnt;
    for(I i=0;i<m;i++){
      I r;Lf p;cin>>r>>p;
      if(r>=cnt)res*=(1-p);
    }
    printf("%Lf\n",1-res);
  }
}