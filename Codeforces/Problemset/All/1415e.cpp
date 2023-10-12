#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=5e5;
I a_arr[N];
vector<I>upps,lows;
multiset<Lli,greater<Lli>>bucs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(a>=0)upps.push_back(a);
    if(a<0)lows.push_back(a);
  }
  sort(upps.begin(),upps.end());
  Lli acc=0,sum=0;
  for(I i=0;i<upps.size();i++)acc+=(Lli)i*upps[i],sum+=upps[i];
  Lli res=acc;
  bucs.insert(sum);
  sort(lows.begin(),lows.end(),greater<I>());
  for(auto i:lows){
    auto it=bucs.begin();
    Lli sum=*it;
    if(sum<0&&bucs.size()<k+1){
      bucs.insert(i);
    }else{
      bucs.erase(it);
      res+=sum;
      bucs.insert(sum+i);
    }
  }
  printf("%lli\n",res);
}