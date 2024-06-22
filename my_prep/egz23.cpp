int main()
{
  std::vector<Object *> objs;
  ConsoleObject *console0 = new ConsoleLine();
  ConsoleObject *console1 = new ConsoleText();
  GuiObject *gui0 = new GuiLine();
  GuiObject *gui1 = new GuiText();

  objs.push_back(console0);
  objs.push_back(console1);
  objs.push_back(gui0);
  objs.push_back(gui1);

  for (unsigned i = 0; i != objs.size(); i++)
    cout << objs[i]->print(",");
}