#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1000;
const I L=31;

vector<pair<I,I>>nods;
B adjs[N][N];

void add(I a,I b,I c,I d){
  adjs[a][c]=adjs[c][a]=1;
  adjs[b][c]=adjs[c][b]=1;
  adjs[a][d]=adjs[d][a]=1;
  adjs[b][d]=adjs[d][b]=1;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I k;cin>>k;
  I a=0,b=0;
  nods.push_back({0,0});
  I n=1;
  for(I i=1;i<L;i++){
    I c=n+1,d=n+2;
    nods.push_back({c,d});
    add(a,b,c,d);
    a=c,b=d,n+=2;
  }
  for(I i=L-2;i>=0;i--){
    auto[a,b]=nods[i];
    for(I j=i+1;j<L;j++){
      I c=n+1;
      add(a,b,c,c);
      a=c,b=c,n+=1;
    }
    nods.push_back({a,b});
  }
  reverse(nods.begin(),nods.end());
  for(I i=1;i<L;i++)nods.pop_back();
  for(I i=0;i<L;i++)if(k>>i&1){
    auto[a,b]=nods[i];
    add(a,b,1,1);
  }
  n++;
  printf("%i\n",n);
  for(I i=0;i<n;i++){
    for(I j=0;j<n;j++)
      printf("%c",adjs[i][j]?'Y':'N');
    printf("\n");
  }
  return 0;
}