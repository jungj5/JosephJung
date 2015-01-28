"""
Joseph Jung
jungj5@rpi.edu
Section 3
Charles Park
parkc9@rpi.edu
Section 2
"""






import Tkinter as tk
from Ball1 import *
from random import *


if __name__ == "__main__":
    
    
    a = raw_input("Enter y to run the graphical output ==>")
    ran = raw_input('Enter y to run the generate random ball position ==>')
    txt = open(raw_input('Enter the name of the data file ==> '))
    read_line = txt.readline()
    read_line = read_line.strip().split()
    
    N,max_iter,maxx,maxy = int(read_line[0]),int(read_line[1]),int(read_line[2]),int(read_line[3])
    ball_list = []
    
    
    if ran == 'y' or ran == 'Y':
        for i in range(int(N)):
            name = i
            radius = randint(5,10)
            x_pos = randint(radius, maxx - radius)
            y_pos = randint(radius, maxy - radius)
            dx = randint(-8,8)
            dy = randint(-8,8)
            color = choice( ["black", "blue", "red", "green", "magenta", "orange", "pink", \
            "purple", "yellow"] )
            
            
            ballin1 = Ball(name, x_pos, y_pos, dx, dy, radius, color)
            ball_list.append(ballin1)
    else:
        i = 0
        for line in txt:
            line1 = line.strip().split()
            x0, y0, radius, dx, dy, color = int(line1[0]), int(line1[1]), int(line1[2]), int(line1[3]), int(line1[4]), line1[5]
            name = i
            ballin2 = Ball(name, x0, y0, dx, dy, radius, color)
            ball_list.append(ballin2)
            i += 1
            
        
            
            
            
        
        
        
    
    if a == 'y' or a == 'Y':
        ##  We will create a root object, which will contain all 
        ##  our user interface elements
        ##
        root = tk.Tk()
        root.title("HW 8")
    
        ##  Create a canvas, like an image, that we can draw objects on.
        ##  This canvas is called chart_1.  By passing root in the call
        ##  before, chart_1 is attached to the root canvas.
        ##
        # canvas width, in pix # canvas height, in pixels
        chart_1 = tk.Canvas(root, width=maxx, height=maxy, background="white")
        chart_1.grid(row=0, column=0)
    
        ##  We are going to repeatedly draw a ball on the canvas, "moving"
        ##  it across the canvas.  The ball is specified by (a) its x and
        ##  y center coordinates (a tuple), (b) its radius, (c) the delta
        ##  x and delta y to move the ball in each time increment, and (d)
        ##  its color.
        ##
       
                

        
    
        ##  Loop until the ball runs off the screen.
        print 
        print "Initial ball configuration"
        for item in ball_list:
            print "Ball: %d: position (%.1f,%.1f), radius %.1f, motion (%.1f,%.1f), color %s"%(item.ID, item.x, item.y, item.r, item.dx, item.dy, item.color)
        iteration = 1
        total_balls=len(ball_list)
        while True and iteration <= max_iter and len(ball_list) > 1:
                
            #  Here is the time in milliseconds between consecutive instances
            #  of drawing the ball.  If this time is too small the ball will
            #  zip across the canvas in a blur.
            wait_time = 60
    
            #  Remove all the previously-drawn balls
            chart_1.delete(tk.ALL)
            
            # Draw an oval on the canvas within the bounding box
            for b in ball_list:
                chart_1.create_oval(b.bounding_box(), fill=b.color)
                
            chart_1.update()      # Actually refresh the drawing on the canvas.
    
            # Pause execution.  This allows the eye to catch up
            chart_1.after(wait_time)
    
            # Move the ball + EVENTS HANDLING
            for b in ball_list:
                b.move()
                b.check_and_reverse(maxx,maxy)
            for b in ball_list:
                
                for b1 in ball_list:
                    if b != b1:
                        oldID_b, oldID_b1 = b.ID, b1.ID
                        s2 = "Ball %d: position (%.1f,%.1f), radius %.1f, motion (%.1f,%.1f), color %s"%(b.ID, b.x, b.y, b.r, b.dx, b.dy, b.color)
                        s3 = "Ball %d: position (%.1f,%.1f), radius %.1f, motion (%.1f,%.1f), color %s"%(b1.ID, b1.x, b1.y, b1.r, b1.dx, b1.dy, b1.color)
                        delete_b = b.intersect(b1,total_balls)
                        if delete_b != -1:
                            print
                            print "Iteration %d collision between ball %d and %d to form ball %d"%(iteration,oldID_b, oldID_b1, total_balls)
                            print s2
                            print s3
                            if b.r > b1.r:
                                print "New ball %d: position (%.1f,%.1f), radius %.1f, motion (%.1f,%.1f), color %s"%(b.ID, b.x, b.y, b.r, b.dx, b.dy, b.color)
                                
                            else:
                                print "New ball %d: position (%.1f,%.1f), radius %.1f, motion (%.1f,%.1f), color %s"%(b1.ID, b1.x, b1.y, b1.r, b1.dx, b1.dy, b1.color)
                                
                                
                                
                            
                            ball_list.remove(delete_b)
                            total_balls += 1
                            print "Num remaining: %d"%(len(ball_list))
                            print 
                            if b.r > b1.r and len(ball_list) == 1:
                                print "Ends at iteration %d with only ball %d remaining"%(iteration + 1, b.ID)
                            if b1.r > b.r and len(ball_list) == 1:
                                print "Ends at iteration %d with only ball %d remaining"%(iteration + 1, b1.ID)                            
            chart_1.update()
          
                            
                            
            iteration += 1
                            
       
        ## This is an infinite loop that allows the window to listen to
        ## "events", which are user inputs.  The only user event here is
        ## closing the window, which ends the program. 
        root.mainloop()
#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    else:
        remove_list = []
        print 
        print "Initial ball configuration"
        for item in ball_list:
            print "Ball: %d: position (%.1f,%.1f), radius %.1f, motion (%.1f,%.1f), color %s"%(item.ID, item.x, item.y, item.r, item.dx, item.dy, item.color)
        iteration = 1
        total_balls=len(ball_list)
        while True and iteration <= max_iter and len(ball_list) > 1:
                
            
    
            # Move the ball + EVENTS HANDLING
            for b in ball_list:
                b.move()
                b.check_and_reverse(maxx,maxy)
            for b in ball_list:
                
                for b1 in ball_list:
                    if b != b1:
                        #Tuple to save old IDs
                        oldID_b, oldID_b1 = b.ID, b1.ID
                        s2 = "Ball %d: position (%.1f,%.1f), radius %.1f, motion (%.1f,%.1f), color %s"%(b.ID, b.x, b.y, b.r, b.dx, b.dy, b.color)
                        s3 = "Ball %d: position (%.1f,%.1f), radius %.1f, motion (%.1f,%.1f), color %s"%(b1.ID, b1.x, b1.y, b1.r, b1.dx, b1.dy, b1.color)
                        delete_b = b.intersect(b1,total_balls)
                        if delete_b != -1:
                            print
                            print "Iteration %d collision between ball %d and %d to form ball %d"%(iteration,oldID_b, oldID_b1, total_balls)
                            print s2
                            print s3
                            if b.r > b1.r:
                                print "New ball %d: position (%.1f,%.1f), radius %.1f, motion (%.1f,%.1f), color %s"%(b.ID, b.x, b.y, b.r, b.dx, b.dy, b.color)
                            else:
                                print "New ball %d: position (%.1f,%.1f), radius %.1f, motion (%.1f,%.1f), color %s"%(b1.ID, b1.x, b1.y, b1.r, b1.dx, b1.dy, b1.color)
                            
                            #Collision Handling
                            remove_list.append(delete_b)
                            for item in remove_list:
                                if item in ball_list:
                                    ball_list.remove(item)
                            total_balls += 1
                            print "Num remaining: %d"%(len(ball_list))
                            print
                            
                            if b.r > b1.r and len(ball_list) == 1:
                                print "Ends at iteration %d with only ball %d remaining"%(iteration + 1, b.ID)
                            if b1.r > b.r and len(ball_list) == 1:
                                print "Ends at iteration %d with only ball %d remaining"%(iteration + 1, b1.ID)
                                
            

          
                            
                            
            iteration += 1

                            
       

                

        
    
            
        
    
    
        

        
    
    
