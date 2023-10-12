#include<bits/stdc++.h>
using namespace std;
using I=int;
const I M=2e5;
I a_arr[M];
I b_arr[M];
I inds[M];
I ress[M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>m;
  for(I i=0;i<m;i++)cin>>a_arr[i];
  for(I i=0;i<m;i++)cin>>b_arr[i];
  sort(a_arr,a_arr+m);
  iota(inds,inds+m,0);
  sort(inds,inds+m,[&](I a,I b){
    return b_arr[a]>b_arr[b];
  });
  for(I i=0;i<m;i++)ress[inds[i]]=a_arr[i];
  for(I i=0;i<m;i++)printf("%i ",ress[i]);
}
/*
since F(x + 1, y) is greater than F(x, y) (between a[i] and a[j] such that
a[i] > a[j], b[k] should go to a[i]) and F(x, y) is greater than F(x, y + 1),
(between b[i] and b[j] such that b[i] > b[j], a[k] should get b[j]) the
smallest b[i] should be greedily assigned to the largest a[j]
*/