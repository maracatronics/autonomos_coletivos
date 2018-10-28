/*
 * *********************************************************
 * Copyright (c) 2009 - 2013, Tigers DHBW Mannheim
 * Project: TIGERS - GrSimAdapter
 * Date: 17.07.2012
 * Author(s): Peter Birkenkampf, TilmanS
 * *********************************************************
 */
package edu.dhbw.mannheim.tigers.sumatra.model.modules.impls.botmanager.bots.grsim;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.GregorianCalendar;

import jssc.SerialPort;

import org.apache.log4j.Logger;

import edu.dhbw.mannheim.tigers.sumatra.Sumatra;
import edu.dhbw.mannheim.tigers.sumatra.model.data.GrSimCommands;
import edu.dhbw.mannheim.tigers.sumatra.model.data.GrSimPacket;


/**
 * Creates the Protobuf commands that are to be sent to grSim
 * 
 * @author Peter Birkenkampf, TilmanS
 */
public class GrSimConnection
{
	// --------------------------------------------------------------
	// --- instance-variables ---------------------------------------
	// --------------------------------------------------------------
	
	private static final Logger	log	= Logger.getLogger(GrSimConnection.class.getName());
	private DatagramSocket			ds;
	private String						ip;
	private int							port, id;
	private float						timeStamp, wheel1, wheel2, wheel3, wheel4, kickspeedx, kickspeedz, velx, vely, velz;
	private boolean					spinner, wheelSpeed, teamYellow;
	private int							kickmode;
	private boolean					kickerDisarm;
	private float						spinnerspeed;
	private float						velx_old, vely_old, timer_warm;
	
	
	// --------------------------------------------------------------
	// --- constructor(s) -------------------------------------------
	// --------------------------------------------------------------
	
	/**
	 * @param config
	 */
	public GrSimConnection(final GrSimNetworkCfg config)
	{
		ip = config.getIp();
		port = config.getPort();
		teamYellow = config.isTeamYellow();
		
		timeStamp = 0;
		wheel1 = 0;
		wheel2 = 0;
		wheel3 = 0;
		wheel4 = 0;
		kickspeedx = 0;
		kickspeedz = 0;
		velx = 0;
		vely = 0;
		velz = 0;
		id = 0;
		spinner = false;
		wheelSpeed = false;
		kickmode = 1;
		kickerDisarm = true;
		spinnerspeed = 1400.0f;
		
	}
	
	
	// --------------------------------------------------------------------------
	// --- methods --------------------------------------------------------------
	// --------------------------------------------------------------------------
	
	
	/**
	 */
	public void open()
	{
		try
		{
			ds = new DatagramSocket();
		} catch (SocketException err)
		{
			log.error("Could not open datagram socket for grSimBot", err);
		}
	}
	
	
	/**
	 */
	public void close()
	{
		ds.close();
		ds = null;
	}
	
	
	/**
	 * @param timeStamp
	 */
	public void setTime(final float timeStamp)
	{
		this.timeStamp = timeStamp;
	}
	
	
	/**
	 * @param wheel1
	 */
	public void setWheel1(final float wheel1)
	{
		this.wheel1 = wheel1;
	}
	
	
	/**
	 * @param wheel2
	 */
	public void setWheel2(final float wheel2)
	{
		this.wheel2 = wheel2;
	}
	
	
	/**
	 * @param wheel3
	 */
	public void setWheel3(final float wheel3)
	{
		this.wheel3 = wheel3;
	}
	
	
	/**
	 * @param wheel4
	 */
	public void setWheel4(final float wheel4)
	{
		this.wheel4 = wheel4;
	}
	
	
	/**
	 * @param mode
	 */
	public void setKickmode(final int mode)
	{
		kickmode = mode;
	}
	
	
	/**
	 * @param disarm
	 */
	public void setKickerDisarm(final boolean disarm)
	{
		kickerDisarm = disarm;
	}
	
	
	/**
	 * @param kickspeedx
	 */
	public void setKickspeedX(final float kickspeedx)
	{
		this.kickspeedx = kickspeedx;
	}
	
	
	/**
	 * @param kickspeedz
	 */
	public void setKickspeedZ(final float kickspeedz)
	{
		this.kickspeedz = kickspeedz;
	}
	
	
	/**
	 * @param velx
	 */
	public void setVelX(final float velx)
	{
		this.velx = velx;
	}
	
	
	/**
	 * @param vely
	 */
	public void setVelY(final float vely)
	{
		this.vely = vely;
	}
	
	
	/**
	 * @param velz
	 */
	public void setVelZ(final float velz)
	{
		this.velz = velz;
	}
	
	
	/**
	 * @param id
	 */
	public void setId(final int id)
	{
		this.id = id;
	}
	
	
	/**
	 * @param spinner
	 */
	public void setSpinner(final boolean spinner)
	{
		this.spinner = spinner;
	}
	
	
	/**
	 * @param speed
	 */
	
	public void setSpinnerSpeed(final float speed)
	{
		spinnerspeed = speed;
	}
	
	
	/**
	 * @param wheelSpeed
	 */
	public void setWheelSpeed(final boolean wheelSpeed)
	{
		this.wheelSpeed = wheelSpeed;
	}
	
	
	/**
	 * @param teamYellow
	 */
	public void setTeamYellow(final boolean teamYellow)
	{
		this.teamYellow = teamYellow;
	}
	
	
	/**
	 * @param ip
	 */
	
	public void setIp(final String ip)
	{
		this.ip = ip;
	}
	
	
	/**
	 * @param port
	 */
	public void setPort(final int port)
	{
		this.port = port;
	}
	
	
	@SuppressWarnings("javadoc")
	public byte[] encode(final double input, final int size, final int precision)
	{
		double tempInput = input;
		
		for (int i = 0; i < precision; i++)
		{
			tempInput *= 10;
		}
		
		int output = (int) tempInput;
		
		String strOut = String.format("%0" + size + "d", output);
		
		return strOut.getBytes();
	}
	
	
	/**
	 * Creates the protobuf command and sends it away
	 */
	public void send()
	{
		
		if (ds == null)
		{
			log.error("No open connection to grSim Bot.");
			return;
		}
		GrSimCommands.grSim_Robot_Command command = GrSimCommands.grSim_Robot_Command.newBuilder().setId(id)
				.setWheel2(wheel2).setWheel1(wheel1).setWheel3(wheel3).setWheel4(wheel4).setKickspeedx(kickspeedx)
				.setKickspeedz(kickspeedz).setVeltangent(velx).setVelnormal(vely).setVelangular(velz).setSpinner(spinner)
				.setWheelsspeed(wheelSpeed).setKickmode(kickmode).setDisarmKicker(kickerDisarm)
				.setSpinnerspeed(spinnerspeed).build();
		GrSimCommands.grSim_Commands command2 = GrSimCommands.grSim_Commands.newBuilder().setTimestamp(timeStamp)
				.setIsteamyellow(teamYellow).addRobotCommands(command).build();
		GrSimPacket.grSim_Packet packet = GrSimPacket.grSim_Packet.newBuilder().setCommands(command2).build();
		byte[] buffer2 = packet.toByteArray();
		
		// System.out.println("Commands: ");
		// System.out.println("Id: " + id + "Wheel 1: " + wheel1 + "Wheel 2: " + wheel2 + "Wheel 3: " + wheel3);
		// System.out.println("Whell 4: " + wheel4 + "KickSpeedX: " + kickspeedx + "KickSpeedZ: " + kickspeedz);
		// System.out.println("VelX: " + velx + "VelY: " + vely + "VelZ: " + velz + "Spinner: " + spinner);
		// System.out.println("WheelSpeed: " + wheelSpeed + "KickMode: " + kickmode + "DisarmKicker: " + kickerDisarm);
		// System.out.println("SpinnerSpeed: " + spinnerspeed);
		
		try
		{
			DatagramPacket dp = new DatagramPacket(buffer2, buffer2.length, InetAddress.getByName(ip), port);
			ds.send(dp);
		} catch (IOException e)
		{
			log.error("Could not send package to grSim", e);
		}
		
		
		boolean control = false; // true - novo sistema, false -antigo sistema
		try
		{
			byte pwmM1 = 0, pwmM2 = 0, pwmM3 = 0, dirM1 = 0, dirM2 = 0, dirM3 = 0, chute = 0;
			double norma, angle = 0, coeficienteT, coeficienteR, potencia = 0;
			// TODO Macros globais
			float LIMITE_ROTACAO = 6;
			
			// true - novo sistema, não usar por favor
			if (control)
			{
				double[] test = new double[] { 2, 1, 1, 4, -6, 0, -2, 7, 2 };
				TransformMatrix t = new TransformMatrix(3, 3, test);
				BotTransform.velocityVector = new double[] { velx, vely, velz };
				System.out.println("t:\n");
				t.print();
				System.out.println("\n");
				System.out.println("inverse t:\n");
				t.inverse().print();
				System.out.println("\n");
				System.out.println("t*inverse t:\n");
				t.multiplication(t.inverse()).print();
				
				BotTransform.getAccelerationVector();
				System.out.println("\n");
				System.out.println("a:\n");
				BotTransform.a.print();
				
				BotTransform.getVelocityVector();
				System.out.println("\n");
				System.out.println("m:\n");
				BotTransform.m.print();
				
				System.out.println("\nD:\n");
				BotTransform.D.print();
				System.out.println("\n");
				System.out.println("inverse D:\n");
				BotTransform.D.inverse().print();
				System.out.println("\n");
				System.out.println("D*inverse D:\n");
				BotTransform.D.multiplication(BotTransform.D.inverse()).print();
				
				
			}
			else
			{
				// false - antigo sistema
				
				// maior valor para norma encontrado até agora foi 2.5
				norma = Math.sqrt((Math.pow(velx, 2) + Math.pow(vely, 2)));
				
				if (velx == 0)
				{
					if (vely >= 0)
					{
						angle = Math.PI / 2;
					}
					else
					{
						angle = -Math.PI / 2;
					}
				}
				else
				{
					angle = Math.atan(vely / velx);
					if (velx < 0)
					{
						angle = Math.PI + angle;
					}
				}
				
				switch (id)
				{
					case 1:
						// TRANSLAÇÃO
						// restrinções de norma //TODO
						if (norma > 0)
						{
							norma += 1.3;
						}
						if (norma > 2.5)
						{
							norma = 2.5;
						}
												
						coeficienteT = 40.0; // deixar 44.0 se não restringir o valor da norma
						potencia = coeficienteT * norma;
						pwmM1 = (byte) Math.round(potencia *
								Math.cos(angle + ((7 * Math.PI) / 6)));
						pwmM2 = (byte) Math.round(potencia *
								Math.cos(angle + (Math.PI / 2)));
						pwmM3 = (byte) Math.round(potencia *
								Math.cos(angle + (-Math.PI / 6)));
						
						// ROTAÇÃO
						if (velz > LIMITE_ROTACAO)
						{
							velz = LIMITE_ROTACAO;
						}
						if (velz < -LIMITE_ROTACAO)
						{
							velz = -LIMITE_ROTACAO;
						}
						
						coeficienteR = 5.0; // deixar coeficienteR * velz no máximo 30
						pwmM1 = (byte) (pwmM1 + Math.round((coeficienteR * velz)));
						pwmM2 = (byte) (pwmM2 + Math.round((coeficienteR * velz)));
						pwmM3 = (byte) (pwmM3 + Math.round((coeficienteR * velz)));
						
//						// verificando direção de giro das rodas
						// sentido horário = positivo (dirM = 0) ; sentido anti-horário = negativo (dirM = (byte) 0x80)
						if (pwmM1 < 0)
						{
							dirM1 = (byte) 0x80;
						}
						if (pwmM2 < 0)
						{
							dirM2 = (byte) 0x80;
						}
						if (pwmM3 < 0)
						{
							dirM3 = (byte) 0x80;
						}
						
//						// VALORES ABSOLUTOS
						pwmM1 = (byte) Math.abs(pwmM1);
						pwmM2 = (byte) Math.abs(pwmM2);
						pwmM3 = (byte) Math.abs(pwmM3);
						
						// AJUSTES DE PWM // TODO
//						if (pwmM1 > 0)
//						{
//							//pwmM1 += 5;
//						}
//						if ((dirM1 == 0) && (pwmM1 > 0))
//						{
//							//pwmM1 += 5;
//						}
//						if (pwmM2 > 40)
//						{
//							pwmM2 += 15;
//						}
//						if (pwmM3 > 0)
//						{
//							pwmM3 += 10;
//						}
						
						// LIMITADOR DE PWM
						if (pwmM1 > 127)
						{
							pwmM1 = 127;
						}
						if (pwmM2 > 127)
						{
							pwmM2 = 127;
						}
						if (pwmM3 > 127)
						{
							pwmM3 = 127;
						}
						break;
						
					case 2:
						// TRANSLAÇÃO
						// restrinções de norma //TODO
						if (norma > 0)
						{
							norma += 1.3;
						}
						if (norma > 2.5)
						{
							norma = 2.5;
						}
												
						coeficienteT = 40.0; // deixar 44.0 se não restringir o valor da norma
						potencia = coeficienteT * norma;
						pwmM1 = (byte) Math.round(potencia *
								Math.cos(angle + ((7 * Math.PI) / 6)));
						pwmM2 = (byte) Math.round(potencia *
								Math.cos(angle + (Math.PI / 2)));
						pwmM3 = (byte) Math.round(potencia *
								Math.cos(angle + (-Math.PI / 6)));
						
						// ROTAÇÃO
						if (velz > LIMITE_ROTACAO)
						{
							velz = LIMITE_ROTACAO;
						}
						if (velz < -LIMITE_ROTACAO)
						{
							velz = -LIMITE_ROTACAO;
						}
						
						coeficienteR = 5.0; // deixar coeficienteR * velz no máximo 30
						pwmM1 = (byte) (pwmM1 + Math.round((coeficienteR * velz)));
						pwmM2 = (byte) (pwmM2 + Math.round((coeficienteR * velz)));
						pwmM3 = (byte) (pwmM3 + Math.round((coeficienteR * velz)));
						
//						// verificando direção de giro das rodas
						// sentido horário = positivo (dirM = 0) ; sentido anti-horário = negativo (dirM = (byte) 0x80)
						if (pwmM1 < 0)
						{
							dirM1 = (byte) 0x80;
						}
						if (pwmM2 < 0)
						{
							dirM2 = (byte) 0x80;
						}
						if (pwmM3 < 0)
						{
							dirM3 = (byte) 0x80;
						}
						
//						// VALORES ABSOLUTOS
						pwmM1 = (byte) Math.abs(pwmM1);
						pwmM2 = (byte) Math.abs(pwmM2);
						pwmM3 = (byte) Math.abs(pwmM3);

						
						// AJUSTES DE PWM // TODO
						if (pwmM1 > 0)
						{
							pwmM1 += 36;
						}
//						if ((dirM1 == 0) && (pwmM1 > 0))
//						{
//							pwmM1 += 5;
//						}
						if (pwmM2 > 30)
						{
							pwmM2 += 10;
						}
					//	if ((pwmM2 > 30) && (dirM2 == 0))
					//	{
					//		pwmM2 += 10;
					//		pwmM1 -= 25;
					//	}
						if (pwmM3 > 0)
						{
							pwmM3 += 38;
						}
						
						
						
						// LIMITADOR DE PWM
						if (pwmM1 > 127)
						{
							pwmM1 = 127;
						}
						if (pwmM2 > 127)
						{
							pwmM2 = 127;
						}
						if (pwmM3 > 127)
						{
							pwmM3 = 127;
						}
						
						// Correcao andar direita
						/*if (Math.toDegrees(angle) >= -110 && Math.toDegrees(angle) <= -80) {
							System.out.println("DIREITA KRAI");
							pwmM3 += 80;
							pwmM2 -= 20;
							pwmM1 -= 35;
						}*/
						break;

					case 3:  //Tubarao
						// TRANSLAÇÃO
						// restrinções de norma //TODO
						if (norma > 0)
						{
							norma += 1.3;
						}
						if (norma > 2.5)
						{
							norma = 2.5;
						}
												
						coeficienteT = 40.0; // deixar 44.0 se não restringir o valor da norma
						potencia = coeficienteT * norma;
						pwmM1 = (byte) Math.round(potencia *
								Math.cos(angle + ((7 * Math.PI) / 6)));
						pwmM2 = (byte) Math.round(potencia *
								Math.cos(angle + (Math.PI / 2)));
						pwmM3 = (byte) Math.round(potencia *
								Math.cos(angle + (-Math.PI / 6)));
						
						// ROTAÇÃO
						if (velz > LIMITE_ROTACAO)
						{
							velz = LIMITE_ROTACAO;
						}
						if (velz < -LIMITE_ROTACAO)
						{
							velz = -LIMITE_ROTACAO;
						}
						
						coeficienteR = 5.0; // deixar coeficienteR * velz no máximo 30
						pwmM1 = (byte) (pwmM1 + Math.round((coeficienteR * velz)));
						pwmM2 = (byte) (pwmM2 + Math.round((coeficienteR * velz)));
						pwmM3 = (byte) (pwmM3 + Math.round((coeficienteR * velz)));
						
//						// verificando direção de giro das rodas
						// sentido horário = positivo (dirM = 0) ; sentido anti-horário = negativo (dirM = (byte) 0x80)
						if (pwmM1 < 0)
						{
							dirM1 = (byte) 0x80;
						}
						if (pwmM2 < 0)
						{
							dirM2 = (byte) 0x80;
						}
						if (pwmM3 < 0)
						{
							dirM3 = (byte) 0x80;
						}
						
//						// VALORES ABSOLUTOS
						pwmM1 = (byte) Math.abs(pwmM1);
						pwmM2 = (byte) Math.abs(pwmM2);
						pwmM3 = (byte) Math.abs(pwmM3);
						
						// AJUSTES DE PWM // TODO
						if (pwmM1 > 0)
						{
							pwmM1 += 30;
						}
//						if ((dirM1 == 0) && (pwmM1 > 0))
//						{
//							//pwmM1 += 5;
//						}
						
						if (pwmM2 > 40)
						{
							pwmM2 += 30;
						}
						if (pwmM3 > 0)
						{							
							pwmM3 += 10;
						}
						
						// LIMITADOR DE PWM
						if (pwmM1 > 127 || pwmM1 < 0)
						{
							pwmM1 = 127;
						}
						if (pwmM2 > 127 || pwmM2 < 0)
						{
							pwmM2 = 127;
						}
						if (pwmM3 > 127 || pwmM3 < 0)
						{
							pwmM3 = 127;
						}
						break;

					case 4:   //Troinha
						// TRANSLAÇÃO
						// restrinções de norma //TODO
						if (norma > 0)
						{
							norma += 1.3;
						}
						if (norma > 2.5)
						{
							norma = 2.5;
						}
												
						coeficienteT = 40.0; // deixar 44.0 se não restringir o valor da norma
						potencia = coeficienteT * norma;
						pwmM1 = (byte) Math.round(potencia *
								Math.cos(angle + ((7 * Math.PI) / 6)));
						pwmM2 = (byte) Math.round(potencia *
								Math.cos(angle + (Math.PI / 2)));
						pwmM3 = (byte) Math.round(potencia *
								Math.cos(angle + (-Math.PI / 6)));
						
						// ROTAÇÃO
						if (velz > LIMITE_ROTACAO)
						{
							velz = LIMITE_ROTACAO;
						}
						if (velz < -LIMITE_ROTACAO)
						{
							velz = -LIMITE_ROTACAO;
						}
						
						coeficienteR = 5.0; // deixar coeficienteR * velz no máximo 30
						pwmM1 = (byte) (pwmM1 + Math.round((coeficienteR * velz)));
						pwmM2 = (byte) (pwmM2 + Math.round((coeficienteR * velz)));
						pwmM3 = (byte) (pwmM3 + Math.round((coeficienteR * velz)));
						
//						// verificando direção de giro das rodas
						// sentido horário = positivo (dirM = 0) ; sentido anti-horário = negativo (dirM = (byte) 0x80)
						if (pwmM1 < 0)
						{
							dirM1 = (byte) 0x80;
						}
						if (pwmM2 < 0)
						{
							dirM2 = (byte) 0x80;
						}
						if (pwmM3 < 0)
						{
							dirM3 = (byte) 0x80;
						}
						
//						// VALORES ABSOLUTOS
						pwmM1 = (byte) Math.abs(pwmM1);
						pwmM2 = (byte) Math.abs(pwmM2);
						pwmM3 = (byte) Math.abs(pwmM3);
						
						// AJUSTES DE PWM // TODO
//						if (pwmM1 > 0)
//						{
//							//pwmM1 += 5;
//						}
//						if ((dirM1 == 0) && (pwmM1 > 0))
//						{
//							//pwmM1 += 5;
//						}
						if (pwmM2 > 40)
						{
							pwmM2 += 10;
						}
						if (pwmM3 > 0)
						{
							pwmM3 += 5;
						}
						
						// LIMITADOR DE PWM
						if (pwmM1 > 127)
						{
							pwmM1 = 127;
						}
						if (pwmM2 > 127)
						{
							pwmM2 = 127;
						}
						if (pwmM3 > 127)
						{
							pwmM3 = 127;
						}
						break;

					default:
						pwmM1 = 0;
						dirM1 = 0;
						pwmM2 = 0;
						dirM2 = 0;
						pwmM3 = 0;
						dirM3 = 0;
				}
				int drible=0;
				if (spinner)
				{
					drible = 1;
				}
				else
				{
					drible = 0;
				}
				// kickspeedx = intensidade do chute pra frente
				// kickspeedz = intensidade do chute pra cima [CHIP KICK]
				// kickMode = ?!?!?
				if (kickerDisarm == false)
				{
					// CHUTE
					chute = 1;
				} else
				{
					chute = 0;
				}
				
				System.out.println("ID: " + id);
				System.out.println("Time Amarelo: " + teamYellow);
				System.out.println("Velx: " + velx);
				System.out.println("Vely: " + vely);
				System.out.println("Vel Angular: " + velz);
				System.out.println("Potencia: " + potencia);
				System.out.println("drible: " + spinner);
				System.out.println("dribleBit: " + drible);
//				System.out.println("chute x: " + kickspeedx);
//				System.out.println("chute z: " + kickspeedz);
//				System.out.println("KickMode: " + kickmode);
				System.out.println("KickerDisarm: " + kickerDisarm);
				System.out.println("norma: " + norma);
				System.out.println("angulo: " + Math.toDegrees(angle));
				System.out.println("dirM1: " + dirM1);
				System.out.println("pwmM1: " + pwmM1);
				System.out.println("dirM2: " + dirM2);
				System.out.println("pwmM2: " + pwmM2);
				System.out.println("dirM3: " + dirM3);
				System.out.println("pwmM3: " + pwmM3);
				
				
				byte M1 = (byte) (dirM1 | pwmM1);
				byte M2 = (byte) (dirM2 | pwmM2);
				byte M3 = (byte) (dirM3 | pwmM3);
				
				// X CC D B III
				
				byte primeiro = (byte) (id + (chute << 6) + (drible << 4));
				
				
				byte[] arrayBytes = new byte[6];
				
				//GAMBIARRA - transmissor não pode enviar zero
				if (M1 == 0) {
					M1 = 1;
				}
				if (M2 == 0) {
					M2 = 1;
				}
				if (M3 == 0) {
					M3 = 1;
				}
				//***
				
				arrayBytes[0] = (byte) 0xff; // starter byte
				arrayBytes[1] = primeiro;
				arrayBytes[2] = M1;
				arrayBytes[3] = M2;
				arrayBytes[4] = M3;
				arrayBytes[5] = (byte) 0x01; // lixo
				
//				System.out.println("pacote: " + javax.xml.bind.DatatypeConverter.printHexBinary(arrayBytes));
				System.out.println();
				Sumatra.serialPort.purgePort(SerialPort.PURGE_RXCLEAR); // PURGE_RXCLEAR: input buffer
				Sumatra.serialPort.purgePort(SerialPort.PURGE_TXCLEAR);
				Sumatra.serialPort.writeBytes(arrayBytes);
				
				Thread.sleep(10);
				//log.debug("teste");
			}
		} catch (Exception e)
		{
			GregorianCalendar gc = new GregorianCalendar();
			log.debug(gc.getTime().toString() + "\n" + e.getMessage());
		}
	}
	
	
	@Override
	public String toString()
	{
		String s = "";
		s += "time: " + timeStamp + "\t";
		s += "ip: " + ip + "\t";
		s += "port: " + port + "\n";
		s += "team: ";
		if (teamYellow)
		{
			s += "Yellow";
		} else
		{
			s += "Blue";
		}
		s += "\tBotId " + id + "\n";
		if (wheelSpeed)
		{
			s += "wheel1: " + wheel1 + "\t";
			s += "wheel2: " + wheel2 + "\t";
			s += "wheel3: " + wheel3 + "\t";
			s += "wheel4: " + wheel4 + "\n";
		} else
		{
			s += "velX: " + velx + "\t";
			s += "velY: " + vely + "\t";
			s += "velZ: " + velz + "\n";
		}
		s += "kickerX: " + kickspeedx + "\t";
		s += "kickerZ: " + kickspeedz + "\t";
		s += "Spinner ";
		if (spinner)
		{
			s += "on";
		} else
		{
			s += "off";
		}
		return s;
	}
	
}
