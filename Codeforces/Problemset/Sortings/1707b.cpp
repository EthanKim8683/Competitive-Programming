#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
I a_arr[N];
vector<I>curs[2];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I w=0,t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    curs[w].clear();
    for(I i=0;i<n;i++)curs[w].push_back(a_arr[i]);
    for(I i=0;i<n-1;i++,w=!w){
      sort(curs[w].begin(),curs[w].end());
      reverse(curs[w].begin(),curs[w].end());
      if(curs[w][1]==0)break;
      while(curs[w].size()>2&&curs[w].back()==0)curs[w].pop_back();
      if(curs[w].size()<n-i)curs[w].push_back(0);
      curs[!w].clear();
      for(I j=0;j+1<curs[w].size();j++)curs[!w].push_back(curs[w][j]-curs[w][j+1]);
    }
    printf("%i\n",curs[w][0]);
  }
}