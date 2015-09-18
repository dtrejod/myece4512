% Digital Communications 
% Lab 2
% By: Devin Trejo

%% 
clear; clc; close all;

% Input parameters
A = 1; % Amplitude of sine wave (V)
N1 = 0.1E-3; % Time legnth of Ramp1
N2 = 0.2E-3; % Time legnth of constant
N3 = 0.25E-3;% Time legnth of Ramp2
T = 1.5E-3;  % Period of waveform (secs)

% Simulation Specific Input
Ts = 1E-6; % Sample Time Period
fs = 1/Ts; % Sample Frequency
startTime = 0; % Simulation Start Time (sec) (Do not change from 0)
stopTime = T; % Simulation Stop Time (sec) - Simulate over one period
N = fs*T; % Samples in Simulation
kVec = 0:9;
spec_cf = 0;
spec_span = Ts*max(kVec);

% ----------------------------------------------------------
% - Below this line everything is automatically calculated -
% ----------------------------------------------------------

% ------------------------------------
% - Simulate Simulink Model (Part 2) -
% ------------------------------------

% Run Simulink Simulation with given workspace parameters
options = simset('SrcWorkspace','current');
set_param('lab2', 'StartTime', num2str(startTime), 'StopTime', ...
    num2str(stopTime));
sim('lab2',[],options);

% Extracted Values for first five values in Spectrum Analyzer (in dBm)
Xsim = [0 36.371E-3 17.592E-3 4.646E-3 712E-6 281.039E-6];

% Extract Data from Simunlink Simulation. The simulation spits out one
% extra sample so we truncate it by one. We also define the signal in terms
% of only one period
x = sig.Data';
sigP = x(1:N); % Signal over one period
%%
% ---------------------------------------------
% - Find Fourier Series Coefficients (Part 3) -
% ---------------------------------------------

% Find Fourier Series Complex Components. We define a inline function
%devFFTMag(x, fs);
FTM = fft(sigP, N)/N;
f = fs/2*linspace(0,1,N/2+1);
X = abs(FTM(1:N/2+1));

figure()
plot(f,abs(X));
xlabel('Frequency (Hz)');
ylabel('Power');
xlim([0 f(max(kVec)+1)]);
grid on;

% Find Fourier Transform from Spectrum Analyzer and Calculated
Per_err = abs(Xsim(1:max(kVec)+1)-X(1:max(kVec)+1))./X(1:max(kVec)+1).*100;

% Print to console the findings
tableLegend = {'f'; 'n'; 'X_Calc'; 'X_Sim'; 'Percent_Diff'};
Presults = table(f(1:max(kVec)+1)',kVec(:),abs(X(1:max(kVec)+1))',...
    abs(Xsim(1:max(kVec)+1))', Per_err', ...
    'VariableNames', tableLegend);   
    
disp(Presults)

% ----------------------------
% - Calculate Power (Part 1) -
% ----------------------------

% Calculate Power two different ways
Pav = 1/N*sum(sigP.^2); % Assume RL = 1 ohm
PavdBm = pow2db(Pav) + 30; % Power calculated using Parsevals (in dBm)
Pav2 = sum((abs(FTM)).^2);
Pav2dBm = pow2db(Pav2) + 30;

% Normalized Average Power
Pnorm = Pav2/Pav * 100;

fprintf(['Power in signal = %0.2f Watts / %0.2f dBm \n'...
    'Power in signal as specified using Parserval''s theorem = '...
    '%0.2f Watts / %0.2f dBm\n'], ...
    Pav, PavdBm, Pav2, Pav2dBm);

fprintf('Normalized Power = %0.2f %%\n', Pnorm);

% DC Value
DC = sqrt(X(1));

% Print scope and spectrum analyzer to figures
figure();
plot(sig);
hold on
plot(xlim, [DC DC], 'r');
grid on
xlabel('time (secs)');
ylabel('Amplitude (V)');
legend('Original Signal', 'DC Value');

