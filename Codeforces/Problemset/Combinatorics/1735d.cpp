#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e3;
const I K=20;
I c_arr[N][K];
map<Lli,I>vals;
I cnts[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)for(I j=0;j<k;j++)cin>>c_arr[i][j];
  for(I i=0;i<n;i++){
    Lli val=0;
    for(I j=0;j<k;j++)val=val*3+c_arr[i][j];
    vals[val]=i;
  }
  Lli res=0;
  for(I i=0;i<n;i++)for(I j=i+1;j<n;j++){
    Lli val=0;
    for(I l=0;l<k;l++){
      I a=c_arr[i][l],b=c_arr[j][l];
      if(a==b)val=val*3+a;
      else val=val*3+3-a-b;
    }
    if(!vals.count(val))continue;
    I k=vals[val];
    if(k<=j)continue;
    res+=cnts[i]++;
    res+=cnts[j]++;
    res+=cnts[k]++;
  }
  printf("%lli\n",res);
}