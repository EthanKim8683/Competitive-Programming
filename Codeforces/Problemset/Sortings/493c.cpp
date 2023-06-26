#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
const I M=2e5;
const I MIN=-1e9;
I a_arr[N];
I b_arr[M];
vector<I>cpss;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I m;cin>>m;
  for(I i=0;i<m;i++)cin>>b_arr[i];
  sort(a_arr,a_arr+n);
  sort(b_arr,b_arr+m);
  for(I i=0;i<n;i++)cpss.push_back(a_arr[i]);
  for(I i=0;i<m;i++)cpss.push_back(b_arr[i]);
  sort(cpss.begin(),cpss.end());
  cpss.erase(unique(cpss.begin(),cpss.end()),cpss.end());
  I x=0,y=0;
  tuple<I,I,I>res={n*3-m*3,n*3,m*3};
  for(I i=0;i<cpss.size()&&(x<n||y<m);i++){
    while(x<n&&a_arr[x]<=cpss[i])x++;
    while(y<m&&b_arr[y]<=cpss[i])y++;
    I tot1=x*2+(n-x)*3,tot2=y*2+(m-y)*3;
    res=max(res,{tot1-tot2,tot1,tot2});
  }
  auto[dif,a,b]=res;
  printf("%i:%i\n",a,b);
}