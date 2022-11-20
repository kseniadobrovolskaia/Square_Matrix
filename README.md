# Square Matrix  
>Сalculates the determinant of a matrix N*N whose data is of any type  

1. Чтобы собрать весь проект:  
```
  $make
```
1. Чтобы удалить объектные файлы со всего проекта:  
```
  $make clean
```

1. Чтобы запустить *определитель матрицы* нужно в директории **Matrix**:  
``` 
  $./Matrix.exe   
```
1. Чтобы запустить *тестирование определителя матрицы* нужно в директории **Tests**:  
``` 
  $./Matrix_Test.exe  
  $cmake -S . -B build
  $cmake --build build  
  $cd build    
  $ctest  
```    
 
