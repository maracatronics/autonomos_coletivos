
import java.lang.Math;
import java.util.regex.*;

class Brain extends Thread implements SensorInput{
    public Brain(SendCommand agent, String team, char side, int number, String playMode){
		m_timeOver = false;
		m_agent = agent;
		m_memory = new Memory();
		m_team = team;
		m_side = side;
		m_number = number;
		m_playMode = playMode;
		m_waiting=true;
		start();
    }

    public void run(){
	    moveToMySide();

		while(!m_timeOver){
			if(playOn){
				lookForObjects();

				if(ball!=null){
					if(Math.abs(ball.m_distChange)>=1.0) init=false;
				}

				if(position){
					if(m_side=='l') position=!moveToMyPosition(goalR);
					else position=!moveToMyPosition(goalL);

					if(position==false) init=false;

					positioned=!position;
				}

				if(findBall()){
					decidePosition();

					if(closeToBall()){
						stopPosition();

						passOrKick();
					}
					else goOrLookToBall();
				}
			}
			else{
				moveToMySide();

				stopPosition();

				position=true;

				init=true;
			}
			
	 		try{
	 		    Thread.sleep(2*SoccerParams.simulator_step);
	 		}catch(Exception e){}
	    }

		m_agent.bye();
	}


    //===========================================================================
    // Here are suporting functions for implement logic
	public void decidePosition(){
		if(m_side=='l'){
			if(goalL!=null && m_number>8 && ball.m_distance>=30 && add!=10){
				add=10;

				position=true;
			}else if(m_number>8 && add!=0 && ball.m_distance<=10){
				add=0;

				position=true;
			}
		}
		else{
			if(goalR!=null && m_number>8 && ball.m_distance>=30 && add!=10){
				add=10;

				position=true;
			}else if(m_number>8 && add!=0 && ball.m_distance<=10){
				add=0;

				position=true;
			}
		}
	}

	public void stopPosition(){
		position=false;
		estadoMoveToMyPosition=0;

		add=0;
	}

	public boolean findBall(){
		if(ball==null){
			if(!position){
				m_agent.turn(40);

				m_memory.clearInfo();
			}

			if(!positioned) position=true;

			return false;
		}

		return true;		
	}

	public boolean closeToBall(){
		if(ball.m_distance>1.0) return false;

		return true;
	}

	public void passOrKick(){
		if(canPass() && !init) pass();
		else if(canKick()){
			if(findGoal()) kick();
		}
	}

	public boolean findGoal(){
		if((m_side=='l' && goalR==null) || (m_side=='r' && goalL==null)){
			m_agent.turn(40);

			m_memory.clearInfo();

			return false;
		}

		return true;
	}

	public void pass(){
		if(m_side=='l') m_agent.kick(robot.m_distance*3, robot.m_direction);
		else m_agent.kick(robot.m_distance*3, robot.m_direction);

		position=true;
	}

	public boolean canPass(){
		boolean Mygoal=false, otherGoal=false;

		if(m_side=='l' && goalL!=null) Mygoal=true;

		if(m_side=='r' && goalR!=null) Mygoal=true;

		if(m_side=='l' && goalR==null) otherGoal=true;

		if(m_side=='r' && goalL==null) otherGoal=true;

		if(robot==null){
			if(m_number<9) m_agent.turn(40);

			m_memory.clearInfo();

			return false;
		}

		if(robot.m_distance<5 || Mygoal || (m_number>8 && otherGoal)){
			m_agent.turn(40);

			m_memory.clearInfo();

			return false;
		}

		return true;
	}

	public boolean canKick(){
		if(init || m_number==9 || m_number==10 || m_number==11) return true;

		if(m_side=='l'){
			if(goalR!=null){
				if(goalR.m_distance<=40) return true;
			}
		}
		else{
			if(goalL!=null){
				if(goalL.m_distance<=40) return true;
			}	
		}

		return false;
	}

	public void kick(){
		if(m_side=='l') {
			if(goalR.m_distance>30 && !init) m_agent.kick(5, goalR.m_direction);
			else{
				m_agent.kick(100, goalR.m_direction);

				position=true;
			}
		}
		else {
			if(goalL.m_distance>30 && !init) m_agent.kick(5, goalL.m_direction);
			else{
				m_agent.kick(100, goalL.m_direction);

				position=true;
			}
		}
	}

	public void goOrLookToBall(){
		if(Math.abs(ball.m_direction)>1 && !position) m_agent.turn(ball.m_direction);
		else if(canGoToBall()){
			stopPosition();

			positioned=false;

			float power=dash_factor*(ball.m_distance+10);
			dash_factor*=0.9; //this decreases the dash factor, it is restored when we get new visual info
			if(power > 100)
		    	power=100;
			m_agent.dash(power);
		}
	}

	public boolean canGoToBall(){
		if(ball.m_distance<=15 || robot==null || (m_number<4 && ball.m_distance<=20)){
			if(robot!=null){
				if(ball.m_distance<=robot.m_distance-ball.m_distance || m_number<4) return true;
			}
			else return true;
		}

		if(!positioned) position=true;

		return false;
	}

	public void lookForObjects(){
		ball=null; line=null; goalR=null; goalL=null; robot=null; robot2=null; flagC=null;

		try{
			for(int c=0 ; c<m_memory.m_info.m_objects.size(); c++){
				ObjectInfo object=(ObjectInfo)m_memory.m_info.m_objects.elementAt(c);

				String[] objects=object.m_type.split(" ");

				if(object.m_type.compareTo("flag c")==0) flagC=object;

				if(object.m_type.compareTo("ball")==0) ball=object;

				if(objects[0].compareTo("player")==0){
					if(object.m_type.compareTo("player "+m_team)==0) robot=object;
					else robot2=object;
				}

				if(object.m_type.compareTo("goal l")==0) goalL=object;

				if(object.m_type.compareTo("goal r")==0) goalR=object;

				if(object.m_type.compareTo("line")==0) line=object;
			}
		}catch(Exception e){}
	}

	public boolean lookToC(){
		if(flagC==null){
			m_agent.turn(40);

			m_memory.clearInfo();

    		return false;
		}

		if(flagC.m_distance<=30) return true;

		if(flagC.m_direction!=0) m_agent.turn(flagC.m_direction);

		m_agent.dash(50*flagC.m_distance);

		return false;
	}

    private int estadoMoveToMyPosition=0;
    public boolean moveToMyPosition(ObjectInfo goal){
    	boolean answer=false;

    	switch(estadoMoveToMyPosition){
    		case 0: if(lookToC()) estadoMoveToMyPosition=1;

    		case 1: if(goToGoal(goal, postionX())) estadoMoveToMyPosition=2;
    				break;		

    		case 2: rollToSide(); 

    				estadoMoveToMyPosition=3;
    				break;

    		case 3: if(goTo(postionY())){
						estadoMoveToMyPosition=0;

    					answer=true;
    				}
    				break;
    	}

    	return answer;
    }

    public boolean goToGoal(ObjectInfo goal, double position){
    	if(lookForward(goal)){
    		double error=goal.m_distance-position;

			m_agent.dash(50*error);

			if(error>=-1 && error<=1) return true;
    	}

    	return false;
    }

	public boolean lookForward(ObjectInfo goal){
		if(goal==null){
			m_agent.turn(40);

			m_memory.clearInfo();
		}
		else if(goal.m_direction!=0) m_agent.turn(goal.m_direction);
		else return true;

		return false;
	}

    public boolean goTo(double position){
    	if(line==null){
    		double mult;
			if(m_number%2==0) mult=-1;
			else mult=1;

    		m_agent.turn(40*mult);

    		m_memory.clearInfo();
    	}
    	else{
    		double error=line.m_distance-position;

    		m_agent.dash(50*error);

    		if(error>=-1 && error<=1) return true;
    	}

    	return false;
    }

    public double postionX(){
    	double answer=0;

    	switch(m_number){
    		case 1: answer=100+add;
    				break;

    		case 2: answer=80+add;
    				break;		

    		case 3: answer=80+add;
    				break;

    		case 4:	answer=70+add;
    				break;

    		case 5: answer=70+add;
    				break;	

    		case 6: answer=50+add;
    				break;						

    		case 7: answer=50+add;
    				break;	

    		case 8: answer=60+add;			
    				break;

    		case 9: answer=30+add;
    				break;		

    		case 10: answer=40+add;
    				 break;			

    		case 11: answer=40+add;
    				 break;		 
    	}

    	return answer;
    }

    public double postionY(){
    	double answer=0;

    	switch(m_number){
    		case 1: answer=35;
    				break;

    		case 2: answer=25;
    				break;		

    		case 3: answer=25;
    				break;

    		case 4: answer=10;
    				break;

    		case 5: answer=10;
    				break;

    		case 6: answer=20;
    				break;

    		case 7: answer=20;
    				break;

    		case 8: answer=35;
    				break;				

    		case 9: answer=35;
    				break;		

    		case 10: answer=20;
    				 break;		

    		case 11: answer=20;
    				 break;		 
    	}

    	return answer;
    }

	public void rollToSide(){
		double mult;
		if(m_number%2==0) mult=-1;
		else mult=1;

		m_agent.turn(90*mult);

		m_memory.clearInfo();
	}

	public void moveToMySide(){
	    switch(m_number){
			case 1: m_agent.move(-1*52.5, 34-0.5*68.0); //Goleiro
					break;

			case 2: m_agent.move(-0.8*52.5, 34-0.6*68.0);	//Zagueiro
					break;

			case 3: m_agent.move(-0.8*52.5, 34-0.4*68.0);	//Zagueiro
					break;		

			case 4: m_agent.move(-0.8*52.5, 34-0.8*68.0);	//Lateral
					break;		

			case 5: m_agent.move(-0.8*52.5, 34-0.2*68.0);	//Lateral
					break;										

			case 6: m_agent.move(-0.4*52.5, 34-0.8*68.0);	//Meia
					break;

			case 7: m_agent.move(-0.4*52.5, 34-0.2*68.0);	//Meia
					break;		

			case 8: m_agent.move(-0.4*52.5, 34-0.5*68.0);	//Meia
					break;		

			case 9: m_agent.move(-0.3*52.5, 34-0.5*68.0);	//Atacante
					break;		

			case 10: m_agent.move(-0.3*52.5, 34-0.6*68.0); //Atacante
					break;

			case 11: m_agent.move(-0.3*52.5, 34-0.4*68.0); //Atacante									
					 break;
		}
    }

    //===========================================================================
    // Implementation of SensorInput Interface

    //---------------------------------------------------------------------------
    // This function sends see information
    public void see(VisualInfo info){
		m_memory.store(info);
		dash_factor=20;
    }


    //---------------------------------------------------------------------------
    // This function receives hear information from player
    public void hear(int time, int direction, String message){

    }

    //---------------------------------------------------------------------------
    // This function receives hear information from referee
    public void hear(int time, String message){
    	String[] messages=message.split("_");


    	if(messages[0].compareTo("goal")==0) playOn=false;

    	if(messages[0].compareTo("kick")==0 || message.compareTo("play_on")==0){
    		playOn=true;

			init=true;
    	}

		if(message.compareTo("time_over")==0) m_timeOver=true;
	
		if(Pattern.matches("^before_kick_off.*", message)){
			m_playMode=message;

			playOn=false;
		}

    }

    //--------------------------------------------------------------------------
    // This function receives a sense_body message
    // It doesn't do anything other than signaling the time to send a command
    public void sense(String message){
		m_waiting=false;
    }

    //===========================================================================
    // Private members
    private boolean position=false, positioned=false, init=true;
    private ObjectInfo ball, line, goalR, goalL, robot, robot2, flagC;
    private boolean playOn=false;
    private int m_number, add=0;
    private SendCommand m_agent;
    private Memory m_memory;		
    private char m_side;
    volatile private boolean m_timeOver,m_waiting;
    private String m_team;
    volatile private String m_playMode;
    volatile private float dash_factor=20;
}
