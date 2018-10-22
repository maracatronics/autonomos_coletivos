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

    int estadoPosition=0;
    boolean goingToBall=false;
    public void run(){

	    moveToMySide();

		while(!m_timeOver){
			if(playOn){
				lookForObjects();

				if(position){
					goingToBall=false;

					switch(estadoPosition){
						case 0: if(neckBody()) estadoPosition=1;
								break;

						case 1: if(moveToMyPosition()) estadoPosition=2;
								break;

						case 2: position=false;
								estadoPosition=0;
								positioned=true;
								break;
					}
				}

				if(findBall()){
					if(closeToBall()) kick();
					else if(canDefense()){
						if(canGoToBall()){
							goingToBall=true;

							if(neckBody()) goToBall();
						}
						else{
							goingToBall=false;

							pid(ball.m_direction);
						}
					}
					else if(!positioned) position=true;
				}
				else if(!positioned && !goingToBall) position=true;
			}
			else{
				position=true;

				moveToMySide();
			}
			
	 		try{
	 		    Thread.sleep(2*SoccerParams.simulator_step);
	 		}catch(Exception e){}
	    }

		m_agent.bye();
	}

    //===========================================================================
    // Here are suporting functions for implement logic
	public boolean findBall(){
		if(ball==null){
			if(!position) m_agent.turn(-90);

			return false;
		}

		return true;
	}

	public void goToBall(){
		if(Math.abs(ball.m_direction)>0.2) m_agent.turn(ball.m_direction);
		else{
			float power=dash_factor*(ball.m_distance+10);
			dash_factor*=0.9; //this decreases the dash factor, it is restored when we get new visual info
			if(power > 100)
		    	power=100;
			m_agent.dash(power);
		}

		positioned=false;
	}

	public boolean canDefense(){
		if(ball.m_distance<=20) return true;

		return false;
	}

    boolean right=true;
    public boolean neckBody(){
    	if(!right){
    		positioned=false;

    		turnNeckToBody();

    		right=true;
    	}

    	return right;
    }

    public void turnNeckToBody(){
    	m_agent.turn_neck(90);
    }

    private int estadoMoveToMyPosition=1;
    public boolean moveToMyPosition(){
    	boolean answer=false;

    	switch(estadoMoveToMyPosition){
			case 1: if(lookForward()) estadoMoveToMyPosition=2;
    				break;

    		case 2: if(goToGoal(100)) estadoMoveToMyPosition=3;
    				break;

    		case 3: rollToSide();

    				estadoMoveToMyPosition=4;
    				break;

    		case 4: if(goTo(35)) estadoMoveToMyPosition=5;
    				break;		

    		case 5:	if(findGoalNeck()) estadoMoveToMyPosition=6;
    				break;

    		case 6: if(lookForward()){
    					right=false;

    					estadoMoveToMyPosition=1;

    					answer=true;
    				}
    				break;
    	}

    	return answer;
    }

    public boolean goToGoal(double position){
    	if(lookForward()){
    		double error=goal.m_distance-position;

			m_agent.dash(50*error);

			if(error>=-1 && error<=1) return true;
    	}

    	return false;
    }

    double preError=0;
	public void pid(double angle){
		double error=angle, kp=3, kd=15;

		double P=error*kp;

		double D=(error-preError)*kd;
		preError=error;

		double PD=P+D;

		positioned=false;

		m_agent.dash(PD);
	}

	public boolean closeToBall(){
		if(ball.m_distance>1) return false;

		return true;
	}

	public boolean findGoal(){
		if(goal==null){
			m_agent.turn(40);

			m_memory.clearInfo();

			return false;
		}

		return true;
	}

	public boolean findGoalNeck(){
		if(goal==null){
			m_agent.turn_neck(-90);

			m_memory.clearInfo();

			return false;
		}

		return true;
	}	

	public void kick(){
		if(Math.abs(ball.m_distChange)<=0.4){
			if(canPass()){
				m_agent.kick(robot.m_distance*3, robot.m_direction+40);
				position=true;
			}
		}
		else{
			m_agent.kick(200, -90);
			position=true;
		}
	}

	public boolean canPass(){
		if(robot==null){
			m_agent.turn(40);

			m_memory.clearInfo();

			return false;
		}

		return true;
	}

	public boolean canGoToBall(){
		if(ball.m_distance<=15 && Math.abs(ball.m_distChange)<=0.2) return true;

		return false;
	}

	public void lookForObjects(){
		ball=null; goal=null; line=null; robot=null; robot2=null;

		try{
			for(int c=0 ; c<m_memory.m_info.m_objects.size(); c++){
				ObjectInfo object=(ObjectInfo)m_memory.m_info.m_objects.elementAt(c);

				String[] objects=object.m_type.split(" ");

				if(objects[0].compareTo("player")==0){
					if(object.m_type.compareTo("player "+m_team)==0) robot=object;
					else robot2=object;
				}
				
				if(object.m_type.compareTo("player "+m_team)==0) robot=object;

				if(object.m_type.compareTo("line")==0) line=object;			

				if(object.m_type.compareTo("ball")==0) ball=object;

				if(m_side=='l'){
					if(object.m_type.compareTo("goal r")==0) goal=object;
				}
				else{
					if(object.m_type.compareTo("goal l")==0) goal=object;
				}
			}
		}catch(Exception e){}
	}

	public boolean lookForward(){
		if(goal==null){
			m_agent.turn(40);

			m_memory.clearInfo();
		}
		else if(goal.m_direction!=0) m_agent.turn(goal.m_direction);
		else return true;

		return false;
	}

    public boolean goTo(double distance){
    	if(line==null){
    		m_agent.turn(40);

    		m_memory.clearInfo();
    	}
    	else{
    		double error=line.m_distance-distance;

    		m_agent.dash(50*error);

    		if(error>=-1 && error<=1) return true;
    	}

    	return false;
    }

    public double postionX(){
    	double answer=0;

    	switch(m_number){
    		case 1: answer=150;
    				break;

    		case 2: answer=80;
    				break;

    		case 3: answer=80;
    				break;

    		case 4:	answer=70;
    				break;

    		case 5: answer=70;
    				break;

    		case 6: answer=50;
    				break;

    		case 7: answer=50;
    				break;

    		case 8: answer=60;
    				break;

    		case 9: answer=20;
    				break;	

    		case 10: answer=30;
    				 break;

    		case 11: answer=30;
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
		m_agent.turn(95);

		m_memory.clearInfo();
	}

	public void rollToOtherSide(){
		double mult;
		if(m_number%2==0) mult=-1;
		else mult=1;

		m_agent.turn(180*mult);

		m_memory.clearInfo();
	}

	public void moveToMySide(){
	    switch(m_number){
			case 1: m_agent.move(-0.98*52.5, 34-0.5*68.0); //Goleiro
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
    public void hear(int time, int direction, String message){}

    //---------------------------------------------------------------------------
    // This function receives hear information from referee
    public void hear(int time, String message){
    	String[] messages=message.split("_");

    	if(messages[0].compareTo("goal")==0 && messages[1].compareTo("kick")!=0) playOn=false;

    	if(messages[0].compareTo("kick")==0 || message.compareTo("play_on")==0) playOn=true;

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
    private boolean position=true, positioned=false;
    private ObjectInfo ball, goal, line, robot, robot2;
    private boolean playOn=false;
    private int m_number, side=-1;
    private SendCommand m_agent;
    private Memory m_memory;		
    private char m_side;
    volatile private boolean m_timeOver,m_waiting;
    private String m_team;
    volatile private String m_playMode;
    volatile private float dash_factor=20;
}