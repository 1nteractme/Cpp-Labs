set title 'Проверка точки в треугольнике'
set xlabel 'X'
set ylabel 'Y'
set grid
set size ratio -1
plot 'triangle_data.dat' index 0 with lines lw 2 lc rgb 'blue' title 'Треугольник', 'triangle_data.dat' index 1 with points pt 7 ps 1.5 lc rgb 'green' title 'Точка внутри'
pause -1 'Нажмите Enter для выхода...'
