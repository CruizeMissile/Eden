#pragma once
#include <iterator>

namespace edn
{
	namespace Query
	{
		struct base_operator {};

		template<typename Iterator1, typename Iterator2, typename Operation>
		class range_operation_const_iterator : public std::iterator<std::forward_iterator_tag, typename Iterator1::value_type>
		{
		public:
			typedef range_operation_const_iterator<Iterator1, Iterator2, Operation> this_type;
			friend Operation;

			inline range_operation_const_iterator(Iterator1 f1, Iterator1 l1, Iterator2 f2, Iterator2 l2)
				: f1(f1)
				, l1(l1)
				, f2(f2)
				, l2(l2)
			{
				Operation::get_first(*this);
			}

			inline range_operation_const_iterator(const this_type& other)
				: f1(other.f1)
				, l1(other.l1)
				, f2(other.f2)
				, l2(other.l2)
			{
				Operation::get_first(*this);
			}

			inline range_operation_const_iterator& operator++()
			{
				Operation::get_next(*this);
				return *this;
			}

			range_operation_const_iterator operator++(int)
			{
				range_operation_const_iterator temp(*this);
				Operation::get_value(*this);
				return *this;
			}

			inline bool operator==(const range_operation_const_iterator& other)
			{
				return f1 == other.f1 && f2 == other.f2;
			}

			inline bool operator!=(const range_operation_const_iterator& other)
			{
				return Operation::not_equal(*this, other);
			}

			inline typename Iterator1::value_type operator*()
			{
				return Operation::get_value(*this);
			}

		private:
			Iterator1 f1;
			Iterator1 l1;
			Iterator2 f2;
			Iterator2 l2;
		};

		// ----------------------------------------------------------------------------------------

		struct Intersection : base_operator
		{
			template<class Iterator>
			static inline typename Iterator::value_type get_value(Iterator & it)
			{
				return *it.f1;
			}

			template<class Iterator1, class Iterator2>
			static inline bool not_equal(const Iterator1 & one, const Iterator2 & two)
			{
				return one.f1 != two.f1 && one.f2 != two.f2;
			}

			template<class Iterator>
			static void get_first(Iterator & it)
			{
				while ((it.f1 != it.l1 && it.f2 != it.l2) && *it.f1 != *it.f2)
					*it.f1 < *it.f2 ? ++it.f1 : ++it.f2;
				
				if (it.f1 == it.l1)
					it.f2 = it.l2;
				
				if (it.f2 == it.l2)
					it.f1 = it.l1;
			}

			template<class Iterator>
			static void get_next(Iterator & it)
			{
				++it.f1;
				get_first(it);
			}
		};

		struct Difference : base_operator
		{
			template<class Iterator>
			static inline typename Iterator::value_type get_value(Iterator & it)
			{
				return *it.f1;
			}

			template<class Iterator1, class Iterator2>
			static inline bool not_equal(const Iterator1 & one, const Iterator2 & two)
			{
				return one.f1 != two.f1 || one.f2 != two.f2;
			}

			template<class Iterator>
			static void get_first(Iterator & it)
			{
				while ((it.f1 != it.l1 && it.f2 != it.l2) && !(*it.f1 < *it.f2))
				{
					if (*it.f1 == *it.f2)
						++it.f1;
					++it.f2;
				}

				if (it.f1 == it.l1)
					it.f2 = it.l2;
			}

			template<class Iterator>
			static void get_next(Iterator & it)
			{
				if (it.f1 != it.l1)
				{
					++it.f1;
					get_first(it);
				}
				else
					it.f2 = it.l2;
			}
		};

		// ----------------------------------------------------------------------------------------

		struct Union : base_operator
		{
			template<class Iterator>
			static inline typename Iterator::value_type get_value(Iterator & it)
			{
				if (it.f1 != it.l1 && (it.f2 == it.l2 || *it.f1 < *it.f2))
					return *it.f1;
				return *it.f2;
			}

			template<class Iterator1, class Iterator2>
			static inline bool not_equal(const Iterator1 & one, const Iterator2 & two)
			{
				return one.f1 != two.f1 || one.f2 != two.f2;
			}

			template<class Iterator>
			static void get_first(Iterator & it)
			{
			}

			template<class Iterator>
			static void get_next(Iterator & it)
			{
				if (it.f1 != it.l1)
				{
					if (it.f2 == it.l2)
						++it.f1;
					else if (*it.f1 == *it.f2)
					{
						++it.f1;
						++it.f2;
					}
					else if (*it.f1 < *it.f2)
					{
						++it.f1;
						if (it.f1 != it.l1 && *it.f1 == *it.f2)
							++it.f2;
					}
					else
					{
						++it.f2;
						if (it.f2 != it.l2 && *it.f1 == *it.f2)
							++it.f1;
					}
				}
				else
					++it.f2;
			}
		};

		// ----------------------------------------------------------------------------------------

		struct Exclusive : base_operator
		{
			template<class Iterator>
			static inline typename Iterator::value_type get_value(Iterator & it)
			{
				if (it.f1 == it.l1)
					return *it.f2;
				else if (it.f2 == it.l2)
					return *it.f1;
				else if (*it.f1 < *it.f2)
					return *it.f1;
				return *it.f2;
			}

			template<class Iterator1, class Iterator2>
			static inline bool not_equal(const Iterator1 & one, const Iterator2 & two)
			{
				return one.f1 != two.f1 || one.f2 != two.f2;
			}

			template<class Iterator>
			static void get_first(Iterator & it)
			{
				if (it.f1 == it.l1 || it.f2 == it.l2)
					return;

				while (*it.f1 == *it.f2)
				{
					if (*it.f1 == *it.f2)
					{
						++it.f1;
						++it.f2;
					}
					else if (*it.f1 < *it.f2)
						++it.f1;
					else
						++it.f2;
				}
			}

			template<class Iterator>
			static void get_next(Iterator & it)
			{
				if (it.f1 != it.l1 && (it.f2 == it.l2 || *it.f1 < *it.f2))
					++it.f1;
				else
					++it.f2;
				get_first(it);
			}
		};

		// ----------------------------------------------------------------------------------------

		// stores the begin and end functions so that it can loop through a range a way to wrap the
		// range_operation_const_iterator 
		template<typename Iterator1, typename Iterator2, typename Operation>
		class RangeOperation
		{
		public:
			typedef range_operation_const_iterator<Iterator1, Iterator2, Operation> const_iterator;

			inline const_iterator begin() const
			{
				return const_iterator(f1, l1, f2, l2);
			}

			inline const_iterator end() const
			{
				return const_iterator(l1, l1, l2, l2);
			}

			inline RangeOperation(Iterator1 f1, Iterator1 l1, Iterator2 f2, Iterator2 l2)
				: f1(f1)
				, l1(l1)
				, f2(f2)
				, l2(l2)
			{}

			template<class Range1, class Range2>
			inline RangeOperation(const Range1 & range1, const Range2 & range2)
				: f1(range1.begin())
				, l1(range1.end())
				, f2(range2.begin())
				, l2(range2.end())
			{}

		private:
			Iterator1 f1;
			Iterator1 l1;
			Iterator2 f2;
			Iterator2 l2;
		};

		// ----------------------------------------------------------------------------------------

		// Helper functions to add the operator template
		template<class Iterator1, class Iterator2>
		inline RangeOperation<typename Iterator1::const_iterator, typename Iterator2::const_iterator, Intersection>
			make_intersection_range(Iterator1 & one, Iterator2 & two)
		{
			return RangeOperation<typename Iterator1::const_iterator, typename Iterator2::const_iterator, Intersection>(one, two);
		}

		template<class Iterator1, class Iterator2>
		inline RangeOperation<Iterator1, Iterator2, Intersection>
			make_intersection_range(Iterator1 & f1, Iterator1 & l1, Iterator2 & f2, Iterator2 & l2)
		{
			return RangeOperation<Iterator1, Iterator2, Intersection>(f1, l1, f2, l2);
		}

		template<class Iterator1, class Iterator2>
		inline RangeOperation<typename Iterator1::const_iterator, typename Iterator2::const_iterator, Difference>
			make_difference_range(Iterator1 & one, Iterator2 & two)
		{
			return RangeOperation<typename Iterator1::const_iterator, typename Iterator2::const_iterator, Difference>(one, two);
		}

		template<class Iterator1, class Iterator2>
		inline RangeOperation<Iterator1, Iterator2, Difference>
			make_difference_range(Iterator1 & f1, Iterator1 & l1, Iterator2 & f2, Iterator2 & l2)
		{
			return RangeOperation<Iterator1, Iterator2, Difference>(f1, l1, f2, l2);
		}

		template<class Iterator1, class Iterator2>
		inline RangeOperation<typename Iterator1::const_iterator, typename Iterator2::const_iterator, Union>
			make_union_range(Iterator1 & one, Iterator2 & two)
		{
			return RangeOperation<typename Iterator1::const_iterator, typename Iterator2::const_iterator, Union>(one, two);
		}

		template<class Iterator1, class Iterator2>
		inline RangeOperation<Iterator1, Iterator2, Union>
			make_union_range(Iterator1 & f1, Iterator1 & l1, Iterator2 & f2, Iterator2 & l2)
		{
			return RangeOperation<Iterator1, Iterator2, Union>(f1, l1, f2, l2);
		}

		template<class Iterator1, class Iterator2>
		inline RangeOperation<typename Iterator1::const_iterator, typename Iterator2::const_iterator, Exclusive>
			make_exclusive_range(Iterator1 & one, Iterator2 & two)
		{
			return RangeOperation<typename Iterator1::const_iterator, typename Iterator2::const_iterator, Exclusive>(one, two);
		}

		template<class Iterator1, class Iterator2>
		inline RangeOperation<Iterator1, Iterator2, Exclusive>
			make_exclusive_range(Iterator1 & f1, Iterator1 & l1, Iterator2 & f2, Iterator2 & l2)
		{
			return RangeOperation<Iterator1, Iterator2, Exclusive>(f1, l1, f2, l2);
		}
	}
}