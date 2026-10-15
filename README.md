# FIFO-chrono-test

Benchmarking C++ Containers: Vector vs. Array vs. List

Projekt zawiera program w języku C++ służący do testowania wydajności (benchmarking) podstawowych kontenerów i struktur danych: std::vector, tradycyjnej tablicy statycznej (C-style array) oraz std::list.
Aplikacja mierzy czas wykonywania operacji za pomocą biblioteki <chrono> i wypisuje wyniki w milisekundach.

📊 Zakres testów

Program wykonuje pomiary dla 100 000 elementów bazowych oraz dodatkowych 50 000 elementów w trzech etapach:
1. Wstawianie na koniec (Push Back / Initialization):
	• Wypełnienie struktur losowymi liczbami przy użyciu rand().
2. Wstawianie w środek + Sortowanie:
	• Dynamiczne dodawanie elementów dokładnie w aktualny środek kontenera.
	• Sortowanie końcowe całej struktury (std::sort lub lista.sort()).
3. Usuwanie ze środka:
	• Sekwencyjne usuwanie elementów z samej połowy kontenera (zmniejszanie struktur o 50 000 elementów).

🚀 Zastosowane optymalizacje

Kod został w pełni zoptymalizowany pod kątem eliminacji wąskich gardeł wydajnościowych (O(N²)), dzięki czemu wykonuje się w kilka sekund zamiast kilkunastu minut:
• Iterator Cache dla listy: Podczas wstawiania i usuwania ze środka std::list, pożądana pozycja jest aktualizowana lokalnie o przesunięcie bitowe/iteracyjne, zamiast kosztownego wywoływania std::advance od początku listy w każdej iteracji.
• Sortowanie jednorazowe: Sortowanie struktur wywołuje się raz – po zakończeniu pętli wstawiającej, co odzwierciedla realny profil operacji na danych.

🛠️ Jak uruchomić


Wymagania

• Kompilator wspierający standard C++11 lub nowszy (np. GCC, Clang, MSVC).

Kompilacja z linii poleceń

bash
g++ -O3 main.cpp -o benchmark
./benchmark
Używaj kodu z rozwagą.
Zaleca się użycie flagi optymalizacyjnej -O3 w celu uzyskania miarodajnych wyników czasowych.

📈 Spodziewane wnioski z pomiarów

• Wektor vs Tablica: Wykazują niemal identyczną wydajność przy operacjach sekwencyjnych. Wektor zachowuje przewagę łatwego zarządzania pamięcią.
• Wstawianie/Usuwanie w środku: Wektor i tablica wymagają fizycznego przesuwania elementów w pamięci (operacja kosztowna pamięciowo), natomiast lista wymaga jedynie przepięcia wskaźników (operacja bardzo szybka po uprzednim znalezieniu iteratora).
• Sortowanie: std::vector oraz tablica są sortowane znacznie szybciej dzięki ciągłości pamięci podręcznej cache procesora w porównaniu do rozproszonej w pamięci struktury std::list.
