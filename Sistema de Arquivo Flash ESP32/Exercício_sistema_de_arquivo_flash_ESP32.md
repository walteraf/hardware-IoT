# Exercício

- Monte o circuito abaixo, e altere o status do led a cada vez que o botão é pressionado,
ou seja, clicou no botão, led fica aceso, apertou novamente, desliga.
- Salve em um arquivo .txt no SPIFFS o estado atual do led. E cada vez que o esp32
reiniciar, leia o arquivo e defina o estado do led como o último salvo

# Desafio

- Pesquise sobre servidores externos NTP para pegar dados de data e hora e criar um
sistemas de logs interno no ESP32.
- Salve na memória interna os últimos 100 logs do led, logs de quando houve mudança de
estado, com sua hora e data.