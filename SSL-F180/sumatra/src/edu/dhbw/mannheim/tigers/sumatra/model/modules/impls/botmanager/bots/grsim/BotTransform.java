package edu.dhbw.mannheim.tigers.sumatra.model.modules.impls.botmanager.bots.grsim;


public class BotTransform
{
	static double				M								= 1;																	// massa
	// double R; //raio
	// double I; //momento de inercia, I = alfa*M*R²
	static double				alfa							= 0.25;																// alfa =
																																			// I/(M*R²),
																																			// com 0
																																			// <= alfa <= 1
	static double[]			teta							= new double[] {
																	gradToRad(60),
																	gradToRad(180),
																	gradToRad(300) };												// angulo das
																																			// rodas
	static double[][]			forceCouplingMatrix		= new double[][] {
			{ -Math.sin(teta[0]) / M, -Math.sin(teta[1]) / M, -Math.sin(teta[2]) / M },
			{ Math.cos(teta[0]) / M, Math.cos(teta[1]) / M, Math.cos(teta[2]) / M },
			{ 1 / (alfa * M), 1 / (alfa * M), 1 / (alfa * M) } };
	static double[][]			velocityCouplingMatrix	= new double[][] {
																	{ -Math.sin(teta[0]), Math.cos(teta[0]), 1 },
																	{ -Math.sin(teta[1]), Math.cos(teta[1]), 1 },
																	{ -Math.sin(teta[2]), Math.cos(teta[2]), 1 } };
	static TransformMatrix	C								= new TransformMatrix(3, 3, forceCouplingMatrix);
	static TransformMatrix	D								= new TransformMatrix(3, 3, velocityCouplingMatrix);
	static double[]			forceVector					= new double[] { 1, 4, 6 };									// vetor forca
	static double[]			velocityVector				= new double[] { 1, 4, 6 };									// vetor
																																			// velocidade
	static double[]			accelerationVector		= new double[3];													// vetor
																																			// aceleracao
	static double[]			motorsSpeedsVector		= new double[3];													// vetor
																																			// aceleracao
	static TransformMatrix	a;
	static TransformMatrix	m;
	static double				ax;																									// aceleracao
																																			// traslacional
																																			// x
	static double				ay;																									// aceleracao
																																			// traslacional
																																			// y
	static double				Rw;																									// aceleracao
																																			// tangencial,
																																			// w
																																			// = aceleracao
																																			// angular,
																																			// R*f = I*w
	static double				v1;
	static double				v2;
	static double				v3;
	
	
	public static double gradToRad(final double g)
	{
		return (g * Math.PI) / 180;
	}
	
	
	static void getAccelerationVector()
	{
		TransformMatrix f = new TransformMatrix(3, 1, forceVector);
		a = C.multiplication(f);
		ax = accelerationVector[0] = a.getData()[0][0];
		ay = accelerationVector[1] = a.getData()[1][0];
		Rw = accelerationVector[2] = a.getData()[2][0];
	}
	
	
	static void getVelocityVector()
	{
		TransformMatrix v = new TransformMatrix(3, 1, velocityVector);
		m = D.multiplication(v);
		v1 = motorsSpeedsVector[0] = m.getData()[0][0];
		v2 = motorsSpeedsVector[1] = m.getData()[1][0];
		v3 = motorsSpeedsVector[2] = m.getData()[2][0];
	}
	
	
	public static void main(final String[] args)
	{
		// TODO Auto-generated method stub
		
		double[] test = new double[] { 2, 1, 1, 4, -6, 0, -2, 7, 2 };
		TransformMatrix t = new TransformMatrix(3, 3, test);
		System.out.println("t:\n");
		t.print();
		System.out.println("\n");
		System.out.println("inverse t:\n");
		t.inverse().print();
		System.out.println("\n");
		System.out.println("t*inverse t:\n");
		t.multiplication(t.inverse()).print();
		
		getAccelerationVector();
		System.out.println("\n");
		System.out.println("a:\n");
		a.print();
		
		getVelocityVector();
		System.out.println("\n");
		System.out.println("m:\n");
		m.print();
		
		System.out.println("\nD:\n");
		D.print();
		System.out.println("\n");
		System.out.println("inverse D:\n");
		D.inverse().print();
		System.out.println("\n");
		System.out.println("D*inverse D:\n");
		D.multiplication(D.inverse()).print();
	}
	
}
