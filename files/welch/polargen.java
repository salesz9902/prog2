import java.util.Random;
import java.io.*;
import java.lang.Math;

public class PolarGen	{

  public final  static int RAND_MAX = 32767;
  private static boolean bExists;
  private double dValue;
  static Random cRandomGenerator = new Random();
  

  public PolarGen() { 			//a konstruktor kifejtése
	bExists = false;
	cRandomGenerator.setSeed(20); 	//random inicializálás
  };
  
  public double PolarGet()	{
    	if (!bExists)
  {
		double u1, u2, v1, v2, w;

		do{
			u1 = cRandomGenerator.nextInt (RAND_MAX) / (RAND_MAX + 1.0); //innentől jön az algoritmus
			u2 = cRandomGenerator.nextInt (RAND_MAX) / (RAND_MAX + 1.0);
			v1 = 2 * u1 - 1;
			v2 = 2 * u2 - 1;
			w = v1 * v1 + v2 * v2;
		    }
		while (w > 1);

		double r = Math.sqrt ((-2 * Math.log (w)) / w);

		dValue = r * v2; 
		bExists = !bExists;

		return r * v1; //idáig tart az algoritmus
	}
	
	else
	{
		bExists = !bExists; //ha van korábbi random érték, akkor azt adja vissza
		return dValue;
	}
  };    
  
  public static void main(String args[])	{
    PolarGen cPolarGen = new PolarGen();
    double  dEredmeny = cPolarGen.PolarGet();
    System.out.println(dEredmeny);
  }
  
}
