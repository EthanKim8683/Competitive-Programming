n := File standardInput readLine asNumber;
a := 0;
b := 1;
for(i,1,n,
  c := a+b;
  a := b;
  b := c;
);
b print;