/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names can be
 * found in the AUTHORS file distributed with this source
 * distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * The Infinity, Aurora, Odyssey, Eclipse and Lycium engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 */

/** @file engines/kotor/script/function_template.h
 *  Templates to correctly execute NWScript functions
 */

#ifndef ENGINES_KOTOR_SCRIPT_FUNCTION_TEMPLATE_H
#define ENGINES_KOTOR_SCRIPT_FUNCTION_TEMPLATE_H

#include "engines/kotor/script/functions.h"

#define BOOST_RESULT_OF_USE_DECLTYPE

#include "boost/fusion/include/vector.hpp"
#include "boost/fusion/include/invoke.hpp"
#include "boost/fusion/include/transform.hpp"
#include "boost/fusion/include/mpl.hpp"
#include "boost/fusion/include/as_vector.hpp"
namespace fu = boost::fusion;
namespace result_of = fu::result_of;

#include "boost/mpl/int.hpp"
#include "boost/mpl/at.hpp"
#include "boost/mpl/vector.hpp"
#include "boost/mpl/range_c.hpp"
#include "boost/mpl/transform.hpp"
#include "boost/mpl/for_each.hpp"
namespace mpl = boost::mpl;

#include <functional>

using Aurora::kObjectIDInvalid;

// NWScript
using Aurora::NWScript::kTypeVoid;
using Aurora::NWScript::kTypeInt;
using Aurora::NWScript::kTypeFloat;
using Aurora::NWScript::kTypeString;
using Aurora::NWScript::kTypeObject;
using Aurora::NWScript::kTypeEngineType;
using Aurora::NWScript::kTypeVector;
using Aurora::NWScript::kTypeScriptState;
using Aurora::NWScript::createSignature;
using Aurora::NWScript::createDefaults;

namespace Engines {

namespace KotOR {

template <class T>
struct getParameter;

template <>
struct getParameter<int> {
	static int call(const Aurora::NWScript::Variable& v) {
		return v.getInt();
	}
};

template <>
struct getParameter<float> {
	static float call(const Aurora::NWScript::Variable& v) {
		return v.getFloat();
	}
};

template <class Fn>
struct ExtractArgument {
	Aurora::NWScript::FunctionContext *_ctx;
	explicit ExtractArgument(Aurora::NWScript::FunctionContext &ctx) : _ctx(&ctx) {}

	template <int N>
	struct result_type {
		typedef typename mpl::at_c<typename Fn::args, N>::type type;
    };

	template <int N>
	struct default_type {
		typedef typename mpl::at_c<typename Fn::defaults, N>::type type;
    };

	template <class T>
	typename result_type<T::value>::type operator()(T) const {
		static const int N = T::value;
		if (N < _ctx->getParamsSpecified()) {
			return getParameter<typename result_type<N>::type>::call(_ctx->getParams()[N]);
        } else {
			return getDefault<N>();
        }
    }

	template <int N>
	typename std::enable_if<std::is_void<typename default_type<N>::type>::value, typename result_type<N>::type>::type getDefault() const {
		throw std::exception("no default for this parameter");
	}

	template <int N>
	typename std::enable_if<!std::is_void<typename default_type<N>::type>::value, typename result_type<N>::type>::type getDefault() const {
		return default_type<N>::type::value;
	}
};

template <class Fn>
typename result_of::as_vector<typename Fn::args>::type getArguments(Aurora::NWScript::FunctionContext &ctx) {
	static const int args_count = mpl::size<typename Fn::args>::type::value;
	typedef mpl::range_c<int, 0, args_count> indices;
	return fu::as_vector(fu::transform(indices(), ExtractArgument<Fn>(ctx)));
}

template <class Fn>
void run_function(Aurora::NWScript::FunctionContext &ctx) {
	ctx.getReturn() = fu::invoke(Fn(), getArguments<Fn>(ctx));
}

} // End of namespace KotOR

} // End of namespace Engines

#endif // ENGINES_KOTOR_SCRIPT_FUNCTION_TEMPLATE_H
