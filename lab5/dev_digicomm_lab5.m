% Digital Communications 
% Lab 5
% By: Devin Trejo

%% 
clear; clc; close all;

% --------------------
% - Given parameters - 
% --------------------
% Birthday month April (4)
%
A0 = 0.2; % Amplitude for binary 0
A1 = 1.25; % Amplitude for binary 1
Ac = 12; % Amplitude for carrier
fc = 50E3; % Frequency of carrier
rb = 5E3; % Datarate bits/sec

% ---------------------------------
% - Operator Chossen parameters - 
% ---------------------------------
% Simulation Specific Input
%
Tb = 1/rb; % Bit time
Ts = Tb/100; % Sample Time Period (100 Samples per bit time)
fs = 1/Ts; % Sample Frequency
Threshold = 0;
% Transmit Delay Time
%
delta = round(310E-6*fs);

% -------------------------
% - Calculated parameters - 
% -------------------------
% Time Data
%
startTime = 0; % Simulation Start Time (sec) (Do not change from 0)
stopTime = 10*Tb; % Simulation Stop Time (sec)
t = startTime:Ts:stopTime; % Time vector

% Signals for binary 0/1
%
m0 = A0*sin(pi*t/Tb); % Representation of Binary 0
m1 = A1*sin(pi*t/Tb); % Representation of Binary 1
figure();
plot(t, m0, t, m1);
legend('m0','m1');

% Carrier Signal
%
carrier = Ac*sin(2*pi*fc*t);
reference = carrier;
% Noise Power
%
sigma = 0;

% ----------------------------------------------------------
% ----------------------------------------------------------
% - Below this line everything is automatically calculated -
% ----------------------------------------------------------
% ----------------------------------------------------------

% Run Simulink Simulation with given workspace parameters
options = simset('SrcWorkspace','current');
set_param('lab5', 'StartTime', num2str(startTime), 'StopTime', ...
    num2str(stopTime));
sim('lab5',[],options);