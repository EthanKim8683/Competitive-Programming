#include<iostream>
#include<cstdio>

using namespace std;

using I=int;
using B=bool;

const I N=300000;
const I M=300000;

pair<I,I>pais[M];
I cnts[N];
I m;

B chk(I a,I b){
  for(I i=0;i<m;i++){
    auto[c,d]=pais[i];
    if(a!=c&&a!=d&&b!=c&&b!=d)return false;
  }
  return true;
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b,a--,b--;
    cnts[a]++,cnts[b]++;
    pais[i]={a,b};
  }
  for(I i=0;i<n;i++)
    if(cnts[i]==m){printf("YES\n");return 0;}
  auto[a,b]=pais[0];
  if(chk(a,b)){printf("YES\n");return 0;}
  for(I i=1;i<m;i++){
    auto[c,d]=pais[i];
    if(c==a||c==b||d==a||d==b)continue;
    if(chk(a,c)||chk(a,d)||chk(b,c)||chk(b,d)||chk(c,d))printf("YES\n");
    else printf("NO\n");
    return 0;
  }
  printf("NO\n");
  return 0;
}