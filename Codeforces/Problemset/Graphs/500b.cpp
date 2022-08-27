#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using S=string;

const I N=300;

I p_arr[N];
I pars[N];
vector<I>mems[N];

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  fill_n(pars,n,-1);
  for(I i=0;i<n;i++)cin>>p_arr[i];
  for(I i=0;i<n;i++){
    S s;cin>>s;
    for(I j=0;j<n;j++)
      if(s[j]=='1')uni(i,j);
  }
  for(I i=0;i<n;i++)
    mems[fnd(i)].push_back(-p_arr[i]);
  for(I i=0;i<n;i++)
    sort(mems[i].begin(),mems[i].end());
  for(I i=0;i<n;i++){
    I j=fnd(i);
    printf("%i ",-mems[j].back());
    mems[j].pop_back();
  }
  return 0;
}