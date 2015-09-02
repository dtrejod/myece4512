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

samPerSim = stoptime/runtime;

% Calculate samples per period
f = 1/T;
samPeriod = 2*pi/(f*samTime);

% Simulate the simulink model
sim('Lab1');