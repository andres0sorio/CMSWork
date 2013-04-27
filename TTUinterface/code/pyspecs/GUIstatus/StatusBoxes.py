from Tkinter import *

class Boxes:
    """This class defines the very basic unit"""
    sectors=''
    status=0
    x1=0
    x2=0
    y1=0
    y2=0
    statuscode=['green','yellow','red']
    color='white'
        
    def __init__(self, xx):
        self.x1 = int(xx[0])
        self.x2 = int(xx[2])
        self.y1 = int(xx[1])
        self.y2 = int(xx[3])
        
    def setstatus(self, status):
        self.status = status
        self.color  = self.statuscode[self.status - 1]

    def setsectors(self,sectors):
        self.sectors = sectors

    def drawbox(self, canvas):
        canvas.create_rectangle(self.x1, self.y1, self.x2, self.y2, fill=self.color)
        
class StatusBoxes:
    """This class sets a GUI for the status of each RBC board in TTU"""
    outfileps=''
    outfilepng=''
    maxrbc=6
    coordinates=[]
    boxes=[]
    wheel=''
    
    def __init__(self, ttu, wheel):
        self.wheel = wheel
        self.outfileps  = 'ttu'+ ttu + '_W' + wheel + '_status.ps'
        self.outfilepng = 'ttu'+ ttu + '_W' + wheel + '_status.png'
        print 'creating: ' + self.outfilepng + '</br>'
        xx = self.readcoordinates('coordinates.txt')
        for i in range(0,self.maxrbc):
            box = Boxes( xx[i] )
            self.boxes.append( box )

    def readcoordinates(self, filename):
        infile = open(filename)
        allcoord=[]
        for i in range(0,self.maxrbc):
            coordline   = infile.readline()
            coordinates = coordline.split()
            xx=[ coordinates[0],coordinates[1],coordinates[2], coordinates[3] ]
            allcoord.append(xx)
        return allcoord
    
    def setstatus(self, pos, stat):
        self.boxes[pos].setstatus(stat)

    def setsectors(self,pos, sectors):
        self.boxes[pos].setsectors(sectors)

    def printstatus(self):
        print 'Status for wheel: ' + self.wheel + ': </br>'
        print '<table border=0>'
        print '<tr>'
        for i in range(0,self.maxrbc):
            print '<td class="topics">'
            print self.boxes[i].sectors, '</td>'
            print '<td>'
            print self.boxes[i].status , '</td></tr>'
        print '</table>'
            
    def drawboxes(self,canvas):
        for i in range(0,self.maxrbc):
            self.boxes[i].drawbox(canvas)
            
