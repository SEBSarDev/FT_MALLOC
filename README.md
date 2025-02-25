# FT_MALLOC

Recode malloc in C.
To test this project you can run :
```
make
gcc mytest.c
./run_linux.sh ./a.out
```
"make" will compile librairie, then  "gcc mytest.c" will compile our test program (but you can use an other one if you want).
Finaly "./run_linux.sh ./a.out" will place our librairie instead the default malloc librairie, so when we run imediatly ./a.out, it will use our malloc.

For explanation and useful links, please see the Ressources repository.
