# SO-trabalho-M2

usar "gcc -o virtual_memory_translate virtual_memory_translate.c -lrt"
para compilar o código

e usar "./virtual_memory_translate"
para executar

para 16 bits:
apenas páginas de 2KB
para simular um "tlb miss", usar um valor superior a 16x2048 = 32768

para 32 bits:
apenas páginas de 4KB
para simular um "tlb miss", usar um valor superior a 16x4096 = 65536
