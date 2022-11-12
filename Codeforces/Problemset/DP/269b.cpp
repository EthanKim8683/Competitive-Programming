#include<bits/stdc++.h>

using namespace std;

using I=int;
using Lf=long double;

const I N=5000;
const I M=N;

pair<I,Lf>plts[N];
vector<Lf>dp;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++){
    I s;Lf x;cin>>s>>x;
    plts[i]={s,x};
  }
  sort(plts,plts+n);
  for(I i=0;i<n;i++){
    Lf x=plts[i].second;
    auto it=lower_bound(dp.begin(),dp.end(),x);
    if(it==dp.end())dp.push_back(x);
    else *it=x;
  }
  printf("%i\n",n-dp.size());
}