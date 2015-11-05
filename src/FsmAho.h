#include <vector>
class FsmAho {
  public:
	std::vector< std::vector<int> > occ ;
	std::vector<int> f;
	std::vector<std::vector<int> > g; 
};