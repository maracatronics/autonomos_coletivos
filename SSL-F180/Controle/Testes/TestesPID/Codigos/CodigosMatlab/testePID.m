R = 1.24;                       %Resistencia Terminal
L = 0.56e-3;                    %Indut�ncia Terminal
J = 92.5e-7;                    %In�rcia do rotor
tm = 17.6e-3;                   %Constante de tempo mec�nico
Kt = 25.5e-3;                   %Constante de torque
Ks = 374;                       %Constante de velocidade
p = 3;                          %Pois o motor � trif�sico e tem um arranjo sim�trico
Ts = 0.02;                      %Tempo de amostragem do microcontrolador


te = L/(p*R);                   %Constante de tempo el�trico
Ke = (3*R*J)/(tm*Kt);           %Constante de back emf

num = 1/Ke;
den = [tm*te tm 1];

G = tf(num,den);                %Fun��o de Transfer�ncia (tempo cont�nuo)
G_disc = c2d(G,Ts);             %Fun��o de Transfer�ncia (tempo discreto)
%%
%Gr�fico da resposta ao degrau unit�rio
step(G, 0.5);
title('Resposta ao degrau em malha aberta (tempo cont�nuo)'); 
xlabel('Tempo, (s)')
ylabel('Tens�o, (V)') 
grid on;
%%
%Gr�fico da resposta ao degrau unit�rio
step(G_disc, 0.5);
title('Resposta ao degrau em malha aberta (tempo discreto)'); 
xlabel('Tempo, (s)')
ylabel('Tens�o, (V)') 
grid on;
%%
% plots the Root-locus figure;
rlocus(G);
title('Open Loop Root Locus diagram');
grid on;
%%
% plots the Nyquist diagram figure;
nyquist(G);
title('Open Loop Nyquist diagram');
grid on;
%%
% plots the Bode Plot figure;
bode(G);
title('Open Loop Bode plot diagram 1');
grid on;
%%
% plots the Bode Plot figure;
bode(G,{0.1 , 100});
title('Open Loop Bode plot diagram with wider frequency spacing');
grid on;
%%
% plots the Bode Plot figure;
GD = c2d(G, 0.5);
bode(G,'r', GD,'b--');
title('Open Loop Bode plot diagram with discretisied response');
grid on;
%%
Kp = 1.34593531764331;
Ki = 381.621340361213;
Kd = -1.14172984271721e-5;

b0 = Kp + Ki*(Ts/2) + Kd*(1/Ts); 
b1 = -Kp + Ki*(Ts/2) - 2*Kd*(1/Ts);
b2 = Kd*(1/Ts);

numPID1 = [Kd Kp Ki];
denPID1 = [0 1 0];

numPID2 = [b0 b1 b2];
denPID2 = [1 -1 0];

G_PID = tf(numPID1, denPID1); 
G_PID_disc = tf(numPID2, denPID2, Ts);
%%
numT = [(Kd/Ke) (Kp/Ke) (Ki/Ke)];
denT = [(tm*te) (tm + (Kd/Ke)) (1 + (Kp/Ke)) (Ki/Ke)];

T = tf(numT, denT);
T_disc = c2d(T, Ts);
%%
%Gr�fico da resposta ao degrau unit�rio
step(T, 0.5);
title('Resposta ao degrau em malha fechada (tempo cont�nuo)'); 
xlabel('Tempo, (s)')
ylabel('Tens�o, (V)') 
grid on;
%%
%Gr�fico da resposta ao degrau unit�rio
step(T_disc, 0.5);
title('Resposta ao degrau em malha fechada (tempo discreto)'); 
xlabel('Tempo, (s)')
ylabel('Tens�o, (V)') 
grid on;