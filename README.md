# Square Matrix  
>Сalculates the determinant of a matrix N*N whose data is of any type  

1. Чтобы собрать весь проект:  
```
  $make
```
2. Чтобы удалить объектные файлы со всего проекта:  
```
  $make clean
```

3. Чтобы запустить *определитель матрицы* нужно в директории **Matrix**:  
``` 
  $./Matrix.exe   
```
4. Чтобы запустить *тестирование определителя матрицы* нужно в директории **Tests**:  
``` 
  $./Matrix_Test.exe  
  $cmake -S . -B build
  $cmake --build build  
  $cd build    
  $ctest  
```    
 
