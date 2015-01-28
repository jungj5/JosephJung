from Pig import *
from Bird import *

def processfile(file, type):
    for line in file:
        objectlist = []
        for item in line.split("|"):
            item = item.strip()
            objectlist.append(item)
        if type == "pig":
            mypig = Pig(objectlist[0], objectlist[1], objectlist[2], objectlist[3])
            pigslist.append(mypig)
        if type == "bird":
            mybird = Bird(objectlist[0], objectlist[1], objectlist[2], objectlist[3], objectlist[4], objectlist[5])
            birdslist.append(mybird)
def checkmove(birdslist):
    for item in birdslist:
        if item.ismoving == False:
            return False
    return True


if __name__ == "__main__":
    
    
    
    bird = open(raw_input("File for birds: "),'r')
    pig = open(raw_input("File for pigs: "))
    time = 0
    birdslist = []
    pigslist = []
    processfile(bird, "bird")
    processfile(pig, "pig")
    print "Number of birds:", len(birdslist)
    for item in birdslist:
        print "%s (%.1f,%.1f)" %(item.n, item.x, item.y)
    
    print 
    
    print "Number of pigs:", len(pigslist)
    for item in pigslist:
        print "%s (%.1f,%.1f)" %(item.n, item.x, item.y)
    count = 0        
    for item in birdslist:
        count += 1
        print "Time %d: %s starts at (%.1f, %.1f)"%(time, item.n, item.x, item.y)
        while item.ismoving and len(pigslist) > 0:
            
            time += 1
            
            #move the bird
            item.move()
            #check if bird collided with pig
            for item1 in pigslist:
                #if it did, print NAME, POS_X, POS_Y of bird and NAME of pig
                if item.collided(item1):
                    print "Time %d: %s at location (%.1f,%.1f) pops %s"%(time, item.n, item.x, item.y, item1.n)
                
            
                    ###remove pig from pigslist
                    pigslist.remove(item1)
                    
            
                    ###use speedchange()
                    #item.speedchange
                    item.dx = item.dx * .5
                    print "Time %d: %s at location (%.1f,%.1f) now has (dx,dy) = (%.1f,%.1f)"%(time,item.n,item.x,item.y,item.dx,item.dy)
                    
                    #check if item.speed<=6
                    if math.hypot(item.dx, item.dy) <= 6:
                        #if above is true, set item.ismoving == False
                        item.ismoving = False
                
                    
                        #give NAME, POSITION, SPEED
                        print "Time %d: %s at location (%.1f,%.1f) with speed %.1f stops"%(time, item.n, item.x, item.y, math.hypot(item.dx, item.dy))
                        break
            
            #check if bird is out of bounds. If it is, set item.ismoving == False
            if item.x + float(item.r) > 1000 or item.x - float(item.r) < 0 or item.y + float(item.r) > 1000 or item.y - float(item.r) < 0:
                item.ismoving = False
                ###output the NAME, POSITION of bird
                print "Time %d: %s at location (%.1f,%.1f) has left the game"%(time, item.n, item.x, item.y)
                break
    if len(pigslist) == 0:
        print "Time %d: All pigs are popped. The birds win!"%(time)
    if len(pigslist) > 0 and count == len(birdslist):
        print "Time %d: No more birds. The pigs win!"%(time)  
    if len(pigslist) > 0:
        print "Remaining pigs:"    
    for item2 in pigslist:
        if len(pigslist) > 0:
            
            print item2.n
            
            
        
        
        
    
    
            
    
        
    
        
    