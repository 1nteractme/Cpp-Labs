set encoding utf8
set title 'Интерполяция функции x*sin(1/x)'
set grid
set key top left
plot 'interpolation_data.dat' index 0 using 1:2 with points pt 7 ps 2 lc rgb 'red' title 'Узлы', \
     'interpolation_data.dat' index 1 using 1:2 with lines lw 2 lc rgb 'blue' title 'f(x)', \
     'interpolation_data.dat' index 1 using 1:3 with lines lw 2 lc rgb 'green' title 'Ньютон 1', \
     'interpolation_data.dat' index 1 using 1:4 with lines lw 2 lc rgb 'orange' title 'Ньютон 2'
pause -1
