#controlFlow.py
x = int(input("please input an integer:"))

if x < 0:
    x = 0
    print( 'Negative changed to zero')
elif x == 0:
    print( 'Zero')
elif x == 1:
    print( 'Single')
else:
    print( 'More')

mylist = ['a','goober','zxv']

for listmember in mylist:
    print( listmember)

#now use ranges just like we'd do a normal 'for' in C/C++
print('mylist = range(12)')
mylist = range(12)

for listmember in mylist:
    print( listmember)

#shorthand:
print( "shorthand..")
for listmember in range(3):
    print( listmember)

#negative progression..
print( "start negative progression")
# range([start],stop [,step])
for currofst in range(0,-10,-1):
    print( currofst)
    
#while statement.. with continue
#only print odd numbers, but iterate over all numbers between
#from 0 to 19
myint = 0
while myint < 20:
    if((myint%2) == 0):
        myint += 1
        continue
    print( myint)
    myint += 1

# break on 12
myint = 0
while myint < 20:
    if(myint==12):
        break
    print( myint)
    myint += 1
