#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Concatenates two lists together such at list B occurs after list A and returns the result
vector<int> cat(vector<int> A, vector<int> B) {
  if (B.size() == 0) return A;
  for (int i = 0; i < B.size(); i++) {
    A.push_back(B[i]);
  }
  return A;
}

// Returns A[i:j], that is the slice of A from index i to index j-1
vector<int> slice(vector<int> A, int i, int j) {
  vector<int> ret;
  if (j - i <= 0) return A;
  for (int k = i; k < j; k++) ret.push_back(A[k]);
  return ret;
}

// Returns the sorted version of list A
vector<int> sort(vector<int> A) {
  sort(A.begin(), A.end());
  return A;
}

// Returns a list of all permutations of A, with duplicates removed
vector< vector<int> > allPerms(vector<int> A) {
  sort(A.begin(), A.end());
  vector< vector<int> > out;
  do {
    out.push_back(A);
  } while (next_permutation(A.begin(), A.end()));
  return out;
}

// Returns whether B is a permutation of A
bool isPerm(vector<int> A, vector<int> B) {
  vector< vector<int> > C = allPerms(B);
  for (int i = 0; i < C.size(); i++) {
    if (A == C[i]) return true;
  }
  return false;
}

// Removes any duplicates from list A
void removeDupes(vector< vector<int> > &A) {
  sort(A.begin(), A.end());
  A.erase( unique(A.begin(), A.end()), A.end() );
}

// Returns a list of all subsequences of list A
vector< vector<int> > subseqs(vector<int> A) {
    vector< vector<int> > subset;
    vector<int> empty;
    subset.push_back( empty );

    for (int i = 0; i < A.size(); i++)
    {
        vector< vector<int> > subsetTemp = subset;

        for (int j = 0; j < subsetTemp.size(); j++)
            subsetTemp[j].push_back( A[i] );

        for (int j = 0; j < subsetTemp.size(); j++)
            subset.push_back( subsetTemp[j] );
    }
    
    removeDupes(subset);
    return subset;
}

// Returns whether list B is a subsequence of list A
bool subseq(vector<int> A, vector<int> B) {
  vector< vector<int> > C = subseqs(B);
  for (int i = 0; i < C.size(); i++) {
    if (A == C[i]) return true;
  }
  return false;
}

// Returns a list of all sublists of list A
vector< vector<int> > sublists(vector<int> A) {
  int size = A.size();
  vector< vector<int> > ret;
  vector<int> empty;
  ret.push_back(empty);
  for (int i = 0; i < size; i++) {
    ret.push_back({A[i]});
    ret.push_back(slice(A, i, size));
    ret.push_back(slice(A, 0, size - i));
    ret.push_back(slice(A, i, size - i));
  }
  removeDupes(ret);
  return ret;
}

// Returns ehther list B is a sublist of list A
bool sublist(vector<int> A, vector<int> B) {
  vector< vector<int> > C = sublists(B);
  for (int i = 0; i < C.size(); i++) {
    if (A == C[i]) return true;
  }
  return false;
}
