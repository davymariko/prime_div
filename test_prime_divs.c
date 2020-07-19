#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "multithreadFactorization.h"


int init_suite(void)
{ 
	return 0; 
}

int clean_suite(void) 
{ 
	return 0; 
}

//Tester success

void test_intnumber(void)
{
	CU_ASSERT_EQUAL(intnumber(124) , 3);
    CU_ASSERT_EQUAL(intnumber(11) , 2);
    CU_ASSERT_EQUAL(intnumber(7845) , 4);
    CU_ASSERT_EQUAL(intnumber(1844674407370955161), 19);
    CU_PASS("Test of intnumber");
}

void test_getint(void)
{
	CU_ASSERT_EQUAL(getint("857") , 857);
    CU_ASSERT_EQUAL(getint("458") , 458);
    CU_ASSERT_EQUAL(getint("7894"), 7894);
    CU_ASSERT_EQUAL(getint("1844674407370955161"), 1844674407370955161);
    CU_PASS("Test of getint");
}

void test_optimizedFactorization(void)
{
	CU_ASSERT_EQUAL(optimizedFactorization(666343)[1] , 666343);
	CU_ASSERT_EQUAL(optimizedFactorization(666343)[2] , 89);
	CU_ASSERT_EQUAL(optimizedFactorization(98286)[2] , 2);
    CU_ASSERT_EQUAL(optimizedFactorization(98286)[3] , 3);
    CU_ASSERT_EQUAL(optimizedFactorization(18214)[2] , 2);
    CU_ASSERT_EQUAL(optimizedFactorization(18214)[1] , 18214);
    CU_PASS("Test of optimizedFactorization");
}

//Tester failure

void fail_intnumber(void)
{
	CU_ASSERT_NOT_EQUAL(intnumber(124) , 2);
    CU_ASSERT_NOT_EQUAL(intnumber(11) , 3);
    CU_ASSERT_NOT_EQUAL(intnumber(11978) , 4);
    CU_ASSERT_NOT_EQUAL(intnumber(1844674407370955161), 18);
    CU_PASS("Test of Failure of intnumber");
}

void fail_getint(void)
{
	CU_ASSERT_NOT_EQUAL(getint("857") , "857");
    CU_ASSERT_NOT_EQUAL(getint("458") , 9458);
    CU_ASSERT_NOT_EQUAL(getint("968") , 789);
    CU_ASSERT_NOT_EQUAL(getint("1844674407370955161"), 184467440737095516);
    CU_PASS("Test of Failure of getint");
}

void fail_optimizedFactorization(void)
{
	CU_ASSERT_NOT_EQUAL(optimizedFactorization(666343)[0] , 89);
	CU_ASSERT_NOT_EQUAL(optimizedFactorization(666343)[1] , 89);
    CU_ASSERT_NOT_EQUAL(optimizedFactorization(529973)[1] , 5299);
    CU_ASSERT_NOT_EQUAL(optimizedFactorization(18214)[2] , 18214);
    CU_ASSERT_NOT_EQUAL(optimizedFactorization(18214)[1] , 2);
    CU_PASS("Test of Failure of optimizedFactorization");
}

int main (void)// Main function
{
	CU_pSuite pSuite = NULL;

	// Initialiser CUnit
	if (CUE_SUCCESS != CU_initialize_registry()){
		return CU_get_error();
	}

	// Suite
	pSuite = CU_add_suite("Basic_Test_Suite", init_suite, clean_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	// Tests
	if ((NULL == CU_add_test(pSuite,"Testing test_intnumber function", test_intnumber)) ||
		(NULL == CU_add_test(pSuite,"Testing test_getint function", test_getint)) ||
		(NULL == CU_add_test(pSuite,"Testing optimizedFactorization function", test_optimizedFactorization)) ||
		(NULL == CU_add_test(pSuite,"Testing Fail of is_div function", fail_intnumber)) || 
		(NULL == CU_add_test(pSuite,"Testing Failure of is_prime function", fail_getint)) || 
		(NULL == CU_add_test(pSuite,"Testing Failure of prime_divs function", fail_optimizedFactorization)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests();// OUTPUT to the screen

	CU_cleanup_registry();
	return CU_get_error();

}