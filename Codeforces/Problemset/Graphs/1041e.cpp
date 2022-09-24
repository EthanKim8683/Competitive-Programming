#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

using I=int;

const I N=1000;

I vals[N];
set<I>unvs;
vector<I>pats;
vector<pair<I,I>>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n-1;i++){
    I a,b;cin>>a>>b,a--,b--;
    if(a==b){printf("NO\n");return 0;}
    if(a>b)swap(a,b);
    if(b!=n-1){printf("NO\n");return 0;}
    vals[i]=a;
  }
  for(I i=0;i<n;i++)unvs.insert(i);
  sort(vals,vals+n-1);
  for(I i=0;i<n-1;i++){
    auto it=unvs.upper_bound(vals[i]);
    if(it==unvs.begin()){printf("NO\n");return 0;}
    pats.push_back(*--it);
    unvs.erase(it);
  }
  pats.push_back(n-1);
  for(I i=0;i<n-1;i++)ress.push_back({pats[i],pats[i+1]});
  printf("YES\n");
  for(auto[i,j]:ress)printf("%i %i\n",i+1,j+1);
  return 0;
}