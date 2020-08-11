import threading
import time

class myThread (threading.Thread):
   def __init__(self, pThreadID, pName, pCounter):
        threading.Thread.__init__(self,name=pName)
        self.threadID = pThreadID
        self.name = pName
        self.counter = pCounter
   def run(self):
        print( "Starting " + self.name)
        # Get lock to synchronize threads
        #threadLock.acquire()  #essentially single threads the threads.. kinda defeats the purpose!
        print_time(self.name, self.counter, 3,self.threadID)
        # Free lock to release next thread
        #threadLock.release()

def print_time(pThreadName, pDelay, pCounter,pThreadID):
    counter = pCounter
    while counter:
        time.sleep(pDelay)
        print( "%s[%s](%s): %s" % (pThreadName,pThreadID,counter, time.ctime(time.time())))
        counter -= 1

#threadLock = threading.Lock()
threads = []

# Create new threads
thread1 = myThread(1, "Thread-1", 1)
thread2 = myThread(2, "Thread-2", 2)
thread3 = myThread(3, "Thread-3", 3)
thread4 = myThread(4, "Thread-4", 4)

# Start new Threads
thread1.start()
thread2.start()
thread3.start()
thread4.start()

# Add threads to thread list
threads.append(thread1)
threads.append(thread2)
threads.append(thread3)
threads.append(thread4)

# Wait for all threads to complete
for t in threads:
    t.join()
print("Exiting Main Thread")