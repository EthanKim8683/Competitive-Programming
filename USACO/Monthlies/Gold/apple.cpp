#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

using I=int;
using B=bool;
struct Cow{I t,x,n;};
struct App{I t,x,n;};

vector<Cow>cows;
vector<App>apps;
I res=0;

B cmp1(Cow a,Cow b){return a.t<b.t;}
B cmp2(App a,App b){return a.t<b.t;}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I qi,ti,xi,ni;cin>>qi>>ti>>xi>>ni;
    if(qi==1)cows.push_back({ti,xi,ni});
    if(qi==2)apps.push_back({ti,xi,ni});
  }
  sort(cows.begin(),cows.end(),cmp1);
  sort(apps.begin(),apps.end(),cmp2);
  for(auto[ti,xi,ni]:cows){
    
  }
  return 0;
}