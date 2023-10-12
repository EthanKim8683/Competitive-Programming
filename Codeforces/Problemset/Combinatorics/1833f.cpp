#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2e5;
const Lli MOD=1e9+7;
I a_arr[N];
Lli ps[N+1];
map<I,I>cnts1;
vector<pair<I,I>>cnts2;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    cnts1.clear();
    for(I i=0;i<n;i++)cnts1[a_arr[i]]++;
    cnts2.assign(cnts1.begin(),cnts1.end());
    I k=cnts2.size();
    ps[0]=1;
    for(I i=0;i<k;i++)ps[i+1]=ps[i]*cnts2[i].second%MOD;
    Lli res=0;
    for(I i=0;i+m<=k;i++)if(cnts2[i+m-1].first-cnts2[i].first==m-1)(res+=ps[i+m]*inv(ps[i]))%=MOD;
    printf("%lli\n",res);
  }
}
/*
since there are m distinct dancers, and the difference between the minimum and
maximum dancer is m - 1 (less than m, but allows for m unique dancers), a
magnificent dance is a dance containing dancers with levels i, i + 1, i + 2,
..., i + m - 1
*/