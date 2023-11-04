# Prática 1: Comunicação SPI com RFID

- Simule um controle de acesso com o módulo RFID. Utilize 2 leds e 1 buzzer. O led vermelho
inicialmente ficará aceso. Ao inserir uma tag rfid previamente cadastrada, apague o led
vermelho e acenda um led verde por 10 segundos e mostre na tela a mensagem “Acesso
liberado”.
- Caso a tag não esteja cadastrada, mostre na tela a mensagem “cartão invalido” e pisque o led
vermelho algumas 3 vezes.
- Em caso de inserir por 5 vezes uma tag que não esteja cadastrada, imprima a mensagem
“SISTEMA BLOQUEADO”, o led vermelho ficará piscando e o buzzer acionado por 30
segundos.