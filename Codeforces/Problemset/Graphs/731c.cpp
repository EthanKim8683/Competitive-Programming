#include<iostream>
#include<cstdio>
#include<algorithm>
#include<unordered_map>

using namespace std;

using I=int;

const I N=200000;
const I K=200000;

I c_arr[N];
I pars[N];
unordered_map<I,I>cols[N];
I chgs[N];

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
  I n,m,k;cin>>n>>m>>k;
  fill_n(pars,n,-1);
  for(I i=0;i<n;i++){I c;cin>>c,c_arr[i]=c-1;}
  for(I i=0;i<m;i++){I l,r;cin>>l>>r,uni(l-1,r-1);}
  for(I i=0;i<n;i++)cols[fnd(i)][c_arr[i]]++;
  for(I i=0;i<n;i++){
    if(i!=fnd(i))continue;
    I chg=-1,cur;
    for(auto[col,cnt]:cols[i])
      if(chg==-1||cnt>cur)chg=col,cur=cnt;
    chgs[i]=chg;
  }
  I res=0;
  for(I i=0;i<n;i++)res+=c_arr[i]!=chgs[fnd(i)];
  printf("%i\n",res);
  return 0;
}