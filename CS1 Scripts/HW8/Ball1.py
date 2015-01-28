import math
class Ball(object):
    def __init__(self,ID,ball_x, ball_y, ball_dx, ball_dy, ball_r, ball_color):
        self.ID= ID
        self.x = ball_x
        self.y = ball_y
        self.r = ball_r
        self.dx = ball_dx
        self.dy = ball_dy
        self.color = ball_color
        
    def __lt__(self,other):
        return self.r < other.r
    def position(self):
        x = self.x
        y = self.y
        tup1 = (x, y);
        return tup1
    def move(self):
        self.x += self.dx
        self.y += self.dy
    def bounding_box(self):
        tup2 = (self.x-self.r, self.y-self.r, self.x+self.r, self.y+self.r) ;
        return tup2
    def get_color(self):
        color = self.color
        return color
    def some_inside(self,maxx,maxy):
        a = True
        b = False
        if 0 < self.x + self.r and self.x - self.r < maxx and \
                0 < self.y + self.r and self.y - self.r < maxy:
            return a
        else:
            return b
    def check_and_reverse(self, maxx, maxy):
        if self.x + self.r > maxx:
            self.dx = self.dx * -1
        if self.x - self.r < 0:
            self.dx = self.dx * -1
            
        if self.y + self.r > maxy:
            self.dy = self.dy * -1
        if self.y - self.r < 0:
            self.dy = self.dy * -1
    def intersect(self,other,newID):
        
                
        min_dist = float(self.r) + float(other.r)
        
        diff_x = math.fabs(self.x - other.x)
        diff_y = math.fabs(self.y - other.y)
        distance = math.hypot(diff_x,diff_y)
        
        if distance <= min_dist:
            #Self is larger
            #Need to make Self Larger
            if self > other:
                
                aSelf = math.pi * (self.r)**2
                aOther = math.pi*(other.r)**2
                self.r = math.sqrt((aSelf + aOther)/math.pi)
                
                self.x = (aSelf*self.x+aOther*other.x)/ (aSelf +aOther)
                self.y = (aSelf*self.y + aOther*other.y)/(aSelf+aOther)
                self.dx = (aSelf*self.dx + aOther*other.dx)/(aSelf+aOther)
                self.dy = (aSelf*self.dy+ aOther*other.dy)/(aSelf+aOther)
                aSelf = aSelf+aOther
                self.color=self.color
                self.ID = newID
                
                return other
            
            else:
                aSelf = math.pi * (self.r)**2
                aOther = math.pi*(other.r)**2
                other.r = math.sqrt((aSelf + aOther)/math.pi)
                other.x = (aSelf*self.x +aOther*other.x)/ (aSelf +aOther)
                other.y = (aSelf*self.y + aOther*other.y)/(aSelf+aOther)
                other.dx = (aSelf*self.dx + aOther*other.dx)/(aSelf+aOther)
                other.dy = (aSelf*self.dy+ aOther*other.dy)/(aSelf+aOther)
                aOther = aSelf+aOther
                other.color=other.color
                other.ID = newID

                return self
        return -1

        

    def morph(self):
        aSelf = math.pi * (self.r)**2
        aOther = math.pi*(other.r)**2
        self.x = (aSelf*self.x +aOther*other.x)/ (aSelf +aOther)
        self.y = (aSelf*self.y + aOther*other.y)/(aSelf+aOther)
        self.dx = (aSelf*self.dx + aOther*other.dx)/(aSelf+aOther)
        self.dy = (aSelf*self.dy+ aOther*other.dy)/(aSelf+aOther)
        aSelf = aSelf+aOther
        self.color=self.color        
        return self
            
        
        
        
        
        
        
    
    
        
        
    
    