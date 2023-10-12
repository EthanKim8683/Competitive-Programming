#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e3;
pair<I,I>pnts[N];
vector<I>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x,y;cin>>x>>y;
    pnts[i]={x,y};
  }
  I f=0;
  for(I i=0;i+1<n;i++){
    auto[x1,y1]=pnts[i];auto[x2,y2]=pnts[i+1];
    f=gcd(f,abs(x1-x2)),f=gcd(f,abs(y1-y2));
  }
  for(I i=n-1;i>=0;i--){
    auto[x1,y1]=pnts[i];auto[x2,y2]=pnts[0];
    pnts[i]={(x1-x2)/f,(y1-y2)/f};
  }
  for(I i=0;i<n;i++){
    auto[x,y]=pnts[i];
    if((x+y)%2==0)ress.push_back(i);
  }
  if(ress.size()==n||ress.size()==0){
    ress.clear();
    for(I i=0;i<n;i++){
      auto[x,y]=pnts[i];
      if((x*2+y)%2==0)ress.push_back(i);
    }
  }
  if(ress.size()==n||ress.size()==0){
    ress.clear();
    for(I i=0;i<n;i++){
      auto[x,y]=pnts[i];
      if((x+y*2)%2==0)ress.push_back(i);
    }
  }
  printf("%i\n",ress.size());
  for(auto i:ress)printf("%i ",i+1);
}
/*
if we choose a displacement vector v, we can form a space using v and some w
orthogonal to v as basis vectors i and j, respectively

for every point a * i + b * j from an origin such that a and b are integers,
we can assign a color based on the checkerboard color of (a, b)

this guarantees that no yellow number will be equal to any blue number because
all white points are a "white" distance away and all black points are a "black"
distance away from the aforementioned origin, meaning black and white points
each form their own group
*/