#include <iostream>
#include <map>

template <typename FIRST, typename SECOND>
class MapNode
{
private:
public:
  FIRST first;
  SECOND second;
  MapNode() {}
  MapNode(SECOND _second, FIRST _first) : second(_second), first(_first) {}
  ~MapNode(SECOND _second, FIRST _first) {}
};

template <typename KEY, typename VALUE>
class Map
{
};

int main(int argc, char *argv[])
{
  std::map<int, int> map;
}