# page-replacement-simulator
Учебный репозиторий.
Консольное приложение на C++, моделирующее работу диспетчера памяти операционной системы и демонстрирующее классические алгоритмы замещения страниц при нехватке физической ОЗУ.
Пользователь выбирает алгоритм через консольное меню, программа выводит состояние кадров и итоговую статистику.

Реализованные алгоритмы:

**FIFO (First-In, First-Out).** Первой выгружается страница, которая дольше всех находится в памяти. Используется структура данных «очередь». При Page Fault и отсутствии свободных кадров страница из головы очереди вытесняется на диск, новая помещается в хвост. Главный недостаток — не учитывает частоту использования страниц и подвержен аномалии Белэди: увеличение числа кадров может увеличить число промахов.

**LRU (Least Recently Used).** Выгружается страница, к которой дольше всего не было обращений. Основан на принципе локальности ссылок. Для каждой страницы отслеживается метка времени последнего доступа; при нехватке памяти заменяется страница с минимальным значением счётчика. Устойчив к аномалии Белэди, но имеет высокие накладные расходы на обновление счётчиков.

**CLOCK (Second Chance).** Аппроксимация LRU с использованием циклического буфера и аппаратного бита обращения R-bit. При обращении процессора к странице её R-бит устанавливается в 1. При поиске жертвы для вытеснения указатель движется по кольцу: если R=1 — страница получает второй шанс и бит сбрасывается в 0, если R=0 — страница выгружается.

Статус: Архив / Read-Only. Проект завершен, разработка и внесение изменений не планируются.

# page-replacement-simulator
Educational repository. 
A C++ console application simulating the operation of an operating system's memory manager and demonstrating classic page replacement algorithms in the event of a shortage of physical RAM. The user selects an algorithm via a console menu, and the program outputs the state of the frames and the final statistics.

Implemented algorithms:

FIFO (First-In, First-Out). The page that has been in memory the longest is evicted first. The "queue" data structure is used. On a Page Fault and in the absence of free frames, the page from the head of the queue is evicted to disk, and the new one is placed at the tail. The main drawback is that it does not take into account the frequency of page usage and is subject to Belady's anomaly: an increase in the number of frames can increase the number of misses.

LRU (Least Recently Used). The page that has not been accessed for the longest time is evicted. It is based on the principle of locality of reference. For each page, the timestamp of the last access is tracked; in case of a memory shortage, the page with the minimum counter value is replaced. It is resistant to Belady's anomaly but has high overhead for updating counters.

CLOCK (Second Chance). An approximation of LRU using a circular buffer and a hardware reference bit (R-bit). When the processor accesses a page, its R-bit is set to 1. When searching for a victim for eviction, the pointer moves around the ring: if R=1, the page gets a second chance and the bit is reset to 0; if R=0, the page is evicted.

Status: Archive / Read-Only. The project is completed, no further development or changes are planned.
