set title 'Интерполяция функции x*sin(x)'
set grid
set key top left
plot'interpolation_data.txt' index 0 with points pt 1 ps 2 lc rgb 'red' title 'Узлы', \
    'interpolation_data.txt' index 1 using 1:2 with lines lw 2 lc rgb 'blue' title 'f(x) = x * sin(x)', \
    'interpolation_data.txt' index 1 using 1:3 with lines lw 2 lc rgb 'green' title 'Полином'
pause -1
