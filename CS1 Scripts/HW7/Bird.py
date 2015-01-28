import math
class Bird(object):
     def __init__(self, name, bird_x, bird_y, bird_r, bird_dx, bird_dy):
          self.n = name
          self.x = float(bird_x)
          self.y = float(bird_y)
          self.r = bird_r
          self.dx = float(bird_dx)
          self.dy = float(bird_dy)
          self.ismoving = True
          self.speed = math.hypot(self.dx, self.dy)
     
     def move(self):
          self.x += self.dx
          self.y += self.dy
     def collided(self, other):
          min_dist = float(self.r) + float(other.r)
          diff_x = math.fabs(self.x - other.x)
          diff_y = math.fabs(self.y - other.y)
          distance = math.hypot(diff_x,diff_y)
          if distance <= min_dist:
               return True
          else:
               return False
     def speedchange(self):
          self.dx = self.dx/2
          
          
          
            
    
    

        
            
            
