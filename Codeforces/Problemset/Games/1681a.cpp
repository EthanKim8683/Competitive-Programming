#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=50;
const I M=50;
I a_arr[N];
I b_arr[M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    I m;cin>>m;
    for(I i=0;i<m;i++)cin>>b_arr[i];
    I a=*max_element(a_arr,a_arr+n);
    I b=*max_element(b_arr,b_arr+m);
    if(a>b)printf("Alice\nAlice\n");
    if(b>a)printf("Bob\nBob\n");
    if(a==b)printf("Alice\nBob\n");
  }
}
/*
denote Alice's greatest card A and Bob's greatest card B

if A > B, Alice can always play A on her turn and will always win

if B > A, Bob can always play B on his turn and will always win

if A = B, if Alice goes first, she plays A and Bob loses, but if Bob goes
first, he plays B and Alice loses
*/