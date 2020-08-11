mylist = ["123","spam","1.44"]
print( mylist)
print( len(mylist))
print( mylist[1])

#concatenate

mylist = mylist + ["egg",'snip',"burble"]
print( mylist)


mylist.append("weeee")
print( mylist)

#end of list..
mylist.pop(-1)
print( mylist)

mylist.append("werbleweee")

print( mylist)

mylist.sort()
print( mylist)
print( len(mylist))

matrix = [[1,2,3],[4,5,6],[7,8,9]]

print( matrix[0])
print( matrix[0][0])

#row comprehension

matrix_col2=[row[1] for row in matrix]
print( matrix_col2)

#showing expressions..

matrix_col2=[row[1]+100 for row in matrix]
print( matrix_col2)

#filter out odd with an if..
matrix_col2=[row[1] for row in matrix if row[1] % 2 == 0]
print( matrix_col2)
