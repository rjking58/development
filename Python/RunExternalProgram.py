import subprocess

print ("trying to stop")
subprocess.call([r"net","start","bthserv"])
print ("post try")
