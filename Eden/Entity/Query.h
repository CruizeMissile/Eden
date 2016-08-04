#pragma once

namespace edn
{
	namespace Query
	{
		template<typename Iterator1, typename Iterator2, typename Operation>
		class range_const_iterator
		{
			range_const_iterator<Iterator1, Iterator2, Operation> this_type;
			friend Operation;
		public:

			inline range_const_iterator(Iterator1 one, Iterator2 two)
			{
				first1 = one.begin();
				last1 = one.end();
				first2 = two.begin();
				last2 = two.end();
			}

			inline range_const_iterator(range_const_iterator & other)
				: first1(other.first1)
				, last1(other.last1)
				, first2(other.first2)
				, last2(other.last2)
			{
			}

			range_const_iterator operator++()
			{
				
			}

		private:
			Iterator1 first1;
			Iterator1 last1;
			Iterator2 first2;
			Iterator2 last2;
		};
	}

	struct Intersection
	{
		template<typename Iterator1, typename Iterator2>
		static next(
			Iterator1 & first1,
			Iterator1 & last1,
			Iterator2 & first2,
			Iterator2 & last2)
		{
			if (*first1 == *first2)
			{
				++first1;
				++first2;
			}

			while (first1 != last1 && first2 != last2)
			{
				if (*first1 == *first2)
					return;
				first1 < first2 ? ++first1 : ++first2;
			}
		}
	};

	struct Difference
	{
		template<typename Iterator1, typename Iterator2>
		static next(
			Iterator1 & first1,
			Iterator1 & last1,
			Iterator2 & first2,
			Iterator2 & last2)
		{
			// If the case coming in is alreay a valid case move first one up and moving on
			if (*first1 < *first2)
				++first1;

			// one is greater then two then we want to catch up two.
			// If they are the same then we want to bump two and check
			// again.
			while (*first1 >= *first2 && first2 != last2)
			{
				++first2;
			}

			//// This is the valid case and return
			//if (*first1 < *first2)
			//	return;
		}
	};

	struct Union
	{
		template<typename Iterator1, typename Iterator2>
		static next(
			Iterator1 & first1,
			Iterator1 & last1,
			Iterator2 & first2,
			Iterator2 & last2)
		{
			if (*first1 == *first2)
			{
				++first1;
				++first2;
			}
			else if (*first1 < *first2)
			{
				++first1;
			}
			else
			{
				++first2;
			}
		}
	};

	struct Exclusive
	{
		template<typename Iterator1, typename Iterator2>
		static next(
			Iterator1 & first1,
			Iterator1 & last1,
			Iterator2 & first2,
			Iterator2 & last2)
		{
		}
	};
}