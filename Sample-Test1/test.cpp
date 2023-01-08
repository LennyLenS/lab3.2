#include "pch.h"
#include "../lab3.2/array_sequence.hpp"
#include "../lab3.2/list_sequence.hpp"
#include "../lab3.2/avl.hpp"
#include "../lab3.2/set.hpp"
#include "../lab3.2//sorted_sequence.hpp"
#include "../lab3.2/Pair.hpp"


TEST(ArraySequenceTest, AS_Append) {
	ArraySequence<int> as;
	as.Append(3);
	as.Append(5);
	as.Append(1);
	as.Append(17777);
	as.Append(-199);
	as.Append(213);

	ASSERT_EQ(as.GetLength(), 6);
}

TEST(ArraySequenceTest, AS_Get1) {
	ArraySequence<int> as;
	as.Append(7);
	as.Append(5);
	as.Append(1);
	as.Append(2323);
	as.Append(-199);
	as.Append(666);

	ASSERT_EQ(as.Get(1), 5);
}

TEST(ArraySequenceTest, AS_Get2) {
	ArraySequence<int> as;
	as.Append(3);
	as.Append(5);
	as.Append(1);
	as.Append(17777);
	as.Append(-199);
	as.Append(213);

	ASSERT_EQ(as.Get(3), 17777);
}

TEST(ArraySequenceTest, AS_Set1) {
	ArraySequence<int> as;
	as.Append(3);
	as.Append(5);
	as.Append(1);
	as.Append(17777);
	as.Append(-199);
	as.Append(213);

	as.Set(2344, 0);
	ASSERT_EQ(as.Get(0), 2344);
}

TEST(ArraySequenceTest, AS_Set2) {
	ArraySequence<int> as;
	as.Append(3);
	as.Append(5);
	as.Append(1);
	as.Append(17777);
	as.Append(-199);
	as.Append(213);

	as.Set(-123, 2);
	ASSERT_EQ(as.Get(2), -123);
}



TEST(ListSequenceTest, LS_Append) {
	ListSequence<int> as;
	as.Append(3);
	as.Append(5);
	as.Append(1);
	as.Append(17777);
	as.Append(-199);
	as.Append(213);

	ASSERT_EQ(as.GetLength(), 6);
}

TEST(ListSequenceTest, LS_Get1) {
	ListSequence<int> as;
	as.Append(7);
	as.Append(5);
	as.Append(1);
	as.Append(2323);
	as.Append(-199);
	as.Append(666);

	ASSERT_EQ(as.Get(1), 5);
}

TEST(ListSequenceTest, LS_Get2) {
	ListSequence<int> as;
	as.Append(3);
	as.Append(5);
	as.Append(1);
	as.Append(17777);
	as.Append(-199);
	as.Append(213);

	ASSERT_EQ(as.Get(3), 17777);
}

TEST(ListSequenceTest, LS_Set1) {
	ListSequence<int> as;
	as.Append(3);
	as.Append(5);
	as.Append(1);
	as.Append(17777);
	as.Append(-199);
	as.Append(213);

	as.Set(2344, 0);
	ASSERT_EQ(as.Get(0), 2344);
}

TEST(ListSequenceTest, LS_Set2) {
	ListSequence<int> as;
	as.Append(3);
	as.Append(5);
	as.Append(1);
	as.Append(17777);
	as.Append(-199);
	as.Append(213);

	as.Set(-123, 2);
	ASSERT_EQ(as.Get(2), -123);
}

TEST(AVLTEST, AVL_1) {
	AVL<int> avl;
	avl.add(4);
	avl.add(6);
	avl.add(2);
	ArraySequence<int> ans = avl.getelements();
	ASSERT_EQ(ans.GetLength(), 3);
}

TEST(AVLTEST, AVL_2) {
	AVL<int> avl;
	avl.add(4);
	avl.add(6);
	avl.add(255);
	avl.add(324234);
	ArraySequence<int> ans = avl.getelements();
	ASSERT_EQ(ans.GetLength(), 4);
}

TEST(AVLTEST, AVL_3) {
	AVL<int> avl;
	avl.add(4);
	avl.add(6);
	avl.add(2);
	avl.add(1312);
	avl.add(-1213123);
	ArraySequence<int> ans = avl.getelements();
	ASSERT_EQ(ans.GetLength(), 5);
}

TEST(AVLTEST, AVL_4) {
	AVL<int> avl;
	avl.add(4);
	avl.add(6);
	avl.add(2);
	ASSERT_EQ(avl.find(5), false);
}

TEST(AVLTEST, AVL_5) {
	AVL<int> avl;
	avl.add(4);
	avl.add(6);
	avl.add(2);
	ASSERT_EQ(avl.find(4), true);
}

TEST(AVLTEST, AVL_6) {
	AVL<int> avl;
	avl.add(4);
	avl.add(6);
	avl.add(2);
	avl.add(0);
	avl.add(3);
	ArraySequence<int> ans = avl.getelements();
	ArraySequence<int> buf;
	buf.Append(0);
	buf.Append(2);
	buf.Append(3);
	buf.Append(4);
	buf.Append(6);
	for (int i = 0; i < 5; ++i) {
		ASSERT_EQ(ans.Get(i), buf.Get(i));
	}
}

TEST(AVLTEST, AVL_7) {
	AVL<int> avl;
	avl.add(4);
	avl.add(6);
	avl.add(2);
	avl.add(0);
	avl.add(3);
	avl.delet(3);
	ArraySequence<int> ans = avl.getelements();
	ArraySequence<int> buf;
	buf.Append(0);
	buf.Append(2);
	buf.Append(4);
	buf.Append(6);
	for (int i = 0; i < 4; ++i) {
		ASSERT_EQ(ans.Get(i), buf.Get(i));
	}
}

TEST(SetTEST, Set1) {
	Set<int> a;
	a.add(4);
	a.add(1);
	a.add(123);
	a.add(444);
	ArraySequence<int> ans = a.getelement();
	ArraySequence<int> buf;
	buf.Append(1);
	buf.Append(4);
	buf.Append(123);
	buf.Append(444);
	for (int i = 0; i < 4; ++i) {
		ASSERT_EQ(ans.Get(i), buf.Get(i));
	}
}

TEST(SetTEST, Set2) {
	Set<int> a;
	a.add(4);
	a.add(1);
	a.add(123);
	a.add(444);
	a.add(3);
	a.add(123);
	ArraySequence<int> ans = a.getelement();
	ArraySequence<int> buf;
	buf.Append(1);
	buf.Append(3);
	buf.Append(4);
	buf.Append(123);
	buf.Append(444);
	for (int i = 0; i < 5; ++i) {
		ASSERT_EQ(ans.Get(i), buf.Get(i));
	}
}

TEST(SetTEST, Set3) {
	Set<int> a;
	a.add(4);
	a.add(1);
	a.add(123);
	a.add(444);
	ArraySequence<int> ans = a.getelement();
	ArraySequence<int> buf;
	buf.Append(1);
	buf.Append(4);
	buf.Append(123);
	buf.Append(444);
	for (int i = 0; i < 4; ++i) {
		ASSERT_EQ(ans.Get(i), buf.Get(i));
	}
}

TEST(SSTEST, SS1) {
	Sorted_sequence<int> a;
	a.add(4);
	a.add(1);
	a.add(123);
	a.add(444);
	ArraySequence<int> ans = a.getelement();
	ArraySequence<int> buf;
	buf.Append(1);
	buf.Append(4);
	buf.Append(123);
	buf.Append(444);
	for (int i = 0; i < 4; ++i) {
		ASSERT_EQ(ans.Get(i), buf.Get(i));
	}
}

TEST(SSTEST, SS2) {
	Sorted_sequence<int> a;
	a.add(4);
	a.add(1);
	a.add(123);
	a.add(444);
	a.add(3);
	a.add(123);
	ArraySequence<int> ans = a.getelement();
	ArraySequence<int> buf;
	buf.Append(1);
	buf.Append(3);
	buf.Append(4);
	buf.Append(123);
	buf.Append(123);
	buf.Append(444);
	for (int i = 0; i < 5; ++i) {
		ASSERT_EQ(ans.Get(i), buf.Get(i));
	}
}

TEST(SSTEST, SS3) {
	Set<int> a;
	a.add(4);
	a.add(1);
	a.add(123);
	a.add(-13);
	ArraySequence<int> ans = a.getelement();
	ArraySequence<int> buf;
	buf.Append(-13);
	buf.Append(1);
	buf.Append(4);
	buf.Append(123);
	for (int i = 0; i < 4; ++i) {
		ASSERT_EQ(ans.Get(i), buf.Get(i));
	}
}