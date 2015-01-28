def babylonian(s0,x):
    return (s0+x/s0)/2

firstguess = 1
print "Computing the sqrt of 2.0"

s0 = babylonian(firstguess, 2)
print "Estimate 1:", babylonian(firstguess,2.)

s1=babylonian(s0,2.)
print "Estimate 2:", babylonian(s1,2.)

s2=babylonian(s1,2.)
print "Estimate 3:", babylonian(s2,2.)

s3=babylonian(s2,2.)
print "Estimate 4:", babylonian(s3,2.)

s4=babylonian(s3,2.)
print "Estimate 5:", babylonian(s4,2.)

#####################################################

print "Computing the sqrt of 10.0"
guess=1
print "Estimate 1: 1"

d0 = babylonian(guess,10.)
print "Estimate 2:", d0

d1=babylonian(d0,10.)
print "Estimate 3:", babylonian(d0,10.)

d2=babylonian(d1,10.)
print "Estimate 4:", d2

d3=babylonian(d2,10.)
print "Estimate 5:", d3

d4=babylonian(d3,10.)
print "Estimate 6:", d4

d5=babylonian(d4,10.)
print "Estimate 7:", d5




