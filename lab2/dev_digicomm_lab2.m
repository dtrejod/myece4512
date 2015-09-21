% Digital Communications 
% Lab 2
% By: Devin Trejo

%% 
clear; clc; close all;

% Input parameters
A = 1; % Amplitude of sine wave (V)
N1 = 0.1; % Time legnth of Ramp1
N2 = 0.2; % Time legnth of constant
N3 = 0.25;% Time legnth of Ramp2
T = 1.5E-3;  % Period of waveform (secs)

t0 = 0;
t1 = N1*T;
t2 = (N1+N2)*T;
t3 = (N1+N2+N3)*T;

% Simulation Specific Input
Ts = 1E-6; % Sample Time Period
fs = 1/Ts; % Sample Frequency
startTime = 0; % Simulation Start Time (sec) (Do not change from 0)
stopTime = T; % Simulation Stop Time (sec) - Simulate over one period
N = fs*T; % Samples in Simulation
kVec = 0:5;

% ----------------------------------------------------------
% ----------------------------------------------------------
% - Below this line everything is automatically calculated -
% ----------------------------------------------------------
% ----------------------------------------------------------

% ------------------------------------
% - Simulate Simulink Model (Part 2) -
% ------------------------------------

% Frequnecy Range in accordance with Nyquist
f = linspace(0,fs,N);

% Max freqeuncy to display on Spectrum Analyzer
spec_span = f(length(kVec));

% Run Simulink Simulation with given workspace parameters
options = simset('SrcWorkspace','current');
set_param('lab2_1', 'StartTime', num2str(startTime), 'StopTime', ...
    num2str(stopTime));
sim('lab2_1',[],options);

% Extracted Values for first five values in Spectrum Analyzer (in Watts)
Pw_XSim = [130.173E-3 161.838E-3 33.651E-3 1.781E-3 220.210E-6 ...
    144.803E-6];
% In terms of watts. We convert back to Volts (assume Rload = 1ohm)
XSim = sqrt(Pw_XSim*2);
XSim(1) = sqrt(Pw_XSim(1));

% Extract Data from Simunlink Simulation. The simulation spits out one
% extra sample so we truncate it by one. We also define the signal in terms
% of only one period
x = sig.Data';
sigP = x(1:N); % Signal over one period

% ---------------------------------------------
% - Find Fourier Series Coefficients (Part 3) -
% ---------------------------------------------

% Find Fourier Series Complex Components. We define a inline function
n = 0:N-1;
ts = T/N;
t = n*ts;

% Define inline fn to calculate the Rectangular Fourier Series
getA = @(n) (2/T)*sum(sigP.*cos(2*pi*n/T*t))*ts;
getB = @(n) (2/T)*sum(sigP.*sin(2*pi*n/T*t))*ts;
getAs = @(ns) arrayfun(getA,ns);
getBs = @(ns) arrayfun(getB,ns);
getXs = @(ns) sqrt(getAs(ns).^2 + getBs(ns).^2);

% Calculate the Fourier Series
XCalc = getXs(kVec);
XCalc(1) = XCalc(1)/2;

% Find Actualy FFT
XAct = 2*abs(fft(sigP)/N);
XAct(1) = XAct(1)/2;

% ----------------------------
% - Calculate Power (Part 1) -
% ----------------------------

% Calculate Average Power for Actual, Simulated, and Calculated
PavAct = mean(sigP.^2); % Assume RL = 1 ohm
PavActdBm = pow2db(PavAct) + 30;
PavSim = sum(XSim.^2);
PavSimdBm = pow2db(PavSim) + 30;
PwX = XCalc.^2/2;
PwX(1) = XCalc(1).^2;
PwX = cumsum(PwX);
PavCalc = sum(PwX);
PavCalcdBm = pow2db(PavCalc) + 30;

% Max Harmonic
kMax = max(kVec)+1;

% Plot
figure()
plot(f(1:kMax),XCalc);
xlabel('Frequency (Hz)');
ylabel('Power (dBm)');
xlim([0 f(max(kVec+1))]);
grid on;

% DC Value
DC = mean(sigP);
DC2 = XSim(1);
DC3 = XCalc(1);

% RMS Values
RMS = rms(sigP);
RMS2 = sqrt(mean(XSim(1).^2));
RMS3 = sqrt(mean(XCalc(1).^2));

% Print scope and spectrum analyzer to figures
figure();
plot(t, sigP);
hold on
plot(xlim, [DC DC], 'r--');
plot(xlim, [RMS RMS], 'm--');
grid on
xlabel('time (secs)');
ylabel('Amplitude (V)');
legend('Original Signal', 'DC Value', 'RMS Value');

% -----------------------------
% - Different in Coefficients -
% -----------------------------

% Find normalized power in each harmonic
Pharm = PwX/PavAct*100;

% Find Fourier Transform from Spectrum Analyzer and Calculated
Per_err = abs(XSim-XCalc)./XCalc*100;

% Print to console the findings
tableLegend = {'f'; 'n'; 'Norm_Power'; 'Pw_XAct'; 'Pw_XSim'; ...
    'Pw_XCalc'; 'Percent_Diff'};
Presults = table(f(1:kMax)', kVec(:), Pharm(:), XAct(1:kMax)', ...
    XSim', XCalc', Per_err', ...
    'VariableNames', tableLegend);   
disp(Presults);

fprintf(['Actual: DC = %0.2f / RMS = %0.2f\n'...
    'Simulated: DC = %0.2f / RMS = %0.2f\n'...
    'Calculated: DC = %0.2f / RMS = %0.2f\n\n'], ...
    DC, RMS, DC2, RMS2, DC3, RMS3);

% Plot a comparison between simulated and calculated values. 
figure()
plot(kVec, XAct(1:kMax), 'LineWidth', 2);
hold on
plot(kVec, XSim);
plot(kVec, XCalc);
xlabel('harmonics (n)');
ylabel('Volts (V)');
legend('Actual', 'Simulated', 'Calculated');
grid on