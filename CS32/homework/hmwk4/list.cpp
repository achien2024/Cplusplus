// Aaron Chien
// 405498016
void listAll(const MenuItem* m, string path) // two-parameter overload
{
  if (m == nullptr)
  {
    return;
  }
  string n_path;
  if (path.empty())
  {
    n_path = m->name();
  }
  else
  {
    n_path = path + "/" + m->name();
  }
  
  if (!n_path.empty())
    cout << n_path << endl;

  if (m->menuItems() == nullptr)
  {
    return;
  }
	for (vector<MenuItem*>::const_iterator it = m->menuItems()->begin(); it != m->menuItems()->end(); it++)
	  listAll(*it, n_path);
}