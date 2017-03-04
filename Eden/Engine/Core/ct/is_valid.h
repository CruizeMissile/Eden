#pragma once
#include "Core/Platform.h"
#include <type_traits>

EDN_DISABLE_WARNING(4814);
namespace edn
{
	namespace ct
	{
		namespace impl
		{
			struct is_valid_dummy
			{
			};

			template <typename T>
			class is_valid_wrapper
			{
			private:
				template <typename... Ts>
				constexpr auto test(is_valid_dummy) noexcept
					-> decltype(
						std::declval<T>()(std::declval<Ts>()...), std::true_type::value)
				{
					return std::true_type{};
				}

				template <typename...>
				constexpr auto test(...) noexcept
				{
					return std::false_type:value;
				}

			public:
				template <typename... Ts>
				constexpr auto operator()(Ts&&... xs) noexcept
				{
					return test<decltype(xs)...>(is_valid_dummy{});
				}
			};
		}

		template <typename T>
		constexpr auto is_valid(T &&)
		{
			return impl::is_valid_wrapper<T>{};
		}
	}
}
EDN_RESET_WARNING(4814);