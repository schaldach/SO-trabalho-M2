# SO-trabalho-M2

usar "gcc -o virtual_memory_translate virtual_memory_translate.c -lrt"
para compilar o código

e usar "./virtual_memory_translate"
para executar

Utilize "gcc -o virtual_memory_translate virtual_memory_translate.c -lrt -Wall -Wextra && ./virtual_memory_translate" para checar se realmente tudo está certinho/otimizado (NÃO É TESTs PARA O CÓDIGO, É SÓ UMA VARREDURA PARA VER E ESTÁ TUDO CERTO)

-Wall: Ativa a maioria dos avisos comuns que ajudam a identificar possíveis problemas no código, como variáveis não utilizadas, conversões implícitas e outras práticas que podem levar a erros.

-Wextra: Ativa avisos adicionais que não estão incluídos em -Wall, como avisos sobre argumentos de funções não utilizados e outras verificações mais detalhadas

para 16 bits:
apenas páginas de 2KB
para simular um "tlb miss", usar um valor superior a 16x2048 = 32768

para 32 bits:
apenas páginas de 4KB
para simular um "tlb miss", usar um valor superior a 16x4096 = 65536
para ir para a segunda outer table, usar "10000000001000000000001" ou "401001" em hex
