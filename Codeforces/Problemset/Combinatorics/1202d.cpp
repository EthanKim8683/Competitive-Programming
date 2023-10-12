#include<bits/stdc++.h>
using namespace std;
using I=int;
const I SQTN=31623;
vector<I>pres;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    pres.clear();
    while(n>0){
      I l=2,r=SQTN;
      while(l<r){
        I m=l+(r-l+1)/2;
        m*(m-1)/2<=n?l=m:r=m-1;
      }
      pres.push_back(l);
      n-=l*(l-1)/2;
    }
    sort(pres.begin(),pres.end());
    for(I i=pres.size()-1;i>0;i--)pres[i]-=pres[i-1];
    printf("1");
    for(auto len:pres){
      for(I j=0;j<len;j++)printf("3");
      printf("7");
    }
    printf("\n");
  }
}
/*
we can produce a sequence satisfying the following regular expression:
13{2}7(3+7)*

where the sum equals the sum among all prefixes p satisfying 1[37]+7,
n * (n - 1) / 2, where n is the number of 3's in p
*/