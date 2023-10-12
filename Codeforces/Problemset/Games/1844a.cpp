#include<bits/stdc++.h>
using namespace std;
using I=int;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I a,b;cin>>a>>b;
    printf("%i\n",a+b);
  }
}
/*
if n = a + b, if the first player chooses to remove exactly a stones, the
second player can remove b stones, leaving 0 stones remaining

and if the first player chooses to remove exactly b stones, the second player
can remove a stones, also leaving 0 stones remaining
*/