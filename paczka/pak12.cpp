int main()
{
  typedef /* UZUPEŁNIĆ */ kontener_typ;
  kontener_typ c;
  c.insert(Person("Nowak", "Jan"));
  c.insert(Person("Nowak", "Adam"));
  c.insert(Person("Kowalski", "Jan"));
  c.insert(Person("Nowak", "Adam"));
  c.insert(Person("Iksinski", "Adam"));
  std::copy(c.begin(), c.end(), /*UZUPEŁNIĆ*/);
}
Wynika działania : Iksinski Adam, Kowalski Jan, Nowak Adam, Nowak Jan