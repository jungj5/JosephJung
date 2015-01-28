def coordinatesx(x):
    return x
def coordinatesy(y):
    return y

actor0x= int(raw_input("Enter actor 0's x position: "))
print actor0x

actor0y= int(raw_input("Enter actor 0's y position: "))
print actor0y


actor1x= int(raw_input("Enter actor 1's x position: "))
print actor1x

actor1y= int(raw_input("Enter actor 1's y position: "))
print actor1y


actor2x= int(raw_input("Enter actor 2's x position: "))
print actor2x

actor2y= int(raw_input("Enter actor 2's y position: "))
print actor2y


actor3x= int(raw_input("Enter actor 3's x position: "))
print actor3x

actor3y= int(raw_input("Enter actor 3's y position: "))
print actor3y


print "---------------------------------------"

lowercornerx = int(min(actor0x,actor1x,actor2x,actor3x)) - 5.5
lowercornery = int(min(actor0y,actor1y,actor2y,actor3y)) - 5.5
print "The lower corner of the rectangle is", "(",lowercornerx,",",lowercornery,")"



uppercornerx = int(max(actor0x,actor1x,actor2x,actor3x)) + 5.5
uppercornery = int(max(actor0y,actor1y,actor2y,actor3y)) + 5.5
print "The upper corner of the rectangle is", "(",uppercornerx,",",uppercornery,")"

