#include <iostream>
#include "p2.h"
using namespace std;

#include <vector>
list_t convenient(vector<int> v){
	list_t list = list_make();
	for(int i = v.size() - 1; i >= 0; i--){
		list = list_make(v[i], list);
	}
	return list;
}

int main(int argc, char const *argv[])
{
	vector<int> v = {1, 2, 3, 3, 5};
	list_t list1 = convenient(v);
	cout << "Size is "<< size(list1) << endl;
	int a = 2;
	list_print(list1);
	cout << "if contains" << a << "?(should be 1) " << memberOf(list1, a) << endl;
	a = 6;
	cout << "if contains" << a << "?(should be 0) " << memberOf(list1, a) << endl;
	v = {5, 2};
	list_t list2 = convenient(v);
	cout << "dot product is(should be 9) " << dot(list1, list2) << endl;
	list_print(list1);
	cout << "if increasng?(should be 1) " << isIncreasing(list1) << endl;
	list_print(list2);
	cout << "if increasng?(should be 0) " << isIncreasing(list2) << endl;
	cout << "if increasng?(should be 1) " << isIncreasing(list_make()) << endl;
	cout << "if increasng?(should be 1) " << isIncreasing(list_make(4, list_make())) << endl;
	list_print(reverse(list1));
	list_print(append(list1, list2)); cout << endl;

	v = {1, 3, 5, 7, 9};
	list_t list3 = convenient(v);
	list_print(list1);
	cout << " isArithmetic? " << isArithmeticSequence(list1) << endl;
	list_print(list3);
	cout << " isArithmetic? " << isArithmeticSequence(list3) << endl;
	v = {3, 4, 1, 5, 6};
	list_t list4 = convenient(v);
	list_print(list4);
	cout << " after filter_odd ";
	list_print(filter_odd(list4)); cout << endl;
	v = {1, 1, 2, 1, 3, 5, 5, 3, 4, 5, 4};
	list_t list5 = convenient(v);
	list_print(list5);
	cout << " after unique is ";
	list_print(unique(list5)); cout << endl;
	v = {1,2,3};
	list_t list_6 = convenient(v);
	v = {4,5,6};
	list_t list_7 = convenient(v);
	cout << "insert(( 1 2 3 ), ( 4 5 6 ), 2) gives ( 1 2 4 5 6 3 )" << endl << "now gives ";
	list_print(insert_list(list_6, list_7, 2)); cout << endl;
	cout << "after chop "; list_print(chop(list5, 8)); cout << endl;

	cout << "\n----- tree test starts ------" << endl;
	tree_t tree1 = tree_make(4, 
							tree_make(2, tree_make(), tree_make(3, 
																tree_make(), 
																tree_make())), 
							tree_make(5, tree_make(), tree_make()));
	cout << "tree is \n";
	tree_print(tree1);
	cout << "sum is " << tree_sum(tree1) << endl;
	cout << "search 3? " << tree_search(tree1, 3) << endl;
	cout << "depth is " << depth(tree1) << endl;
	cout << "max is " << tree_max(tree1) << endl;
	list_print(traversal(tree1)); cout << endl;
	cout << "mono? " << tree_hasMonotonicPath(tree1) << endl;
	cout << "largepathsum? " << tree_allPathSumGreater(tree1, -1) << endl;
	cout << "largepathsum? " << tree_allPathSumGreater(tree1, 6) << endl;
	tree_t tree2 = tree_make(4, 
								tree_make(2, tree_make(), tree_make()), 
								tree_make());
	tree_t tree3 = tree_make(4, 
								tree_make(3, tree_make(), tree_make()), 
								tree_make());
	cout << "cover by? " << covered_by(tree2, tree1) << endl;
	cout << "cover by? " << covered_by(tree3, tree1) << endl;
	tree_t tree4 = tree_make(5, tree_make(), tree_make());
	cout << "contained by? " << contained_by(tree4, tree1) << endl;
	cout << "contained by? " << contained_by(tree3, tree1) << endl;

	cout << "after insert \n"; tree_print(insert_tree(1, tree1)); cout << endl;
	return 0;
}





