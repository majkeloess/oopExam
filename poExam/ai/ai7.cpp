int main()
{
  const Shape *s1 = new Circle(5);
  Shape *s2 = new Rectangle(4, 6);

  std::cout << "s1 area: " << s1->area() << std::endl;
  std::cout << "s2 area: " << s2->area() << std::endl;

  s1->print();
  s2->print();

  delete s1;
  delete s2;

  std::vector<Shape *> shapes;
  shapes.push_back(new Circle(3));
  shapes.push_back(new Rectangle(2, 2));

  for (const auto &shape : shapes)
  {
    shape->print();
    std::cout << "Area: " << shape->area() << std::endl;
  }

  for (auto &shape : shapes)
  {
    delete shape;
  }

  // Circle c = *s1; // Odkomentowanie powinno powodować błąd kompilacji

  return 0;
}

/* Oczekiwany output:
s1 area: 78.5398
s2 area: 24
Circle with radius 5
Rectangle with width 4 and height 6
Circle with radius 3
Area: 28.2743
Rectangle with width 2 and height 2
Area: 4
*/