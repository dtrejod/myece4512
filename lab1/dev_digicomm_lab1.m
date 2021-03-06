% Digital Communications 
% Lab 1
% By: Devin Trejo

%% 
clear; clc; close all;

% Input parameters
A = 7; % Amplitude of sine wave (V)
T = 2E-3; % Period of sine wave (secs)
TH = 3.5; % Threshold of sine wave (V)

% Simulation Specific Input
samTime = 2E-6; % Simulation sample period
startTime = 0; % Simulation Start Time (sec) (Do not change from 0)
stopTime = T; % Simulation Stop Time (sec)

% ----------------------------------------------------------
% - Below this line everything is automatically calculated -
% ----------------------------------------------------------

% Convert from period to frequency
f0 = 1/T;
fs = 1/samTime;

% Find the discrete time frequency
dis_sigf = f0/fs;

% Calculate discrete time period
samPeriod = ceil(1/dis_sigf);

% We want the simulation to run for one period
samPerSim = samPeriod;

% Print Signal Statics to Console
fprintf(['Signal Stats: \n'...
    '    - Signal Amplitude: %s V\n'...
    '    - Signal Frequency (f0): %s Hz / Period: %s secs\n']...
    , num2str(A), num2str(f0), num2str(T)); 
fprintf('\n\n');

% ---------------------------
% - Simulate Simulink Model -
% ---------------------------

% Run Simulink Simulation with given workspace parameters
options = simset('SrcWorkspace','current');
set_param('Lab1', 'StartTime', num2str(startTime), 'StopTime', ...
    num2str(stopTime));
sim('Lab1',[],options);

% Autoscale all opened scopes
set(0, 'showhiddenhandles', 'on')
scope = findobj(0, 'Tag', 'SIMULINK_SIMSCOPE_FIGURE');
for i=1:length(scope)
  % this is the callback of the "autoscale" button:
  simscope('ScopeBar', 'ActionIcon', 'Find', scope(i))
end
set(0, 'showhiddenhandles', 'off')

% Extract Data from Simunlink Simulation. The simulation spits out one
% extra sample so we truncate it by one. We also define the signal in terms
% of only one period
x = mod_sig.Data;
sig = x(1:length(x)-1)';
sigPeriod = sig(1:samPeriod);

% Print scope and spectrum analyzer to figures
figure();
plot(org_sig);
hold on
plot(mod_sig);
xlabel('time (secs)');
ylabel('Amplitude (V)');
legend('Original Signal', 'Distorted Signal');

% -------------------------------
% - Fourier Series Calculations -
% -------------------------------

% Find Fourier Series Complex Components. We define a inline function
n = 0:samPeriod-1;
c  = @(k) (1/samPeriod) * sum(sigPeriod.*exp(-j*2*pi*k*n/samPeriod));

% Lets solve for "c" for many different values of k by using a loop
kVec = -5:5;
cVec = 0*kVec;
i = 1;
for k = kVec
    cVec(i) = c(k);
    i = i + 1;
end

% Find the Fourier Series Components in Polar Form (degrees)
for i = 1:length(cVec)
    polarCVec(i) = cellstr(rtp(cVec(i), 'd'));
end

% Print Fourier Series Cofficients to Screen
fprintf('Fourier Series Complex Components:\n');
for i=1:length(cVec)
   fprintf(['    - Fourier Series Coefficient k = %d:\n'...
       '        ck = %s / %s \n'], ...
       kVec(i), num2str(cVec(i)), polarCVec{i});
end
fprintf('\n\n');

% Find Fourier Series General Components. We define a inline function
n = 0:samPeriod-1;
a = @(k) (2/samPeriod) * sum(sigPeriod.*cos(2*pi*k*n/samPeriod));
b = @(k) (2/samPeriod) * sum(sigPeriod.*sin(2*pi*k*n/samPeriod));

% Lets solve for "c" for many different values of k by using a loop
aVec = 0*kVec;
bVec = 0*kVec;
cVec2 = 0*kVec;
i = 1;
for k = kVec
    if k == 0
        % For k=0 we have a special case we need to consider
        aVec(i) = 1/samPeriod * sum(sigPeriod);
        bVec(i) = b(k);
        cVec2(i)=aVec(i);
        i = i + 1;
        continue
    end
    aVec(i) = a(k);
    bVec(i) = b(k);
    % Next we want to convert to complex coefficents to compare the 
    % two methods. We do this by finding the magnitude of the coefficients
    cVec2(i)=1/2*(aVec(i)-j*bVec(i));
    i = i + 1;
end

% Find the Fourier Series Components in Polar Form (degrees)
for i = 1:length(cVec)
    polarC2Vec(i) = cellstr(rtp(cVec2(i), 'd'));
end

fprintf('Fourier Series General Components:\n');
for i=1:length(aVec)
   fprintf(['    - Fourier Series Coefficient k = %d:\n'...
       '        ak = %s / bk = %s \n', ...
       '        ck = %s / %s \n'], ...
       kVec(i), num2str(aVec(i)), num2str(bVec(i)), num2str(cVec2(i)),...
       polarC2Vec{i});
end
fprintf('\n\n');

% ----------------------
% - Power Calculations - 
% ----------------------

% Lastly we are asked to find the normalized average power.
i = 1;
Pav = 1/samPeriod * sum(abs(sigPeriod).^2);
for numHarm = 2:1:5
    % We have special cases depending on if we go over negative ks or not.
    if kVec(1) == 0
    middleIndex = 1;
    PavComplex(i) = 2*sum(abs(cVec(1:numHarm)).^2);
    PavPolar(i) = abs(aVec(middleIndex))^2 + ...
        1/2*sum(aVec(middleIndex + 1:middleIndex + numHarm).^2 ...
        + bVec(middleIndex + 1:middleIndex + numHarm).^2);
    else
       middleIndex = ceil(length(aVec)/2);
       PavComplex(i) = sum(abs(cVec(middleIndex-numHarm:middleIndex+numHarm)).^2);
       PavPolar(i) = abs(aVec(middleIndex))^2 + ...
            1/2*sum(aVec(middleIndex + 1:middleIndex + numHarm).^2 ...
            + bVec(middleIndex + 1:middleIndex + numHarm).^2);
    end

    i = i + 1;
end

% 1W = 30dBm
fprintf('Power Calculations:\n');
fprintf('    Actual Power in signal: %s Watts / %s dBm\n', ...
    num2str(Pav), num2str(pow2db(Pav)+30));
i = 1;
for i=1:length(PavPolar)
   if kVec(1) == 0
   fprintf(['    - Power in harmonics %d -> %d:\n'...
       '        From Complex (ck) = %s Watts / %s dBm\n'...
       '        From Polar (ak & bk) = %s Watts / %s dBm\n', ...
       '        Normalized Average Power = %s%%\n'],...
       kVec(middleIndex), kVec(middleIndex+i+1), ...
       num2str(PavComplex(i)), num2str(pow2db(PavComplex(i))+30), ...
       num2str(PavPolar(i)), num2str(pow2db(PavPolar(i))+30),...
       num2str(PavPolar(i)/Pav*100)); 
   else
   fprintf(['    - Power in harmonics %d -> %d:\n'...
       '        From Complex (ck) = %s Watts / %s dBm\n'...
       '        From Polar (ak & bk) = %s Watts / %s dBm\n' ...
       '        Normalized Average Power = %s%%\n'],...
       kVec(middleIndex-i-1), kVec(middleIndex+i+1), ...
       num2str(PavComplex(i)), num2str(pow2db(PavComplex(i))+30), ...
       num2str(PavPolar(i)), num2str(pow2db(PavPolar(i))+30), ....
       num2str(PavPolar(i)/Pav*100)); 
   end
end
fprintf('\n\n');
