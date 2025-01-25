# Saper - Dokumentacja

## Opis

Program "Saper" to implementacja klasycznej gry logicznej, w której użytkownik odkrywa pola na planszy, unikając min. Program obsługuje tryb interaktywny oraz tryb automatyczny z odczytem ruchów z pliku. Po zakończeniu gry wyświetlany jest wynik gracza, a wszystkie wyniki są zapisywane w pliku.

---

## Funkcjonalności

1. **Tryb interaktywny**:
   - Gracz podaje współrzędne pól do odkrycia (x, y) lub stawia flagi.
   - Obsługiwane akcje:
     - `r x y` – Odkrycie pola.
     - `f x y` – Postawienie lub usunięcie flagi.

2. **Tryb automatyczny (z pliku)**:
   - Uruchomienie programu z opcją `-f [plik]`, gdzie plik zawiera zapis ruchów w formacie:
     ```
     r 0 1
     f 2 2
     r 3 3
     ```
   - Po zakończeniu gry wyświetlane są:
     - Liczba poprawnych ruchów.
     - Wynik gracza.
     - Status gry (wygrana/przegrana).

3. **Zapisywanie wyników**:
   - Wyniki graczy są zapisywane w pliku `scores.txt`.
   - Pod koniec każdej gry wyświetlane jest Top 5 najlepszych wyników.

4. **Różne poziomy trudności**:
   - Łatwy: 9x9, 10 min.
   - Średni: 16x16, 40 min.
   - Trudny: 16x30, 99 min.
   - Tryb własny: Gracz sam wybiera wymiary planszy i liczbę min.

---

## Kompilacja

Aby skompilować program, użyj polecenia:
```bash
make
```

Dostępne komendy w Makefile:
- `make` – Kompilacja programu.
- `make test` – Uruchomienie testów.
- `make clean` – Usunięcie plików wykonywalnych i obiektowych.

---

## Uruchamianie programu

1. **Tryb interaktywny:**
   ```bash
   ./saper
   ```
   Gracz podaje swoje ruchy ręcznie.

2. **Tryb automatyczny (z pliku):**
   ```bash
   ./saper -f ruchy.txt
   ```
   Program odczytuje ruchy z pliku `ruchy.txt`.

---

## Struktura projektu

- **`main.c`**:
  Obsługuje argumenty wiersza poleceń i zarządza trybami gry.
- **`board.c` / `board.h`**:
  Obsługuje planszę gry, jej inicjalizację, odkrywanie pól i stawianie flag.
- **`config.c` / `config.h`**:
  Definiuje ustawienia gry, w tym poziomy trudności.
- **`test.c`**:
  Zawiera testy jednostkowe programu.
- **`scores.txt`**:
  Plik zawierający historię wyników graczy.

---

## Przykładowe pliki

### Przykładowy plik ruchów

Plik `ruchy.txt`:
```
r 0 1
f 1 1
r 2 2
```
Opis:
- `r 0 1` – Odkrycie pola (x=0, y=1).
- `f 1 1` – Postawienie flagi na polu (x=1, y=1).
- `r 2 2` – Odkrycie pola (x=2, y=2).

---

## Testy

Aby przetestować program, uruchom:
```bash
make test
```
Testy sprawdzają:
1. Poprawność działania dla różnych poziomów trudności.
2. Prawidłowość odczytu ruchów z pliku.
3. Obsługę niestandardowych plansz.

