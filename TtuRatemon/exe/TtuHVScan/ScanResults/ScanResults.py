from array import array

class ScanResults:
    """This class builds the scan results object"""

    def __init__(self):
         self.xxunits='HV [kV]'
         self.yyunits='Rates [Hz]'
         self.labels      = []
         self.rates       = []
         self.hvvalues    = []
         self.hvcrtvalues = []
         self.xxunits     = ''
         self.yyunits     = ''
         self.maxcols     =  0
         self.pressure    = 0.0
         self.tempUXC     = 0.0
         
    def readinfo(self, infile):

        input = open(infile,'r')
        line = input.readline()[:-1]
        self.labels = line.split()
        hv = self.labels.pop(0)
        
        serialinfo = []
        while 1:
            line = input.readline()[:-1]

            if line == '':
                break
            
            info = line.split()
            self.hvvalues.append( float( info[0] ) )
                        
            for i in range( 1, len(info), 2):
                xx = float( info[i] )
                xxerr = float( info[i+1] )
                serialinfo.append( (xx,xxerr) )
        
        input.close()

        indx = 0
        for col in self.labels:
            colvalues=[]
            for k in range(indx, len(serialinfo), len( self.labels )):
                colvalues.append(serialinfo[k])
            self.rates.append ( colvalues )
            indx+=1
        #print self.rates, len(self.rates)
        self.maxcols = len(self.rates)
    
    def getXArrays(self, xxval, xxvalerr):
        
        for x in self.hvvalues:
            xxval.append( x )
        
        for x in self.hvvalues:
            xxvalerr.append( 0.0 )

    def getXCArrays(self, xxval, xxvalerr):
         
         for x in self.hvcrtvalues:
             xxval.append( x )
        
    def getYArrays(self, yyval, yyvalerr, col):

        for x in self.rates[col]:
            yyval.append( x[0] )
        
        for x in self.rates[col]:
            yyvalerr.append( x[1] )

    def setPandT( self, p, t):
        self.pressure = p
        self.tempUXC = t

    def calculateHV( self, hvapp ):
	#V_eff = V_app*(P_0/P)*(T/T0), where P0=1010 mbar (not 1020), and T0=293.15 K (20 deg C)
	p0 = 1010.0
	temp0 = 293.15
	tempK = self.tempUXC + 273.15
	factor = (p0 / self.pressure ) * ( tempK / temp0)
	veff = hvapp * factor 
        print 'correction applied: ', factor, veff
	return veff

    def applyHVCorrection( self ):
        for x in self.hvvalues:
            hveff = self.calculateHV( x )
            self.hvcrtvalues.append( hveff )

    
