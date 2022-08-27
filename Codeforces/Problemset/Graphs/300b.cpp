#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;

const I N=48;

I pars[N];
vector<I>ones,twos;
vector<I>cons[N];

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

I siz(I i){
  return -pars[fnd(i)];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(pars,n,-1);
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b;
    uni(a-1,b-1);
  }
  for(I i=0;i<n;i++){
    if(i!=fnd(i))continue;
    I s=siz(i);
    if(s>3){printf("-1\n");return 0;}
    if(s==3)continue;
    if(s==2)twos.push_back(i);
    if(s==1)ones.push_back(i);
  }
  while(twos.size()&&ones.size()){
    uni(twos.back(),ones.back());
    twos.pop_back(),ones.pop_back();
  }
  if(twos.size()){printf("-1\n");return 0;}
  if(ones.size()%3){printf("-1\n");return 0;}
  for(I i=0;i<ones.size();i+=3){
    I r=ones.back();ones.pop_back();
    uni(r,ones.back()),ones.pop_back();
    uni(r,ones.back()),ones.pop_back();
  }
  for(I i=0;i<n;i++)cons[fnd(i)].push_back(i);
  for(I i=0;i<n;i++)if(i==fnd(i)){
    for(auto j:cons[i])printf("%i ",j+1);
    printf("\n");
  }
  return 0;
}