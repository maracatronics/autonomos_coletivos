/*
 * *********************************************************
 * Copyright (c) 2009 - 2013, DHBW Mannheim - Tigers Mannheim
 * Project: TIGERS - Sumatra
 * Date: 18.06.2013
 * Author(s): AndreR
 * 
 * *********************************************************
 */
package edu.dhbw.mannheim.tigers.sumatra.test.junit.model.modules.impls.botmanager.commands;

import java.util.zip.CRC32;

import org.junit.Test;


/**
 * Test CRC calculation.
 * 
 * @author AndreR
 * 
 */
public class TigerBootloaderDataTest
{
	// --------------------------------------------------------------------------
	// --- variables and constants ----------------------------------------------
	// --------------------------------------------------------------------------
	
	
	// --------------------------------------------------------------------------
	// --- constructors ---------------------------------------------------------
	// --------------------------------------------------------------------------
	
	
	// --------------------------------------------------------------------------
	// --- methods --------------------------------------------------------------
	// --------------------------------------------------------------------------
	/** */
	@Test
	public void testCrc()
	{
		byte payload[] = new byte[64];
		for (int i = 0; i < payload.length; i++)
		{
			payload[i] = 0;
		}
		
		CRC32 crc32 = new CRC32();
		
		crc32.reset();
		crc32.update(payload);
		long crc = crc32.getValue();
		
		System.out.println(Long.toHexString(crc));
	}
	
	
	// --------------------------------------------------------------------------
	// --- getter/setter --------------------------------------------------------
	// --------------------------------------------------------------------------
}
