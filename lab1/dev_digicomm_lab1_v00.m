% Digital Communications 
% Lab 1
% By: Devin Trejo

%% 
clear; clc; close all;

% Input parameters
A = 7; % Amplitude of sine wave
T = 2; % Period of sine wave
TH = 3.5; % Threshold of sine wave
samTime = 2E-6;
startTime = 0;
stopTime = 1;


% Calculate samples per period
sigf = 1/T;
samf = 1/samTime;
samPeriod = 2*pi/(sigf*samTime);
samPerSim = stopTime/(stopTime - startTime);

% Convert parameters to string format
str_samTime = num2str(samTime);
str_samPeriod = num2str(samPeriod);
str_startTime = num2str(startTime);
str_stopTime = num2str(stopTime);

% Simulate the simulink model
set_param('Lab1', 'StartTime', str_startTime, 'StopTime', str_startTime);
sim('Lab1');