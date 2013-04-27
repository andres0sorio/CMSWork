from _TTUspecs import *

class TTUinfo:
    """This class collects all of the 3 ttu information"""
    ttuvec=[]
    ttustat=[]
    
    def __init__(self):
        for i in range(0,3):
            board = TTUBoardConfig()
            self.ttuvec.append( board )

    def readinfo(self, infile):
        for i in range(0,3):
            ttuline = infile.readline()
            ttuinfo = ttuline.split()

            self.ttuvec[i].m_runId       = int(ttuinfo[0])
            self.ttuvec[i].m_runType     = int(ttuinfo[1])
            self.ttuvec[i].m_triggerMode = int(ttuinfo[2])
            self.ttuvec[i].Firmware      = int(ttuinfo[3])
            self.ttuvec[i].LengthOfFiber = int(ttuinfo[4])
            self.ttuvec[i].Delay         = int(ttuinfo[5])
            self.ttuvec[i].MaxNumWheels  = int(ttuinfo[6])
            self.ttuvec[i].m_Wheel1Id    = int(ttuinfo[7])
            self.ttuvec[i].m_Wheel2Id    = int(ttuinfo[8])            
            self.ttuvec[i].LogicType     = ttuinfo[9]

            maskline = infile.readline()
            maskinfo = maskline.split()
            for j in range(0,12):
                val  =  int(maskinfo[j])
                self.ttuvec[i].MaskedSectors.append( val )

            forceline = infile.readline()
            forceinfo = forceline.split()
            for j in range(0,12):
                val  = int(maskinfo[j])
                self.ttuvec[i].ForcedSectors.append( val )

    def printinfo(self):
        for i in range(0,3):
            print self.ttuvec[i].Firmware,self.ttuvec[i].MaxNumWheels
            print self.ttuvec[i].LogicType
            print self.ttuvec[i].MaskedSectors
            print self.ttuvec[i].ForcedSectors
            print '------'
    
    def setstatus(self, infile):
        self.ttustat=[]
        statline = infile.readline()
        statinfo = statline.split()

        for i in statinfo:
            self.ttustat.append(i)
