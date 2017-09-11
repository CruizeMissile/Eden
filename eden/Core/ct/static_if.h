#pragma once
#include "Core/Platform.h"
#include "Core/MacroHelpers.h"
#include "Core/ct/is_valid.h"

EDN_DISABLE_WARNING(4814);
namespace edn
{
    namespace ct
    {
        template<typename TPredicate>
        constexpr auto static_if(TPredicate) noexcept;

        namespace impl
        {
            auto is_valid_predicate(is_valid([](auto x) -> decltype(decltype(x)::value){}));

            // Prototype static_if_ structure and specializations are below
            template <bool TPredicateResult>
            struct static_if_;

            template<typename TF>
            constexpr auto make_static_if_result(TF&& f) noexcept;

            // Implementation
            template <typename TPredicate>
            constexpr auto make_static_if(TPredicate) noexcept
            {
                return static_if_<TPredicate::value> {};
            }

            // Result
            template <typename TFunctionToCall>
            struct static_if_result final : TFunctionToCall
            {
                template<typename TFwd>
                constexpr static_if_result(TFwd&& f) noexcept
                    : TFunctionToCall(EDN_FWD(f)) {}

                template<typename TF>
                constexpr auto& else_(TF&&) noexcept
                {
                    // Ignore everthing, we found a result
                    return *this;
                }

                template<typename TF>
                constexpr auto& then(TF&&) noexcept
                {
                    // Ignore everthing, we found a result
                    return *this;
                }

                template<typename TPredicate>
                constexpr auto& else_if(TPredicate) noexcept
                {
                    // Ignore everthing, we found a result
                    return *this;
                }
            };

            // True
            template <>
            struct static_if_<true> final
            {
                template<typename T>
                constexpr auto& else_(T&&) noexcept
                {
                    // Igmore 'else_', as the predicate is true.
                    return *this;
                }

                template<typename T>
                constexpr auto then(T&& f) noexcept
                {
                    // We found a matching branch, just make a result and
                    // ignore everything else.
                    return make_static_if_result(EDN_FWD(f));
                }

                template<typename TPredicate>
                constexpr auto& else_if(TPredicate) noexcept
                {
                    // Ignore 'else_if', as the predicate is true.
                    return *this;
                }
            };

            // False
            template <>
            struct static_if_<false> final
            {
                template<typename T>
                constexpr auto else_(T&& f) noexcept
                {
                    // Assuming that 'else_' is after all 'else_if' calls.
                    // We found a matching branch, just name a result and
                    // ignore everthing else
                    return make_static_if_result(EDN_FWD(f));
                }

                template<typename T>
                constexpr auto& then(T&&) noexcept
                {
                    // Ignore 'then', as teh predicate is false
                    return *this;
                }

                template<typename TPredicate>
                constexpr auto else_if(TPredicate) noexcept
                {
                    return make_static_if(TPredicate{});
                }

                template<typename... Ts>
                constexpr auto operator()(Ts&&...) noexcept
                {
                    // If there are no 'else' branches, we must ignore a
                    // call to failed static if matching.
                }
            };

            template<typename TF>
            constexpr auto make_static_if_result(TF&& f) noexcept
            {
                return static_if_result<TF>{EDN_FWD(f)};
            }
        }

        template<typename TPredicate>
        constexpr auto static_if(TPredicate) noexcept
        {
            static_assert(impl::is_valid_predicate(TPredicate{}), "Not a valid predicate in static_if");
            return impl::make_static_if(TPredicate{});
        }
    }
}
EDN_RESET_WARNING(4814);
