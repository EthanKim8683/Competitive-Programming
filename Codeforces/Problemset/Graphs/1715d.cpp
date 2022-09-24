#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

using I=int;

const I N=1e5;

vector<pair<I,I>>adjs1[N];
vector<pair<I,I>>adjs2[N];
I msks[N];
I ress[N];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,q;cin>>n>>q;
  fill_n(msks,n,(1<<30)-1);
  for(I i=0;i<q;i++){
    I a,b,x;cin>>a>>b>>x,a--,b--;
    if(a>b)swap(a,b);
    adjs1[a].push_back({b,x});
    adjs2[b].push_back({a,x});
    msks[a]&=x,msks[b]&=x;
  }
  for(I i=0;i<n;i++){
    for(auto[j,x]:adjs2[i])
      ress[i]|=x&~ress[j];
    for(auto[j,x]:adjs1[i])
      ress[i]|=x&~msks[j];
  }
  for(I i=0;i<n;i++)
    printf("%i ",ress[i]);
  return 0;
}