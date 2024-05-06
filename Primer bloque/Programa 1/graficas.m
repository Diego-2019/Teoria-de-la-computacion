% Leer los datos
data = readtable('ocurrenciasReporte.csv');

% Elimina espacios al inicio y al final de los nombres de las columnas
data.Properties.VariableNames = strtrim(data.Properties.VariableNames);

% Crear una nueva figura con un tamaño específico
figure('Position', [100, 100, 1800, 600]); % Ajusta el tamaño para acomodar ambas gráficas

% Primera grafica: Valores originales
% subplot(1, 2, 1); % Divide la ventana de la figura en 1 fila y 2 columnas, y selecciona la primera posición
% plot(data.Cadena, data.OcurrenciaA, 'o-', 'MarkerFaceColor', [31/255, 119/255, 180/255]);
% legend('Ocurrencia de A', 'Location', 'best');
% xlabel('Cadena');
% ylabel('Ocurrencias de A');
% title('Ocurrencias de A por Cadena');
% grid off;
% ylim([0, max(data.OcurrenciaA)]);

% Prepara los datos para la segunda gráfica
ocurrenciaA_log = data.OcurrenciaA;
indices_no_cero = ocurrenciaA_log ~= 0; % Encuentra índices donde el valor es diferente de cero
ocurrenciaA_log(indices_no_cero) = log10(ocurrenciaA_log(indices_no_cero)); % Aplica log10 solo a valores no cero

% Segunda grafica: Valores después de aplicar log10
% subplot(1, 2, 2); % Selecciona la segunda posición para la próxima gráfica
plot(data.Cadena, ocurrenciaA_log, 'o-', 'MarkerFaceColor', [31/255, 119/255, 180/255]);
xlabel('Cadena');
ylabel('Log10 de Ocurrencias de A');
title('Log10 de Ocurrencias de A por Cadena');
legend('Log10 de Ocurrencia de A', 'Location', 'best');
grid off;
ylim([0, 5]);
