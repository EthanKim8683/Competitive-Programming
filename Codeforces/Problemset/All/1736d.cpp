#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using C=char;
vector<pair<I,I>>rngs;
vector<I>rots,subs;
I cnts[2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    S s;cin>>s;
    I par=0;
    for(auto c:s)par+=c-'0';
    if(par%2){printf("-1\n");continue;}
    rngs.clear();
    I l=0;
    for(I i=1;i<2*n;i++)if(s[i]!=s[l])rngs.push_back({l,i}),l=i;
    rngs.push_back({l,2*n});
    rots.clear();
    I pre=0,add=1;
    for(auto[l,r]:rngs){
      if(s[l]=='0')pre^=(r-l)%2;
      if(s[l]=='1'){
        if((r-l)%2){
          if(add){
            if(pre)rots.push_back(l-1),pre=0;
            else rots.push_back(r),pre=1;
          }else{
            if(pre)rots.push_back(l),pre=0;
            else rots.push_back(r-1),pre=1;
          }
          add^=1;
        }else{
          if(add){
            if(pre)rots.push_back(l-1),rots.push_back(r-1),pre=1;
          }else{
            if(pre)rots.push_back(l),rots.push_back(r),pre=1;
          }
        }
      }
    }
    for(I i=rots.size()-1;i>0;i--)swap(s[rots[i]],s[rots[i-1]]);
    fill_n(cnts,2,0);
    subs.clear();
    for(I i=0;i<2*n;i++)if(cnts[s[i]-'0']^=1)subs.push_back(i);
    printf("%i",rots.size());
    for(auto i:rots)printf(" %i",i+1);
    printf("\n");
    for(auto i:subs)printf("%i ",i+1);
    printf("\n");
  }
}
/*
if the number of 1's or 0's are odd, there is no solution since it would be
impossible to distribute them evenly

otherwise, there will always be an even number of odd-length groups of 1's,
which we can make even by adding a 1 to a half and removing a 1 from the
other, meaning a solution is always possible
*/