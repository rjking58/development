mystr = "Spam"
print (len(mystr))
print (mystr[0])
print (mystr[1])
print (mystr[2])
print (mystr[3])

#show negative indexing..
print (mystr[-1])
print (mystr[-2])
print (mystr[-3])
print (mystr[-4])

#range indexing
#note that the final number is NON-inclusive!
print (mystr[1:3])
print (mystr[1:])
print (mystr[:3])
print (mystr[:])


#concatenate

print (mystr + " in a can")
mystr = mystr + " for a wolf "
print (mystr)

# use of math to repeat strings
mystr = mystr*3
print (mystr)

print (mystr.find("wolf"))
#note that the replace is GLOBAL for all instances of the
#search string
mystr = mystr.replace("wolf","frog")
print (mystr)

#splitting..
myline="aaa,bbb,ccccc,dd"
print (myline.split(","))

print (myline.upper())


print (myline.isalpha())

print (myline[0:3].isalpha())

#formatting
print ("I blow my {0} in your general {1}".format("nose","direction"))

#multi-line
msg = """ aaaaaaaaaa
bbb'''bbbbbbbbb""bbbbbbb'bbb
ccccccccccccccc"""
print (msg)
