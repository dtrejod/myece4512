% Digital Communications 
% Lab 1
% By: Devin Trejo

%% 
clear; clc; close all;

% Input parameters
A = 7; % Amplitude of sine wave (V)
T = 2E-3; % Period of sine wave (ms)
TH = 3.5; % Threshold of sine wave (V)

% Simulation Specific Input
samTime = 2E-6; % Simulation sample period
startTime = 0; % Simulation Start Time (sec)
stopTime = T; % Simulation Stop Time (sec)

% Convert from period to frequency
f0 = 1/T;
fs = 1/samTime;

% Find the discrete time frequency
dis_sigf = f0/fs;

% Calculate discrete time period
samPeriod = ceil(1/dis_sigf);

% We want the simulation to run for one period
samPerSim = samPeriod;

% Simulate the simulink model
options = simset('SrcWorkspace','current');
set_param('Lab1', 'StartTime', num2str(startTime), 'StopTime', ...
    num2str(stopTime));
sim('Lab1',[],options);

% Extract Data from Simunlink Simulation
x = mod_sig.Data;
sig = x(2:length(x));

% Find Fourier Series Components
n = 0:samPerSim-1;
ck = @(k) ((1/samPerSim)* sum(sig*exp(-j*2*pi.*n.*k/samPerSim)));

c = 0*sig;
for i = 0:1:5;
    c(:,i+1) = ck(i);
end