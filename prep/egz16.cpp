struct Obj;
template <typename T>
struct Box;

/* uzupe�nij 1*/

int main()
{

  Box<int>{3} b_i;
  Obj &r_1 = b_i;
  r_1.Draw();
  int i = b_i;
  Box<double>{3.4} b_d;
  Obj &r_2 = b_d;
  r_2.Draw();
  double d = b_d;
  Box<Box<int>>{3} bb_i;
  const Obj &r_3 = bb_i;
  r_3.Draw();
  Box<int> b_i = bb_i;
  Box<Box<double>>{3.4} bb_d;
  const Obj &r_4 = bb_d;
  r_4.Draw();
  Box<double> b_d = bb_d;

  // Box<int> _ = 3; Odkomentowanie powoduje b��d kompilacji
}
/* standardowe wyj�cie:
struct Box<int>::Draw() --> 3
struct Box<double>::Draw() --> 3.4
struct Box<Box<int>>::Draw() --> 3
struct Box<Box<double>>::Draw() --> 3.4