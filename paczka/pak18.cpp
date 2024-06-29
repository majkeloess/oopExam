int main(int argc, char **argv)
{
  Para p[2] = {{21, 7}, {1, 2}};
  p[1].a = 4;
  p[1].b = 1;
  std::cout << "Para t[0] = " << p[0] << "\n";
  std::cout << "Para t[1] = " << p[1] << "\n";
  double d[2] = {p[0], p[1]};
  std::cout << "d = " << d[0] << ", " << d[1] << "\n";
}
