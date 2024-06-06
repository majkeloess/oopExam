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

Czesc destrukturowa i konstrukturowa:

```cpp
  // czeœæ destruktorowa
  delete a;
  delete b;

  // czeœæ konstruktorwa
  a = new double(*K.a);
  b = new double(*K.b);


```

Wykorzystując priv ctor i dtor:

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

```cpp
int main() {

	std::vector<std::function<void(int)>> vec;
	std::vector<std::function<void()>> vec2;

	vec.emplace_back(F1());
	vec.emplace_back(F2());
	vec.emplace_back(F3());

//emplace_back: Dodaje elementy do wektora.
//F1(), F2(), F3(): Tworzone są tymczasowe obiekty struktur (funktory), które są od razu dodawane do wektora vec.
	int i = 0;
	for(auto& el : vec) {
		el(++i);
		vec2.emplace_back(std::bind(el, i));
	}
//std::bind(el, i): Tworzymy nowy obiekt funkcyjny (binder) za pomocą funkcji std::bind. Ten binder "zapamiętuje" funkcję el oraz aktualną wartość i. Gdy binder zostanie wywołany później, automatycznie wywoła funkcję el z zapamiętaną wartością i
	vec2.push_back(F4());
	vec2.emplace_back(F5());
	for(auto& el : vec2)
		el();

}

```

Functional z refem:

```cpp
operator int() {
    return sum;
}
//Ten operator jest wywoływany niejawnie (automatycznie) przez kompilator w sytuacjach, gdy oczekuje się wartości typu int, a podawany jest obiekt typu Sum.
//Przekształca obiekt typu suma na int, żeby nie trzeba było przeładowywać <<

int main()
{

	Sum s{10};
	std::cout << "Suma = " << s << std::endl;

	for (int i = 0; i < 5; ++i)	{
		s(i);
		std::cout << "Suma = " << s << std::endl;
	}

	{
		std::function<void(int)> f_s = s;
		f_s(100);
		std::cout << "Suma f_s = " << s << std::endl;
	}
	{
		std::function<void(int)> f_s = std::ref(s);
		f_s(100);
		std::cout << "Suma std::ref f_s = " << s << std::endl;
	}
}
//Pierwszy blok {}:
//std::function<void(int)> f_s = s;: Tworzy obiekt f_s typu std::function, który przechowuje kopię obiektu s.
//f_s(100);: Wywołuje funkcję f_s (czyli kopię s), dodając 100 do sumy kopii.
//std::cout << "Suma f_s = " << s << std::endl;: Wyświetla wartość s. Ponieważ f_s była kopią, wartość oryginalnego s pozostaje niezmieniona.

//Drugi blok {}:
//std::function<void(int)> f_s = std::ref(s);: Tworzy obiekt f_s typu std::function, który przechowuje referencję do obiektu s.
//f_s(100);: Wywołuje funkcję f_s (czyli referencję do s), dodając 100 do oryginalnej sumy w s.
//std::cout << "Suma std::ref f_s = " << s << std::endl;: Wyświetla wartość s, która teraz jest zwiększona o 100.

```

### Operator ->

-Rzadko używany

-Przydaje się gdy piszemy klasę, której obiekty pełnią rolę podobną do wskaźników

-Wykorzystany między innymi przy tworzeniu klasy unique_ptr z STL-a

```cpp
class WskaznikInteligentny {
public:
    WskaznikInteligentny(int* ptr) : ptr_(ptr) {}

    int* operator->() {
        std::cout << "Operator -> wywołany\n";
        return ptr_;
    }

private:
    int* ptr_;
};

int main() {
    int liczba = 42;
    WskaznikInteligentny sprytnyWskaznik(&liczba);

    std::cout << sprytnyWskaznik->operator->(); // Wypisze "Operator -> wywołany\n42"
}

//Wyrażenie sprytnyWskaznik->operator->() jest równoważne sprytnyWskaznik->(), co wywołuje przeciążony operator ->.
//Operator zwraca wskaźnik do liczba, który jest następnie używany do wypisania wartości 42.

```

### Operatory pre i post ++ --

Argument int w operatorach postinkrementacji i postdekrementacji jest jedynie sztuczką składniową, która pozwala kompilatorowi odróżnić je od operatorów preinkrementacji i predekrementacji. Ten argument jest zwykle ignorowany wewnątrz funkcji.

Obiekty tymczasowe są tworzone w operatorach postinkrementacji i postdekrementacji, aby zachować semantykę tych operatorów. Operator postinkrementacji (x++) powinien: zwrócić oryginalną wartość zmiennej x i zwiększyć wartość zmiennej x o jeden.

```cpp

//jako składowe

Point& operator++() {
    ++_a; ++_b;
    return *this;
  }


//w post jest tworzony obiekt tymczasowy
  Point operator++(int){
    Point tmp = *this;
    ++_a; ++_b;
    return tmp;
  }

//jako globalne

Point& operator--(Point& K)
{ --K._a; --K._b; return K; }

Point operator--(Point& K, int)
{ Point tmp = K;  --K._a; --K._b; return tmp; }

```

## Operatory << i >>

-Przy przeładowywaniu tych operatorów w stosunkudo klasy iostream możemy je zdefiniować tylko
jako globalne funkcje

-Funkcja operatorowa musi pracować na zmiennych lub metodach globalnych

-Ewentualnie musi być zaprzyjaźniona z naszą klasą, jeżeli ma pracować na zmiennych
prywatnych

## Operatory new i delete

W stosunku do klas funkcje przeładowujące te operatory są zawsze typu static, nawet jeśli tego nie zadeklarujemy.

Przydają się kiedy chcemy uzyskać jakąś dodatkową funkcjonalność np. statystykę.

Tworzymy obiekty w predefiniowanej wcześniej pamięci.

Używamy niestandardowej biblioteki do tworzenia nowych obiektów.

```cpp
void* operator new(std::size_t sz) {
    std::cout << "global op new called, size = " << sz << std::endl;
    return std::malloc(sz);
}
void operator delete(void* ptr) noexcept //c++11
{
    std::cout << "global op delete called" << std::endl;
    std::free(ptr);
}
//W kodzie, który przedstawiłeś, przeładowany jest jedynie globalny operator new, a nie new[]. Pomimo tego, kod działa poprawnie dla tablic int. Wynika to z faktu, że standardowa implementacja operatora new[] wewnętrznie wywołuje operator new, aby zaalokować odpowiednią ilość pamięci dla tablicy.

int main()
{
	int* p2 = new int[10];
	delete [] p2;

	std::vector<char> v(1213);
}
//global op new called, size = 40
//global op delete called
//global op new called, size = 1213
//global op delete called


```

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

Słowo kluczowe inline jest wskazówką dla kompilatora, że funkcja powinna być w miarę możliwości wstawiana bezpośrednio w miejscu wywołania, zamiast być wywoływana przez zwykły mechanizm wywołania funkcji. To może przynieść korzyści w wydajności, zwłaszcza dla małych, często wywoływanych funkcji, takich jak operator konwersji. Decyzja o tym, czy funkcja zostanie faktycznie wstawiona inline, należy do kompilatora. Może on zignorować wskazówkę inline, jeśli uzna to za bardziej optymalne (np. dla dużych funkcji).

# II Dziedziczenie

-Dziedziczenie to technika umożliwiająca zdefiniowanie nowej klasy z wykorzystaniem klasy już istniejącej

Nowa klasa staje się automatycznie nowym typem danych

Klasę z której dziedziczymy nazywamy klasą bazową lub podstawową

Klasa która odziedzicza składniki i metody po innej klasie nazywana jest klasą pochodną

Przy dziedziczenia public (class Nowa : public Baza) odziedziczone składniki public i protected pozostają takie niezmienione.

Przy dziedziczenia protected (class Nowa :protected Baza) odziedziczone składniki zarówno public i protected stają się protected

Przy dziedziczenia private (class Nowa : private Baza) odziedziczone składniki staję się prywatną własnością klasy pochodnej ,domyślnie (bez podania sposobu) dziedziczenie jest
prywatne dla klas

Jeżeli dziedziczymy dane pola prywatnie możemy za pomocą using zmienić ich dostęp na publicznym jest to tzw deklaracja dostępu:

```cpp
class Rec : Shape
{
public:
  using Shape::SetX; //c++11
  using Shape::SetY;
};

```

Elementy niedziedziczone:

1. Konstruktory
2. Operator przypisania (=)
3. Destruktor

W klasie pochodnej w pewnym sensie tkwi klasa
podstawowa. Tworzenie klasy pochodnej to dobudowywanie
elementów do klasy podstawowej. Do pracy najpierw rusza konstruktor klasy
podstawowej, a dopiero potem klasy pochodnej.

Konstruktory klasy pochodnej tworzy się w znany już sposób. Należy pamiętać, że na liście inicjalizacyjnej konstruktora
klasy pochodnej trzeba umieść konstruktor klasy
podstawowej chyba, że:

1. Klasa podstawowa nie ma żadnego konstruktora
2. Ma konstruktory, a wśród nich jest konstruktor domyślny

Na liście inicjalizacyjnej umieszcza się tylko konstruktory klas
podstawowych bezpośrednich, czyli znajdujących się o jeden poziom
wyżej w hierarchii.

Tak jak przy zwykłej klasie nie ma sensu definiować
operatora przypisania jeżeli zostanie on
wygenerowany przez kompilator i będzie działał
dobrze.

Jeżeli nie zdefiniujemy konstruktora kopiującego to klasa
pochodna wygeneruje go sobie sama.

Jeżeli nie ma faktycznej potrzeby to nie definiujemy tego
konstruktora, pozwalamy kompilatorowi na automatyczną
jego generację.

# III Funkcje wirtualne

## Konwersje standardowe przy dziedziczeniu

Chodzi o to, że w C++, gdy mamy do czynienia z dziedziczeniem klas, możemy w pewnych sytuacjach automatycznie (niejawnie) konwertować wskaźniki lub referencje obiektów klasy pochodnej na wskaźniki lub referencje obiektów klasy bazowej.

Kiedy to działa?

Dziedziczenie publiczne: Konwersja działa tylko wtedy, gdy klasa pochodna dziedziczy publicznie po klasie bazowej.
Dostępność jednoznaczna: Klasa bazowa musi być dostępna jednoznacznie, czyli nie może być sytuacji, w której klasa pochodna dziedziczy po kilku klasach bazowych o tej samej nazwie.

```cpp

class Zwierze {};
class Pies : public Zwierze {};

Pies* pies = new Pies();
Zwierze* zwierze = pies; // Niejawna konwersja Pies* -> Zwierze*


void nakarm(Zwierze& zwierze) { /* ... */ }

Pies pies;
nakarm(pies); // Niejawna konwersja Pies& -> Zwierze&


```

## Funkcje wirtualne

Realizacja klas podstawowych i pochodnych w
zasadzie jest taka sama ale pojawia się słowo virtual przy nazwach funkcji
składowych (niekoniecznie wszystkich), które umożliwia
wykonywanie różnych funkcji w zależności od typu
obiektu na rzecz, którego chcemy taką funkcję wywołać, wykorzystanie funkcji wirtualnych może w znakomity sposób ułatwić i uprościć nam pracę na projektem.

Możliwe jest ustawienie wskaźnika (referencji) typu klasy
podstawowej tak, żeby pokazywał na obiekt klasy
pochodnej, wynika to z uogólnienia tzn. klasa pochodna jest
szczególnym (bardziej wyspecjalizowanym) typem klasy
podstawowej. Np. mając wskaźnik do pojazdów możemy nim pokazywać na
samochód lub nawet na „malucha” i nie jest to niezgodne z naszym
wyobrażeniem o rzeczywistości (samochód jest rodzajem
pojazdu). Sytuacja odwrotna nie jest już prawdziwa.

## Różnica między funkcją wirtualną, a zwykłą

Niewirtualnej (zwykłej) spowoduje wywołanie odpowiedniej funkcji
składowej w klasie podstawowej – zupełnie normalna sytuacja.

Wirtualnej spowoduje wywołanie odpowiedniej funkcji składowej
uzależnionej od typu obiektu, na który w danym momencie pokazuje
wskaźnik.

Dodanie przymiotnika virtual przy funkcji składowej w klasie
podstawowej mówi, że od tego momentu wszystkie dalsze
pokolenia będą tą funkcję mieć wirtualną, Tylko wtedy kiedy taka funkcja jest identyczna tzn. posiada taką samą nazwę, przyjmuje takie same parametry oraz zwraca taki sam typ.

## Polimorfizm

Polimorfizm – wielość form. Jest to wykazywanie przez metodę różnych form
działania w zależności od tego jaki typ obiektu
aktualnie jest wskazywany przez wskaźnik lub
referencję. Sama funkcja wirtualna polimorfizmu nie wykazuje, funkcja nie jest polimorficzna, ale tylko jej wywołanie jest.

W tym konkretnym kodzie, wirtualny destruktor (virtual ~Shape()) w klasie bazowej Shape jest użyty głównie z myślą o poprawnej obsłudze polimorfizmu i uniknięciu potencjalnych problemów z wyciekiem pamięci.

Polimorfizm i usuwanie obiektów: Gdy używasz wskaźników lub referencji do klasy bazowej (Shape) do przechowywania obiektów klas pochodnych (np. Circ), wirtualny destruktor zapewnia, że przy usuwaniu takiego obiektu zostanie wywołany poprawny destruktor (z klasy pochodnej). Bez wirtualnego destruktora, zostałby wywołany tylko destruktor klasy bazowej, co mogłoby prowadzić do niepełnego zwalniania zasobów, a w konsekwencji do wycieków pamięci.

Bezpieczeństwo i rozszerzalność: Nawet jeśli w tej chwili klasa Shape nie ma żadnych zasobów do zwolnienia (np. zaalokowanej dynamicznie pamięci), dodanie wirtualnego destruktora jest dobrą praktyką programistyczną. Jeśli w przyszłości zdecydujesz się rozszerzyć klasę Shape o nowe składowe, które wymagają zwalniania zasobów, wirtualny destruktor będzie już na swoim miejscu i zapewni prawidłowe działanie.

```cpp
//Shape:
class Shape
{
public:
	Shape(double x = 0, double y = 0) : m_x(x), m_y(y)
	{}
	virtual ~Shape()
	{}
	double GetX() const;
	double GetY() const;
	void SetX(double x);
	void SetY(double y);

	virtual void Rys() const
	{ std::cout << "Nie wiem jak!\n"; }
	virtual double Pole() const
	{ return 0.0; }

protected:
	double m_x, m_y;
};

//Circle:
class Circ : public Shape
{
public:
	Circ(double x = 0, double y = 0, double rad = 1) : Shape(x, y), m_rad(rad)
	{}
	double Pole() const override;
	void Rys() const override;

protected:
	double m_rad;
};

```

## Pożytek z polimorfizmu

Program jest rozszerzalny o nowe obiekty (typy), a ich
dodanie nie wymaga zmian w już istniejącym kodzie, W szczególności w miejscach, gdzie decyduje się jakiej klasy jest obiekt pokazywany przez wskaźnik lub nazywany referencją.

## Early and late binding

Wczesne wiązanie następuje w sytuacji kiedy wywoływane są
zwykłe funkcje i na etapie kompilacji wywołania funkcji powiązane
zostają z adresami, pod którymi te funkcje się znajdują, inaczej wiązanie w trakcie kompilacji.

Późne wiązanie występuje w sytuacji kiedy posługujemy się
funkcjami wirtualnymi. Kiedy kompilator widzi funkcję wirtualną
to nie podstawia określonego adresu, ale generuje odpowiedni
kod pozwalający na wybór określonej wersji funkcji na etapie
wykonania programu

W wywołaniu funkcji wirtualnych może wystąpić wczesne
wiązanie jeżeli już na etapie kompilacji wiadomo dokładnie, która
wersja funkcji ma zostać wywołana

## Klasy abstrakcyjne

Klasa abstrakcyjna to taka klasa, która nie
reprezentuje żadnego konkretnego obiektu. Np. pojazd, figura geometryczna itp...

Takie klasy tworzy się, aby po nich dziedziczyć. W pewnym sensie są to niedokończone klasy. Tworzymy funkcje wirtualne, których będziemy
używać, ale implementacje tych funkcji
pozostawiamy klasom pochodnym. Np. w klasie figura, powinna znaleźć się funkcja rysuj,
mimo iż jeszcze nie wiadomo jak taką figurę narysować

## Funkcje czysto wirtualne

Funkcje czysto wirtualne mają ścisły związek z klasami
abstrakcyjnymi, skoro nie ma sensu tworzyć obiektów klasy abstrakcyjnej
to dla przykładowej funkcji rysuj nie jest potrzebna
implementacja w klasie podstawowej.

Deklaracja funkcji czysto wirtualnej:

```cpp
  virtual void rysuj() = 0;
```

Dopóki klasa ma chociaż jedną funkcje czysto wirtualną to
NIE MOŻNA stworzyć żadnego obiektu takiej klasy

Brak możliwości stworzenie obiektu klasy
abstrakcyjnej z funkcją czysto wirtualną odnosi
się do wszystkich sytuacji:

```cpp
	//Nie mo�na stworzy� obiektu klasy abstrakcyjnej
	// Shape aShape;
	Rec aRec;
	Circ aCirc;

	//mo�emy u�y� referencji
	Shape& RefShape = aCirc;
	//mo�emy u�y� wskaznika
	Shape* Shape;
```

## Wirtualny destruktor

Jeżeli klasa ma być klasą bazową to zawsze powinna
deklarować destruktor jako wirtualny

```cpp
	virtual ~Shape()
	{}
```

## C++11 override i final

Chcąc wymusić sprawdzenie czy funkcja, którą deklarujemy przesłania
metodę wirtualną z klasy bazowej należy użyć słowa override

Z drugiej strony czasami istnieje potrzeba aby zagwarantować aby
wirtualna metoda nie była przesłaniana w klasach pochodnych, wtedy używa się final

Podobnie można sobie wyobrazić że klasa ma sam nie pozawalać aby po
niej dziedziczyć, wtedy do definicji klasy dodajemy słowo final

```cpp
struct Base {
  virtual void foo() const
  {}
};

struct A : Base {
  void foo() const final
  {}

  // void bar() final; // Error: bar is non-virtual
};

struct B final : A {
  // void foo() const override; //Error: A:foo is final
};

struct C //: B  // Error: B is final
{

};

int main(int argc, char *argv[]) {
	A a;
	B b;
  C c;
}


```

## Konwersje jawne

Podczas wykorzystywania polimorfizmu możemy natrafić na
pewien problem: posługując się obiektem za pomocą uogólnienia nie znamy jego
rzeczywistego typu, w niektórych sytuacjach potrzebna nam jest dokładana
informacja o faktycznym typie obiektu.

W C++ możemy jednak odzyskać informację o typie
obiektu za pomocą mechanizmu RTTI (run-time type
information), spróbować przekształcić obiekt na jego rzeczywisty typ
korzystając z rzutowania

## Rzutowanie dynamic_cast

Posługując się operatorem rzutowania dynamic_cast
możemy przywrócić obiektowi jego rzeczywisty typ

```cpp
  RecLbl(const std::string& s) : RecLbl()  // Delegacja do konstruktora bezargumentowego
  {
      m_ptrOpis = s;
  }
```

## Zapytanie o typ

Za pomocą operatora typeid możemy ustalić typ obiektu
podczas wykonania programu, musimy dołączyć nagłówek typeinfo

```cpp
  cout << typeid(obj).name();
  if(typeid(obj) == typeid(Klasa))
```

Operator typeid zwraca obiekt std::type_info, dla
którego zdefiniowane są między innymi:

1. Funkcja name() – zwraca nazwę klasy (dokładna postać zależy
   od implementacji)
2. Operatory == i != pozwalające na porównanie dwóch typów

## Mechanizm RTTI i projektowanie klas

1. Mechanizm RTTI należy używać z rozwagą (w
   szczególności typeid)
2. Używanie tego mechanizmu sprzyja tworzeniu
   nieprawidłowo zaprojektowanego kodu, dlatego należy go
   unikać
3. Jeżeli tylko jest możliwe to należy używać funkcji
   wirtualnych i projektować klasy tak, żeby możliwe było
   wywołanie odpowiedniej funkcji składowej
4. W szczególnym przypadku możemy posłużyć się
   rzutowaniem dynamic_cast

```cpp
#include <iostream>
#include <typeinfo>

class Zwierze {
public:
    virtual void dajGlos() const { std::cout << "Zwierzęcy dźwięk\n"; }
};

class Pies : public Zwierze {
public:
    void dajGlos() const override { std::cout << "Hau hau!\n"; }
};

class Kot : public Zwierze {
public:
    void dajGlos() const override { std::cout << "Miau!\n"; }
};

int main() {
    Zwierze *zwierze1 = new Pies();
    Zwierze *zwierze2 = new Kot();

    // Użycie typeid do sprawdzenia typu
    std::cout << "Typ zwierze1: " << typeid(*zwierze1).name() << std::endl; // Pies
    std::cout << "Typ zwierze2: " << typeid(*zwierze2).name() << std::endl; // Kot

    // Użycie dynamic_cast do rzutowania
    Pies* pies = dynamic_cast<Pies*>(zwierze1);
    if (pies) {
        pies->dajGlos(); // Hau hau!
    }

    Kot* kot = dynamic_cast<Kot*>(zwierze2);
    if (kot) {
        kot->dajGlos(); // Miau!
    }

    delete zwierze1;
    delete zwierze2;

    return 0;
}

```

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
