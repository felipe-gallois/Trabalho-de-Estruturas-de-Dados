# Versão do programa com ABP
abp:
	gcc "src\main.c" "src\abp.c" "src\leitor.c" -I "inc" -D PROGRAMA_ABP -Wall -o abp

# Versão do programa com AVL
avl:
	gcc "src\main.c" "src\avl.c" "src\leitor.c" -I "inc" -D PROGRAMA_AVL -Wall -o avl