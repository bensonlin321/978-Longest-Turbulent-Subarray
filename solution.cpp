#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <limits>
#include <utility> // pair
#include <tuple>
#include <algorithm>
#include <map>
#define MINUS_INT_MAX INT_MAX * (-1);

/*
    A[k] > A[k+1] when k is odd, and A[k] < A[k+1] when k is even;
    OR
    A[k] > A[k+1] when k is even, and A[k] < A[k+1] when k is odd.

    when k is odd
    A[k-1] < A[k] > A[k+1]

    when k is even
    A[k-1] > A[k] < A[k+1]
*/

class Solution {
public:

    bool checkIsTurbulenceElement(std::vector<int>& A, int index) {
        int left = index - 1 >= 0 ? index-1 : 0;
        int right = index + 1 <= A.size()-1 ? index+1 : A.size()-1;
        if(index % 2 == 0) {
            // even
            if( A[left] > A[index] && A[index] < A[right] ){
                return true;
            } else if(index == 0 && A[index] < A[right]) {
                return true;
            } else if(index == A.size()-1 && A[left] > A[index]) {
                return true;
            }
        } else {
            // odd
            if( A[left] < A[index] && A[index] > A[right] ){
                return true;
            } else if(index == 0 && A[index] > A[right]) {
                return true;
            } else if(index == A.size()-1 && A[left] < A[index]) {
                return true;
            }
        }
        return false;
    }

    int maxTurbulenceSize(std::vector<int>& A) {
        if(A.size() <= 0) {
            return -1;
        }

        if(A.size() == 0) {
            return 1;
        }

        // build a turbulence array which store the information: which element is turbulent element
        std::vector<int> is_turbulence_array;
        for(int i = 0 ; i < A.size(); i++) {
            bool is_t = checkIsTurbulenceElement(A, i);
            is_turbulence_array.push_back(is_t);
        }
        printf("turbulence_array:\n[\t");
        for(int i = 0 ; i < is_turbulence_array.size() ; i++)
            printf("%d\t", is_turbulence_array.at(i));

        printf("]\n");
        int max_size_of_turbulence = 0;
        int tmp_sum                = 0;
        int last_elem_index        = 0;
        int first_elem_index       = 0;

        for(int i = 0 ; i < is_turbulence_array.size() ; i++) {
            if(is_turbulence_array.at(i) == 1) {
                tmp_sum += 1;
                //max_size_of_turbulence = std::max(max_size_of_turbulence, tmp_sum);
                if(max_size_of_turbulence < tmp_sum) {
                    max_size_of_turbulence = tmp_sum;
                    first_elem_index       = i - (tmp_sum - 1);
                    last_elem_index        = i;
                    printf("[%d] tmp_sum:%d, max_size_of_turbulence:%d\n", i, tmp_sum, max_size_of_turbulence);
                }
                
            } else {
                tmp_sum = 0;
            }
        }
        printf("first_elem_index:%d, last_elem_index:%d\n", first_elem_index, last_elem_index);

        // max_size_of_turbulence does not include first elem and last elem of turbulence array
        // need to add first elem and last elem
        if(first_elem_index != 0)           max_size_of_turbulence++;
        if(last_elem_index != A.size() - 1) max_size_of_turbulence++;
        return max_size_of_turbulence; 
    }


    int maxTurbulenceSize_DP(std::vector<int>& A) {
        std::vector<int> right(A.size(), 1);
        std::vector<int> left(A.size(), 1);
        int ans = 1;
        for(int i = 1; i < A.size(); i++) {
            if(A[i] > A[i - 1]) right[i] = left[i - 1]  + 1;
            if(A[i] < A[i - 1]) left[i]  = right[i - 1] + 1;
          ans = std::max(ans, std::max(right[i], left[i]));      
        }
        return ans;
      }

};

int main(int argc, char *argv[]) {
    Solution *s = new Solution();

    std::vector<int> nums1{ 9,4,2,10,7,8,8,1,9};
    printf("output:%d\n", s -> maxTurbulenceSize(nums1));

}