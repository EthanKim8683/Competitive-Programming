#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1000;
vector<I>secs[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I k;cin>>k;
    secs[i].resize(k);
    for(I j=0;j<k;j++)cin>>secs[i][j];
    sort(secs[i].begin(),secs[i].end());
  }
  I res=0;
  for(I i=0;i<n;i++){
    for(I j=0;j+1<secs[i].size();j++){
      I l=(i+n-1)%n,r=(i+1)%n,low=secs[i][j],upp=secs[i][j+1];
      res+=upper_bound(secs[l].begin(),secs[l].end(),upp)-lower_bound(secs[l].begin(),secs[l].end(),low)!=upper_bound(secs[r].begin(),secs[r].end(),upp)-lower_bound(secs[r].begin(),secs[r].end(),low);
    }
  }
  printf("%i\n",res);
}