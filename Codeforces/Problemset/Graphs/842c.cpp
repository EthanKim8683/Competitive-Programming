#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;

const I N=2e5;

vector<I>adjs[N];
I a_arr[N];
I ress[N];
vector<I>facs;
vector<I>cnts;
I a;

I gcd(I a,I b){
  return b?gcd(b,a%b):a;
}

void dfs1(I a,I p=-1,I g=0){
  ress[a]=g;
  for(auto b:adjs[a])if(b!=p)dfs1(b,a,gcd(g,a_arr[b]));
}

void dfs2(I a,I p=-1,I d=0){
  for(I i=0;i<facs.size();i++)cnts[i]+=a_arr[a]%facs[i]==0;
  for(I i=0;i<facs.size();i++)if(cnts[i]>=d)ress[a]=max(ress[a],facs[i]);
  for(auto b:adjs[a])if(b!=p)dfs2(b,a,d+1);
  for(I i=0;i<facs.size();i++)cnts[i]-=a_arr[a]%facs[i]==0;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y),adjs[y].push_back(x);
  }
  dfs1(0);
  a=a_arr[0];
  for(I i=1;i*i<=a;i++){
    if(a%i==0){
      facs.push_back(i);
      if(a/i!=i)facs.push_back(a/i);
    }
  }
  cnts.resize(facs.size());
  dfs2(0);
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
  return 0;
}