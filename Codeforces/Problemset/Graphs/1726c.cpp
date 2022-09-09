#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using S=string;

const I N=1e5;

I pars[2*N];
vector<I>stks;
I cnt;

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
  cnt--;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    cnt=2*n;
    fill_n(pars,2*n,-1);
    for(I i=0;i<2*n;i++){
      if(s[i]=='(')stks.push_back(i);
      else uni(stks.back(),i),stks.pop_back();
    }
    for(I i=0;i+1<2*n;i++)
      if(s[i]==')'&&s[i+1]=='(')uni(i,i+1);
    printf("%i\n",cnt);
  }
  return 0;
}