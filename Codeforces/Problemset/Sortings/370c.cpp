#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5000;
const I M=100;
I c_arr[N];
I cnts[M+1];
vector<pair<I,I>>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>c_arr[i];
  sort(c_arr,c_arr+n);
  for(I i=0;i<n;i++)cnts[c_arr[i]]++;
  I rot=*max_element(cnts,cnts+m+1),res=0;
  for(I i=0;i<n;i++){
    I a=c_arr[i],b=c_arr[(i+rot)%n];
    res+=a!=b,ress.push_back({a,b});
  }
  printf("%i\n",res);
  for(auto[a,b]:ress)printf("%i %i\n",a,b);
}