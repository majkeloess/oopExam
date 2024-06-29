/*uzupelnij*/
int main()
{
  // tu stworzone zostaly obiekty normal_order i reverse_order, ale nie pamietam jak to dokladnie
  wygladalo typedef /*uzupelnij*/ kontener_typ;
  kontener_typ c(normal_order);
  // tu byl kod ktory wstawial jakies 4 trzy-literowe stringi do c uzywajac insert
  copy(c.begin(), c.end(), std::ostream_iterator<std::string>(std::cout, ", "));
  kontener_typ d(reverse_order);
  // tu byl jakis kod
  copy(c.begin(), c.end(), /*uzupelnij*/);
  copy(d.begin(), d.end(), std::ostream_iterator<std::string>(std::cout, ", "));
  // tu byl jakis kod
}