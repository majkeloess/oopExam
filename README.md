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

-Nie musi być funkcją zaprzyjaźnioną ale wtedy korzystamy z getterów
-Jeżeli wymaga dostępu do zmiennych prywatnych
to musi być zaprzyjaźniona

```cpp
  friend Vector operator+(const Vector &v1, const Vector &v2);
```

## Operatory, które muszą być funkcjami składowymi

### Operator przypisania (copy) =

-Generowany automatyczne przez kompilator, tak że
przepisuje obiekt składnik po składniku
-Nie jest generowany automatycznie w sytuacjach:
◼ Jeżeli klasa ma składnik const
◼ Jeżeli klasa ma składnik będący referencją
◼ Jeżeli klasa ma składową klasę, w której operator przypisania
jest prywatny
◼ Jeżeli klasa ma klasę podstawową z prywatnym operatorem

```cpp
Point& Point::operator=(const Point& K)
{
        //sprawdzenie czy nie jest wywo�anie np: a = a;
        if(&K == this)
                return *this;

        *a = *K.a;
        *b = *K.b;

        // pozwala na wielokrotne wywo�anie operatora,
        // poniewa� zwaraca referencj� do obiektu
        // na rzecz kt�rego operator zosta� wywo�any
        return *this;
}

```

Czesc destrukturowa i konstrukturowa

```cpp
  // czeœæ destruktorowa
  delete a;
  delete b;

  // czeœæ konstruktorwa
  a = new double(*K.a);
  b = new double(*K.b);


```

Wykorzystując priv ctor i dtor

```cpp
class Point
{
public:
  friend int main();

  Point(double aa = 0, double bb = 0) : a(new double(aa)), b(new double(bb))
  {
  }
  Point(const Point &K)
  {
    ctor(K);
  }
  ~Point()
  {
    dtor();
  }
  Point &operator=(const Point &K)
  {
    // sprawdzenie czy nie jest wywo³anie np: a = a;
    if (&K == this)
      return *this;

    dtor();
    ctor(K);

    return *this;
  }

private:
  void ctor(const Point &p)
  {
    a = new double(*p.a);
    b = new double(*p.b);
  }

  void dtor()
  {
    delete a;
    delete b;
  }

  double *a;
  double *b;
};
```

### Operator przypisania (move) =

-Funkcja wywoływana jest kiedy pojawia się po lewej stronie =, a po jego prawe stoi
rvalue
-„Kradnie” zasoby obiektu stojącego po prawej stronie : np. dla std::string zostawia po prawej stronie obiekt pusty
-Generowana automatycznie w sytuacji kiedy:
❑ Nie ma konstruktora przenoszalnego (niedomyślnego)
❑ Nie ma kopiującego operatora=
❑ Nie ma destruktora
❑ Nie ma konstruktora kopiującego (niedomyślnego)
❑ Generowany jest wtedy publiczny i inline T& T::operator=(T&&)
-Jeżeli jest „trywialny” wykorzystuje do przenoszenia std::memmove

```cpp
  A &operator=(const A &other) {
    s = other.s;
    std::cout << "copy assigned\n";
    return *this;
  }
  A &operator=(A &&other) {
    s = std::move(other.s);
    std::cout << "move assigned\n";
    return *this;
  }
```

WAŻNE!

```cpp
struct A {
  std::string s {"test"};
  A() = default;
  A(const A &o) : s(o.s) { std::cout << "move failed, copying!\n"; }
  A(A &&o) : s(std::move(o.s)) { std::cout << "moving!\n"; }
  A &operator=(const A &other) {
    s = other.s;
    std::cout << "copy assigned\n";
    return *this;
  }
  A &operator=(A &&other) {
    s = std::move(other.s);
    std::cout << "move assigned\n";
    return *this;
  }
};
//Posiada move i copy assignment, move i copy ctor zdefiniowany przez użytkownika

A f() { return A{}; }
//Tworzy i zwraca obiekt tymczasowy typu A.

struct B : A {
  std::string s2;
  int n;

};
//Dziedziczy po A, Domyślny operator przenoszący B najpierw wywoła operator przenoszący klasy bazowej A, aby przenieść składową s z obiektu źródłowego do obiektu docelowego. A s2 jest przenoszone operatorem przenoszącym std::string

struct C : B {
  ~C() {}
};
//Dziedziczy po B. Ma zdefiniowany destruktor, co uniemożliwia kompilatorowi automatyczne generowanie operatora przypisania przenoszącego.

struct D : B {
  D() {}
  ~D() {}
  D &operator=(D &&) = default;
};
//Dziedziczy po B. Ma zdefiniowany konstruktor domyślny i destruktor, co normalnie uniemożliwiłoby automatyczne generowanie operatora przypisania przenoszącego. D &operator=(D &&) = default; Wyraźnie żądamy, aby kompilator wygenerował domyślny operator przypisania przenoszącego, pomimo istnienia destruktora.
```

### Operator []

Przeładowany operator [] powinien mieć działanie podobne do działania w stosunku do typów wbudowanych. Z tego powodu powinien być zadeklarowany klasa& klasa::operator[](unsigned i);
czyli zwracać referencję do pojedynczego elementu tablicy o indeksie i.

Możliwe będzie wtedy wykonanie:

```cpp
a = tab[i];
tab[i] = a;
```

```cpp
  double &operator[](unsigned i)
  {
    if (i >= m_size)
    {
      double * ptr;
      unsigned new_size = i + 1;
      ptr = new double[new_size];

      for (unsigned k = 0; k < m_size; ++k)
        ptr[k] = m_ptr[k];

      for (unsigned k = m_size; k < new_size; ++k)
        ptr[k] = 0.0;

      m_size = new_size;
      delete[] m_ptr;
      m_ptr = ptr;
    }

    return m_ptr[i];
  }
// Służy do odczytu i zapisu elementów tablicy.
  const double &operator[](unsigned i) const
  {
    return i >= m_size ? m_ptr[m_size - 1] : m_ptr[i];
  }
//Służy do zapisu elementów tablicy
// Pierwsze const: Odnosi się do typu zwracanego (const double &). Oznacza to, że metoda zwraca referencję do stałej wartości double. Dzięki temu nie można modyfikować elementu tablicy przez zwróconą referencję.
//Drugie const: Jest umieszczone na końcu sygnatury metody (const). Oznacza to, że metoda nie modyfikuje stanu obiektu, na którym jest wywołana.
```

### Operator ()

-Może przyjmować dowolną liczbę parametrów
-Może posłużyć do indeksowanie wielowymiarowych tablic
-Może też upraszczać zapis, nie musimy wywoływać funkcji tylko wystarczy sam operator ()
-Bardzo przydatny operator przy wykorzystaniu funktorów zalgorytmami STL

```cpp
class Matrix
{
private:
    double m_data[4][4]{};

public:
    double& operator()(int row, int col);
    double operator()(int row, int col) const; // for const objects
};

double& Matrix::operator()(int row, int col)
{
    assert(row >= 0 && row < 4);
    assert(col >= 0 && col < 4);

    return m_data[row][col];
}

double Matrix::operator()(int row, int col) const
{
    assert(row >= 0 && row < 4);
    assert(col >= 0 && col < 4);

    return m_data[row][col];
}
```

```cpp
#include <iostream>

class Accumulator
{
private:
    int m_counter{ 0 };

public:
    int operator() (int i) { return (m_counter += i); }

    void reset() { m_counter = 0; } // optional
};

int main()
{
    Accumulator acc{};
    std::cout << acc(1) << '\n'; // prints 1
    std::cout << acc(3) << '\n'; // prints 4

    Accumulator acc2{};
    std::cout << acc2(10) << '\n'; // prints 10
    std::cout << acc2(20) << '\n'; // prints 30

    return 0;
}
```
  //TODO przykłady

### Operator ->

-Rzadko używany
-Przydaje się gdy piszemy klasę, której obiekty pełnią rolę podobną do wskaźników
-Wykorzystany między innymi przy tworzeniu klasy unique_ptr z STL-a

### Operatory pre i post ++ --
  //TODO
## Operatory << i >>

-Przy przeładowywaniu tych operatorów w stosunkudo klasy iostream możemy je zdefiniować tylko jako globalne funkcje
-Funkcja operatorowa musi pracować na zmiennych lub metodach globalnych
-Ewentualnie musi być zaprzyjaźniona z naszą klasą, jeżeli ma pracować na zmiennych
prywatnych

## Operatory new i delete
  //TODO

## Dodatkowe informacje z działu

W C++, struktury (podobnie jak klasy) mogą dziedziczyć po innych strukturach (lub klasach). Robi się to za pomocą słowa kluczowego : i określenia trybu dostępu (publiczne, chronione lub prywatne). Domyślnym trybem dostępu dla struktur jest publiczny, co oznacza, że wszystkie publiczne składowe klasy bazowej stają się publicznymi składowymi klasy pochodnej.

Defaultowy konstruktor to konstruktor, który nie przyjmuje żadnych argumentów. Jest on automatycznie generowany przez kompilator, jeśli nie zdefiniujesz żadnego innego konstruktora. Jednakże, jeśli zdefiniujesz choćby jeden konstruktor (np. przyjmujący argumenty), to kompilator przestaje generować domyślny konstruktor. Definiowanie default konstruktora przydaje się gdy chcemy zainicjalizować obiekt

W strukturach można używać public, private, protected

Cecha Struktura(struct) Klasa (class)
Domyślny dostęp Publiczny Prywatny
Domyślny tryb dziedziczenia Publiczny Prywatny
Typowe zastosowanie Przechowywanie danych Modelowanie obiektów

Słowo kluczowe noexcept w konstruktorze przenoszącym (move constructor) i operatorze przypisania przenoszącego (move assignment operator) służy do informowania kompilatora.
Kompilator może dokonać agresywniejszych optymalizacji kodu, wiedząc, że funkcja nie zgłosi wyjątku. Może to prowadzić do szybszego wykonania kodu.

std::assert to makro w C++, które służy do sprawdzania poprawności założeń w kodzie podczas jego wykonywania. Działa ono w następujący sposób: sprawdza warunek jeżeli jest fałszywy wywołuje std::abort() i kończy program oraz wypisuje numer linii

# II Dziedziczenie

-Dziedziczenie to technika umożliwiająca zdefiniowanie nowej klasy z wykorzystaniem klasy już istniejącej
-Nowa klasa staje się automatycznie nowym typem danych
-Klasę z której dziedziczymy nazywamy klasą bazową lub podstawową
-Klasa która odziedzicza składniki i metody po innej klasie nazywana jest klasą pochodną
  //TODO

## Dodatkowe informacje z działu

# III Funkcje wirtualne

## Dodatkowe informacje z działu

# IV Dziedziczenie wielokrotne

## Dodatkowe informacje z działu

# V Szablony funkcji i klas

## Dodatkowe informacje z działu

# VI Wyjątki

## Dodatkowe informacje z działu

# VII STL

## Dodatkowe informacje z działu

# VIII std::vector, std::array




## Dodatkowe informacje z działu

push_back: dodaje istniejący obiekt do wektora, potencjalnie go kopiując lub przenosząc.
emplace_back: konstruuje obiekt bezpośrednio w wektorze, unikając kopiowania/przenoszenia.
Zasada ogólna: Używaj emplace_back, chyba że masz już istniejący obiekt do dodania.