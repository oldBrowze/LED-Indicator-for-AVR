# LED-Indicator-library-for-AVR
 Библиотека, позволяющая управлять 4-разрядным семисегментным индикатором МК AVR.
Функционал реализован на базе микроконтроллера `ATMega328p` и платформы Arduino UNO.
### Используемое ПО 
* AVR Studio 7.0
 ---
 ### Функционал
###### Библиотека занимает
* Весь `PORTD` и весь `PORTB`;
* Нулевой таймер-счетчик `TCCR0` с установкой делителя на `256`;
* Регистр `TIMSK0` для определения прерывания 
* Порт `SREG` для разрешения глобальных прерываний (посредством функциии `sei()`);
###### Планируется реализовать
* Полную совместимость с другими видами микроконтроллеров AVR;
* Поддержка `float`-значений;
* Освободить незанятые биты регистра `PORTB`;
* Поддержка `signed`-значений;
* Увеличение возможностей библиотки;
* Аналог библиотеки для микроконтроллеров `STM` и `PIC`.
