# SO-trabalho-M2

usar "gcc -o virtual_memory_translate virtual_memory_translate.c -lrt"
para compilar o código
-- 
Utilize "gcc -o virtual_memory_translate virtual_memory_translate.c -lrt -Wall -Wextra && ./virtual_memory_translate" para checar se realmente tudo está certinho/otimizado (NÃO É TESTs PARA O CÓDIGO, É SÓ UMA VARREDURA PARA VER E ESTÁ TUDO CERTO)
-Wall: Ativa a maioria dos avisos comuns que ajudam a identificar possíveis problemas no código, como variáveis não utilizadas, conversões implícitas e outras práticas que podem levar a erros.
-Wextra: Ativa avisos adicionais que não estão incluídos em -Wall, como avisos sobre argumentos de funções não utilizados e outras verificações mais detalhadas
--

e usar "./virtual_memory_translate"
para executar

após inicializar o arquivo executável do código "virtual_memory_translate.c", o estado inicial da TLB e da tabela de páginas serão mostrados, e o usuário poderá informar qual o endereço lógico a ser buscado. Então, após a execução do algoritmo, ele informará o número e deslocamento de página retirados a partir do endereço lógico, e o valor lido na memória. O usuário poderá continuar no loop, vendo o novo estado da TLB e tabela de páginas, ou interromper o programa

para 16 bits:
páginas de 2KB, 1KB, 512B ou 256B
para simular um "tlb miss", usar um valor superior a 16x2048 = "32768" em decimal
para simular um "page fault", usar um valor superior a 20x2048 = "40960" em decimal

para 32 bits:
apenas páginas de 4KB
para simular um "tlb miss", usar um valor superior a 16x4096 = "65536" em decimal
para simular um "page fault", usar um valor superior 200x4096 = "819200" em decimal
para ir para a segunda outer table, usar "10000000001000000000001" ou "401001" em hex
