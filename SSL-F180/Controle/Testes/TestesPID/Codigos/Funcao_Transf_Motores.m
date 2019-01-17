clc
% Importando os dados do txt onde as velocidades e input foram salvos

dados111012 = importdata('C:\Users\natal\Desktop\teste_radio\teste\Teste_Novo\Motor 11, Motor 10, Motor 12(5).txt');
%%
%Inicializando as variáveis com os valores lidos do txt
motor11 = dados111012(:,1); % Primeira coluna - roda 1
motor10= dados111012(:,2);  % Segunda coluna - roda 2
motor12 = dados111012(:,3); % Terceira coluna - roda 3
input4 = dados111012(:,4);
%%
% Gerando um objeto do tipo iddata para ser importado no
%"systemIdentification" e achar a função de transferência não linear
fun10 = iddata(motor10,input4,0.1);
fun11 = iddata(motor11,input4,0.1);
fun12 = iddata(motor12,input4,0.1);
%%
%Import data (nome do iddata (fun...), tempo inicial: 0 e sample time: 0.1)
%-> Arrastar para working data -> Estimar o sistema -> nonlianer models ->(TESTAR OS 3 MODOS E COMPARAR O FIT) nonlinear ARX (num input terms: 1/ num output
%terms: 1 ou 2 (testar os 2)/nonlinearity: sigmoid network) E
%Hammerstein-Wiener (nonlinearity: Sigmoid Network/ Ordem dos Zeros:
%1/Ordem dos polos:2)-> Arrastar o dado inicial para o Validation Data e
%comparar os 3 modos selecionando o "Model Output" -> arrastar o melhor
%para "To Workspace" renomeando-o com o nome adequado (nlm...)
systemIdentification;
%%
% Achando os polos e os pontos de operação
[X10,U10] = findop(nlm10,'steady',NaN,NaN);
[X11,U11] = findop(nlm11,'steady',NaN,NaN);
[X12,U12] = findop(nlm12,'steady',NaN,NaN);
%%
% Linearizando as funções de transferências não-lineares em torno dos polos
%e dos pontos de operação (X e U)
N10 = linearize(nlm10,U10,X10);
N11 = linearize(nlm11,U11,X11);
N12 = linearize(nlm12,U12,X12);
%%
% Função de tranferência linerizada e em tempo contínuo
G10 = tf(N10, 'variable','z');
G11 = tf(N11,'variable','z');
G12 = tf(N12, 'variable','z');
%%