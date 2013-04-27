import cx_Oracle
import DBObject_wrapper

connection = cx_Oracle.connect("CMS_RPC_COMMISSIONING", "rpc2009xcms", "devdb10")

#.......... read table data from file ............

fh = open("hardwareconfig-Run0001.txt")

tturows=[]
rbcrows=[]
tablename=['TTUBoardConfig','RBCBoardConfig']

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

cursor = connection.cursor()

for row in tturows:
    command = 'insert into ' + tablename[0] + ' values ( '
    command += str(row.PKey) + ', '
    command += str(row.runId) + ', '
    command += str(row.runType) + ', '
    command += str(row.triggerMode) + ', '
    command += str(row.Firmware) + ', '
    command += str(row.LengthOfFiber) + ', '
    command += str(row.MaxNumWheels) + ', '
    command += str(row.Delay) + ', '
    command += str(row.Wheel1) + ', '
    command += str(row.Wheel2) + ', '
    command += '\'' + str(row.LogicType) + '\', '
    command += str(row.MaskedSector) + ', '
    command += str(row.ForcedSector)
    command += ' )'
    print command
    cursor.execute(command)
    
for row in rbcrows:
    command = 'insert into ' + tablename[1] + ' values ( '
    command += str(row.PKey) + ', '
    command += str(row.Firmware) + ', '
    command += str(row.WheelId) + ', '
    command += str(row.MayorityLevel) + ', '
    command += str(row.Latency) + ', '
    command += '\'' + str(row.LogicType) + '\', '
    command += str(row.MaskedOrInput) + ', '
    command += str(row.ForcedOrInput)
    command += ' )'
    print command
    cursor.execute(command)

cursor.execute('commit')

print 'createTable> done.'
cursor.close()
