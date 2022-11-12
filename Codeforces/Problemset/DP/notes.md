# Practice Problem Notes

## [1285B](https://codeforces.com/contest/1285/problem/B) - Just Eat It!

### Problem:

Find the maximum subarray sum of an array.

<h3 id="kadanes-algorithm">Solution: Kadane's Algorithm</h3>

```cpp
#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=100000;

I a_arr[N];
I n;

// Kadane's Algorithm happens here!
I kad(){
  I res=0;
  for(I i=0;i<n;i++)res=max(res+a_arr[i],0);
  return res;
}

// I/O
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  printf("%i\n",kad());
}
```

The function returns the maximum subarray sum.

## [1526B](https://codeforces.com/problemset/problem/1526/B) - I Hate 1111

### Problem:

Find the largest value impossible to make using any amount of 11 or 111's.

<h3 id="chicken-mcnugget">Solution: Chicken McNugget Theorem</h3>

```cpp
#include<bits/stdc++.h>

using namespace std;

using I=int;

// Chicken McNugget theorem happens here!
I cmn(I n,I m){
  return n*m-n-m;
}

// I/O
I main(){
  cin.tie(0)->sync_with_cstdio(0);
  I n,m;cin>>n>>m;
  printf("%i\n",cmn(n,m));
  return 0;
}
```

The function returns 1099 as the largest impossible sum, allowing all values below to be brute forced in decent time.

## [1743D](https://codeforces.com/contest/1743/problem/D) - Problem with Random Tests

### Problem:

Find the maximum 'or' of two binary substrings given a string.

<h3 id="brute-force">Solution: Brute Force Under Constraint</h3>

```cpp
#include<bits/stdc++.h>

using namespace std;

using I=int;
using S=string;

const I N=1e6;

vector<S>vals;

// Actual solution
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  S s;cin>>s;
  // Remove leading zeroes
  s=s.substr(find(s.begin(),s.end(),'1')-s.begin());
  // Brute force such that first zero is always or'ed into a one
  I j=find(s.begin(),s.end(),'0')-s.begin();
  S res=s;
  for(I i=0;i<=j;i++){
    S a=s,b=S(i,'0')+s.substr(0,n-i);
    for(I i=0;i<n;i++)if(b[i]=='1')a[i]='1';
    // Find the maximum
    res=max(res,a);
  }
  printf("%s\n",res.size()?res.c_str():"0");
}
```

Note that the number of ones before reaching a zero has an expected
value of roughly 1.762. Thus, given such constraints, it would be
reasonable to brute force to an answer.