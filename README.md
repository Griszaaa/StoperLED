# Stoper LED
Projekt stopera elektronicznego na bazie poczwórnego 7-segmentowego wyświetlacza LED. Układ oparto o mikrokontroler AVR ATmega8. W projekcie wykorzystano moduły timerów sprzętowych procesora w celu implementacji mechanizmu multipleksowania poszczególnych wyświetlaczy oraz przerwania zewnętrzne do obsługi przycisków typu microswitch.
Urządzenie wyposażone jest w dwa takie przyciski, tak jak w klasycznym stoperze: "start/stop" oraz "reset", służące do uruchomienia oraz zatrzymania stopera, a także zresetowania go. Stoper zlicza czas do upływu 1 minuty, a następnie rozpoczyna cykl od początku. Odczyt czasu możliwy jest z dokładnością do setnej części sekundy.


