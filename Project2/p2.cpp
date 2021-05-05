#include <iostream>
#include "p2.h"
using namespace std;

int size(list_t list){
	return list_isEmpty(list) ? 0 : (1 + size(list_rest(list)));
}

bool memberOf(list_t list, int val){
	return list_isEmpty(list) ? false : (list_first(list) == val) || memberOf(list_rest(list), val);
}

int dot(list_t v1, list_t v2){
	return (list_isEmpty(v1) || list_isEmpty(v2)) ? false : list_first(v1) * list_first(v2) + dot(list_rest(v1), list_rest(v2));
}

bool isIncreasing(list_t v){
	return size(v) <= 1 ? true : list_first(v) <= list_first(list_rest(v)) && isIncreasing(list_rest(v));
}

static int list_last(list_t v){
	// return the last value of the list
	// list v should not be empty
	return size(v) == 1 ? list_first(v) : list_last(list_rest(v));
}

static list_t list_prior(list_t v){
	// return all but last of the list
	// list v should not be empty
	return size(v) == 1 ? list_make() : list_make(list_first(v), list_prior(list_rest(v)));
}

list_t reverse(list_t list){
	return list_isEmpty(list) ? list_make() : list_make(list_last(list), reverse(list_prior(list)));
}

list_t append(list_t first, list_t second){
	return list_isEmpty(first) ? second : append(list_prior(first), list_make(list_last(first), second));
}

bool isArithmeticSequence(list_t v){
	return size(v) <= 2 ? true : 
	(list_first(v) + list_first(list_rest(list_rest(v))) == 2 * list_first(list_rest(v)) && isArithmeticSequence(list_rest(v)));
}

list_t filter_odd(list_t list){
	return list_isEmpty(list) ? list_make() : (list_first(list) % 2 == 1 ? list_make(list_first(list), filter_odd(list_rest(list))) : filter_odd(list_rest(list)));
}

list_t filter(list_t list, bool (*fn)(int)){
	return list_isEmpty(list) ? list_make() : ( fn(list_first(list)) ? list_make(list_first(list), filter(list_rest(list), fn)) : filter(list_rest(list), fn));
}

// list_t unique_helper(list_t v){
// 	return list_isEmpty(v) ? list_make() : 
// 	(memberOf(list_rest(v), list_first(v)) ? unique_helper(list_rest(list_t list))  );
// }

list_t unique(list_t list){
	return list_isEmpty(list) ? list_make() : 
	( memberOf(list_prior(list), list_last(list)) ? unique(list_prior(list)) : append(unique(list_prior(list)), list_make(list_last(list), list_make() )));
	//return reverse( unique_helper( reverse(list) ) );
}


list_t insert_list(list_t first, list_t second, unsigned int n){
	return n == 0 ? append(second, first) : list_make(list_first(first), insert_list(list_rest(first), second, n - 1));
}

list_t chop(list_t list, unsigned int n){
	return n == 0 ? list : chop(list_prior(list), n - 1);
}

//************************************************************
//*********                                     **************
//*********            BINARY TREE              **************
//*********                                     **************
//************************************************************

int tree_sum(tree_t tree){
	return tree_isEmpty(tree) ? 0 : tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
}

bool tree_search(tree_t tree, int val){
	return tree_isEmpty(tree) ? false : tree_elt(tree) == val || tree_search(tree_left(tree), val) || tree_search(tree_right(tree), val);
}

int depth(tree_t tree){
	return tree_isEmpty(tree) ? 0 : 1 + ( depth(tree_left(tree)) >= depth(tree_right(tree)) ? depth(tree_left(tree)) : depth(tree_right(tree)) );
}

static int max(int a, int b){
	return a >=b ? a : b;
}

int tree_max(tree_t tree){
	if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree)))
		return tree_elt(tree);
	if (tree_isEmpty(tree_left(tree)))
		return max( tree_elt(tree), tree_max(tree_right(tree)) );
	if (tree_isEmpty(tree_right(tree)))
		return max( tree_elt(tree), tree_max(tree_left(tree)) );
	return max(tree_elt(tree), max( tree_max(tree_left(tree)), tree_max(tree_right(tree)) ));
}

list_t traversal(tree_t tree){
	return tree_isEmpty(tree) ? list_make() : append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
}

static bool mono_helper(tree_t tree, bool (*comp)(int, int)){
	return tree_isEmpty(tree_left(tree)) ? true : tree_isEmpty(tree_right(tree)) || 
		(mono_helper(tree_left(tree), comp) && comp(tree_elt(tree), tree_elt(tree_left(tree)))) || 
		(mono_helper(tree_right(tree), comp) && comp(tree_elt(tree), tree_elt(tree_right(tree))));
}

static bool larger(int a, int b){
	return a >= b;
}

static bool smaller(int a, int b){
	return a <= b;
}

bool tree_hasMonotonicPath(tree_t tree){
	return mono_helper(tree, larger) || mono_helper(tree, smaller);
}

bool tree_allPathSumGreater(tree_t tree, int sum){
	if (tree_isEmpty(tree)){
		return sum < 0 ? true : false;
	}
	return  
		(tree_allPathSumGreater(tree_left(tree), sum - tree_elt(tree)) && 
		 tree_allPathSumGreater(tree_right(tree), sum - tree_elt(tree)));
}

bool covered_by(tree_t A, tree_t B){
	if(tree_isEmpty(A))
		return true;
	if(tree_isEmpty(B))
		return false;
	return tree_elt(A) == tree_elt(B) && 
			covered_by(tree_left(A), tree_left(B)) &&
			covered_by(tree_right(A), tree_right(B));
}

bool contained_by(tree_t A, tree_t B){
	return covered_by(A, B) || 
	(!tree_isEmpty(B) && contained_by(A, tree_left(B)) ) || 
	(!tree_isEmpty(B) && contained_by(A, tree_right(B)) );
}

tree_t insert_tree(int elt, tree_t tree){
	if (tree_isEmpty(tree))
		return tree_make(elt, tree_make(), tree_make());
	return elt < tree_elt(tree) ? 
		tree_make(tree_elt(tree), insert_tree(elt, tree_left(tree)), tree_right(tree)) : 
		tree_make(tree_elt(tree), tree_left(tree), insert_tree(elt, tree_right(tree)));
}

