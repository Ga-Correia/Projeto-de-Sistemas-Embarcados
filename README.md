# Projeto de Sistemas Embarcados: Bota Ortopédica
 
 Projeto final da disciplina de Sistemas Embarcados que simula o funcionamento de uma bota ortopédica.

 A aplicação implementa uma comunicação I2C em linguagem C, entre um PIC18F4520 e um Arduino, no qual o PIC faz o papel de master sender da comunicação
 e o arduino como slave receiver.

 Para obter o arquivo hexadecimal referente ao PIC para poder gravar, execute o arquivo "masterPIC.c" dentro da IDE MikroC.

 ## Descrição do circuito

 - O botaõ RB0 do lado do PIC determina quando o circuito estará ligado ou não, sendo esta informação mostrada no LCD presente no Arduino.
 - Quando ligado, a medida que o valor do potenciômetro do lado do PIC varia, a quantidade de leds acesos no Arduino também variam, o que
representaria a potência da bota ortopédica.
 - O sensor de temperatura no Arduino representará no LCD em qual temperatura a bota ortopédica se encontra.
 
