#include "pch.h"
#include "../lab3.2/array_sequence.hpp"
#include "../lab3.2/list_sequence.hpp"
#include "../lab3.2/avl.hpp"
#include "../lab3.2/set.hpp"
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

}