#include <iostream>
#include <string>
#include <map>
#include <mutex>
#include <future>

class Produkt {
public:
Produkt(){}
    Produkt(const std::string& nazwa, int ilosc, double cena)
        : nazwa_(nazwa), ilosc_(ilosc), cena_(cena) {}

    const std::string& getNazwa() const { return nazwa_; }
    int getIlosc() const { return ilosc_; }
    double getCena() const { return cena_; }

    void setIlosc(int ilosc) { ilosc_ = ilosc; }
    void setCena(double cena) { cena_ = cena; }

private:
    std::string nazwa_;
    int ilosc_;
    double cena_;
};

class Magazyn {
public:
    void dodajProdukt(const std::string& nazwa, int ilosc, double cena) {
        std::lock_guard<std::mutex> lock(mutex_);
        produkty_[nazwa] = Produkt(nazwa, ilosc, cena);
    }

    void usunProdukt(const std::string& nazwa) {
        std::lock_guard<std::mutex> lock(mutex_);
        produkty_.erase(nazwa);
    }

    void aktualizujProdukt(const std::string& nazwa, int ilosc, double cena) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = produkty_.find(nazwa);
        if (it != produkty_.end()) {
            it->second.setIlosc(ilosc);
            it->second.setCena(cena);
        }
    }

    void wyswietlProdukty() {
        std::lock_guard<std::mutex> lock(mutex_);
        for (const auto& para : produkty_) {
            std::cout << "Produkt: " << para.second.getNazwa()
                      << ", Ilosc: " << para.second.getIlosc()
                      << ", Cena: " << para.second.getCena() << std::endl;
        }
    }

private:
    std::map<std::string, Produkt> produkty_;
    std::mutex mutex_;
};

int main() {
    Magazyn magazyn;

    auto future1 = std::async(std::launch::async, [&]() {
        magazyn.dodajProdukt("Mleko", 10, 2.50);
    });

    auto future2 = std::async(std::launch::async, [&]() {
        magazyn.aktualizujProdukt("Mleko", 20, 2.75);
    });

    auto future3 = std::async(std::launch::async, [&]() {
        magazyn.usunProdukt("Mleko");
    });

    future1.get();
    future2.get();
    future3.get();

    magazyn.wyswietlProdukty();

    return 0;
}