from _RBCspecs import *

class RBCinfo:
    """This class collects all of the 30 rbc information"""
    rbcvec =[]
    rbcstat=[]
    
    def __init__(self):
        for i in range(0,30):
            board = RBCBoardConfig()
            self.rbcvec.append( board )

    def readinfo(self, infile):
        for i in range(0,30):
            rbcline = infile.readline()
            rbcinfo = rbcline.split()

            self.rbcvec[i].Firmware      = int(rbcinfo[0])
            self.rbcvec[i].WheelId       = int(rbcinfo[1])
            self.rbcvec[i].Latency       = int(rbcinfo[2])
            self.rbcvec[i].MayorityLevel = int(rbcinfo[3])
            self.rbcvec[i].LogicType     = rbcinfo[4]

            maskline = infile.readline()
            maskinfo = maskline.split()
            for j in range(0,15):
                val  =  int(maskinfo[j])
                self.rbcvec[i].MaskedOrInput.append( val )

            forceline = infile.readline()
            forceinfo = forceline.split()
            for j in range(0,15):
                val  = int(maskinfo[j])
                self.rbcvec[i].ForcedOrInput.append( val )

    def printinfo(self):
        for i in range(0,30):
            print self.rbcvec[i].Firmware,self.rbcvec[i].WheelId
            print self.rbcvec[i].Latency, self.rbcvec[i].MayorityLevel
            print self.rbcvec[i].LogicType
            print self.rbcvec[i].MaskedOrInput
            print self.rbcvec[i].ForcedOrInput
            print '------'
    
    def setstatus(self, infile):
        self.rbcstat=[]
        statline = infile.readline()
        statinfo = statline.split()

        for i in statinfo:
            self.rbcstat.append(i)


        
        
