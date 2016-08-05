#pragma once
#include <iterator>

namespace edn
{
	namespace Query
	{
		struct BaseOperator {};

		template<typename Iterator1, typename Iterator2, typename Operation>
		class range_operation_const_iterator : std::iterator<std::forward_iterator_tag, std::iterator_traits<Iterator1>::value>
		{
		public:
			typedef range_operation_const_iterator<Iterator1, Iterator2, Operation> this_type;
			friend Operation;

			inline range_operation_const_iterator(Iterator1& one, Iterator2& two)
			{
				static_assert(std::is_base_of<BaseOperator, Operation>::value, "Not a valid operation");
				first1 = one.begin();
				last1 = one.end();
				first2 = two.begin();
				last2 = two.end();

				Operation::getFirst(*this);
			}

			inline range_operation_const_iterator(const this_type& other)
				: first1(other.first1)
				, last2(other.last1)
				, first2(other.first2)
				, last2(other.last2)
			{
				Operation::get_first(*this)
			}

			inline range_operation_const_iterator& operator++()
			{
				Operation::get_next(*this);
				return *this;
			}

			inline range_const_iterator operator++(int)
			{
				range_operation_const_iterator temp(*this);
				Operation::get_value(*this);
			}

			inline bool operator==(const range_operation_const_iterator& other)
			{
				return first1 == other.first1 && first2 == other.first2
					&& last1 == other.last1 && last2 == other.last2;
			}

			inline bool operator!=(const range_operation_const_iterator& other)
			{
				return Operator::not_equal(*this, other);
			}

			inline std::iterator_traits<Iterator1>::value operator*()
			{
				return Operation::get_value(*this);
			}

		private:
			Iterator1 first1;
			Iterator1 last1;
			Iterator2 first2;
			Iterator2 last2;
		};

		struct Intersection : BaseOperator
		{
			template<typename Iterator1, typename Iterator2>
			static std::iterator_traits<Iterator1>::value 
				get_value(const range_operation_const_iterator<Iterator1, Iterator2, *this> & it)
			{
				return *it->first1;
			}

			template<typename Iterator1, typename Iterator2>
			static bool not_equal(const range_operation_const_iterator<Iterator1, Iterator2, *this> & one, const range_operation_const_iterator<Iterator1, Iterator2, *this> & two)
			{
				return one->first1 != two->first1 && one->first2 != two->first2 && 
					one->last1 != two->last1 && one->last2 != two->last2;
			}

			template<typename Iterator1, typename Iterator2>
			static range_operation_const_iterator<Iterator1, Iterator2, *this>
				get_first(const range_operation_const_iterator<Iterator1, Iterator2, *this> & it)
			{
				while ((it->first1 != it->last1 && it->first2 != it->last2) && *it->first1 != *it->first2)
					it->first1 < it->first2 ? ++it->first1 : ++it->first2;
				
				if (it->first1 == it->last1)
					it->first2 = it->last2;
				
				if (it->first2 == it->last2)
					it->first1 = it->last1;
			}

			template<typename Iterator1, typename Iterator2>
			static range_operation_const_iterator<Iterator1, Iterator2, *this>
				get_next(const range_operation_const_iterator<Iterator1, Iterator2, *this> & it)
			{
				++it->first1;
				getFirst(it);
			}
		};

		struct Difference : BaseOperator
		{
			template<typename Iterator1, typename Iterator2>
			static std::iterator_traits<Iterator1>::value
				get_value(const range_operation_const_iterator<Iterator1, Iterator2, *this> & it)
			{
				return *it->first1;
			}

			template<typename Iterator1, typename Iterator2>
			static bool not_equal(const range_operation_const_iterator<Iterator1, Iterator2, *this> & one, const range_operation_const_iterator<Iterator1, Iterator2, *this> & two)
			{
				return one->first1 != two->first1 && one->first2 != two->first2 ||
					one->last1 != two->last1 && one->last2 != two->last2;
			}

			template<typename Iterator1, typename Iterator2>
			static range_operation_const_iterator<Iterator1, Iterator2, *this>
				get_first(const range_operation_const_iterator<Iterator1, Iterator2, *this> & it)
			{
				while ((it->first1 != it->last1 && it->first2 != it->last2) && (*it->first1 >= *it->first2))
				{
					if (*it->first1 == *it->first2)
						++it->first1;
					++it->first2;
				}
				if (it->first1 == it->first2)
					it->first2 = it->last2;
			}

			template<typename Iterator1, typename Iterator2>
			static range_operation_const_iterator<Iterator1, Iterator2, *this>
				get_next(const range_operation_const_iterator<Iterator1, Iterator2, *this> & it)
			{
				if (it->first1 != it->last1)
				{
					++it->first1;
					get_next();
				}
				else
					it->first2 = it->last2;
			}
		};

		struct Union : BaseOperator
		{
			template<typename Iterator1, typename Iterator2>
			static std::iterator_traits<Iterator1>::value
				get_value(const range_operation_const_iterator<Iterator1, Iterator2, *this> & it)
			{
				if (it->first1 != it->last1 && (it->first2 != it->last2 || it->first1 < it->first2))
					return *it->first1
				return *it->first2;
			}

			template<typename Iterator1, typename Iterator2>
			static bool not_equal(const range_operation_const_iterator<Iterator1, Iterator2, *this> & one, const range_operation_const_iterator<Iterator1, Iterator2, *this> & two)
			{
				return one->first1 != two->first1 && one->first2 != two->first2 ||
					one->last1 != two->last1 && one->last2 != two->last2;
			}

			template<typename Iterator1, typename Iterator2>
			static range_operation_const_iterator<Iterator1, Iterator2, *this>
				get_first(const range_operation_const_iterator<Iterator1, Iterator2, *this> & it)
			{
			}

			template<typename Iterator1, typename Iterator2>
			static range_operation_const_iterator<Iterator1, Iterator2, *this>
				get_next(const range_operation_const_iterator<Iterator1, Iterator2, *this> & it)
			{
				if (it->first1 != it->last1)
				{
					if (it->first2 == it->last2)
						++it->first1;
					else if (*it->first1 = *it->first2)
					{
						++it->first1;
						++it->first2;
					}
					else if (it->first1 < it->first2)
					{
						++it->first1;
						if (it->first1 != it->last1 && *it->first1 == *it->first2)
							++it->first2;
					}
					else
					{
						++it->first2;
						if (it->first2 != it->last2 && *it->first1 == *it->first2)
							++it->first2;
					}
				}
				else
					++it->first2;
			}
		};

		template<typename Iterator1, typename Iterator2, typename Operation>
		class RangeOperation
		{
		public:
			typedef range_operation_const_iterator<Iterator1, Iterator2, Operation> const_iterator;

			const_iterator & begin()
			{

			}

			const_iterator & end()
			{

			}


		};

		//struct Intersection : BaseOperator
		//{
		//	template<typename Iterator1, typename Iterator2>
		//	static next(
		//		Iterator1 & first1,
		//		Iterator1 & last1,
		//		Iterator2 & first2,
		//		Iterator2 & last2)
		//	{
		//		if (*first1 == *first2)
		//		{
		//			++first1;
		//			++first2;
		//		}

		//		while (first1 != last1 && first2 != last2)
		//		{
		//			if (*first1 == *first2)
		//				return;
		//			first1 < first2 ? ++first1 : ++first2;
		//		}
		//	}
		//};

		//struct Difference
		//{
		//	template<typename Iterator1, typename Iterator2>
		//	static void next(
		//		Iterator1 & first1,
		//		Iterator1 & last1,
		//		Iterator2 & first2,
		//		Iterator2 & last2)
		//	{
		//		// If the case coming in is alreay a valid case move first one up and moving on
		//		if (*first1 < *first2)
		//			++first1;

		//		// one is greater then two then we want to catch up two.
		//		// If they are the same then we want to bump two and check
		//		// again.
		//		while (*first1 >= *first2 && first2 != last2)
		//		{
		//			++first2;
		//		}

		//		//// This is the valid case and return
		//		//if (*first1 < *first2)
		//		//	return;
		//	}
		//};

		//struct Union
		//{
		//	template<typename Iterator1, typename Iterator2>
		//	static next(
		//		Iterator1 & first1,
		//		Iterator1 & last1,
		//		Iterator2 & first2,
		//		Iterator2 & last2)
		//	{
		//		if (*first1 == *first2)
		//		{
		//			++first1;
		//			++first2;
		//		}
		//		else if (*first1 < *first2)
		//		{
		//			++first1;
		//		}
		//		else
		//		{
		//			++first2;
		//		}
		//	}
		//};

		//struct Exclusive
		//{
		//	template<typename Iterator1, typename Iterator2>
		//	static next(
		//		Iterator1 & first1,
		//		Iterator1 & last1,
		//		Iterator2 & first2,
		//		Iterator2 & last2)
		//	{
		//	}
		//};
	}
}