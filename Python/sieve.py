
#sieve of eratosthenes, python style...

SIZE = 100

def main ():
    its_a_prime=[True]
    
    #preset entire array..
    for curri in range(1,SIZE,1):
        its_a_prime.append(True)

    #we preload all even numbers above 3 with 'not prime'
    for curri in range(4,SIZE,2):
        its_a_prime[curri] = False
        
    for curri in range(2,SIZE,1):
        if its_a_prime[curri]:
            for currPrimeMultiple in range((curri+curri),SIZE,curri):
                its_a_prime[currPrimeMultiple] = False
    
    #print results
    isFirst=True
    for curri in range(1,SIZE,1) :
        if its_a_prime[curri]:
            if not isFirst  :
                print(',',end=' ')
            print (curri,end='')
            isFirst=False
        
main()
