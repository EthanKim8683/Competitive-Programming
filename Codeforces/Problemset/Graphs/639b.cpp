#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;

const I N=100000;

vector<I>adjs[N];
vector<pair<I,I>>ress;
I deps[N];
I dia=0;

I dfs(I a,I p=-1){
  I res=0;
  for(auto b:adjs[a]){
    if(b==p)continue;
    I len=dfs(b,a);
    dia=max(dia,res+len);
    res=max(res,len);
  }
  return res+1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,d,h;cin>>n>>d>>h;
  I a=h,b=d-h;
  I j=0;
  for(I i=0;i<a;i++,j++){
    adjs[j].push_back(j+1);
    adjs[j+1].push_back(j);
    ress.push_back({j,j+1});
    deps[j]=a-i,deps[j+1]=a-i-1;
  }
  if(b){
    adjs[0].push_back(j+1);
    adjs[j+1].push_back(0);
    ress.push_back({0,j+1});
    j++;
  }
  for(I i=1;i<b;i++,j++){
    adjs[j].push_back(j+1);
    adjs[j+1].push_back(j);
    ress.push_back({j,j+1});
    deps[j]=b-i,deps[j+1]=b-i-1;
  }
  deps[0]=min(a,b);
  I r=0;
  while(r<n&&deps[r]==0)r++;
  while(j+1<n){
    if(r==n){printf("-1\n");return 0;}
    adjs[r].push_back(j+1);
    adjs[j+1].push_back(r);
    ress.push_back({r,j+1});
    j++;
  }
  I hgt=dfs(0)-1;
  if(hgt!=h||dia!=d)printf("-1\n");
  else for(auto[i,j]:ress)
    printf("%i %i\n",i+1,j+1);
  return 0;
}