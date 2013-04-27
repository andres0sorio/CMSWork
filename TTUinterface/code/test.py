import pyspecs.RBCspecs
import pyspecs.TTUspecs
import pyspecs.STLvector

fh = open("hardware-pseudoconfig.txt")
rst = open("rbc-status.txt")
tst = open("ttu-status.txt")

rbcboards = pyspecs.RBCspecs.RBCinfo()
rbcboards.readinfo(fh)
rbcboards.printinfo()

ttuboards = pyspecs.TTUspecs.TTUinfo()
ttuboards.readinfo(fh)
ttuboards.printinfo()

rbcboards.setstatus(rst)
ttuboards.setstatus(tst)

