R = 1.24;                       %Resistencia Terminal
L = 0.56e-3;                    %Indut�ncia Terminal
J = 92.5e-7;                    %In�rcia do rotor
tm = 17.6e-3;                   %Constante de tempo mec�nico
Kt = 25.5e-3;                   %Constante de torque
Ks = 374;                       %Constante de velocidade
p = 3;                          %Pois o motor � trif�sico e tem um arranjo sim�trico


te = L/(p*R);                   %Constante de tempo el�trico
Ke = (3*R*J)/(tm*Kt);           %Constante de back emf

%Fun��o de Transfer�ncia
G = tf([1/Ke],[tm*te tm 1]);

%%
%Plot da resposta ao degrau unit�rio
step(G, 0.5);
title('Open Loop Step Response diagram'); 
xlabel('Time, secs')
ylabel('Voltage, volts') 
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
bode(G,{0.1 , 100})
title('Open Loop Bode plot diagram with wider frequency spacing');
grid on;

%%
% plots the Bode Plot figure;
%GD = c2d(G, 0.5) bode(G,'r', GD,'b--')
%title('Open Loop Bode plot diagram with discretisied response');
%grid on;
% End of code