#include "LinkedList.h"  
#include <cassert>

namespace DYNAMIC_ARRAY {
	void ConstructorTests() {
		int array[] = { 1, 2, 3, 4 };
		int size = 4;

		DynamicArray<int> dynamicArray(array, size);

		for (int i = 0; i < size; i++) {
			assert(dynamicArray.GetElem(i) == array[i]);
		}

		DynamicArray<int> dynamicArray1(size);
		for (int i = 0; i < size; i++) {
			assert(dynamicArray1.GetElem(i) == 0);
		}

		DynamicArray<int> dynamicArray2(dynamicArray);
		for (int i = 0; i < size; i++) {
			assert(dynamicArray2.GetElem(i) == array[i]);
		}
	}
	void CopyConstructorTests() {
		int array[] = { 1, 2, 3, 4 };
		int size = 4;

		DynamicArray<int> dynamicArray1(array, size);
		DynamicArray<int> dynamicArray2 = dynamicArray1;

		for (int i = 0; i < size; i++) {
			assert(dynamicArray1.GetElem(i) == array[i]);
			assert(dynamicArray2.GetElem(i) == array[i]);
		}
	}

	void GetElementsTests() {
		int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int size = 10;

		DynamicArray<int> dynamicArray(array, size);

		for (int i = 0; i < size; i++) {
			assert(dynamicArray.GetElem(i) == array[i]);
		}

		assert(dynamicArray.GetFirstElem() == array[0]);
		assert(dynamicArray.GetLastElem() == array[size - 1]);
	}

	void GetSubsequencesTests() {
		int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int size = 10;

		DynamicArray<int> dynamicArray(array, size);

		DynamicArray<int>* subsequence = dynamicArray.GetSubsequence(0, size);
		assert(dynamicArray.GetLength() == subsequence->GetLength());

		for (int i = 0; i < size; i++) {
			assert(dynamicArray.GetElem(i) == subsequence->GetElem(i));
		}

		int sliceCount = 2;
		subsequence = dynamicArray.GetSubsequence(sliceCount, size - sliceCount);
		assert(size - 2 * sliceCount + 1 == subsequence->GetLength());

		for (int i = 0; i < size - sliceCount - 1; i++) {
			assert(dynamicArray.GetElem(i + sliceCount) == subsequence->GetElem(i));
		}

		int index = 3;
		subsequence = dynamicArray.GetSubsequence(index, index);
		assert(subsequence->GetLength() == 1);
		assert(dynamicArray.GetElem(index) == subsequence->GetElem(0));
	}

	void GetLengthTests() {
		int size = 10;
		DynamicArray<int> dynamicArray(size);
		assert(dynamicArray.GetLength() == size);
	}

	void AppendTest() {
		int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
		int size = 9;
		int number = 9;

		DynamicArray<int> dynamicArray(array, size);
		dynamicArray.Append(number);

		for (int i = 0; i < size; i++) {
			assert(dynamicArray.GetElem(i) == array[i]);
		}

		assert(dynamicArray.GetElem(size) == number);
		assert(dynamicArray.GetLength() == (size + 1));
	}

	void PrependTest() {
		int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int size = 9;
		int number = 0;

		DynamicArray<int> dynamicArray(array, size);
		dynamicArray.Prepend(number);

		for (int i = 0; i < size; i++) {
			assert(dynamicArray.GetElem(i + 1) == array[i]);
		}

		assert(dynamicArray.GetElem(0) == number);
		assert(dynamicArray.GetLength() == (size + 1));
	}

	void InsertAtTest() {
		int array[] = { 0, 1, 2, 3, 5, 6, 7, 8, 9 };
		int size = 9;
		int number = 4;
		int index = 4;

		DynamicArray<int> dynamicArray(array, size);
		dynamicArray.Insert(number, index);

		for (int i = 0; i < index; i++) {
			assert(dynamicArray.GetElem(i) == array[i]);
		}

		assert(dynamicArray.GetElem(index) == number);

		for (int i = index + 1; i < dynamicArray.GetLength(); i++) {
			assert(dynamicArray.GetElem(i) == array[i - 1]);
		}

		assert(dynamicArray.GetLength() == (size + 1));
	}

	void UnionTest() {
		int array1[] = { 0, 1, 2, 3, 5 };
		int array2[] = { 6, 7, 8, 9 };
		int size1 = 5;
		int size2 = 4;

		DynamicArray<int> dynamicArray1(array1, size1);
		DynamicArray<int> dynamicArray2(array2, size2);
		dynamicArray1.Union(&dynamicArray2);

		for (int i = 0; i < size1; i++) {
			assert(dynamicArray1.GetElem(i) == array1[i]);
		}

		for (int i = size1; i < size1 + size2; i++) {
			assert(dynamicArray1.GetElem(i) == array2[i - size1]);
		}
	}

	void IteratorTest() {
		int array[] = { 0, 1, 2, 3, 5, 6, 7, 8, 9 };
		int size = 9;
		DynamicArray<int> dynamicArray(array, size);

		auto begin = dynamicArray.ToBegin();
		auto end = dynamicArray.ToEnd();
		int i = 0;

		while (*begin != *end) {
			assert(dynamicArray.GetElem(i) == **begin);
			++(*begin);
			i++;
		}
	}
	void Call() {
		ConstructorTests();
		CopyConstructorTests();
		GetElementsTests();
		GetSubsequencesTests();
		GetLengthTests();
		AppendTest();
		PrependTest();
		InsertAtTest();
		UnionTest();
		IteratorTest();
	}
}

namespace LINKED_LIST {

	void ConstructorTests() {
		int array[] = { 1, 2, 3, 4 };
		int size = 4;

		LinkedList<int> list(array, size);

		for (int i = 0; i < size; i++) {
			assert(list.GetElem(i) == array[i]);
		}

		LinkedList<int> list1(list);
		for (int i = 0; i < size; i++) {
			assert(list1.GetElem(i) == array[i]);
		}
	}

	void GetElementsTests() {
		int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int size = 10;

		LinkedList<int> list(array, size);

		for (int i = 0; i < size; i++) {
			assert(list.GetElem(i) == array[i]);
		}

		assert(list.GetFirstElem() == array[0]);
		assert(list.GetLastElem() == array[size - 1]);
	}

	void GetSubsequencesTests() {
		int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int size = 10;

		LinkedList<int> list(array, size);

		LinkedList<int>* subsequence = list.GetSubsequence(0, size);
		assert(list.GetLength() == subsequence->GetLength());

		for (int i = 0; i < size; i++) {
			assert(list.GetElem(i) == subsequence->GetElem(i));
		}

		int sliceCount = 2;
		subsequence = list.GetSubsequence(sliceCount, size - sliceCount);
		assert(size - 2 * sliceCount + 1 == subsequence->GetLength());

		for (int i = 0; i < size - sliceCount - 1; i++) {
			assert(list.GetElem(i + sliceCount) == subsequence->GetElem(i));
		}

		int index = 3;
		subsequence = list.GetSubsequence(index, index);
		assert(subsequence->GetLength() == 1);
		assert(list.GetElem(index) == subsequence->GetElem(0));
	}

	void GetLengthTests() {
		int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int size = 10;

		LinkedList<int> list(array, size);
		assert(list.GetLength() == size);
	}

	void AppendTest() {
		int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
		int size = 9;
		int number = 9;

		LinkedList<int> list(array, size);
		list.Append(number);

		for (int i = 0; i < size; i++) {
			assert(list.GetElem(i) == array[i]);
		}

		assert(list.GetElem(size) == number);
		assert(list.GetLength() == (size + 1));
	}

	void PrependTest() {
		int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int size = 9;
		int number = 0;

		LinkedList<int> list(array, size);
		list.Prepend(number);

		for (int i = 0; i < size; i++) {
			assert(list.GetElem(i + 1) == array[i]);
		}

		assert(list.GetElem(0) == number);
		assert(list.GetLength() == (size + 1));
	}

	void InsertAtTest() {
		int array[] = { 0, 1, 2, 3, 5, 6, 7, 8, 9 };
		int size = 9;
		int number = 4;
		int index = 4;

		LinkedList<int> list(array, size);
		list.Insert(number, index);

		for (int i = 0; i < index; i++) {
			assert(list.GetElem(i) == array[i]);
		}

		assert(list.GetElem(index) == number);

		for (int i = index + 1; i < list.GetLength(); i++) {
			assert(list.GetElem(i) == array[i - 1]);
		}

		assert(list.GetLength() == (size + 1));
	}

	void UnionTest() {
		int array1[] = { 0, 1, 2, 3, 5 };
		int array2[] = { 6, 7, 8, 9 };
		int size1 = 5;
		int size2 = 4;

		LinkedList<int> list1(array1, size1);
		LinkedList<int> list2(array2, size2);

		list1.Union(&list2);

		for (int i = 0; i < size1; i++) {
			assert(list1.GetElem(i) == array1[i]);
		}

		for (int i = size1; i < size1 + size2; i++) {
			assert(list1.GetElem(i) == array2[i - size1]);
		}
	}

	void IteratorTest() {
		int array[] = { 0, 1, 2, 3, 5, 6, 7, 8, 9 };
		int size = 9;
		LinkedList<int> list(array, size);

		auto begin = list.ToBegin();
		auto end = list.ToEnd();
		int i = 0;

		while (*begin != *end) {
			assert(list.GetElem(i) == **begin);
			++(*begin);
			i++;
		}
	}

	void Call() {
		ConstructorTests();
		GetElementsTests();
		GetSubsequencesTests();
		GetLengthTests();
		AppendTest();
		PrependTest();
		InsertAtTest();
		UnionTest();
		IteratorTest();
	}
}