"""
Feel free to add more test classes and/or tests that are not provided by the skeleton code!
Make sure you follow these naming conventions: https://docs.pytest.org/en/reorganize-docs/goodpractices.html#test-discovery
for your new tests/classes/python files or else they might be skipped.
"""
from utils import *
import unittest
import numc as nc
"""
For each operation, you should write tests to test correctness on matrices of different sizes.
Hint: use rand_dp_nc_matrix to generate dumbpy and numc matrices with the same data and use
      cmp_dp_nc_matrix to compare the results
"""
class TestAddCorrectness(unittest.TestCase):
    def test_small_add(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(2, 2, rand = True, seed = 1, low = -5, high = 5)
        dp2, nc2 = rand_dp_nc_matrix(2, 2, rand = True, seed = 2, low = -5, high = 5)
        sum1 = dp1 + dp2
        sum2 = nc1 + nc2 
        assert cmp_dp_nc_matrix(dp1, nc1)
        assert cmp_dp_nc_matrix(sum1, sum2)
        pass

    def test_medium_add(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(20, 20, rand = True, seed = 1, low = -50, high = 50)
        dp2, nc2 = rand_dp_nc_matrix(20, 20, rand = True, seed = 2, low = -50, high = 50)
        sum1 = dp1 + dp2
        sum2 = nc1 + nc2 
        assert cmp_dp_nc_matrix(dp1, nc1)
        assert cmp_dp_nc_matrix(sum1, sum2)        
        pass

    def test_large_add(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(200, 200, rand = True, seed = 1, low = -5, high = 5)
        dp2, nc2 = rand_dp_nc_matrix(200, 200, rand = True, seed = 2, low = -5, high = 5)
        sum1 = dp1 + dp2
        sum2 = nc1 + nc2 
        assert cmp_dp_nc_matrix(dp1, nc1)
        assert cmp_dp_nc_matrix(sum1, sum2)        
        pass


class TestSubCorrectness:
    def test_small_sub(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(2, 2, rand = True, seed = 1, low = -5, high = 5)
        dp2, nc2 = rand_dp_nc_matrix(2, 2, rand = True, seed = 2, low = -5, high = 5)
        sum1 = dp1 - dp2
        sum2 = nc1 - nc2 
        assert cmp_dp_nc_matrix(dp1, nc1)
        assert cmp_dp_nc_matrix(sum1, sum2)       
        pass

    def test_medium_sub(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(20, 20, rand = True, seed = 1, low = -50, high = 50)
        dp2, nc2 = rand_dp_nc_matrix(20, 20, rand = True, seed = 2, low = -50, high = 50)
        sum1 = dp1 - dp2
        sum2 = nc1 - nc2 
        assert cmp_dp_nc_matrix(dp1, nc1)
        assert cmp_dp_nc_matrix(sum1, sum2)       
        pass

    def test_large_sub(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(200, 200, rand = True, seed = 1, low = -500, high = 500)
        dp2, nc2 = rand_dp_nc_matrix(200, 200, rand = True, seed = 2, low = -500, high = 500)
        sum1 = dp1 - dp2
        sum2 = nc1 - nc2 
        assert cmp_dp_nc_matrix(dp1, nc1)
        assert cmp_dp_nc_matrix(sum1, sum2)        
        pass


class TestAbsCorrectness:
    def test_small_abs(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(2, 2, rand = True, seed = 1, low = -5, high = 5)
        dp2, nc2 = rand_dp_nc_matrix(2, 2, rand = True, seed = 2, low = -5, high = 5)
        sum1 = abs(dp1) + abs(dp2)
        sum2 = abs(nc1) + abs(nc2) 
        assert cmp_dp_nc_matrix(abs(dp1), abs(nc1))
        assert cmp_dp_nc_matrix(sum1, sum2)          
        pass

    def test_medium_abs(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(20, 20, rand = True, seed = 1, low = -50, high = 50)
        dp2, nc2 = rand_dp_nc_matrix(20, 20, rand = True, seed = 2, low = -50, high = 50)
        sum1 = abs(dp1) + abs(dp2)
        sum2 = abs(nc1) + abs(nc2) 
        assert cmp_dp_nc_matrix(abs(dp1), abs(nc1))
        assert cmp_dp_nc_matrix(sum1, sum2)          
        pass

    def test_large_abs(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(200, 200, rand = True, seed = 1, low = -500, high = 500)
        dp2, nc2 = rand_dp_nc_matrix(200, 200, rand = True, seed = 2, low = -500, high = 500)
        sum1 = abs(dp1) + abs(dp2)
        sum2 = abs(nc1) + abs(nc2)
        assert cmp_dp_nc_matrix(abs(dp1), abs(nc1))
        assert cmp_dp_nc_matrix(sum1, sum2)        
        pass

    
class TestNegCorrectness:
    def test_small_neg(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(2, 2, rand = True, seed = 1, low = -5, high = 5)
        dp2, nc2 = rand_dp_nc_matrix(2, 2, rand = True, seed = 2, low = -5, high = 5)
        sum1 = (-dp1) + (-dp2)
        sum2 = (-nc1) + (-nc2)
        assert cmp_dp_nc_matrix((-dp1),(-nc1))
        assert cmp_dp_nc_matrix(sum1, sum2)
        pass

    def test_medium_neg(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(20, 20, rand = True, seed = 1, low = -50, high = 50)
        dp2, nc2 = rand_dp_nc_matrix(20, 20, rand = True, seed = 2, low = -50, high = 50)
        sum1 = (-dp1) + (-dp2)
        sum2 = (-nc1) + (-nc2)
        assert cmp_dp_nc_matrix((-dp1),(-nc1))
        assert cmp_dp_nc_matrix(sum1, sum2)        
        pass

    def test_large_neg(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(200, 200, rand = True, seed = 1, low = -500, high = 500)
        dp2, nc2 = rand_dp_nc_matrix(200, 200, rand = True, seed = 2, low = -500, high = 500)
        sum1 = (-dp1) + (-dp2)
        sum2 = (-nc1) + (-nc2)
        assert cmp_dp_nc_matrix((-dp1),(-nc1))
        assert cmp_dp_nc_matrix(sum1, sum2)        
        pass

class TestMulCorrectness:
    def test_small_mul(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(2, 2, rand = True, seed = 1, low = -5, high = 5)
        dp2, nc2 = rand_dp_nc_matrix(2, 2, rand = True, seed = 2, low = -5, high = 5)
        mul1 = dp1 * dp2
        mul2 = nc1 * nc2 
        assert cmp_dp_nc_matrix(dp1, nc1)
        assert cmp_dp_nc_matrix(mul1, mul2)
        pass

    def test_medium_mul(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(20, 20, rand = True, seed = 1, low = -50, high = 50)
        dp2, nc2 = rand_dp_nc_matrix(20, 20, rand = True, seed = 2, low = -50, high = 50)
        mul1 = dp1 * dp2
        mul2 = nc1 * nc2 
        assert cmp_dp_nc_matrix(dp1, nc1)
        assert cmp_dp_nc_matrix(mul1, mul2)
        pass

    def test_large_mul(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(200, 200, rand = True, seed = 1, low = -500, high = 500)
        dp2, nc2 = rand_dp_nc_matrix(200, 200, rand = True, seed = 2, low = -500, high = 500)
        mul1 = dp1 * dp2
        mul2 = nc1 * nc2 
        assert cmp_dp_nc_matrix(dp1, nc1)
        assert cmp_dp_nc_matrix(mul1, mul2)        
        pass

class TestPowCorrectness:
    def test_small_pow(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(2, 2, rand = True, seed = 1, low = -5, high = 5)
        pow_dp, pow_nc = [5, 5]
        result1 = dp1 ** pow_dp
        result2 = nc1 ** pow_nc 
        assert cmp_dp_nc_matrix(dp1, nc1)
        pass

    def test_medium_pow(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(20, 20, rand = True, seed = 1, low = -50, high = 50)
        pow_dp, pow_nc = [50, 50]
        result1 = dp1 ** pow_dp
        result2 = nc1 ** pow_nc
        assert cmp_dp_nc_matrix(dp1, nc1)        
        pass

    def test_large_pow(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(200, 200, rand = True, seed = 1, low = -50, high = 50)
        pow_dp, pow_nc = [100, 100]
        result1 = dp1 ** pow_dp
        result2 = nc1 ** pow_nc
        assert cmp_dp_nc_matrix(dp1, nc1)        
        pass

class TestGetCorrectness:
    def test_get(self):
        # TODO: YOUR CODE HERE
        dp1, nc1 = rand_dp_nc_matrix(2, 2, rand = True, seed = 1, low = -5, high = 5)
        for i in range(0, 2):
            for j in range(0, 2):
               self.assertEqual(dp1.get(i, j), nc1.get(i, j))
        pass

class TestSetCorrectness:
    def test_set(self):
        # TODO: YOUR CODE HERE
        mat1 = nc.Matrix(3, 3)
        mat2 = nc.Matrix(3, 3, 1)
        for i in range(0, 2):
            for j in range(0, 2):
               self.assertEqual(mat1.get(i, j), mat2.set(i, j, 0))        
        pass

if __name__ == '__main__':
    unittest.main()