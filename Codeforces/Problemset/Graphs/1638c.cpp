#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;

vector<I>stks;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    stks.clear();
    for(I i=0;i<n;i++){
      I p;cin>>p;
      I t=p;
      while(stks.size()&&stks.back()>p){
        t=max(t,stks.back());
        stks.pop_back();
      }
      stks.push_back(t);
    }
    printf("%i\n",stks.size());
  }
  return 0;
}