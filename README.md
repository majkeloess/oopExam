# I Przeładowania operatorów

Przeładowanie operatora dokonuje się definiując własną
funkcję o nazwie operatorX, gdzie X oznacza symbol
interesującego nas operatora:
-Może być funkcją składową
-Może być globalną funkcją – wyjątki

Natomiast następujące operatory nie mogą być
przeładowywane: ., .\*, ::, ?:

Dla każdej klasy następujące operatory są
generowane automatycznie: =, &(jednoargumentowy – pobranie adresu), new, , , delete

## Funkcja operatorowa jako funkcja składowa

-Jeżeli definiujemy składową funkcje operatorową to
przyjmuje ona zawsze o jeden mniej argument niż ta sam
funkcja napisana w postaci funkcji globalnej

-Funkcja ta nie może być typu static, bo w jej działaniu
bierze udział wskaźnik this

-Nie mogą istnieć dwie funkcje operatorowe pracujące na
tych samych argumentach (zdefiniowane jako funkcja
globalna i funkcja składowa)

-Funkcja operatorowa będąca funkcją składową
klasy wymaga, aby obiekt stojący po lewej stronie
operatora był obiektem tej klasy

```cpp
  Vector operator+(const Vector& other) const { }
```

const na końcu funkcji (czyli const { /_ ... _/ }) oznacza, że sama funkcja nie może modyfikować stanu obiektu, na którym jest wywołana (czyli obiektu, który znajduje się po lewej stronie operatora +). Innymi słowy, funkcja może odczytywać wartości składowych obiektu, ale nie może ich zmieniać.

Dlaczego to jest ważne?

-Bezpieczeństwo: Zapobiega przypadkowym modyfikacjom obiektów, co jest szczególnie istotne w przypadku przekazywania obiektów jako argumentów do funkcji.
-Optymalizacja: Kompilator może lepiej zoptymalizować kod, gdy wie, że funkcja nie modyfikuje stanu obiektu.
-Spójność: Używanie const tam, gdzie to możliwe, poprawia czytelność kodu i ułatwia zrozumienie jego działania.

## Funkcja operatorowa jako funkcja globalna

-Nie musi być funkcją zaprzyjaźnioną
-Jeżeli wymaga dostępu do zmiennych prywatnych
to musi być zaprzyjaźniona

```cpp
  friend Vector operator+(const Vector &v1, const Vector &v2);
```

# II Dziedziczenie

# III Funkcje wirtualne

# IV Dziedziczenie wielokrotne

# V Szablony funkcji i klas

# VI Wyjątki

# VII STL
