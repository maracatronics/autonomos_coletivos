/*
 * *********************************************************
 * Copyright (c) 2009 - 2010, DHBW Mannheim - Tigers Mannheim
 * Project: TIGERS - RCU
 * Date: 06.11.2010
 * Author(s): Lukas
 * *********************************************************
 */
package edu.dhbw.mannheim.tigers.sumatra.model.modules.impls.rcm;

import java.io.Serializable;


/**
 * This class contains all needed attributes for a command.
 * 
 * @author Lukas
 */

public class ActionCommand implements Serializable
{
	// --------------------------------------------------------------------------
	// --- instance variables ---------------------------------------------------
	// --------------------------------------------------------------------------
	private static final long	serialVersionUID	= -68111792087214485L;
	
	/** */
	public double					translateX;
	/** */
	public double					translateY;
	/** */
	public double					wheel1;
	/** */
	public double					wheel2;
	/** */
	public double					wheel3;
	/** */
	public double					rotate;
	/** */
	public double					kick;
	/** */
	public double					chipKick;
	/** */
	public double					kickArm;
	/** */
	private double					chipArm;
	/** */
	public double					dribble;
	/** */
	public double					pass;
	/** */
	public double					disarm;
	
	
	// --------------------------------------------------------------------------
	// --- constructor(s) -------------------------------------------------------
	// --------------------------------------------------------------------------
	/**
	 */
	public ActionCommand()
	{
		fillCommandWithNulls();
	}
	
	
	/**
	 * @param translateY
	 * @param translateX
	 * @param rotate
	 * @param kick
	 * @param chipKick
	 * @param kickArm
	 * @param chipArm
	 * @param dribble
	 * @param pass
	 * @param disarm
	 */
	public ActionCommand(final double translateY, final double translateX, final double rotate, final double kick,
			final double chipKick,
			final double kickArm, final double chipArm, final double dribble, final double pass, final double disarm)
	{
		this.translateY = translateY;
		this.translateX = translateX;
		this.rotate = rotate;
		this.kick = kick;
		this.chipKick = chipKick;
		this.kickArm = kickArm;
		this.chipArm = chipArm;
		this.dribble = dribble;
		this.pass = pass;
		this.disarm = disarm;
	}
	
	
	// --------------------------------------------------------------------------
	// --- methods --------------------------------------------------------------
	// --------------------------------------------------------------------------
	/**
	 */
	private final void fillCommandWithNulls()
	{
		translateY = 0.0;
		translateX = 0.0;
		rotate = 0.0;
		kick = 0.0;
		chipKick = 0.0;
		pass = 0.0;
		kickArm = 0.0;
		dribble = 0.0;
	}
	
	
	// --------------------------------------------------------------------------
	// --- getter/setter --------------------------------------------------------
	// --------------------------------------------------------------------------
	
	
	/**
	 * @param translateX the translateX factor to set
	 */
	public void setTranslateX(final double translateX)
	{
		this.translateX = translateX;
	}
	
	
	public double getWheel1()
	{
		return wheel1;
	}
	
	
	public void setWheel1(final double wheel1)
	{
		this.wheel1 = wheel1;
	}
	
	
	public double getWheel2()
	{
		return wheel2;
	}
	
	
	public void setWheel2(final double wheel2)
	{
		this.wheel2 = wheel2;
	}
	
	
	public double getWheel3()
	{
		return wheel3;
	}
	
	
	public void setWheel3(final double wheel3)
	{
		this.wheel3 = wheel3;
	}
	
	
	/**
	 * @param translateY the translateY factor to set
	 */
	public void setTranslateY(final double translateY)
	{
		this.translateY = translateY;
	}
	
	
	/**
	 * @param rotate the rotate factor to set
	 */
	public void setRotate(final double rotate)
	{
		this.rotate = rotate;
	}
	
	
	/**
	 * @param force the force factor to set
	 */
	public void setKick(final double force)
	{
		kick = force;
	}
	
	
	/**
	 * @param chipKick the chipKick factor to set
	 */
	public void setChipKick(final double chipKick)
	{
		this.chipKick = chipKick;
	}
	
	
	/**
	 * @param pass the pass factor to set
	 */
	public void setPass(final double pass)
	{
		this.pass = pass;
	}
	
	
	/**
	 * @param arm the arm factor to set
	 */
	public void setArm(final double arm)
	{
		kickArm = arm;
	}
	
	
	/**
	 * @param dribble the dribble factor to set
	 */
	public void setDribble(final double dribble)
	{
		this.dribble = dribble;
	}
	
	
	@Override
	public int hashCode()
	{
		final int prime = 31;
		int result = 1;
		long temp;
		temp = Double.doubleToLongBits(kickArm);
		result = (prime * result) + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(chipKick);
		result = (prime * result) + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(dribble);
		result = (prime * result) + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(kick);
		result = (prime * result) + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(pass);
		result = (prime * result) + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(rotate);
		result = (prime * result) + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(translateX);
		result = (prime * result) + (int) (temp ^ (temp >>> 32));
		temp = Double.doubleToLongBits(translateY);
		return (prime * result) + (int) (temp ^ (temp >>> 32));
	}
	
	
	@Override
	public boolean equals(final Object obj)
	{
		if (this == obj)
		{
			return true;
		}
		if (obj == null)
		{
			return false;
		}
		if (getClass() != obj.getClass())
		{
			return false;
		}
		ActionCommand other = (ActionCommand) obj;
		if (Double.doubleToLongBits(kickArm) != Double.doubleToLongBits(other.kickArm))
		{
			return false;
		}
		if (Double.doubleToLongBits(chipKick) != Double.doubleToLongBits(other.chipKick))
		{
			return false;
		}
		if (Double.doubleToLongBits(dribble) != Double.doubleToLongBits(other.dribble))
		{
			return false;
		}
		if (Double.doubleToLongBits(kick) != Double.doubleToLongBits(other.kick))
		{
			return false;
		}
		if (Double.doubleToLongBits(pass) != Double.doubleToLongBits(other.pass))
		{
			return false;
		}
		if (Double.doubleToLongBits(rotate) != Double.doubleToLongBits(other.rotate))
		{
			return false;
		}
		if (Double.doubleToLongBits(translateX) != Double.doubleToLongBits(other.translateX))
		{
			return false;
		}
		if (Double.doubleToLongBits(translateY) != Double.doubleToLongBits(other.translateY))
		{
			return false;
		}
		return true;
	}
	
	
	@Override
	public String toString()
	{
		return "ActionCommand [translateX=" + translateX + ", translateY=" + translateY + ", rotate=" + rotate
				+ ", force=" + kick + ", chipKick=" + chipKick + ", pass=" + pass + ", arm=" + kickArm + ", dribble="
				+ dribble + "]";
	}
	
	
	/**
	 * @return the chipArm
	 */
	public final double getChipArm()
	{
		return chipArm;
	}
	
	
	/**
	 * @param chipArm the chipArm to set
	 */
	public final void setChipArm(final double chipArm)
	{
		this.chipArm = chipArm;
	}
	
	
	/**
	 * @return the translateX
	 */
	public final double getTranslateX()
	{
		return translateX;
	}
	
	
	/**
	 * @return the translateY
	 */
	public final double getTranslateY()
	{
		return translateY;
	}
	
	
	/**
	 * @return the rotate
	 */
	public final double getRotate()
	{
		return rotate;
	}
	
	
	/**
	 * @return the kick
	 */
	public final double getKick()
	{
		return kick;
	}
	
	
	/**
	 * @return the chipKick
	 */
	public final double getChipKick()
	{
		return chipKick;
	}
	
	
	/**
	 * @return the arm
	 */
	public final double getKickArm()
	{
		return kickArm;
	}
	
	
	/**
	 * @return the dribble
	 */
	public final double getDribble()
	{
		return dribble;
	}
	
	
	/**
	 * @return the pass
	 */
	public final double getPass()
	{
		return pass;
	}
	
	
	/**
	 * @return the disarm
	 */
	public final double getDisarm()
	{
		return disarm;
	}
	
	
	/**
	 * @param disarm the disarm to set
	 */
	public final void setDisarm(final double disarm)
	{
		this.disarm = disarm;
	}
}
