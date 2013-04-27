import DBObject_wrapper

#.......... read table data from file ............

fh = open("hardwareconfig-Run0001.txt")

tturows=[]
rbcrows=[]

while 1:
    ttuline = fh.readline()
    if not ttuline:
        break
    pass

    ttuinfo = ttuline.split()
    
    if len(ttuinfo) == 13:
        
        ttutable = DBObject_wrapper.TTUBoardConfig(int(ttuinfo[0]),int(ttuinfo[1]),int(ttuinfo[2]),int(ttuinfo[3]))
        ttutable.Firmware      = int(ttuinfo[4])
        ttutable.LengthOfFiber = int(ttuinfo[5])
        ttutable.MaxNumWheels  = int(ttuinfo[6])
        ttutable.Delay         = int(ttuinfo[7])
        ttutable.Wheel1        = int(ttuinfo[8])
        ttutable.Wheel2        = int(ttuinfo[9])
        ttutable.LogicType     = ttuinfo[10]
        ttutable.MaskedSector  = int(ttuinfo[11])
        ttutable.ForcedSector  = int(ttuinfo[12])
        
        maxboard = 6 * ttutable.MaxNumWheels
        
        for i in range(0,maxboard):
            rbcline = fh.readline()
            rbcinfo = rbcline.split()

            if len(rbcinfo) == 8:

                rbctable = DBObject_wrapper.RBCBoardConfig(int(rbcinfo[0]))
                rbctable.Firmware      = int(rbcinfo[1])
                rbctable.WheelId       = int(rbcinfo[2])
                rbctable.Latency       = int(rbcinfo[3])
                rbctable.MayorityLevel = int(rbcinfo[4])
                rbctable.LogicType     = rbcinfo[5]
                rbctable.MaskedOrInput = int(rbcinfo[6])
                rbctable.ForcedOrInput = int(rbcinfo[7])

                ttutable.addfkey(int(rbcinfo[0]))

                rbcrows.append(rbctable)

        tturows.append(ttutable)

#........... write info to table ............

print len(tturows), len(rbcrows)


    
