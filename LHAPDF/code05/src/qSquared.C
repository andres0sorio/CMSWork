// $Id: $
// Include files 

void qSquared(double y) 
{
  
  double x = 0.0;
  double xMax = 1.0;
  double dx = 0.1;
  double M = 0.938;
  double Enu = 10.0;
  double EnuMax = 1.0E8;
  
  while ( Enu < EnuMax ) 
  {

    x = 0.0;

    while ( x < xMax ) 
    {
      
      double qSquared = 2.0 * M * Enu * x * y;
      
      std::cout << Enu << " " << x << " " << y << " " << qSquared << std::endl;
      
      x += dx;
      
    }
    
    Enu = Enu * 10.0;
    
  }


}
