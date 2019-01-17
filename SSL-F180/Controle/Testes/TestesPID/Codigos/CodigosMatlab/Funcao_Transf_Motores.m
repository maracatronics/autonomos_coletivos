clc
% Importando os dados do txt onde as velocidades e input foram salvos
dados562 = importdata('C:\Users\natal\Documents\Maraca\autonomos_coletivos\SSL-F180\Controle\Testes\TestesPID\Codigos\SalvaSerial\PID\rpmRobo3.txt');
%%
%Inicializando as variáveis com os valores lidos do txt
motor5 = dados562.data(:,2); % Primeira coluna - roda 1
motor6 = dados562.data(:,3); % Segunda coluna - roda 2
motor2 = dados562.data(:,4); % Terceira coluna - roda 3
inputData = dados562.data(:,1);
%%
%Verificar se deu tudo certo na aquisição dos dados para as variáveis
clc
fprintf('          PWM        RODA1       RODA2       RODA3\n');
matrizPrint = [inputData, motor5, motor6, motor2];
disp(matrizPrint);
%%
% Gerando um objeto do tipo iddata para ser importado no
%"systemIdentification" e achar a função de transferência dos motores
%(provavelmente não linear)
fun5 = iddata(motor5,inputData,0.02);
fun6 = iddata(motor6,inputData,0.02);
%fun2 = iddata(motor2,inputData,0.1);
%%
%Import data (nome do iddata (fun...), tempo inicial: 0 e sample time: 0.1)
%-> Arrastar para working data -> Estimar o sistema -> nonlianer models ->(TESTAR OS 3 MODOS E COMPARAR O FIT) nonlinear ARX (num input terms: 1/ num output
%terms: 1 ou 2 (testar os 2)/nonlinearity: sigmoid network) E
%Hammerstein-Wiener (nonlinearity: Wavelet Network/ Ordem dos Zeros:
%1/Ordem dos polos:2)-> Arrastar o dado inicial para o Validation Data e
%comparar os 3 modos selecionando o "Model Output" -> arrastar o melhor
%para "To Workspace" renomeando-o com o nome adequado (nlm...)
systemIdentification;
%%
% Achando os polos e os pontos de operação
[X5,U5] = findop(nlhw5,'steady',NaN,NaN);
[X6,U6] = findop(nlhw6,'steady',NaN,NaN);
%[X2,U2] = findop(nlm12,'steady',NaN,NaN);
%%
% Linearizando as funções de transferências não-lineares em torno dos polos
%e dos pontos de operação (X e U)
N5 = linearize(nlhw5,U5,X5);
N6 = linearize(nlhw6,U6,X6);
%N2 = linearize(nlhw2,U2,X2);
%%
% Função de tranferência linerizada e em tempo contínuo
G5 = tf(N5);
G6 = tf(N6);
%G2 = tf(N2, 'variable','z');
%%
G = tf(arxqs);