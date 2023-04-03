#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100000;
const I SQTN=317;
I ress[N];
vector<pair<I,I>>adds[N],rems[N];
I curs[SQTN+1][SQTN+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  I siz=sqrt(n),rem=(n+siz-1)/siz;
  for(I i=0;i<k;i++){
    I a,l,d;cin>>a>>l>>d,a--;
    if(l<=siz){
      for(I j=0;j<l;j++)ress[a+j*d]++;
    }else{
      I b=a+(l-1)*d;
      adds[a].push_back({d,a%d});
      rems[b].push_back({d,a%d});
    }
  }
  for(I i=0;i<n;i++){
    for(auto[j,k]:adds[i])curs[j][k]++;
    for(I j=1;j<=rem;j++)ress[i]+=curs[j][i%j];
    for(auto[j,k]:rems[i])curs[j][k]--;
  }
  for(I i=0;i<n;i++)printf("%i ",ress[i]);
}