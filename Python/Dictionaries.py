
# curly braces '{}' are used to create dictionarys (as opposed to square braces, which are for lists)
myDict = {7 : 'seven',  3 : 'three', 9 : 'nine', 1 : 'one'}

myDict[5] = "five"

for key in myDict :
    print(key,end='')
    print("=" + myDict[key])

#now print it ordered

#get list of keys
keyList = list(myDict.keys())

#sort them.
keyList.sort()

#full Dictionary, now ordered by keys
for key in keyList :
    print(key,end='')
    print("=" + myDict[key])

#testing a dictionary for membership

print(1 in myDict)
print(10 in myDict)

for currKey in range(1,15,1) :
    if currKey in myDict :
        print(currKey,"=", myDict[currKey])
    else :
        print(currKey , " is missing")