//este es un macro de ROOT. 
// Su codigo debe ir encapsulado entre los corchetes { ...... }
// No olvidar que estamos en C++: 
//   - al final de cada linea insertar punto-y-coma
//   - todo comentario empieza con un doble slash //

{
  
  //definamos primero las variables que usaremos
  int i = 0;
  float x = XXXX ; // cambiar aqui por el valor inicial de su funcion
  float dx = XXXXX ; // cambiar aqui por el valor del incremento en x
  float max_X = XXXXX ; //definir aqui cual es el maximo de su funcion
    
  // Crear un objeto de tipo TGraph
 
  TGraph mygraph;  
  
  // hacemos el loop aqui adicionando en cada iteracion un punto de la funcion
  // en la grafica

  while ( x < max_X ) {
    // esta es nuestra funcion y = f(x)
    
    float fx = XXXXX; //escribir aqui su funcion
    mygraph.SetPoint(i,x,fx);
    i=i+1;
    x=x+dx;
  
  } 
  
  // Dibujar nuestra grafica (la opcion instruye a ROOT lo siguiente
  // A: dibujar ejes
  // C: unir los puntos con una linea continua
  // P: dibujar los puntos
  
  //si quieren cambiarle el color a la linea - quitar comentario:

  //mygraph.SetLineColor(2);

  mygraph.Draw("ACP");
  
}
