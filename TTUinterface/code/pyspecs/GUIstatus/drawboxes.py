from Tkinter import *
from StatusBoxes import *
import sys,os

def drawboxes( inputfile , targetdir):

    canw = 186
    canh = 60

    master = Tk()
    w = Canvas(master, width=canw, height=canh)
    w.pack()

    statusin = open(inputfile)
    statusinfo = statusin.readline()
    status = statusinfo.split()

    ttulist   = ['1','3','2','1','3']
    wheellist = ['-2','-1','0','+1','+2']

    for k in range(0,5):
        
        wheel = StatusBoxes(ttulist[k],wheellist[k])
        istat = int(status[(k*6)+0])
        wheel.setstatus(0,istat)
        wheel.setsectors(0,'12-1')
        istat = int(status[(k*6)+1])
        wheel.setstatus(1,istat)
        wheel.setsectors(1,'2-3')
        istat = int(status[(k*6)+2])
        wheel.setstatus(2,istat)
        wheel.setsectors(2,'4-5')
        istat = int(status[(k*6)+3])
        wheel.setstatus(3,istat)
        wheel.setsectors(3,'6-7')
        istat = int(status[(k*6)+4])
        wheel.setstatus(4,istat)
        wheel.setsectors(4,'8-9')
        istat = int(status[(k*6)+5])
        wheel.setstatus(5,istat)
        wheel.setsectors(5,'10-11')
        wheel.printstatus()
        wheel.drawboxes(w)
        outfile = targetdir + wheel.outfileps
        w.postscript(file=outfile, width=canw, height=canh)
        outfilepng = targetdir + wheel.outfilepng
        command = 'convert ' + outfile + ' ' + outfilepng
        os.system(command)
        items = w.find_all()
        for it in items:
            w.delete(it)
        os.system('rm ' + outfile )
       
    return 1

