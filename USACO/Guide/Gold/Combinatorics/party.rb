r=1
gets.to_i.times{|i|r=(-~i*r-1+i%2*2)%0x3b9aca07}
p r