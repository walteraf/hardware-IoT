# Prática 3: Comunicação Serial entre 2 Arduinos

- Monte em uma protoboard, um arduino que recebe os valores de um sensor de
luminosidade e de um botão, e envia os dados via Serial para um outro arduino;
- Este segundo arduino, recebe os dados do botão e do sensor de luminosidade, enquanto o
botão esteja pressionado, liga o led na alta intensidade, caso contrário, a luminosidade fica
de acordo com o valor do sensor de luminosidade. Caso o valor seja abaixo de 20, imprime
na tela: Baixa luminosidade!