#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
I p_arr[N];
vector<I>stks;
I lows[N],upps[N];
I inds[N+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>p_arr[i];
  for(I i=0;i<n;i++)inds[p_arr[i]]=i;
  for(I i=0;i<n;i++){
    while(stks.size()&&p_arr[i]>p_arr[stks.back()])stks.pop_back();
    if(stks.size())lows[i]=stks.back()+1;
    stks.push_back(i);
  }
  stks.clear(),fill_n(upps,n,n);
  for(I i=n-1;i>=0;i--){
    while(stks.size()&&p_arr[i]>p_arr[stks.back()])stks.pop_back();
    if(stks.size())upps[i]=stks.back()-1;
    stks.push_back(i);
  }
  I res=0;
  for(I i=0;i<n;i++){
    I l1=lows[i],r1=i-1,l2=i+1,r2=upps[i];
    if(r1-l1>r2-l2)swap(l1,l2),swap(r1,r2);
    for(I j=l1;j<=r1;j++){
      I p=p_arr[i]-p_arr[j];
      if(p<1||p>n)continue;
      res+=l2<=inds[p]&&inds[p]<=r2;
    }
  }
  printf("%i\n",res);
}