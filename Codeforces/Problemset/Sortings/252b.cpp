#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
I a_arr[N];
vector<I>cpss;
constexpr I enc(pair<I,I>a){
  auto[x,y]=a;
  return x+y*3;
}
constexpr I enc(tuple<I,I,I>a){
  auto[x,y,z]=a;
  return x+y*3+z*9;
}
constexpr I enc(tuple<I,I,I,I>a){
  auto[x,y,z,w]=a;
  return x+y*3+z*9+w*27;
}
constexpr pair<I,I>enc(tuple<I,I,I>a,pair<I,I>b){
  return{enc(a),enc(b)};
}
constexpr pair<I,I>enc(tuple<I,I,I,I>a,pair<I,I>b){
  return{enc(a),enc(b)};
}
pair<I,I>sols3[10]{
  enc({0,0,1},{1,2}),
  enc({1,0,0},{0,1}),
  enc({0,1,1},{0,1}),
  enc({1,1,0},{1,2}),
  enc({0,1,2},{0,1}),
  enc({0,2,1},{0,1}),
  enc({1,0,2},{1,2}),
  enc({1,2,0},{1,2}),
  enc({2,0,1},{0,1}),
  enc({2,1,0},{0,1})
};
pair<I,I>sols4[2]{
  enc({0,1,0,1},{0,1}),
  enc({1,0,1,0},{0,1})
};
void ini(I i,I siz){
  cpss.clear();
  for(I j=i;j<i+siz;j++)cpss.push_back(a_arr[j]);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
}
I cps(I i){
  return lower_bound(cpss.begin(),cpss.end(),a_arr[i])-cpss.begin();
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i+3<=n;i++){
    ini(i,3);
    I u=enc({cps(i),cps(i+1),cps(i+2)});
    for(auto[v,sol]:sols3)if(u==v)printf("%i %i\n",i+sol/3+1,i+sol%3+1),exit(0);
  }
  for(I i=0;i+4<=n;i++){
    ini(i,4);
    I u=enc({cps(i),cps(i+1),cps(i+2),cps(i+3)});
    for(auto[v,sol]:sols4)if(u==v)printf("%i %i\n",i+sol/3+1,i+sol%3+1),exit(0);
  }
  printf("-1");
}