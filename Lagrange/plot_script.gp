set encoding utf8
set title 'Интерполяция функции ln(x) методом Лагранжа'
set grid
set key top left
plot 'interpolation_data.dat' index 0 with points ls 1 title 'Узлы интерполяции', \
     'interpolation_data.dat' index 1 using 1:2 with lines ls 2 title 'ln(x)', \
     'interpolation_data.dat' index 1 using 1:3 with lines ls 3 title 'Лагранж', \
     'interpolation_data.dat' index 2 with lines ls 4 title 'Погрешность'
pause -1
